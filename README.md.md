# 🌱 OrbitAgro IoT Station

> Monitoramento Agrícola via Satélite e IoT — FIAP Global Solution 2026/1

Sistema IoT embarcado em ESP32 que monitora umidade e temperatura do solo em tempo real, gerando alertas automáticos e permitindo controle de irrigação remoto.

---

## 👥 Integrantes

| Nome | RM | Turma |
|------|----|-------|
| Rodrigo Silva | RM565162 | 2TDSR |
| Nickolas Davi | RM564105 | 2TDSR |
| Samara Vilela | RM566133 | 2TDSR |
| Natália Cristina | RM564099 | 2TDSR |
| Otávio Ferreira | RM565960 | 2TDSR |

---

## 🔗 Links

| Item | Link |
|------|------|
| 🔧 Simulação Wokwi | https://wokwi.com/projects/466213382121544705 |
| 📊 Dashboard | [dashboard.html](./dashboard.html) |
| 📹 Vídeo demonstração | *em breve* |

---

## 💡 Sobre o Projeto

Produtores rurais perdem safras porque percebem problemas visualmente, quando já é tarde. O **OrbitAgro IoT Station** é uma estação de monitoramento embarcada que:

- Lê umidade do solo e temperatura em tempo real
- Acende LED vermelho quando há risco de seca
- Gera alertas automáticos por nível de criticidade
- Permite ativar irrigação pelo botão físico ou via API
- Expõe endpoints JSON para integração com o dashboard e a API principal

---

## 🔌 Hardware

| Componente | Pino ESP32 | Função |
|-----------|-----------|--------|
| Potenciômetro | GPIO 34 | Simula umidade do solo (entrada) |
| DHT22 | GPIO 15 | Temperatura e umidade do ar (entrada) |
| Botão azul | GPIO 18 | Ativar/desativar irrigação (entrada) |
| LED verde | GPIO 26 | Solo saudável (saída) |
| LED vermelho | GPIO 27 | Alerta de seca (saída) |
| Display OLED | GPIO 21/22 | Interface local SSD1306 (saída) |

---

## 📡 Endpoints da API REST

| Método | Endpoint | Descrição |
|--------|----------|-----------|
| GET | `/api/status` | Status geral + sensores + histórico |
| GET | `/api/sensores` | Leitura atual dos sensores |
| GET | `/api/alertas` | Alertas de seca e calor |
| POST | `/api/irrigacao` | Ativar/desativar irrigação |
| GET | `/api/health` | Saúde do dispositivo |

### Exemplo de resposta — `/api/status`
```json
{
  "projeto": "OrbitAgro",
  "estacao": "IoT-Solo-01",
  "statusGeral": "ALERTA",
  "tipoAlerta": "SECA",
  "irrigacaoAtiva": false,
  "sensores": {
    "umidadeSolo": 25.0,
    "temperaturaSolo": 36.5,
    "temperaturaAr": 38.5,
    "umidadeAr": 42.0
  },
  "historicoUmidade": [45, 40, 32, 28, 25]
}
```

### Exemplo de resposta — `/api/alertas`
```json
{
  "alertaSeca": true,
  "alertaCalor": false,
  "tipoAlerta": "SECA",
  "statusGeral": "ALERTA",
  "corMapa": "VERMELHO",
  "mensagem": "Satelite + IoT confirmam: umidade critica no solo!"
}
```

### Exemplo de resposta — `/api/sensores`
```json
{
  "umidadeSolo": 25.0,
  "temperaturaSolo": 36.5,
  "temperaturaAr": 38.5,
  "umidadeAr": 42.0,
  "timestamp": 12500
}
```

---

## 🚦 Lógica de Alertas

| Umidade Solo | Temperatura | Status | LED |
|-------------|-------------|--------|-----|
| > 50% | qualquer | SAUDÁVEL | Verde |
| 30–50% | qualquer | ATENÇÃO | Verde piscando |
| < 30% | qualquer | ALERTA | Vermelho |
| < 30% | > 38°C | CRÍTICO | Vermelho |
| irrigação ativa | — | IRRIGANDO | Verde + Vermelho |

---

## 🛠️ Tecnologias

- ESP32 DevKit C v4
- Wokwi (simulação)
- C++ / Arduino Framework
- WiFi + WebServer
- ArduinoJson
- DHT22 sensor library
- Adafruit SSD1306 + GFX

---

## ▶️ Como Simular

```
1. Acessa: https://wokwi.com/projects/466213382121544705
2. Clica em Play
3. Gira o potenciômetro para simular umidade do solo
4. Veja os LEDs e o OLED reagindo
5. Pega o IP exibido no OLED
6. Abre o dashboard.html no navegador
7. Cola o IP e clica em Conectar
```

---

## 📋 Checklist de Entrega

- [x] ESP32 com 2 entradas (potenciômetro + DHT22)
- [x] ESP32 com 2 saídas (LED verde + LED vermelho)
- [x] Interface local (OLED SSD1306)
- [x] Comunicação Wi-Fi
- [x] WebServer com API REST
- [x] Mínimo 3 endpoints JSON documentados (5 no total)
- [x] Dashboard para visualização dos dados
- [x] Simulação no Wokwi
- [ ] Vídeo de até 3 minutos
