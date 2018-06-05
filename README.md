# leaf

in questo repository è ospitato tutto il codice dell'installazione "leaf" realizzata dai ragazzi del corso digital2 alla scuola holden a giugno 2018.

L'installazione è composta da 3 elementi:

1) un tablet in cui lasciare dei messaggi
2) una stampante termica che stampa i messaggi lasciati nel tablet
3) 10 file di bottiglie di vetro, con all'interno led, memorie stampate e schermi lcd.

### HARDWARE UTILIZZATO:
1 raspberry pi sul quale gira il server
5 mkr1000 che pilotano ognuna 2 file di bottiglie collegate in corda
neopixel strip
schermi lcd i2c
1 thermal printer
1 tablet

### LIBRERIE Arduino da installare;
- wifi101 by Arduino
- MQTT by Joel Gaehwiler v1.10.1
- LiquidCristal_PCF8574 by Matthias Hertel v1.1.1
- Adafruit neopixel library
- Adafruit_ThermalPrinter

## TOOLS utilizzati
La comunicazione tra le componenti dell'installazione è realizzata via mqtt ed utilizza shfitr.io brocker Una visualizzasione del grafo mqtt può essere monitorata quì.
https://shiftr.io/lorenzo/sandbox

La raspi è stata provisionata con forevere-server per avviare l'applicazione app.js ad ogni riavvio.

Inoltre è stato installato e configurato un serviozio offerto da www.remot3.it per l'accesso alla scheda da remoto.

altre info in italiano quì https://docs.google.com/document/d/1uy7KdR3enNkKxGp13uQwrTgSPKTJWtkjBiAGlHRwnek/edit
