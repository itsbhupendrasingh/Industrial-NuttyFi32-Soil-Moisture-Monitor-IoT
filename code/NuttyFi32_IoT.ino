#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

#define SOIL_PIN 34

// 🔥 AP Credentials (change if needed)
const char* ssid = "SME_Plant_Monitoring";
const char* password = "12345678";

WebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;

int wetValue = 3000;
int dryValue = 500;

// ---------- Stable Read ----------
int readSoil() {
  long sum = 0;
  for (int i = 0; i < 15; i++) {
    sum += analogRead(SOIL_PIN);
    delay(5);
  }
  return sum / 15;
}

// ---------- HTML PAGE ----------
String getHTML() {

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Smart Plant Monitor</title>

<style>
body {
  margin: 0;
  font-family: 'Segoe UI', sans-serif;
  background: linear-gradient(135deg, #74ebd5, #ACB6E5);
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
}

/* Card */
.card {
  width: 280px;
  padding: 20px;
  border-radius: 20px;
  background: rgba(255,255,255,0.25);
  backdrop-filter: blur(12px);
  text-align: center;
  color: #333;
}

/* Plant */
.plant {
  font-size: 60px;
  margin-bottom: 10px;
}

/* Value */
.value {
  font-size: 28px;
  font-weight: bold;
}

/* Bar */
.bar-container {
  height: 200px;
  width: 50px;
  background: rgba(255,255,255,0.3);
  border-radius: 25px;
  margin: 20px auto;
  overflow: hidden;
  display: flex;
  align-items: flex-end;
}

.fill {
  width: 100%;
  height: 0%;
  background: linear-gradient(to top, #4CAF50, #8BC34A);
  transition: height 0.7s ease;
  border-radius: 25px;
}

.label {
  font-size: 14px;
  opacity: 0.7;
}
</style>
</head>

<body>

<div class="card">

  <div id="plant" class="plant">🌱</div>

  <div id="value" class="value">--%</div>
  <div class="label">Soil Moisture</div>

  <div class="bar-container">
    <div id="fill" class="fill"></div>
  </div>

  <div style="margin-top:15px; font-size:12px; opacity:0.75; line-height:1.5;">
    <b>Developed by SME Dehradun</b><br>
    Custom IoT Solutions | Product Development<br><br>

    🌐 Services: www.smedehradun.com<br>
    🛒 Products: www.nuttyengineer.com
  </div>

</div>

<script>
async function updateData() {
  try {
    let res = await fetch('/data');
    let data = await res.json();

    let moisture = data.moisture;

    document.getElementById("value").innerText = moisture + "%";
    document.getElementById("fill").style.height = moisture + "%";

    let plant = "🌵";
    if (moisture > 70) plant = "🌿";
    else if (moisture > 40) plant = "🌱";

    document.getElementById("plant").innerText = plant;

    let color = "#4CAF50";
    if (moisture < 30) color = "#f44336";
    else if (moisture < 70) color = "#ff9800";

    document.getElementById("fill").style.background = color;

  } catch (e) {
    console.log("Error:", e);
  }
}

setInterval(updateData, 1000);
updateData();
</script>

</body>
</html>
)rawliteral";

  return html;
}

// ---------- ROUTES ----------

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", getHTML());
}

void handleData() {
  int raw = readSoil();

  int moisture = map(raw, dryValue, wetValue, 0, 100);
  moisture = constrain(moisture, 0, 100);

  String json = "{\"moisture\":" + String(moisture) + "}";
  server.send(200, "application/json", json);
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  // 🔥 Start Access Point
  WiFi.softAP(ssid, password);

  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());

  // 🔥 Start DNS (Captive Portal)
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // Routes
  server.on("/", handleRoot);
  server.on("/data", handleData);

  // 🔥 Redirect ALL unknown requests
  server.onNotFound([]() {
    server.send(200, "text/html", getHTML());
  });

  server.begin();
}

// ---------- LOOP ----------
void loop() {
  dnsServer.processNextRequest();  // 🔥 Required
  server.handleClient();
}
