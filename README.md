### FUGITIVE

A one-handed, Arduino-based, chorded keyboard.


### Notes from the internet:

[forum discussion](http://www.avrfreaks.net/forum/multiplex-several-switches-one-external-interrupt)


> There's no reason to connect the switches to GND and use diodes. Intead connect the switches like shown in the attached > schematic.
> 1) To begin with set the INT pin as input with the internal pull-up resistor activated and enable INT.
> 2) Set all the other pins as outputs pulled to GND. This way the INT input will be pulled low once a switch is pressed.
> 3a) When INT gets triggered, set the INT pin as output pulled to GND and set all the other pins as inputs with the internal pull-up resistors activated.
> 4a) Read the value of all the switch input pins. The ones that are low menas the switch is pressed. If the input is high the input is not pressed. This way you can even see if two or more switches are pressed at the same time.
> After this repeat 1) and 2) and you are ready for a new switch interrupt.
> Alternativevely to point 3a) and 4a) you can do like this instead after point 1) and 2):
> 3b) When INT gets triggered keep it as an input with the pull-up resitor still activated. Then pull all the other output pins high except for the pin connected to S1 that you pull low.
> 4b) Read the status of the INT input, if it's high, then S1 is not activated, if it's low S1 is activated.
> After this repeat 3b) and 4b) but this time with the S2 output pulled low instead of the S1 output and so forth until you > have cycled through all 5 switches.
> After this repeat 2) and wait for a new switch interrupt.
