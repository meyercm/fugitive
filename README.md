### FUGITIVE

A one-handed, Arduino-based, chorded keyboard.

#### Project Overview

Fugitive is an implementation of a 7 key keyboard, inspired by my frustration
trying to type one-handed.  Unlike normal keyboards, where there is a key for
each character, `Fugitive` uses a combination of keys pressed simultaneously to
type a single letter.

Initially, I looked at the [SpiffChorder Project], which definitely shaped the
direction of my efforts, but eventually decided to write my own firmware, and
my own chordset.

#### Hardware configuration

My current design uses a [Pro Micro], with an Atmel 32u4 MCU.  The most
cost-effective source of mechanical switches I could find was an [inexpensive
mechanical keyboard], which was reasonably easy to harvest switches from using a
soldering iron and wick.

For an enclosure, I found a styrofoam sphere in the craft aisle, which I sliced
in half and pressed the switches into.

#### Electrical connections

The seven switches are wired to their own GPIO and to a common ground. The GPIO
pins are set as `INPUT_PULLUP`. When a pin is pressed, the pin will measure low.

#### Software considerations

I was originally concerned because the 32u4 has lesse than 7 interruptable pins.
However, I found a solution (see below) and quickly discarded it- I realized
that even inefficient software would be far faster than the human using it could
perceive.

#### Current status

The keyboard is usable as it is (I'm writing this README with it).  However, it
has a few shortcomings, and at least one bug.

- Periodically seems to miss a single chord
- F1...F10 are not implemented
- Only the 'normal' voice (chordmap) is implemented
- Mouse mode not implemented



#### Notes from the internet regarding interrupt circuits:

[forum discussion](http://www.avrfreaks.net/forum/multiplex-several-switches-one-external-interrupt)

> There's no reason to connect the switches to GND and use diodes. Intead connect the switches like shown in the attached schematic.
> 1) To begin with set the INT pin as input with the internal pull-up resistor activated and enable INT.
> 2) Set all the other pins as outputs pulled to GND. This way the INT input will be pulled low once a switch is pressed.
> 3) (a) When INT gets triggered, set the INT pin as output pulled to GND and set all the other pins as inputs with the internal pull-up resistors activated.
> 4) (a) Read the value of all the switch input pins. The ones that are low menas the switch is pressed. If the input is high the input is not pressed. This way you can even see if two or more switches are pressed at the same time.
> After this repeat 1) and 2) and you are ready for a new switch interrupt.
> Alternativevely to point 3a) and 4a) you can do like this instead after point 1) and 2):
> 3) (b) When INT gets triggered keep it as an input with the pull-up resitor still activated. Then pull all the other output pins high except for the pin connected to S1 that you pull low.
> 4) (b) Read the status of the INT input, if it's high, then S1 is not activated, if it's low S1 is activated.
> After this repeat 3b) and 4b) but this time with the S2 output pulled low instead of the S1 output and so forth until you > have cycled through all 5 switches.
> After this repeat 2) and wait for a new switch interrupt.


[SpiffChorder Project]: http://chorder.cs.vassar.edu/
[Pro Micro]: https://www.amazon.com/gp/product/B01HCXMBOU
[inexpensive mechanical keyboard]: https://www.amazon.com/gp/product/B01MS8YTYX
