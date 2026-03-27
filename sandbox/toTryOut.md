# Stuff to try out

- Modify blinkLed to also use the setup function and see what caused higher brightness in led, (pinMode func).
  - If not included, the pin can behave weird, in this case pinMode initializes that specific pin to be output. In our case, the led works ok but very dimmed, when I use the pinMode function it glows a lot more.
  - We used an analog pin with the digitalWrite and for leds, it works fine, using the digitalWrite with a digital pin works the same for leds it seems.
- Modify script to dim up and down the led, over a certain period of time. file: dimLedSmooth.ino
- Add button to turn led on click.
- Add button to switch on and off the led.
