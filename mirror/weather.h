String tellweather(bool prettyname) {
  String weatheroption = "unknown";
  if (weather == F("clear-day")) {
    weatheroption = F("sunny");
  } else if (weather == F("clear-night")) {
    weatheroption = F("clear_night");
  } else if (weather == F("cloudy")) {
    weatheroption = weather;
  } else if (weather == F("overcast")) {
    weatheroption = F("cloudy");
  } else if (weather == F("fog")) {
    weatheroption = weather;
  } else if (weather == F("hail")) {
    weatheroption = F("mixed_rain");
  } else if (weather == F("lightning")) {
    weatheroption = weather;
  } else if (weather == F("lightning-rainy")) {
    weatheroption = F("storm");
  } else if (weather == F("partly-cloudy-day")) {
    weatheroption = F("mostly_cloudy");
  } else if (weather == F("partly-cloudy-night")) {
    weatheroption = F("mostly_cloudy_night");
  } else if (weather == F("partlycloudy")) {
    weatheroption = F("mostly_cloudy");
  } else if (weather == F("pouring")) {
    weatheroption = F("heavy_rain");
  } else if (weather == F("rain")) {
    weatheroption = F("rainy");
  } else if (weather == F("rainy")) {
    weatheroption = weather;
  } else if (weather == F("sleet")) {
    weatheroption = F("mixed_rain");
  } else if (weather == F("snow")) {
    weatheroption = F("snowy");
  } else if (weather == F("snowy")) {
    weatheroption = weather;
  } else if (weather == F("snowy-rainy")) {
    weatheroption = F("mixed_rain");
  } else if (weather == F("sunny")) {
    weatheroption = weather;
  } else if (weather == F("wind")) {
    weatheroption = F("windy");
  } else if (weather == F("windy")) {
    weatheroption = weather;
  } else if (weather == F("windy-variant")) {
    weatheroption = F("windy");
  }
  if (is_night) {
    if (weather == F("sunny")) {
      weatheroption = F("clear_night");
    } else if (weather == F("partlycloudy")) {
      weatheroption = F("mostly_cloudy_night");
    } else if (weather == F("lightning-rainy")) {
      weatheroption = F("storm_night");
    } else if (weather == F("mostly_cloudy")) {
      weatheroption = F("mostly_cloudy_night");
    }
  }
  if (prettyname) {
    if (weatheroption == F("clear_night")) {
      weatheroption = F("clear (night)");
    } else if (weatheroption == F("storm_night")) {
      weatheroption = F("storm (night)");
    } else if (weatheroption == F("mostly_cloudy")) {
      weatheroption = F("mostly cloudy");
    } else if (weatheroption == F("mostly_cloudy_night")) {
      weatheroption = F("mostly cloudy (night)");
    } else if (weatheroption == F("heavy_rain")) {
      weatheroption = F("heavy rain");
    } else if (weatheroption == F("mixed_rain")) {
      weatheroption = F("mixed rain");
    }
  }
  return weatheroption;
}

void show_mostly_cloudy() {
  for (int i = 20; i < NUM_LEDS - 20; i++) {
    if ((i + int(fln / 5)) % 20 < 4) {
      leds[i] = CHSV(0, 0, int(brightness * 1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.7));
    }
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 200, int(brightness * 0.63));
  }
  for (int i = NUM_LEDS - 20; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, int(brightness * 0.63));
  }
}
void show_mostly_cloudy_night() {
  for (int i = 30; i < round(NUM_LEDS * 0.78); i++) {
    if (i > round(NUM_LEDS * 0.55)) {
      if ((int(fln / 4) + i) % 4 < 2) {
        leds[i] = CHSV(195, 200, int(brightness * 1.1));
      } else {
        leds[i] = CHSV(195, 200, int(brightness * 0.7));
      }
    } else {
      if ((i + int(fln / 5)) % 20 < 10) {
        //leds[i] = CHSV(0, 0, int(brightness * 1.1));
        leds[i] = CHSV(0, 0, 0);
      } else {
        leds[i] = CHSV(0, 0, int(brightness * 0.5));
      }
    }
  }
  for (int i = 0; i < 30; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  for (int i = round(NUM_LEDS * 0.78); i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
}
void show_cloudy() {
  for (int i = 20; i < NUM_LEDS - 20; i++) {
    if ((i + int(fln / 5)) % 20 < 10) {
      leds[i] = CHSV(0, 0, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.6));
    }
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 20; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_clear_night() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i > round(NUM_LEDS * 0.45) && i < round(NUM_LEDS * 0.8)) {
      if ((int(fln / 4) + i) % 4 < 2) {
        leds[i] = CHSV(195, 200, int(brightness * 1.1));
      } else {
        leds[i] = CHSV(195, 200, int(brightness * 0.7));
      }
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
}
void show_fog() {
  for (int i = 20; i < NUM_LEDS - 20; i++) {
    float brightnessoffset = (float) (int(i + fln / 2.0) % 20);
    if (brightnessoffset > 10) {
      brightnessoffset = abs(brightnessoffset - 20);
    }
    brightnessoffset = brightnessoffset / 20.0;
    brightnessoffset += 1.0;
    leds[i] = CHSV(170, 130, int(brightness * 0.8 * brightnessoffset));
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 130, brightness);
  }
  for (int i = NUM_LEDS - 20; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 130, brightness);
  }
}
void show_lightning() {
  for (int i = 20; i < NUM_LEDS - 50; i++) {
    if ((i + fln) % 40 < 4) {
      leds[i] = CHSV(24, 184, int(brightness * 1.2));
    } else {
      leds[i] = CHSV(170, 130, int(brightness * 0.66));
    }
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 50; i < NUM_LEDS - 20; i++) {
    if ((i + (40 - (fln % 40))) % 40 < 4) {
      leds[i] = CHSV(24, 184, int(brightness * 1.2));
    } else {
      leds[i] = CHSV(170, 130, int(brightness * 0.66));
    }
  }
  for (int i = NUM_LEDS - 20; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_storm() {
  for (int i = 20; i < NUM_LEDS - 50; i++) {
    if ((i + fln) % 40 < 4) {
      leds[i] = CHSV(24, 184, int(brightness * 1.2));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.4));
    }
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 50; i < NUM_LEDS - 20; i++) {
    if ((i + (40 - (fln % 40))) % 40 < 4) {
      leds[i] = CHSV(140, 240, int(brightness * 1.2));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.4));
    }
  }
  for (int i = NUM_LEDS - 20; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_storm_night() {
  for (int i = 10; i < NUM_LEDS - 50; i++) {
    if ((i + fln) % 40 < 4) {
      leds[i] = CHSV(24, 184, int(brightness * 1.2));
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = 0; i < 10; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  for (int i = NUM_LEDS - 50; i < NUM_LEDS - 10; i++) {
    if ((i + (40 - (fln % 40))) % 40 < 4) {
      leds[i] = CHSV(140, 240, int(brightness * 1.2));
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = NUM_LEDS - 10; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
}
void show_heavy_rain() {
  for (int i = 10; i < round(NUM_LEDS * 0.45); i++) {
    if ((i + fln) % 20 < 10) {
      leds[i] = CHSV(140, 255, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(140, 255, int(brightness * 0.75));
    }
  }
  for (int i = round(NUM_LEDS * 0.45); i < round(NUM_LEDS * 0.55); i++) {
    if ((i + int(fln / 5)) % 4 < 2) {
      leds[i] = CHSV(0, 0, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.6));
    }
  }
  for (int i = round(NUM_LEDS * 0.55); i < NUM_LEDS - 10; i++) {
    if ((i + (20 - (fln % 20))) % 20 < 10) {
      leds[i] = CHSV(140, 255, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(140, 255, int(brightness * 0.75));
    }
  }
  for (int i = 0; i < 10; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 10; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_rainy() {
  for (int i = 10; i < round(NUM_LEDS * 0.45); i++) {
    if ((i + fln) % 10 < 3) {
      leds[i] = CHSV(140, 255, brightness);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = round(NUM_LEDS * 0.45); i < round(NUM_LEDS * 0.55); i++) {
    if ((i + int(fln / 5)) % 4 < 2) {
      leds[i] = CHSV(0, 0, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.6));
    }
  }
  for (int i = round(NUM_LEDS * 0.55); i < NUM_LEDS - 10; i++) {
    if ((i + (10 - (fln % 10))) % 10 < 3) {
      leds[i] = CHSV(140, 255, brightness);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = 0; i < 10; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 10; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_snowy() {
  for (int i = 10; i < round(NUM_LEDS * 0.45); i++) {
    if ((i + fln) % 10 < 3) {
      leds[i] = CHSV(0, 0, brightness);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = round(NUM_LEDS * 0.45); i < round(NUM_LEDS * 0.55); i++) {
    if ((i + int(fln / 5)) % 4 < 2) {
      leds[i] = CHSV(0, 0, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.6));
    }
  }
  for (int i = round(NUM_LEDS * 0.55); i < NUM_LEDS - 10; i++) {
    if ((i + (10 - (fln % 10))) % 10 < 3) {
      leds[i] = CHSV(0, 0, brightness);
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = 0; i < 10; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 10; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_mixed_rain() {
  for (int i = 10; i < round(NUM_LEDS * 0.45); i++) {
    if ((i + fln) % 10 < 4) {
      if (int((i + fln) / 10) % 2 == 0) {
        leds[i] = CHSV(0, 0, brightness);
      } else {
        leds[i] = CHSV(140, 255, brightness);
      }
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = round(NUM_LEDS * 0.45); i < round(NUM_LEDS * 0.55); i++) {
    if ((i + int(fln / 5)) % 4 < 2) {
      leds[i] = CHSV(0, 0, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.6));
    }
  }
  for (int i = round(NUM_LEDS * 0.55); i < NUM_LEDS - 10; i++) {
    if ((i + (10 - (fln % 10))) % 10 < 4) {
      if (int((i + fln) / 10) % 2 == 0) {
        leds[i] = CHSV(0, 0, brightness);
      } else {
        leds[i] = CHSV(140, 255, brightness);
      }
    } else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  for (int i = 0; i < 10; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 10; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_sunny() {
  for (int i = 28; i < NUM_LEDS - 36; i++) {
    if ((i + int(fln / 5.0)) % 20 < 10) {
      leds[i] = CHSV(41, 255, round(brightness * 0.75));
    } else {
      leds[i] = CHSV(41, 255, round(brightness * 1.25));
    }
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = 20; i < 28; i++) {
    leds[i] = CHSV(158, 200, brightness);
  }
  for (int i = NUM_LEDS - 36; i < NUM_LEDS - 23; i++) {
    leds[i] = CHSV(158, 200, brightness);
  }
  for (int i = NUM_LEDS - 23; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
void show_windy() {
  for (int i = 35; i < NUM_LEDS - 35; i++) {
    if (((NUM_LEDS - 40 - i) + int(fln / 3)) % 20 < 10) {
      leds[i] = CHSV(0, 0, int(brightness * 1.1));
    } else {
      leds[i] = CHSV(0, 0, int(brightness * 0.6));
    }
  }
  for (int i = 20; i < 35; i++) {
    float brightnessoffset = (float) (int(fln / 1.5) % 20);
    if (brightnessoffset > 10) {
      brightnessoffset = abs(brightnessoffset - 20);
    } else if (brightnessoffset == 0) {
      brightnessoffset = 1;
    }
    brightnessoffset = brightnessoffset / 10.0;
    brightnessoffset += 1.0;
    leds[i] = CHSV(0, 0, int(brightness * 0.8 * brightnessoffset));
  }
  for (int i = NUM_LEDS - 35; i < NUM_LEDS - 20; i++) {
    float brightnessoffset = (float) (int(fln / 1.5) % 20);
    if (brightnessoffset > 10) {
      brightnessoffset = abs(brightnessoffset - 20);
    } else if (brightnessoffset == 0) {
      brightnessoffset = 1;
    }
    brightnessoffset = brightnessoffset / 10.0;
    brightnessoffset += 1.0;
    leds[i] = CHSV(0, 0, int(brightness * 0.8 * brightnessoffset));
  }
  for (int i = 0; i < 20; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
  for (int i = NUM_LEDS - 20; i < NUM_LEDS; i++) {
    leds[i] = CHSV(85, 200, brightness);
  }
}
