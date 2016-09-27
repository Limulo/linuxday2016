## ARDUINO LEONARDO / MICRO##

Dato che Arduino Leonardo/Micro ha un solo chip per il controllo del programma e della comunicazione seriale, e che questa è virtualizzata via software, la scheda non può utilizzare la funzione

`void serialEvent()`

della libreria base di Arduino.
Pertanto la lettura dei bytes in entrata e il controllo per quelli in uscita si fa nel _loop_.
