String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String getValue(String data, String separator, String target, int countoff) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex; i++) {
    if (data.charAt(i) == separator.charAt(0) || i == maxIndex) {
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
      String sstring = data.substring(strIndex[0], strIndex[1]);
      if (found == countoff) {
        return sstring;
      }
      if (sstring == target || found > 0) {
        found++;
      }
    }
  }
  return "Nothing";
}

void showString(String stringdata, int line) {
  Heltec.display -> clear();
  messages[line] = stringdata;
  Heltec.display -> drawStringMaxWidth(0, 0 * 12, 130, messages[0]);
  Heltec.display -> drawStringMaxWidth(0, 1 * 12, 130, messages[1]);
  Heltec.display -> drawStringMaxWidth(0, 2 * 12, 130, messages[2]);
  Heltec.display -> drawStringMaxWidth(0, 3 * 12, 130, messages[3]);
  Heltec.display -> drawStringMaxWidth(0, 4 * 12, 130, messages[4]);
  Heltec.display -> display();
}

void showString(String stringdata, int line, int fontsize) {
  Heltec.display -> clear();
  messages[line] = stringdata;
  Heltec.display -> drawStringMaxWidth(0, 0 * fontsize, 130, messages[0]);
  Heltec.display -> drawStringMaxWidth(0, 1 * fontsize, 130, messages[1]);
  Heltec.display -> drawStringMaxWidth(0, 2 * fontsize, 130, messages[2]);
  Heltec.display -> drawStringMaxWidth(0, 3 * fontsize, 130, messages[3]);
  Heltec.display -> drawStringMaxWidth(0, 4 * fontsize, 130, messages[4]);
  Heltec.display -> display();
}

void showclock(time_t t) {
  int hr = hour(t) % 12;
  CHSV hourhand = CHSV(35, 210, 255);
  if (hr <= 5) {
    int offseted = hr * 8;
    for (int i = 47 - offseted; i <= 48 - offseted; i++) {
      leds[i] = hourhand;
    }
  } else {
    int offseted = (hr - 6) * 8;
    for (int i = NUM_LEDS - 2 - offseted; i <= NUM_LEDS - 1 - offseted; i++) {
      leds[i] = hourhand;
    }
  }
  int currentminute = minute(t);
  CHSV minutehand = CHSV(118, 210, 255);
  if (currentminute <= 30) {
    int offseted = currentminute * 8 / 5;
    for (int i = 47 - offseted; i <= 48 - offseted; i++) {
      leds[i] = minutehand;
    }
  } else {
    int offseted = (currentminute - 30) * 8 / 5;
    for (int i = NUM_LEDS - 2 - offseted; i <= NUM_LEDS - 1 - offseted; i++) {
      leds[i] = minutehand;
    }
  }
}
