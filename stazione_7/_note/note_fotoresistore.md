# FOTORESISTORE
Il fotoresistore (o resistore dipendente dalla luce, LDR o fotocellula) è un resisotire variabile controllato dalla luce. La resistenza del fotoresistore diminuisce con l'aumento dell'intensità della luce incidente; in altre parole, esso presenta **fotoconduttività**.

Mi surati con il multimetro, i nostri fotoresistori presentano una resistenza variabile di valori:
* molta luce --> 500 Ohm
* buio qualsi completo --> 500KOhm

Nello sketch che stiamo creando, non siamo tanto interessati a percepire _aumenti_ quanto _diminuzioni_ nel valore di intensità della luce. Un meccanismo controllato da uno o più resistori deve attivarsi solo quando uno o più di questi resistori si trovino oscurati da un oggetto o una mano.
La **resistività** aumenta all'aumentare del _buio_.

## Configurazioni Circuitali

### Serie

Volendo usare più fotoresistori in modo tale che ne basti soltanto uno in ombra per far scattare il meccanismo, allora li si potrebbe connettere in serie tra di loro.

                punto di prelievo
                       |
    Vcc |---[Rfisso]---o---[fotoR]---[fotoR]---[fotoR]---|> GND

Quando almeno uno dei fotoresistori viene oscurato, la **Req** della serie aumenta, così come aumenta quella dell'intero circuito. Al _punto di prelievo_ si misura quindi un valore più alto rispetto a prima.

### Parallelo
Al contrario, se si è interessati ad usarli in modo che quando tutti assieme si trovino in ombra attivino un qualche meccanismo a monte, allora la configurazione circuitale è il parallelo!

    VCC
    ___
     |
    [Rfisso]
     |
     o---- punto di prelievo
     |
     |
     L____________________
     |          |        |
    [fotoR]  [fotoR]  [fotoR]
     |          |        |
     L__________L________|
     |
     GND

Soltanto quando tutti i fotoresistori si trovano contemporaneamente in oscurità di potrà registrare un aumento nel valore di tensione misurato al _punto di prelievo_. Basta infatti che anche un solo fotoresistore resti in luce per fornire alla corrente un passaggio preferenziale e mantenere invariata (o quasi) la tensione al _punto di prelievo_, anche se gli altri fotoresistori sono in ombra.


