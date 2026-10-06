# Smart Air Quality & Gas Safety Monitor

An Arduino-based embedded system that monitors ambient air quality, gas concentration, temperature, and humidity in real time — and provides tiered visual alerts (safe / caution / danger) via LED indicators and an LCD display.

## What It Does

- Reads temperature and humidity via a DHT11 sensor
- Reads air quality (CO2, smoke, ammonia, etc.) via an MQ135 sensor
- Reads gas/alcohol concentration via an MQ3 sensor
- Displays live readings on a 16x2 I2C LCD
- Indicates system status using three LEDs:
  Green — Safe
  Blue — Caution
  Red — Danger

## Hardware Used

Arduino UNO SMD,
DHT11 Temperature & Humidity Sensor,
MQ135 Air Quality Sensor,
MQ3 Gas/Alcohol Sensor,
16x2 LCD (I2C, AIP31068 controller),
Three LEDs (Green, Blue, Red),
Resistors (1K, 2.2K),
Breadboard and jumper wires

## Libraries Required

- `DHT sensor library` (Adafruit) + `Adafruit Unified Sensor` dependency
- `LiquidCrystal_AIP31068` (for the AIP31068-based I2C LCD)
