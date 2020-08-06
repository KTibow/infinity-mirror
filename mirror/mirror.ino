#define NUM_LEDS 97

#include "token.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <WebServer.h>
#include <heltec.h>
#include <TimeLib.h>
#include <FastLED.h>
#include "font.h"

String messages[5] = {"", "", "", "", ""};
String its PROGMEM = "It's ";
String weatheropty = "";
uint8_t taskCoreZero PROGMEM = 0;
uint8_t taskCoreOne PROGMEM = 1;
String weather = "unknown";
String prtweather = "unknown";
TaskHandle_t Task;
CRGB leds[NUM_LEDS];
CHSV randomcolors[NUM_LEDS];
int ledcolors[NUM_LEDS];
unsigned int ln = 0;
unsigned int fln = 0;
int hue = 200;
int saturation = 255;
int brightness = 100;
bool ison = true;
bool is_night = false;
String modeuse = "";
String pattern = "";
String localip = "";
String weatherpattern = "";
WebServer server(80);
const char* host = "esp32";
unsigned long lastmodified = millis();

#include "ota.h"
#include "helpers.h"
#include "weather.h"
#include "updatestatus.h"
#include "setup.h"

void loop() {
  time_t t = now();
  int tt = millis();
  int hr = hour(t) % 12;
  if (hr == 0) {
    hr = 12;
  }
  String curtime = String(hr) + ":";
  if (minute(t) < 10) {
    curtime += "0";
  }
  curtime += String(minute(t));
  String morneven = (hour(t) < 12) ? " AM" : " PM";
  showString(its + curtime + morneven, 0, 20);
  showString(its + tellweather(true), 1, 20);
  if (millis() - lastmodified > 600000) {
    modeuse = "Weather";
  }
  if (ison) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue, saturation, brightness);
    }
    if (modeuse == "Clock") {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue, saturation, round(brightness * 0.7));
      }
      showclock(t);
    } else if (modeuse == F("Rainbow")) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(ledcolors[(i + ln) % NUM_LEDS], 255, brightness);
      }
    } else if (modeuse == F("Weather") || modeuse == F("Force weather")) {
      String wthropt = tellweather(false);
      if (modeuse == F("Force weather")) {
        wthropt = weatherpattern;
      }
      // clear_night
      // cloudy
      // fog
      // lightning
      // storm
      // storm_night
      // mostly_cloudy
      // mostly_cloudy_night
      // heavy_rain
      // rainy
      // snowy
      // mixed_rain
      // sunny
      // windy
      if (wthropt == F("clear_night")) {
        show_clear_night();
      } else if (wthropt == F("cloudy")) {
        show_cloudy();
      } else if (wthropt == F("fog")) {
        show_fog();
      } else if (wthropt == F("lightning")) {
        show_lightning();
      } else if (wthropt == F("storm")) {
        show_storm();
      } else if (wthropt == F("storm_night")) {
        show_storm_night();
      } else if (wthropt == F("mostly_cloudy")) {
        show_mostly_cloudy();
      } else if (wthropt == F("mostly_cloudy_night")) {
        show_mostly_cloudy_night();
      } else if (wthropt == F("heavy_rain")) {
        show_heavy_rain();
      } else if (wthropt == F("rainy")) {
        show_rainy();
      } else if (wthropt == F("snowy")) {
        show_snowy();
      } else if (wthropt == F("mixed_rain")) {
        show_mixed_rain();
      } else if (wthropt == F("sunny")) {
        show_sunny();
      } else if (wthropt == F("windy")) {
        show_windy();
      }
    } else if (modeuse == F("Random")) {
      if (ln % 5 == 0) {
        for (int i = 0; i < NUM_LEDS; i++) {
          CHSV randomcolor = CHSV(random(0, 255), 255, brightness);
          randomcolors[i] = randomcolor;
          leds[i] = randomcolor;
        }
      } else {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = randomcolors[i];
        }
      }
    } else if (modeuse == F("More patterns")) {
      if (pattern == F("Cyan and Magenta")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness);
          } else {
            leds[i] = CHSV(128, 255, brightness);
          }
        }
      } else if (pattern == F("Cyan and Orange")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(31, 255, brightness);
          } else {
            leds[i] = CHSV(128, 255, brightness);
          }
        }
      } else if (pattern == F("Cyan and Green")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(85, 255, brightness);
          } else {
            leds[i] = CHSV(128, 255, brightness);
          }
        }
      } else if (pattern == F("Cyan and Purple")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness / 2);
          } else {
            leds[i] = CHSV(128, 255, brightness);
          }
        }
      } else if (pattern == F("Orange and Magenta")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness);
          } else {
            leds[i] = CHSV(26, 255, brightness);
          }
        }
      } else if (pattern == F("Orange and Green")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(90, 255, brightness);
          } else {
            leds[i] = CHSV(26, 255, brightness);
          }
        }
      } else if (pattern == F("Orange and Purple")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness / 2);
          } else {
            leds[i] = CHSV(26, 255, brightness);
          }
        }
      } else if (pattern == F("Green and Magenta")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness);
          } else {
            leds[i] = CHSV(85, 255, brightness);
          }
        }
      } else if (pattern == F("Green and Purple")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness / 2);
          } else {
            leds[i] = CHSV(85, 255, brightness);
          }
        }
      } else if (pattern == F("Purple and Magenta")) {
        for (int i = 0; i < NUM_LEDS; i++) {
          if ((i % 8 < 4) ^ (ln % 10 < 5)) {
            leds[i] = CHSV(213, 255, brightness);
          } else {
            leds[i] = CHSV(213, 255, brightness / 2);
          }
        }
      }
    }
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  FastLED.show();
  ln++;
  fln++;
  ln = ln % NUM_LEDS;
  while (millis() - tt < 40) {
    server.handleClient();
  }
}
