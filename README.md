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
## Pry apart the infinity mirror
### Bottom
1. First, remove the battery base. Do that by pushing apart the bottom part, and while you do that, pull away the battery holder.
2. Disconnect all of the wires. Just pull/chop them off.
3. Push out the stuff. You might need to push on some stuff really hard in order to push out the switch and power plug.
4. Make the hole between the base and top bigger for the light strip connector.

Note: Don't put the battery base back on, not even later.
### Middle
1. Pry off the coverings. The mirror is made of 3 parts, the middle, and the two covers. Pry off the glue.
2. Pull off one of the mirrors. Be very gentle, or you'll have a scratched-up mirror like I do.
3. Detach the provided light strip. Just pull off the adhesive.
## Cut and place the light strip
1. Place the light strip around the mirror.
2. Find which side is the input and output of the LED strip, and cut off any excess. It's okay to cut off the other connector, too.
3. Count the number of LEDs in the strip.
4. Peel off the adhesive backing and place the light strip. Make sure to put the connector through the hole you made earlier.
5. Route the connector through the light switch hole.

Yahoo! You've done most of the hardware.
## Set up the connections
1. Find your WiFi Kit 32 and solder headers.
2. Place it in the middle of your breadboard.
3. Put one wire at pin 5. Put the other two at 5V and GND.
4. Put the pin 5 wire to the middle, green wire of the connector.
5. Put the 5V wire to the red wire of the connector, and the GND wire to the white wire of the connector.
## Set up your enviroment
1. Make sure the [Arduino IDE](https://www.arduino.cc/en/Main/Software) is installed.
