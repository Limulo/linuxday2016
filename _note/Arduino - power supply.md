# ARDUINO / Currents and Voltages
Questo articolo è in realtà un promemoria per consultazione in caso di dubbio riguardo all'alimentazione della scheda Arduino e alla corrente che la scheda stessa può erogare dai propri pin. In chiusura dell'articolo riporto una serie di link da usare come riferimento per documentarsi ulteriormente.


## tra 5V e GND
* Quando la scheda Arduino UNO è alimentata **alimentata dalla porta USB**, il massimo della corrente che può fornire tra i suoi pin di alimentazione (5V) e terra è pari a **500mA** (corrente massima erogabile dalla prese USB _standard compliant_). In caso i sensori i circuiti connessi facessero richiesta di maggiore corrente, un fusibile (_resettable polyfuse_) interromprerebbe il circuito salvaguardando Arduino e al contempo la porta USB del computer - anche se talvolta è direttamente l'hardware del computer in grado di disabilitare la porta USB incriminata in questi casi.

* Quando la scheda è invece **connessa ad un alimentatore esterno** (che possa erogare correnti >= 1A), il massimo della corrente che Arduino UNO può erogare risulta essere comunque limitato da quanto il regolatore di tensione è in grado di erogare: **1A**;

La corrente di cui si è parlato fino ad ora è da intendersi corrente che scorre **tra Vcc (5V) e ground (GND)**.

## dai pin
La corrente massima erogabile dai pin (i pin digitali ad esempio) invece è pari a **40mA**. Mentre la somma di tutte le correnti ai pin combinate è al massimo pari a **200mA** e tale limite non può essere superato.

---

I limiti delle correnti prelevabili da **5V/GND** da un lato e dai **pin** dall'altro, sono differenti e questa separazione va tenuta bene in considerazione. 

Ad esempio: se si devono pilotare 10 LED con un consumo di circa 20mA ciascuno usando i pin di Arduino (10 x 20mA = 200mA), si è praticamente arrivati al limite fisico della scheda ed è molto probabile che questa sitauzione porti al suo daneggiamento. Per risolvere il problema si può utilizzare un transistor che, pilotato dal pin di Arduino (consumando così poca corrente), ne gestisca poi molta di più (magari facendola scorrere tra 5V e GND) alimentando così i LED senza rischio di danneggiamenti.

## Me lo dimentico sempre

Un'altra cosa che sono solito dimenticare è come Arduino risolve il _conflitto di alimnetazione_ (_power conflict_), in altri termini quando si connettono simultaneamente USB al computer e jack dell'alimentatore alla scheda. Ebbene in tali casi la tensione di alimentazione del cavo USB viene ignorata!
La comunicazione tra mite USB è ancora attiva ma soltanto per quanto riguarda lo scambio dei dati; l'alimentazione proviene invece dall'alimentatore connesso via jack alla scheda o dal pin _Vin_ se connesso.

---

### LINKS e RIFERIMENTI
* [questo](http://arduino-info.wikispaces.com/ArduinoPinCurrent) articolo esamina nello specifico le caratteristiche dei microcontrollori ATMEL montati sulle schede Arduino;
* [link](http://www.electricrcaircraftguy.com/2014/02/arduino-power-current-and-voltage.html)
* [link](http://www.open-electronics.org/the-power-of-arduino-this-unknown/) un articolo molto interessante su come alimentare il nostro Arduino quando lo si voglai sfruttare in sitauzioni in cui non possa essere connesso ad un computer! 

---

### Dati relativi ai sensori di Limulo
I dati qui raccolti sono estrapolati dai datasheet rispettivi:

* US MaxBotix MB1000 - consumo di corrente pari a **3mA** @ 5V;
* US Devantech SRF04 - consumo di corrente pari a **30mA** @ 5V;
* MPR121 - **29μA** typical run current (come da [datasheet](https://cdn-shop.adafruit.com/datasheets/MPR121.pdf));
* [ADXL335](http://www.analog.com/en/products/mems/accelerometers/adxl335.html#product-overview) (accelerometro) - **350 μA** typical;
* SHARP GP2Y0A21YK0F, IR range finder - **30mA** typical (come da [datasheet](http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a21yk_e.pdf));
* BlueSmirf Silver - **50mA** massimo con ponte radio attivato e trasmissione dati (altrimenti meno).
* MAX4466 - **60μA** come da [datasheet](https://cdn-shop.adafruit.com/datasheets/MAX4465-MAX4469.pdf) dell'amplificatore;
* Modulo Grove Relay v1.2 - **100mA** come indicato da [datasheet](http://wiki.seeedstudio.com/wiki/Grove_-_Relay); 
* Servo motore 360° SpringRc [SM-S4303R](https://www.pololu.com/product/1248) - [datasheet](https://www.pololu.com/file/0J336/SM-S4303R.pdf)
* Servo motore 180° - HS-5055MG - alcune [info1](https://www.servocity.com/hs-5055mg-servo) e [info2](http://hitecrcd.com/products/servos/micro-and-mini-servos/digital-micro-and-mini-servos/hs-5055mg-economy-metal-gear-feather-servo/product);
