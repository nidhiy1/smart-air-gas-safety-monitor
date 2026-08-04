/*
  SMART AIR QUALITY & GAS SAFETY MONITOR

  STATUS: Work in progress — sensors and display individually tested.
  Threshold values below are placeholders pending calibration
  (see docs/calibration.md). Bluetooth and relay deferred to future scope
  (see docs/bluetooth-notes.md and README "Future Scope").

  Components: DHT11, MQ135, MQ3, 16x2 I2C LCD (AIP31068, addr 0x3E),
  3 status LEDs (Green/Blue/Red)
*/

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_AIP31068_I2C.h> // adjust include name to match installed library

// ---------- PIN DEFINITIONS ----------
#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ135_PIN A0
#define MQ3_PIN A1
#define GREEN_PIN 5
#define BLUE_PIN 6
#define RED_PIN 7

// ---------- THRESHOLDS (PLACEHOLDER — calibrate per docs/calibration.md) ----------
int MQ135_CAUTION = 300;
int MQ135_DANGER  = 600;
int MQ3_CAUTION   = 300;
int MQ3_DANGER    = 600;

// ---------- OBJECTS ----------
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_AIP31068_I2C lcd(0x3E, 16, 2); // adjust constructor to match installed library's API

unsigned long lastReadTime = 0;
unsigned long lastDisplaySwitch = 0;
int displayMode = 0; // 0 = temp/humidity, 1 = air quality, 2 = gas

float temperature = 0, humidity = 0;
int mq135Value = 0, mq3Value = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  delay(2000); // let sensors stabilize briefly
  lcd.clear();
}

void loop() {
  if (millis() - lastReadTime > 2000) {
    lastReadTime = millis();
    readSensors();
    evaluateStatus();
  }

  if (millis() - lastDisplaySwitch > 2500) {
    lastDisplaySwitch = millis();
    displayMode = (displayMode + 1) % 3;
    updateLCD();
  }
}

void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  mq135Value = analogRead(MQ135_PIN);
  mq3Value = analogRead(MQ3_PIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 read failed!");
  }
}

void updateLCD() {
  lcd.clear();
  if (displayMode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
  } else if (displayMode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Air Quality:");
    lcd.setCursor(0, 1);
    lcd.print("MQ135: ");
    lcd.print(mq135Value);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Gas Level:");
    lcd.setCursor(0, 1);
    lcd.print("MQ3: ");
    lcd.print(mq3Value);
  }
}

void evaluateStatus() {
  bool danger = (mq135Value >= MQ135_DANGER) || (mq3Value >= MQ3_DANGER);
  bool caution = (mq135Value >= MQ135_CAUTION) || (mq3Value >= MQ3_CAUTION);

  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  if (danger) {
    digitalWrite(RED_PIN, HIGH);
  } else if (caution) {
    digitalWrite(BLUE_PIN, HIGH);
  } else {
    digitalWrite(GREEN_PIN, HIGH);
  }
}
