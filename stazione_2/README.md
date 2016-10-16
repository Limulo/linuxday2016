# OVERVIEW
La stazione 2 si compone di alcuni moduli satelliti gestiti da un Arduino Mega.
Nello specifico Arduino Mega controlla tre relay che pilotano l'accensione/spegnimento di oggetti connessi ad alimentazione.
I relay vengono attivati: 
* tramite il suono
* tramite il tocco
* tramite un software su un computer via bluetooth

## Materiali
* Arduino mega
* MAX4466
* BlueSmirf
* moduli relay
* capboard

# SETUP

## Prerequisiti
* il computer ha attiva la comunicazione BlueTooth ed è visibile

## BlueTooth
Per impostare correttamente la comunicazione BT tra un computer e Arduino si deve seguire questa procedura:
* Se e' la **prima** connessione mai stabilita tra il Blue Smirf e il computer, accedere alla modalità _command_ dal monitor seriale di Arduino, digitando il comando `$$$`. 
  Ricordarsi di due cose importanti:
	+ nel serial monitor **scegliere il corretto baudrate**
	+ impostare il CR come fine linea
  Una volta nella modalità _command_, digitare `I` per ricercare i device. Trovato il device interessato, connettersi con il comando `C <indirizzo>`.
  In **Mac OS X** viene richiesto un codice di sicurezza per il pairing: inserire `1234`.
  Nelle preferenze del sistema, aggiungere per il dispositivo BlueTooth appena collegato una porta seriale. Prendere nota di come si chiama la porta seriale.
* Se ci si è già connessi in precedenza, non è necessario compiere ancora queste operazioni.
* Ora la comunicazione tra BlueSmirf e computer può avvenire, a patto di aprire la corretta porta seriale (l'inidirizzo di cui abbiamo preso nota e consultabile dal pannello delle preferenze) e di impostare un corretto baudrate (uguale per entrambi i dispositivi).

**NB**
Si può controllare la connessione bluetooth sia da Processing con libreria _Serial_, sia tramite software, come _Coolterm_, sia da terminale.
Per approfondimenti può essere utile [questo tutorial](https://learn.sparkfun.com/tutorials/terminal-basics/command-line-windows-mac-linux). 


# WORKFLOW

* **1)** collegare i 3 dispositivi 220V alle 3 prese _relays_ delal centralina;
* **2)** connettere la **capboard** e il **microfono** alla centralina;
* **3)** connettere la centralina all'alimentazione 220V;
* **4)** alimentare la centralina usando un trasformatore 9V;
* **5)** sul computer macbook attivare il _bluetooth_ (pairing e porta seriale); così facendo il modulo _BlueSmirf_ dovrebbe segnalare luce verde!
* **6)** Lanciare lo sketch di **Processing**

## NOTA BENE
dopo un tot di tempo che la connessione BlueTooth su mac non viene usata, questa viene interrotta in automatico
Per riattivarla recarsi nelle _Preferenze di Sistema / BlueTooth --> modifica porte seriali_
