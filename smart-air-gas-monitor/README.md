# Smart Air Quality & Gas Safety Monitor

An Arduino-based embedded system that monitors ambient air quality, gas concentration, temperature, and humidity in real time — and provides tiered visual alerts (safe / caution / danger) via LED indicators and an LCD display.

Built using the PES University Electronic Starter Kit Combo-5.

## What It Does

- Reads temperature and humidity via a DHT11 sensor
- Reads air quality (CO2, smoke, ammonia, etc.) via an MQ135 sensor
- Reads gas/alcohol concentration via an MQ3 sensor
- Displays live readings on a 16x2 I2C LCD, cycling through each metric
- Indicates system status using three LEDs:
  - 🟢 Green — Safe
  - 🔵 Blue — Caution
  - 🔴 Red — Danger
- Threshold logic is calibrated against real sensor baselines (see `docs/calibration.md`)

## Hardware Used

| Component | Qty | Notes |
|---|---|---|
| Arduino UNO SMD | 1 | |
| DHT11 Temperature & Humidity Sensor | 1 | Module version (3-pin) |
| MQ135 Air Quality Sensor | 1 | Analog output only |
| MQ3 Gas/Alcohol Sensor | 1 | Analog output only |
| 16x2 LCD (I2C, AIP31068 controller) | 1 | I2C address 0x3E |
| LEDs (Green, Blue, Red) | 3 | With current-limiting resistors |
| Resistors (1K, 2.2K) | Several | LED current limiting |
| Breadboard + jumper wires | — | |

## Wiring

See [`docs/wiring.md`](docs/wiring.md) for the full pin mapping.

## Libraries Required

- `DHT sensor library` (Adafruit) + `Adafruit Unified Sensor` dependency
- `LiquidCrystal_AIP31068` (for the AIP31068-based I2C LCD)

## Project Status

- [x] DHT11 sensor integrated and tested
- [x] MQ135 sensor integrated and tested
- [x] MQ3 sensor integrated and tested
- [x] LCD integrated and tested
- [x] Status LEDs integrated and tested
- [ ] Threshold calibration in progress
- [ ] Final integrated sketch

## Future Scope

- **Bluetooth connectivity (HC-05)**: stream live sensor data to a phone/PC for remote monitoring and logging. Attempted during development; deferred due to pairing issues — wiring notes preserved in `docs/bluetooth-notes.md` for future revisit.
- **Automated ventilation response**: use a relay to automatically switch on an exhaust fan when gas/air quality crosses the danger threshold, turning this from a monitoring system into a monitoring *and* response system.

## Repository Structure

```
├── code/
│   └── smart_air_gas_monitor.ino   # Main integrated sketch
├── docs/
│   ├── wiring.md                   # Full pin mapping and wiring notes
│   ├── calibration.md              # Sensor baseline/threshold notes
│   └── bluetooth-notes.md          # HC-05 wiring notes for future use
├── images/                          # Photos/diagrams of the build
└── README.md
```
