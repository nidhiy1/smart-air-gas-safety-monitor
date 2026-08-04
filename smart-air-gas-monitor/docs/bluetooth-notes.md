# HC-05 Bluetooth — Future Scope Notes

Bluetooth streaming was attempted during initial development but deferred due to pairing issues (module's LED blinked correctly, indicating power was fine, but the device did not appear when scanning from a phone). Preserved here for a future revisit.

## Intended Wiring

| HC-05 Pin | Arduino Connection |
|---|---|
| VCC | 5V |
| GND | GND |
| TX | Arduino Pin 10 (direct) |
| RX | Arduino Pin 11, through a voltage divider |

### Voltage Divider (required for RX line)

HC-05's RX pin expects 3.3V logic; Arduino's TX outputs 5V. A voltage divider steps this down:

```
Arduino Pin 11 --[1K resistor]-- (junction) --[2.2K resistor]-- GND
                                     |
                                 HC-05 RX
```

- The junction point (between both resistors) connects to HC-05 RX.
- This was correctly wired and verified against the resistor color bands (1K = brown-black-red-gold, 2.2K = red-red-red-gold).

## Suspected Issues to Investigate Next Time

- HC-05 may need to be power-cycled while holding its onboard button to enter pairing/AT-command mode on some clone boards.
- Some HC-05 clones ship already paired to a previous host or in an unresponsive state and need an AT command reset.
- Try verifying communication via a second Arduino or USB-to-serial adapter directly (bypassing phone pairing) to isolate whether the issue is the module itself or the phone-side pairing.

## Test Sketch Used

```cpp
#include <SoftwareSerial.h>
SoftwareSerial btSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  Serial.println("Bluetooth test ready");
}

void loop() {
  if (btSerial.available()) {
    Serial.write(btSerial.read());
  }
  if (Serial.available()) {
    btSerial.write(Serial.read());
  }
}
```
