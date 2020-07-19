void setup() {
  Heltec.begin(true, false, true, true, 470E6);
  Heltec.display -> init();
  Heltec.display -> clear();
  Heltec.display -> setFont(Open_Sans_Light_12);
  Heltec.display -> display();
  LEDS.addLeds<WS2812, 5, GRB>(leds, NUM_LEDS);
  LEDS.setBrightness(84);
  Serial.begin(115200);
  showString(F("o......"), 0);
  IPAddress staticIP(192, 168, 1, 97);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns1(1, 1, 1, 1);
  IPAddress dns2(1, 0, 0, 1);
  WiFi.config(staticIP, gateway, subnet, dns1, dns2);
  delay(20);
  WiFi.disconnect(true);
  delay(500);
  showString(F("Wo....."), 0);
  WiFi.mode(WIFI_STA);
  delay(20);
  showString(F("Wio...."), 0);
  WiFi.setAutoConnect(true);
  delay(20);
  showString(F("WiFo..."), 0);
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  delay(150);
  showString(F("WiFio.."), 0);
  byte count = 0;
  bool connectedOn = false;
  while (WiFi.status() != WL_CONNECTED && count < 200 && !connectedOn) {
    count++;
    delay(50);
    HTTPClient testhttp;
    testhttp.begin("https://example.com/");
    int httpCode = testhttp.GET();
    if (httpCode > 0) {
      connectedOn = true;
    } else {
      connectedOn = false;
    }
  }
  bool mdnsOn;
  if (MDNS.begin(host)) {
    mdnsOn = true;
  } else {
    mdnsOn = false;
  }
  MDNS.addService("http", "tcp", 80);
  if (WiFi.status() == WL_CONNECTED && connectedOn && mdnsOn) {
    showString("WiFi o.", 0);
    delay(10);
    showString("WiFi :o", 0);
    delay(10);
    showString("WiFi :)", 0);
    delay(400);
  } else {
    showString("WiFi :(", 0);
    delay(10000);
    ESP.restart();
  }
  #include "otaroute.h"
  showString("HA...", 0);
  int httpCodeHA = -101;
  int trycount = 0;
  static String locipstr PROGMEM = "https://" + HA_URL + "/api/states/sensor.local_ip";
  while (httpCodeHA != 200) {
    HTTPClient httpHA;
    httpHA.begin(locipstr);
    httpHA.addHeader(String(F("Authorization")), String(F("Bearer ")) + HA_TOKEN);
    httpHA.addHeader(String(F("Content-Type")), String(F("application/json")));
    Serial.println(F("Getting..."));
    httpCodeHA = httpHA.GET();
    trycount++;
    showString("HA... (try #" + String(trycount) + ")", 0);
    delay(200);
    if (httpCodeHA == 200) {
      String resp = httpHA.getString();
      localip = getValue(resp, "\"", F("state"), 2);
    }
  }
  showString(F("HA :)"), 0);
  showString(localip, 1);
  Serial.print("IP address: ");
  IPAddress ip = WiFi.localIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  Serial.println(ipStr);
  Heltec.display -> setFont(Open_Sans_Light_17);
  xTaskCreatePinnedToCore(
    updateStuff,
    "updateStuff",
    10000,
    NULL,
    1,
    &Task,
    (xPortGetCoreID() == 1) ? 0 : 1);
  for (int i = 0; i < NUM_LEDS; i++) {
    ledcolors[i] = ((int) round(i * (255.0 / NUM_LEDS))) % 255;
  }
  delay(3000);
  messages[0] = "";
  messages[1] = "";
  messages[2] = "";
  messages[3] = "";
  messages[4] = "";
  HTTPClient httpupdate;
  httpupdate.begin("https://" + HA_URL + "/api/services/shell_command/update_mirror");
  httpupdate.addHeader("Content-Type", "application/json");
  httpupdate.addHeader("Authorization", "Bearer " + HA_TOKEN);
  httpupdate.POST("");
  httpupdate.end();
  unsigned long tt = millis();
  while (millis() - tt < 300) {
    server.handleClient();
  }
}
