# Zylinderino

This is the software behind a top hat engülfed in WS2812B addressable LED-strips.
All the strips are wired in series, so we use one single framebuffer and have to remember where each new line begins.
This could be done using defines or an array.
The microcontroller is a ESP8266, which enables it to open a webserver and stuff.

A friend of mine built a LED top hat himself, but wired the strips all differently.
To accomodate this, the backend and the frontend shall be separated.
Possibly one could also write a top hat emulator sometime.
