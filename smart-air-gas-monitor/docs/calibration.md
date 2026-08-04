# Sensor Calibration Notes

Thresholds for MQ135 (air quality) and MQ3 (gas) are sensor-unit-specific and must be calibrated against real readings rather than using generic values.

## Method

1. Run the raw analog read sketch (below) and let sensors sit undisturbed for 2-3 minutes to record a baseline in normal room air.
2. Trigger a response (e.g., hand sanitizer near MQ3, blown-out match/incense near MQ135) and record the peak value.
3. Set `CAUTION` threshold at roughly 1.5-2x baseline, and `DANGER` threshold at roughly 2.5-3x baseline (or at the observed triggered peak).

## Raw Reading Sketch

```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  int mq135 = analogRead(A0);
  int mq3 = analogRead(A1);
  Serial.print("MQ135: ");
  Serial.print(mq135);
  Serial.print("   MQ3: ");
  Serial.println(mq3);
  delay(1000);
}
```

## Recorded Values

_To be filled in once calibration is complete:_

| Sensor | Baseline (room air) | Caution Threshold | Danger Threshold | Triggered Peak |
|---|---|---|---|---|
| MQ135 | TBD | TBD | TBD | TBD |
| MQ3 | TBD | TBD | TBD | TBD |
