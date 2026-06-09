/*
 * OrbitAgro IoT Station - ESP32 (Wokwi)
 * FIAP Global Solution 2026/1 - Disruptive Architectures (IoT)
 */

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define PIN_UMIDADE_SOLO   34
#define PIN_BOTAO          18
#define PIN_LED_VERDE      26
#define PIN_LED_VERMELHO   27
#define PIN_DHT            15
#define PIN_OLED_SDA       21
#define PIN_OLED_SCL       22

#define DHT_TYPE           DHT22
#define SCREEN_WIDTH       128
#define SCREEN_HEIGHT      64
#define OLED_RESET         -1

const char* WIFI_SSID     = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

const float UMIDADE_SECA       = 30.0;
const float UMIDADE_ATENCAO    = 50.0;
const float TEMP_ALTA          = 38.0;

WebServer server(80);
DHT dht(PIN_DHT, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

struct EstadoOrbitAgro {
  float umidadeSolo;
  float temperaturaSolo;
  float temperaturaAr;
  float umidadeAr;
  bool  alertaSeca;
  bool  alertaCalor;
  bool  irrigacaoAtiva;
  String tipoAlerta;
  String statusGeral;
  unsigned long leituras;
  unsigned long ultimaLeitura;
};

EstadoOrbitAgro estado = {
  0, 0, 0, 0,
  false, false, false,
  "NENHUM", "INICIALIZANDO",
  0, 0
};

float historicoUmidade[20];
float historicoTemp[20];
int historicoIndex = 0;

bool botaoAnterior = HIGH;
unsigned long ultimoDebounce = 0;
const unsigned long DEBOUNCE_MS = 200;

void conectarWiFi();
void lerSensores();
void avaliarAlertas();
void atualizarLEDs();
void atualizarOLED();
void registrarHistorico();
void tratarBotao();
String statusParaCor();

void handleRoot();
void handleStatus();
void handleSensores();
void handleAlertas();
void handleIrrigacao();
void handleHealth();
void handleNotFound();

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== OrbitAgro IoT Station ===");

  pinMode(PIN_UMIDADE_SOLO, INPUT);
  pinMode(PIN_BOTAO, INPUT_PULLUP);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_VERMELHO, OUTPUT);

  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_VERMELHO, LOW);

  Wire.begin(PIN_OLED_SDA, PIN_OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("[ERRO] OLED nao encontrado!");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("OrbitAgro IoT");
    display.println("Iniciando...");
    display.display();
  }

  dht.begin();
  conectarWiFi();

  server.on("/", handleRoot);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/sensores", HTTP_GET, handleSensores);
  server.on("/api/alertas", HTTP_GET, handleAlertas);
  server.on("/api/irrigacao", HTTP_POST, handleIrrigacao);
  server.on("/api/health", HTTP_GET, handleHealth);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("[OK] WebServer na porta 80");
}

void loop() {
  server.handleClient();
  tratarBotao();
  lerSensores();
  avaliarAlertas();
  atualizarLEDs();
  atualizarOLED();
  delay(2000);
}

void conectarWiFi() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Conectando WiFi...");
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 30) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[OK] Wi-Fi conectado!");
    Serial.println(WiFi.localIP());

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi OK!");
    display.print("IP: ");
    display.println(WiFi.localIP());
    display.display();
    delay(1500);
  } else {
    WiFi.softAP("OrbitAgro-IoT", "orbitagro123");
    Serial.println(WiFi.softAPIP());
  }
}

void lerSensores() {
  int rawUmidade = analogRead(PIN_UMIDADE_SOLO);
  estado.umidadeSolo = map(rawUmidade, 4095, 0, 0, 100);
  estado.umidadeSolo = constrain(estado.umidadeSolo, 0, 100);

  float tempAr = dht.readTemperature();
  float umidAr = dht.readHumidity();

  if (!isnan(tempAr)) {
    estado.temperaturaAr = tempAr;
    estado.temperaturaSolo = tempAr - 2.0;
  }
  if (!isnan(umidAr)) {
    estado.umidadeAr = umidAr;
  }

  estado.leituras++;
  estado.ultimaLeitura = millis();
  registrarHistorico();

  Serial.printf("[SENSORES] Umid.Solo: %.1f%% | Temp.Solo: %.1f C\n",
                estado.umidadeSolo, estado.temperaturaSolo);
}

void registrarHistorico() {
  historicoUmidade[historicoIndex] = estado.umidadeSolo;
  historicoTemp[historicoIndex] = estado.temperaturaSolo;
  historicoIndex = (historicoIndex + 1) % 20;
}

void avaliarAlertas() {
  estado.alertaSeca = (estado.umidadeSolo < UMIDADE_SECA);
  estado.alertaCalor = (estado.temperaturaSolo > TEMP_ALTA);

  if (estado.irrigacaoAtiva) {
    estado.tipoAlerta = "IRRIGACAO";
    estado.statusGeral = "IRRIGANDO";
  } else if (estado.alertaSeca && estado.alertaCalor) {
    estado.tipoAlerta = "SECA_E_CALOR";
    estado.statusGeral = "CRITICO";
  } else if (estado.alertaSeca) {
    estado.tipoAlerta = "SECA";
    estado.statusGeral = "ALERTA";
  } else if (estado.umidadeSolo < UMIDADE_ATENCAO) {
    estado.tipoAlerta = "ATENCAO";
    estado.statusGeral = "ATENCAO";
  } else {
    estado.tipoAlerta = "NENHUM";
    estado.statusGeral = "SAUDAVEL";
  }
}

void atualizarLEDs() {
  if (estado.irrigacaoAtiva) {
    digitalWrite(PIN_LED_VERDE, HIGH);
    digitalWrite(PIN_LED_VERMELHO, HIGH);
    return;
  }

  if (estado.alertaSeca || estado.statusGeral == "CRITICO" || estado.statusGeral == "ALERTA") {
    digitalWrite(PIN_LED_VERDE, LOW);
    digitalWrite(PIN_LED_VERMELHO, HIGH);
  } else if (estado.statusGeral == "ATENCAO") {
    digitalWrite(PIN_LED_VERDE, (millis() / 500) % 2);
    digitalWrite(PIN_LED_VERMELHO, LOW);
  } else {
    digitalWrite(PIN_LED_VERDE, HIGH);
    digitalWrite(PIN_LED_VERMELHO, LOW);
  }
}

void atualizarOLED() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("OrbitAgro IoT");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setCursor(0, 14);
  display.printf("Umid.Solo: %.0f%%", estado.umidadeSolo);
  display.setCursor(0, 26);
  display.printf("Temp.Solo: %.1f C", estado.temperaturaSolo);
  display.setCursor(0, 38);
  display.printf("Alerta: %s", estado.tipoAlerta.c_str());

  display.setCursor(0, 52);
  display.printf("Status: %s", statusParaCor().c_str());

  display.display();
}

String statusParaCor() {
  if (estado.statusGeral == "SAUDAVEL") return "VERDE";
  if (estado.statusGeral == "ATENCAO") return "AMARELO";
  return "VERMELHO";
}

void tratarBotao() {
  int leitura = digitalRead(PIN_BOTAO);

  if (leitura != botaoAnterior) {
    ultimoDebounce = millis();
  }

  if ((millis() - ultimoDebounce) > DEBOUNCE_MS) {
    if (leitura == LOW && botaoAnterior == HIGH) {
      estado.irrigacaoAtiva = !estado.irrigacaoAtiva;
      if (estado.irrigacaoAtiva) {
        estado.umidadeSolo = min(estado.umidadeSolo + 15.0f, 100.0f);
      }
    }
  }
  botaoAnterior = leitura;
}

void handleRoot() {
  String html = R"(
<!DOCTYPE html>
<html><head>
<meta charset="UTF-8">
<title>OrbitAgro IoT</title>
<style>
  body{font-family:Arial;background:#0a0e27;color:#fff;padding:20px}
  h1{color:#00d4ff} a{color:#00d4ff}
</style></head><body>
<h1>OrbitAgro IoT Station</h1>
<ul>
  <li><a href="/api/status">GET /api/status</a></li>
  <li><a href="/api/sensores">GET /api/sensores</a></li>
  <li><a href="/api/alertas">GET /api/alertas</a></li>
  <li><a href="/api/health">GET /api/health</a></li>
</ul>
</body></html>)";
  server.send(200, "text/html", html);
}

void handleStatus() {
  StaticJsonDocument<768> doc;
  doc["projeto"] = "OrbitAgro";
  doc["estacao"] = "IoT-Solo-01";
  doc["statusGeral"] = estado.statusGeral;
  doc["corMapa"] = statusParaCor();
  doc["tipoAlerta"] = estado.tipoAlerta;
  doc["irrigacaoAtiva"] = estado.irrigacaoAtiva;
  doc["leituras"] = estado.leituras;
  doc["uptimeMs"] = millis();
  doc["wifiRssi"] = WiFi.RSSI();

  JsonObject sensores = doc.createNestedObject("sensores");
  sensores["umidadeSolo"] = round(estado.umidadeSolo * 10) / 10.0;
  sensores["temperaturaSolo"] = round(estado.temperaturaSolo * 10) / 10.0;
  sensores["temperaturaAr"] = round(estado.temperaturaAr * 10) / 10.0;
  sensores["umidadeAr"] = round(estado.umidadeAr * 10) / 10.0;

  JsonArray hist = doc.createNestedArray("historicoUmidade");
  for (int i = 0; i < 20; i++) {
    int idx = (historicoIndex + i) % 20;
    if (historicoUmidade[idx] > 0) hist.add(historicoUmidade[idx]);
  }

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void handleSensores() {
  StaticJsonDocument<384> doc;
  doc["umidadeSolo"] = round(estado.umidadeSolo * 10) / 10.0;
  doc["temperaturaSolo"] = round(estado.temperaturaSolo * 10) / 10.0;
  doc["temperaturaAr"] = round(estado.temperaturaAr * 10) / 10.0;
  doc["umidadeAr"] = round(estado.umidadeAr * 10) / 10.0;
  doc["timestamp"] = millis();

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void handleAlertas() {
  StaticJsonDocument<512> doc;
  doc["alertaSeca"] = estado.alertaSeca;
  doc["alertaCalor"] = estado.alertaCalor;
  doc["tipoAlerta"] = estado.tipoAlerta;
  doc["statusGeral"] = estado.statusGeral;
  doc["corMapa"] = statusParaCor();
  doc["mensagem"] = estado.alertaSeca
    ? "Satelite + IoT confirmam: umidade critica no solo!"
    : "Condicoes dentro do normal.";

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void handleIrrigacao() {
  if (server.hasArg("plain")) {
    StaticJsonDocument<128> doc;
    if (!deserializeJson(doc, server.arg("plain")) && doc.containsKey("ativar")) {
      estado.irrigacaoAtiva = doc["ativar"];
    }
  } else {
    estado.irrigacaoAtiva = !estado.irrigacaoAtiva;
  }

  StaticJsonDocument<256> resp;
  resp["irrigacaoAtiva"] = estado.irrigacaoAtiva;
  resp["mensagem"] = estado.irrigacaoAtiva ? "Irrigacao ativada" : "Irrigacao desativada";

  String json;
  serializeJson(resp, json);
  server.send(200, "application/json", json);
}

void handleHealth() {
  StaticJsonDocument<256> doc;
  doc["status"] = "online";
  doc["projeto"] = "OrbitAgro";
  doc["versao"] = "1.0.0";
  doc["wifi"] = WiFi.status() == WL_CONNECTED ? "conectado" : "desconectado";
  doc["ip"] = WiFi.localIP().toString();
  doc["leituras"] = estado.leituras;

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void handleNotFound() {
  StaticJsonDocument<128> doc;
  doc["erro"] = "Endpoint nao encontrado";

  String json;
  serializeJson(doc, json);
  server.send(404, "application/json", json);
}