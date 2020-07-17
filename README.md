# infinity-mirror
Example code for a smart infinity mirror!
Okay, so first of all, here's some credits:
- Thanks to the people on the Arduino fourm! You've helped my a lot.
- Thanks for HelTec's [OLED display API docs](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/oled/API.md), and the [rest of their library](https://github.com/HelTecAutomation/Heltec_ESP32/).
- Thanks to [simple-weather-card](https://github.com/kalkih/simple-weather-card). Your icons gave me the inspiration for the patterns, and your source gave me a really good mapping.
- Thanks to the [World Time API](https://worldtimeapi.org/) for the API.
- Thanks to [Home Assistant](https://home-assistant.io/), of course!
- Thanks to [Dave's Garage](https://www.youtube.com/channel/UCNzszbnvQeFzObW0ghk0Ckw) and [this post from him](https://www.youtube.com/post/Ugzhaf4slmPXC9Kkzo54AaABCQ).
  
Okay, now for some pictures:  
![Screenshot of simple control in HA](/2020-07-17-135802_1920x1080_scrot.png)
![Screenshot of full control in HA](/rsz_2020-07-17-140729_1920x1080_scrot.png)
![Picture of screen](/IMG_20200717_141543.jpg)
![Picture of infinity mirror](/IMG_20200717_141323.jpg)  

Now let's go to the parts.
1. (Only tested on) [HelTec Wifi Kit 32](https://heltec.org/project/wifi-kit-32/)
2. [Any USB cable](https://www.amazon.com/USB-Cables/b?node=464394)
3. [Any breadboard](https://www.amazon.com/breadboard/s?k=breadboard)
4. [Any couple male-to-male jumper wires](http://adafru.it/759)
5. (Only tested on) [LED strip](https://www.btf-lighting.com/products/ws2812b-led-pixel-strip-30-60-74-96-100-144-pixels-leds-m?variant=25586938511460)
6. (Only tested on) [Infinity mirror to hack](https://www.amazon.com/dp/B07LF4YMCZ)

Okay, let's do this.
1. Pry apart the infinity mirror.
  - First, remove the battery base. Do that by pushing apart the bottom part, and while you do that, pull away the battery holder.
