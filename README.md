# infinity-mirror
Example code for a smart infinity mirror!
Okay, so first of all, here's some credits:
- Thanks to the people on the Arduino fourm! You've helped my a lot.
- Thanks for HelTec's [OLED display API docs](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/oled/API.md), and the [rest of their library](https://github.com/HelTecAutomation/Heltec_ESP32/).
- Thanks to [simple-weather-card](https://github.com/kalkih/simple-weather-card). Your icons gave me the inspiration for the patterns, and your source gave me a really good mapping.
- Thanks to the [World Time API](https://worldtimeapi.org/) for the API.
- Thanks to [Home Assistant](https://home-assistant.io/), of course!
- Thanks to [Dave's Garage](https://www.youtube.com/channel/UCNzszbnvQeFzObW0ghk0Ckw) and [this post from him](https://www.youtube.com/post/Ugzhaf4slmPXC9Kkzo54AaABCQ).
  
And here's the fourm discussion: https://community.home-assistant.io/t/212410?u=ktibow
  
<details><summary>Okay, now for some pictures:</summary>
  
![Screenshot of full control in HA](/rsz_2020-07-17-140729_1920x1080_scrot.png)
![Picture of screen](/IMG_20200717_141543.jpg)
![Picture of infinity mirror](/IMG_20200717_141323.jpg)  
</details>

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
## Set up Home Assistant
1. Add the Local IP integration using the GUI.
2. Add these `input_number` helpers:
- `input_number.mirror_brightness`
  - Name: Mirror Brightness
  - Icon: `mdi:mirror`
  - Max value: `255`
  - Leave everything else
- `input_number.hue`
  - Name: Hue
  - Icon: `mdi:mirror`
  - Max value: `255`
  - Leave everything else
- `input_number.saturation`
  - Name: Saturation
  - Icon: `mdi:mirror`
  - Max value: `255`
  - Leave everything else
3. Add these `input_select` helpers:
- `input_select.mirror_force_weather`
  - Name: Mirror force weather
  - Icon: `mdi:mirror`
  - <details><summary>Options:</summary>

    - clear_night
    - cloudy
    - fog
    - lightning
    - storm
    - storm_night
    - mostly_cloudy
    - mostly_cloudy_night
    - heavy_rain
    - rainy
    - snowy
    - mixed_rain
    - sunny
</details>

  - Leave everything else
- `input_select.mirror_mode`
  - Name: Mirror mode
  - Icon: `mdi:mirror`
  - <details><summary>Options:</summary>

    - Light
    - Clock
    - Weather
    - Force weather
    - Rainbow
    - Random
    - More patterns
</details>

  - Leave everything else
- `input_select.mirror_pattern`
  - Name: Mirror pattern
  - Icon: `mdi:mirror`
  - <details><summary>Options:</summary>

    - Cyan + Magenta
    - Cyan + Orange
    - Cyan + Green
    - Cyan + Purple
    - Orange + Magenta
    - Orange + Green
    - Orange + Purple
    - Green + Magenta
    - Green + Purple
    - Purple + Magenta
</details>

  - Leave everything else
4. Add these `input_text` helpers:
- `input_text.mirror_status`
  - Name: Mirror status
  - Icon: `mdi:mirror`
  - Maximum length: 10
  - Leave everything else
5. Add this light to your `configuration.yaml`:
```yaml
- platform: template
  lights:
    infinity_mirror:
      friendly_name: Infinity Mirror
      value_template: '{{is_state(''input_text.mirror_status'', ''on'')}}'
      level_template: '{{((states(''input_number.mirror_brightness'') | int - 10) / 68 * 100) | int}}'
      color_template: '({{(states(''input_number.hue'') | int / 255 * 360) | int}}, {{(states(''input_number.saturation'') | int / 255 * 100) | int}})'
      turn_on:
        service: input_text.set_value
        data:
          entity_id: input_text.mirror_status
          value: 'on'
      turn_off:
        service: input_text.set_value
        data:
          entity_id: input_text.mirror_status
          value: 'off'
      set_level:
        service: input_number.set_value
        data_template:
          entity_id: input_number.mirror_brightness
          value: '{{(brightness | int / 100 * 68 + 10) | int}}'
      set_color:
        - service: input_number.set_value
          data_template:
            value: "{{(h | int / 360 * 255) | int}}"
            entity_id: input_number.hue
        - service: input_number.set_value
          data_template:
            value: "{{(s | int / 100 * 255) | int}}"
            entity_id: input_number.saturation
```
6. Add this template sensor to your `configuration.yaml`:
```yaml
sensor:
  - platform: template
    sensors:
      mtms:
        value_template: '{{states(''weather.kbfi_hourly'')}}|{{states(''input_text.mirror_status'')}}|{{states(''input_number.mirror_brightness'')}}|{{states(''input_number.hue'')}}|{{states(''input_number.saturation'')}}|{{states(''input_select.mirror_mode'')}}|{{states(''sun.sun'')}}|{{states(''input_select.mirror_pattern'')}}|{{states(''input_select.mirror_force_weather'')}}'
```
7. Add this command to your `configuration.yaml`:
```yaml
shell_command:
  update_mirror: '/usr/bin/curl "http://192.168.1.97/collect?info={{states(''sensor.mtms'')}}"'
```
8. Restart Home Assistant
9. Short UI control (requires `slider-entity-row`, `rgb-light-card`):
```yaml
entities:
  - entity: light.infinity_mirror
    full_row: true
    toggle: true
    type: 'custom:slider-entity-row'
  - colors:
      - hs_color:
          - 315
          - 85
        icon_color: 'hsl(315, 100%, 75%)'
      - hs_color:
          - 0
          - 77
        icon_color: 'hsl(0, 100%, 75%)'
      - hs_color:
          - 40
          - 85
        icon_color: 'hsl(40, 100%, 75%)'
      - hs_color:
          - 99
          - 85
        icon_color: 'hsl(99, 100%, 75%)'
      - hs_color:
          - 140
          - 85
        icon_color: 'hsl(140, 100%, 75%)'
      - hs_color:
          - 180
          - 80
        icon_color: 'hsl(180, 100%, 75%)'
      - hs_color:
          - 215
          - 80
        icon_color: 'hsl(215, 100%, 75%)'
      - hs_color:
          - 270
          - 80
        icon_color: 'hsl(270, 100%, 75%)'
    entity: light.infinity_mirror
    justify: center
    size: 35
    type: 'custom:rgb-light-card'
show_header_toggle: false
type: entities
```
Make sure you include this automation:
```yaml
- id: 'turn_on_light_when_color_changes'
  alias: Set mode to light when color changes
  description: ''
  trigger:
  - entity_id: sensor.currentcolor
    platform: state
  condition:
  - condition: not
    conditions:
    - condition: state
      entity_id: input_select.mirror_mode
      state: Clock
  action:
  - data:
      option: Light
    entity_id: input_select.mirror_mode
    service: input_select.select_option
```
10. More UI control with `light-entity-card`:
```yaml
entities:
  - entity: light.infinity_mirror
  - brightness: true
    brightness_icon: weather-sunny
    child_card: true
    color_picker: true
    color_temp: true
    color_wheel: true
    consolidate_entities: false
    entity: light.infinity_mirror
    full_width_sliders: false
    hide_header: true
    persist_features: false
    shorten_cards: true
    show_slider_percent: true
    smooth_color_wheel: false
    temperature_icon: thermometer
    type: 'custom:light-entity-card'
    white_icon: file-word-box
    white_value: true
  - entity: input_select.mirror_mode
  - entity: input_select.mirror_pattern
  - entity: input_select.mirror_force_weather
show_header_toggle: false
title: Infinity mirror
type: entities
```
11. And add this automation too, so HA can tell the mirror when anything changes:
```yaml
- id: 'let_mirror_know_when_status_changes'
  alias: Let mirror know when anything changes
  description: ''
  trigger:
  - entity_id: sensor.mtms
    platform: state
  condition: []
  action:
  - data: {}
    service: shell_command.update_mirror
```
## Set up your enviroment and upload
1. Make sure the [Arduino IDE](https://www.arduino.cc/en/Main/Software) is installed, and set up for HelTec's board. [Here's HelTec's guide.](https://heltec-automation-docs.readthedocs.io/en/latest/esp32+arduino/quick_start.html#via-arduino-board-manager)
2. Download [the zip](https://github.com/KTibow/infinity-mirror/archive/master.zip), unzip it, and open `mirror.ino` in `mirror`.
3. Open `token.h` and change the stuff, and open `mirror.ino` and change the number of LEDS. You might also need to change your gateway, subnet, and DNS IP addresses in `setup.h`.
4. Upload it!
## You're done!
Let me know if you have any problems [in an issue](https://github.com/KTibow/infinity-mirror/issues/new). BTW: You can upload a compiled binary at `esp32.local` with username and password `program`.
