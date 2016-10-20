# Capboard Issue

Evidentemente la capboard è una scheda molto sensibile alle tensioni e alle correnti in gioco, per questo, anche memori della **ISSUE#21** del repository di **Lexuxs**, pensiamo che i relay (pur alimentati separatamente da dalla Scheda Arduino), creino comunque dei distrurbi di tipo elettrico.

## test da effettuare
* alimentazione Relay separata con alimentatore separato e senza passare per **Vin**
* alimentazione separata per la capboard, tipo batteria a pastiglia!
* fotoaccoppiatore ai pin digitali di arduino
* provare a PLOTTARE i valori restituiti dalla capboard.
