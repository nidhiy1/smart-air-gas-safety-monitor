# Wiring Guide

## DHT11 (Temperature & Humidity)

| DHT11 Pin | Arduino Pin |
|---|---|
| G (GND) | GND |
| V (VCC) | 5V |
| D (Data) | Digital Pin 2 |

## LCD — RG1602A-19-I2C (AIP31068 controller)

| LCD Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

- Library: `LiquidCrystal_AIP31068`
- I2C Address: `0x3E`

## MQ135 (Air Quality)

| MQ135 Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| AO | A0 |
| DO | Not connected |

## MQ3 (Gas/Alcohol)

| MQ3 Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| AO | A1 |
| DO | Not connected |

## Status LEDs

Using 3 individual LEDs (not a single RGB package):

| LED | Arduino Pin | Meaning |
|---|---|---|
| Green | Digital Pin 5 | Safe |
| Blue | Digital Pin 6 | Caution |
| Red | Digital Pin 7 | Danger |

Each LED: long leg (anode) → resistor → Arduino pin; short leg (cathode) → GND.

## Notes

- MQ135 and MQ3 need a warm-up period after power-up before readings stabilize — avoid taking readings in the first few minutes.
- The DHT11 requires `DHTTYPE` to be set to `DHT11` (not `DHT22`) in code.
