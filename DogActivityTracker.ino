#include <LiquidCrystal.h>

class IMUdata {
public:
  float x, y, z;
};

class SimulatedQMI8658 {
private:
  bool motionDetected;
  void (*wakeupCallback)();

public:
  SimulatedQMI8658() : motionDetected(false), wakeupCallback(nullptr) {}

  bool begin() {
    return true;
  }

  bool readFromFifo(IMUdata* acc, int accCount, IMUdata* gyr, int gyrCount) {
    for (int i = 0; i < accCount; i++) {
      acc[i].x = random(-1000, 1000) / 1000.0;
      acc[i].y = random(-1000, 1000) / 1000.0;
      acc[i].z = random(-1000, 1000) / 1000.0;
    }
    for (int i = 0; i < gyrCount; i++) {
      gyr[i].x = random(-5000, 5000) / 100.0;
      gyr[i].y = random(-5000, 5000) / 100.0;
      gyr[i].z = random(-5000, 5000) / 100.0;
    }
    return true;
  }

  void setWakeupMotionEventCallBack(void (*callback)()) {
    wakeupCallback = callback;
  }

  void simulateMotion() {
    if (random(100) < 20 && !motionDetected) {
      motionDetected = true;
      if (wakeupCallback) wakeupCallback();
    } else {
      motionDetected = false;
    }
  }
};

String classifyActivity(IMUdata* acc, int count) {
  float total = 0;
  for (int i = 0; i < count; i++) {
    total += abs(acc[i].x) + abs(acc[i].y) + abs(acc[i].z);
  }
  float avg = total / (count * 3);

  if (avg < 0.1) return "Resting";
  else if (avg < 0.5) return "Walking";
  else if (avg < 1.0) return "Running";
  else return "Playing";
}

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String logData[10];
int logIndex = 0;

SimulatedQMI8658 sensor;
unsigned long lastLogTime = 0;

void motionCallback() {
  Serial.println("Motion detected!");
  lcd.setCursor(0, 1);
  lcd.print("Motion Detected ");
}

void setup() {
  Serial.begin(9600);
  sensor.begin();
  sensor.setWakeupMotionEventCallBack(motionCallback);

  lcd.begin(16, 2);
  lcd.print("Dog Tracker Ready");
  Serial.println("Dog Activity Tracker started.");
}

void loop() {
  static IMUdata acc[10], gyr[10];

  sensor.simulateMotion();

  sensor.readFromFifo(acc, 10, gyr, 10);

  if (millis() - lastLogTime > 10000) {
    String activity = classifyActivity(acc, 10);
    Serial.print("Activity: ");
    Serial.println(activity);

    lcd.setCursor(0, 0);
    lcd.print("Activity:        "); 
    lcd.setCursor(10, 0);
    lcd.print(activity);

    if (logIndex < 10) {
      logData[logIndex++] = activity;
    } else {
      for (int i = 0; i < 9; i++) logData[i] = logData[i + 1];
      logData[9] = activity;
    }

    lastLogTime = millis();
  }

  delay(500);
}
