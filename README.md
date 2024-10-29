This device presents a NMEA stream via WIFI, so you can link something like a [CAMINO-701 CLASS A AIS Transponder](https://www.svb24.com/en/amec-camino-701-class-a-ais-transponder.html) to your chartplotter like [Navionics](https://play.google.com/store/apps/details?id=it.navionics.singleAppMarineLakesHD&hl=en) without using the AMEC Junction box or any other hardware.

# Description

The ESP32 uses a RS232 module to connect to NMEA. It simulates being a known gateway (in this case just by setting the SSID to `WSK-1-Actisense` and using UDP port `60003`) just to simplify the process, since commercial chartplotters will likely detect it automatically.

<img src="https://github.com/user-attachments/assets/dda1edb5-ed95-4780-bbfb-c2b0caa7341e" height="400">

<img src="https://github.com/user-attachments/assets/32c86b61-fee4-4207-b253-3d4940cbf0cc" height="400">

## Details

The current implementation assumes a DB37 connector (for the AMEC AIS), but it can be adapted to any NMEA output. 

### NMEA wiring

This is also only RX, the wiring and the code does not handle TX.

<img src="https://github.com/user-attachments/assets/ad203725-ea48-4a54-8a1d-1d5b9e69d31d" height="400">

### ESP32 wiring

- RS232 `RX`,`TX` is wired to pin `17`,`16` respectively
- RGB led is wired to pins `22`,`21`,`23`
