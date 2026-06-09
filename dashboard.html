<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>OrbitAgro IoT Dashboard</title>
<style>
  * { box-sizing: border-box; margin: 0; padding: 0; }
  body { font-family: Arial, sans-serif; background: #0a0e27; color: #fff; padding: 20px; }
  h1 { color: #00d4ff; font-size: 22px; margin-bottom: 4px; }
  .sub { color: #8892b0; font-size: 13px; margin-bottom: 20px; }
  .badge { display: inline-block; padding: 4px 12px; border-radius: 6px; font-size: 12px; font-weight: bold; margin-left: 12px; }
  .badge-ok { background: #0d3321; color: #00d4a0; }
  .badge-alerta { background: #3a2800; color: #ffa500; }
  .badge-critico { background: #3a0000; color: #ff4444; }
  .badge-offline { background: #1a1a2e; color: #8892b0; }
  .ip-row { display: flex; gap: 10px; margin-bottom: 20px; flex-wrap: wrap; }
  .ip-row input { flex: 1; min-width: 200px; padding: 8px 12px; background: #112240; border: 1px solid #233554; border-radius: 6px; color: #fff; font-size: 14px; }
  .ip-row input:focus { outline: none; border-color: #00d4ff; }
  .btn { padding: 8px 16px; border-radius: 6px; border: 1px solid #233554; background: #112240; color: #00d4ff; cursor: pointer; font-size: 14px; }
  .btn:hover { background: #1a2f4e; }
  .btn-sim { color: #8892b0; }
  .cards { display: grid; grid-template-columns: repeat(auto-fit, minmax(140px, 1fr)); gap: 12px; margin-bottom: 20px; }
  .card { background: #112240; border-radius: 8px; padding: 16px; border: 1px solid #233554; }
  .card-label { font-size: 12px; color: #8892b0; margin-bottom: 8px; }
  .card-value { font-size: 26px; font-weight: bold; color: #ccd6f6; }
  .card-unit { font-size: 14px; color: #8892b0; font-weight: normal; }
  .row { display: flex; gap: 16px; flex-wrap: wrap; margin-bottom: 16px; }
  .section { background: #112240; border: 1px solid #233554; border-radius: 10px; padding: 16px; flex: 1; min-width: 220px; }
  .section-title { font-size: 14px; font-weight: bold; color: #ccd6f6; margin-bottom: 14px; }
  .bar-wrap { margin-bottom: 12px; }
  .bar-header { display: flex; justify-content: space-between; font-size: 13px; margin-bottom: 4px; color: #8892b0; }
  .bar-val { color: #ccd6f6; font-weight: bold; }
  .bar-bg { height: 8px; background: #0a0e27; border-radius: 4px; overflow: hidden; }
  .bar-fill { height: 100%; border-radius: 4px; transition: width 0.5s; }
  .fill-ok { background: #00d4a0; }
  .fill-atencao { background: #ffa500; }
  .fill-critico { background: #ff4444; }
  .alerta-box { border-radius: 8px; padding: 12px 14px; font-size: 13px; margin-bottom: 12px; border: 1px solid; }
  .alerta-ok { background: #0d3321; border-color: #00d4a0; color: #00d4a0; }
  .alerta-atencao { background: #3a2800; border-color: #ffa500; color: #ffa500; }
  .alerta-critico { background: #3a0000; border-color: #ff4444; color: #ff4444; }
  .alerta-titulo { font-weight: bold; margin-bottom: 4px; }
  .alerta-msg { font-size: 12px; opacity: 0.85; }
  .btn-irrig { width: 100%; padding: 10px; border-radius: 6px; border: 1px solid #233554; background: #0a0e27; color: #8892b0; cursor: pointer; font-size: 14px; margin-top: 8px; }
  .btn-irrig:hover { background: #112240; }
  .btn-irrig.ativa { background: #0d3321; color: #00d4a0; border-color: #00d4a0; }
  .leds { display: flex; gap: 20px; margin-top: 12px; }
  .led-item { display: flex; align-items: center; gap: 8px; font-size: 13px; color: #8892b0; }
  .led { width: 14px; height: 14px; border-radius: 50%; }
  .led-verde-on { background: #00d4a0; box-shadow: 0 0 8px #00d4a0; }
  .led-verde-off { background: #233554; }
  .led-verm-on { background: #ff4444; box-shadow: 0 0 8px #ff4444; }
  .led-verm-off { background: #233554; }
  .historico { display: flex; align-items: flex-end; gap: 3px; height: 64px; margin-bottom: 6px; }
  .hbar { flex: 1; border-radius: 2px; min-height: 4px; transition: height 0.4s; }
  .endpoints { display: flex; flex-direction: column; gap: 10px; }
  .ep { display: flex; align-items: center; gap: 10px; font-size: 13px; }
  .method { font-size: 11px; font-weight: bold; padding: 2px 8px; border-radius: 4px; min-width: 38px; text-align: center; }
  .get { background: #0d3321; color: #00d4a0; }
  .post { background: #0d1f3a; color: #00d4ff; }
  .path { font-family: monospace; color: #ccd6f6; }
  .ep-desc { color: #8892b0; font-size: 12px; }
  .last { font-size: 12px; color: #8892b0; text-align: right; margin-top: 8px; }
  .full { width: 100%; margin-bottom: 16px; }
</style>
</head>
<body>

<div style="display:flex; align-items:center; margin-bottom:4px;">
  <h1>🌱 OrbitAgro IoT Dashboard</h1>
  <span class="badge badge-offline" id="badge-status">Offline</span>
</div>
<div class="sub">Monitoramento agrícola via satélite e IoT — FIAP Global Solution 2026/1</div>

<div class="ip-row">
  <input type="text" id="ip-input" placeholder="IP do ESP32 (ex: 192.168.1.100)" value="192.168.1.100" />
  <button class="btn" onclick="conectar()">Conectar ao ESP32</button>
  <button class="btn btn-sim" onclick="simularDados(false)">Simular dados</button>
</div>

<div class="cards">
  <div class="card">
    <div class="card-label">💧 Umidade do solo</div>
    <div class="card-value" id="val-umidade">--<span class="card-unit">%</span></div>
  </div>
  <div class="card">
    <div class="card-label">🌡️ Temperatura solo</div>
    <div class="card-value" id="val-temp">--<span class="card-unit">°C</span></div>
  </div>
  <div class="card">
    <div class="card-label">☁️ Temperatura ar</div>
    <div class="card-value" id="val-temp-ar">--<span class="card-unit">°C</span></div>
  </div>
  <div class="card">
    <div class="card-label">🌬️ Umidade do ar</div>
    <div class="card-value" id="val-umidade-ar">--<span class="card-unit">%</span></div>
  </div>
</div>

<div class="row">
  <div class="section">
    <div class="section-title">📊 Níveis atuais</div>
    <div class="bar-wrap">
      <div class="bar-header"><span>Umidade do solo</span><span class="bar-val" id="bar-umid-val">--%</span></div>
      <div class="bar-bg"><div class="bar-fill fill-ok" id="bar-umid" style="width:0%"></div></div>
    </div>
    <div class="bar-wrap">
      <div class="bar-header"><span>Temperatura solo</span><span class="bar-val" id="bar-temp-val">--°C</span></div>
      <div class="bar-bg"><div class="bar-fill fill-ok" id="bar-temp" style="width:0%"></div></div>
    </div>
    <div class="leds">
      <div class="led-item"><span class="led led-verde-off" id="led-verde"></span> LED verde</div>
      <div class="led-item"><span class="led led-verm-off" id="led-vermelho"></span> LED vermelho</div>
    </div>
  </div>

  <div class="section">
    <div class="section-title">🔔 Alertas</div>
    <div class="alerta-box alerta-ok" id="alerta-box">
      <div class="alerta-titulo" id="alerta-titulo">Aguardando leitura</div>
      <div class="alerta-msg" id="alerta-msg">Conecte ao ESP32 ou clique em simular</div>
    </div>
    <button class="btn-irrig" id="btn-irrigacao" onclick="toggleIrrigacao()">💧 Ativar irrigação</button>
    <div class="last" id="ultima-leitura"></div>
  </div>
</div>

<div class="section full">
  <div class="section-title">📈 Histórico de umidade do solo (últimas 20 leituras)</div>
  <div class="historico" id="historico-bars"></div>
  <div style="font-size:11px; color:#8892b0;">Verde = saudável · Amarelo = atenção · Vermelho = crítico</div>
</div>

<div class="section full">
  <div class="section-title">🔌 Endpoints do ESP32</div>
  <div class="endpoints">
    <div class="ep"><span class="method get">GET</span><span class="path">/api/status</span><span class="ep-desc">Status geral + histórico + sensores</span></div>
    <div class="ep"><span class="method get">GET</span><span class="path">/api/sensores</span><span class="ep-desc">Leitura atual dos sensores</span></div>
    <div class="ep"><span class="method get">GET</span><span class="path">/api/alertas</span><span class="ep-desc">Alertas de seca e calor</span></div>
    <div class="ep"><span class="method post">POST</span><span class="path">/api/irrigacao</span><span class="ep-desc">Ativar/desativar irrigação</span></div>
    <div class="ep"><span class="method get">GET</span><span class="path">/api/health</span><span class="ep-desc">Status de saúde do dispositivo</span></div>
  </div>
</div>

<script>
let irrigacaoAtiva = false;
let autoRefresh = null;

function conectar() {
  const ip = document.getElementById('ip-input').value.trim();
  if (!ip) return;
  buscarDados(ip);
  if (autoRefresh) clearInterval(autoRefresh);
  autoRefresh = setInterval(() => buscarDados(ip), 3000);
}

async function buscarDados(ip) {
  const base = ip.startsWith('http') ? ip : 'http://' + ip;
  try {
    const r = await fetch(base + '/api/status');
    const d = await r.json();
    atualizarUI({
      umidadeSolo: d.sensores.umidadeSolo,
      temperaturaSolo: d.sensores.temperaturaSolo,
      temperaturaAr: d.sensores.temperaturaAr,
      umidadeAr: d.sensores.umidadeAr,
      statusGeral: d.statusGeral,
      tipoAlerta: d.tipoAlerta,
      irrigacaoAtiva: d.irrigacaoAtiva,
      historico: d.historicoUmidade || [],
      leituras: d.leituras
    });
  } catch(e) {
    document.getElementById('badge-status').textContent = 'Offline';
    document.getElementById('badge-status').className = 'badge badge-offline';
  }
}

function atualizarUI(d) {
  document.getElementById('val-umidade').innerHTML = Math.round(d.umidadeSolo) + '<span class="card-unit">%</span>';
  document.getElementById('val-temp').innerHTML = d.temperaturaSolo.toFixed(1) + '<span class="card-unit">°C</span>';
  document.getElementById('val-temp-ar').innerHTML = d.temperaturaAr.toFixed(1) + '<span class="card-unit">°C</span>';
  document.getElementById('val-umidade-ar').innerHTML = Math.round(d.umidadeAr) + '<span class="card-unit">%</span>';

  const umid = Math.round(d.umidadeSolo);
  const temp = d.temperaturaSolo;
  document.getElementById('bar-umid').style.width = Math.min(umid, 100) + '%';
  document.getElementById('bar-umid-val').textContent = umid + '%';
  document.getElementById('bar-umid').className = 'bar-fill ' + (umid < 30 ? 'fill-critico' : umid < 50 ? 'fill-atencao' : 'fill-ok');
  document.getElementById('bar-temp').style.width = Math.min((temp / 50) * 100, 100) + '%';
  document.getElementById('bar-temp-val').textContent = temp.toFixed(1) + '°C';
  document.getElementById('bar-temp').className = 'bar-fill ' + (temp > 38 ? 'fill-critico' : temp > 32 ? 'fill-atencao' : 'fill-ok');

  const badge = document.getElementById('badge-status');
  const s = d.statusGeral;
  if (s === 'SAUDAVEL') { badge.textContent = 'Saudável'; badge.className = 'badge badge-ok'; }
  else if (s === 'ATENCAO') { badge.textContent = 'Atenção'; badge.className = 'badge badge-alerta'; }
  else { badge.textContent = 'Crítico'; badge.className = 'badge badge-critico'; }

  const box = document.getElementById('alerta-box');
  const t = d.tipoAlerta;
  if (t === 'NENHUM') { box.className = 'alerta-box alerta-ok'; document.getElementById('alerta-titulo').textContent = 'Solo saudável'; document.getElementById('alerta-msg').textContent = 'Condições dentro do normal.'; }
  else if (t === 'ATENCAO') { box.className = 'alerta-box alerta-atencao'; document.getElementById('alerta-titulo').textContent = 'Atenção necessária'; document.getElementById('alerta-msg').textContent = 'Umidade abaixo do ideal.'; }
  else if (t === 'IRRIGACAO') { box.className = 'alerta-box alerta-ok'; document.getElementById('alerta-titulo').textContent = 'Irrigação ativa'; document.getElementById('alerta-msg').textContent = 'Sistema irrigando o solo.'; }
  else { box.className = 'alerta-box alerta-critico'; document.getElementById('alerta-titulo').textContent = 'ALERTA: ' + t.replace('_', ' + '); document.getElementById('alerta-msg').textContent = 'Satélite + IoT confirmam: umidade crítica no solo!'; }

  irrigacaoAtiva = d.irrigacaoAtiva;
  const btn = document.getElementById('btn-irrigacao');
  btn.textContent = irrigacaoAtiva ? '🛑 Desativar irrigação' : '💧 Ativar irrigação';
  btn.className = irrigacaoAtiva ? 'btn-irrig ativa' : 'btn-irrig';

  document.getElementById('led-verde').className = 'led ' + ((s === 'SAUDAVEL' || irrigacaoAtiva) ? 'led-verde-on' : 'led-verde-off');
  document.getElementById('led-vermelho').className = 'led ' + ((s !== 'SAUDAVEL' || irrigacaoAtiva) ? 'led-verm-on' : 'led-verm-off');

  if (d.historico && d.historico.length > 0) renderHistorico(d.historico);
  document.getElementById('ultima-leitura').textContent = 'Leituras: ' + d.leituras + ' — ' + new Date().toLocaleTimeString('pt-BR');
}

function renderHistorico(hist) {
  const c = document.getElementById('historico-bars');
  c.innerHTML = '';
  hist.forEach(v => {
    const b = document.createElement('div');
    b.className = 'hbar';
    b.style.height = Math.max((v / 100) * 100, 4) + '%';
    b.style.background = v < 30 ? '#ff4444' : v < 50 ? '#ffa500' : '#00d4a0';
    b.title = Math.round(v) + '%';
    c.appendChild(b);
  });
}

function toggleIrrigacao() {
  irrigacaoAtiva = !irrigacaoAtiva;
  simularDados(irrigacaoAtiva);
}

function simularDados(irrigando) {
  const umid = irrigando ? 75 : Math.round(15 + Math.random() * 70);
  const temp = parseFloat((20 + Math.random() * 20).toFixed(1));
  const hist = Array.from({length: 19}, () => Math.round(15 + Math.random() * 70));
  hist.push(umid);
  let tipo = 'NENHUM', status = 'SAUDAVEL';
  if (irrigando) { tipo = 'IRRIGACAO'; }
  else if (umid < 30 && temp > 38) { tipo = 'SECA_E_CALOR'; status = 'CRITICO'; }
  else if (umid < 30) { tipo = 'SECA'; status = 'ALERTA'; }
  else if (umid < 50) { tipo = 'ATENCAO'; status = 'ATENCAO'; }
  atualizarUI({ umidadeSolo: umid, temperaturaSolo: temp, temperaturaAr: parseFloat((temp+2).toFixed(1)), umidadeAr: Math.round(40+Math.random()*40), statusGeral: status, tipoAlerta: tipo, irrigacaoAtiva: !!irrigando, historico: hist, leituras: Math.round(Math.random()*500+10) });
}

simularDados(false);
</script>
</body>
</html>
