void updateHA(String resp) {
  Serial.println(F("Updating HA..."));
  bool changed = false;
  Serial.println(resp);
  weather = getValue(resp, '|', 0);
  if (getValue(resp, '|', 1) == "on") {
    if (ison != true) {
      changed = true;
    }
    ison = true;
  } else {
    if (ison != false) {
      changed = true;
    }
    ison = false;
  }
  if (brightness != round(getValue(resp, '|', 2).toInt())) {
    bool itsdark = brightness == round(round(getValue(resp, '|', 2).toInt()) / 2.0);
    if (!(is_night && itsdark)) {
      changed = true;
    }
  }
  if (getValue(resp, '|', 6) == "below_horizon") {
    is_night = true;
  } else {
    is_night = false;
  }
  brightness = round(getValue(resp, '|', 2).toInt());
  if (is_night) {
    brightness = round(brightness / 2.0);
  }
  if (hue != round(getValue(resp, '|', 3).toInt())) {
    changed = true;
  }
  hue = round(getValue(resp, '|', 3).toInt());
  if (saturation != round(getValue(resp, '|', 4).toInt())) {
    changed = true;
  }
  saturation = round(getValue(resp, '|', 4).toInt());
  if (modeuse != getValue(resp, '|', 5) && millis() - lastmodified < 600000) {
    changed = true;
  }
  modeuse = getValue(resp, '|', 5);
  if (pattern != getValue(resp, '|', 7)) {
    changed = true;
  }
  pattern = getValue(resp, '|', 7);
  if (weatherpattern != getValue(resp, '|', 8)) {
    changed = true;
  }
  weatherpattern = getValue(resp, '|', 8);
  if (changed) {
    lastmodified = millis();
  }
  Serial.println("Weather: " + weather +
                  " Is on: " + String(ison) +
                  " Brightness: " + String(brightness) +
                  " Hue: " + String(hue) +
                  " Saturation: " + String(saturation) +
                  " Mode: " + modeuse +
                  " Sun up: " + String(is_night) +
                  " Pattern: " + pattern +
                  " Weather pattern: " + weatherpattern +
                  " Last changed (millis): " + String(lastmodified));
}
void updateStuff(void * pvParameters) {
  while (true) {
    Serial.println(F("Updating time..."));
    HTTPClient httptime;
    const static char apiurl[] PROGMEM = "https://worldtimeapi.org/api/ip";
    httptime.begin(apiurl);
    int httpCodeTime = -101;
    int count = 0;
    while (httpCodeTime != 200 && count < 2) {
      httpCodeTime = httptime.GET();
      if (httpCodeTime == 200) {
        String resp = httptime.getString();
        if (resp.length() > 3) {
          String ooffset = getValue(resp, "\"", "utc_offset", 2);
          String punixtime = getValue(resp, "\"", "unixtime", 1);
          int currentunixtime = punixtime.substring(1, punixtime.length() - 1).toInt();
          int hoffset = getValue(ooffset, ':', 0).toInt() * 60 * 60;
          int ntime = currentunixtime + hoffset;
          setTime(ntime);
        }
      } else {
        Serial.print(F("ERROR TIME"));
        delay(random(200, 400));
      }
      count++;
    }
    httptime.end();
    delay(random(850, 1150));
  }
}
