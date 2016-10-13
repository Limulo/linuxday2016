# PROXIMITY and SERVOS - a TouchBoard issue.
[Arduino Leonardo](https://www.arduino.cc/en/Main/arduinoBoardLeonardo), on which the BareConductive Touchboard is based , has 7 PWM channels: **3, 5, 6, 9, 10, 11**, and **13**.

After some experiments where we wanted to make the board emit a sound and drive a servo at the same time when detecting a proximity via the MPR121, we have discovered that PWM pins **3, 5, 6** and **9** are not working as expected. In other words, attaching a servo to those pins ends up in upredictable results: sometimes the servo seems to work but no sound is emitted while in other tries neither the MP3 player and the serso work and the board is freezed (no _loop_ cycling).

Fortunately we were able to make everything work since PWM digital pins **10, 11** and **13** behaves noramlly.

## LINKS and REFERENCES
* [Sparkfun MP3 shield](https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup-guide-v15)
* an (old) TouchBoard [schematic](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/touch-board-schematic.pdf) and [datasheet](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/TouchBoard_TechDataSheet.pdf);

