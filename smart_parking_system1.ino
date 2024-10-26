#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define t1 10
#define t2 9
#define t3 8
#define t4 13

int distanceThreshold = 100;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  Serial.begin(9600);
}

long readDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void loop() {
  float d1 = 0.01723 * readDistance(t1, t1);
  float d2 = 0.01723 * readDistance(t2, t2);
  float d3 = 0.01723 * readDistance(t3, t3);
  float d4 = 0.01723 * readDistance(t4, t4);

  Serial.println("d1 = " + String(d1) + "cm");
  Serial.println("d2 = " + String(d2) + "cm");
  Serial.println("d3 = " + String(d3) + "cm");
  Serial.println("d4 = " + String(d4) + "cm");

  int freeSlots = (d1 > distanceThreshold) + (d2 > distanceThreshold) + 
                  (d3 > distanceThreshold) + (d4 > distanceThreshold);

  lcd.clear();
  
  if (freeSlots == 4) {
    lcd.setCursor(0, 0);
    lcd.print("4 Slots Free");
    lcd.setCursor(0, 1);
    lcd.print("Slot 1 2 3 4 Free");
  } 
  else if (freeSlots == 3) {
    lcd.setCursor(0, 0);
    lcd.print("3 Slots Free");
    lcd.setCursor(0, 1);
    if (d1 > distanceThreshold && d2 > distanceThreshold && d3 > distanceThreshold) lcd.print("Slot 1 2 3 Free");
    else if (d1 > distanceThreshold && d2 > distanceThreshold && d4 > distanceThreshold) lcd.print("Slot 1 2 4 Free");
    else if (d1 > distanceThreshold && d3 > distanceThreshold && d4 > distanceThreshold) lcd.print("Slot 1 3 4 Free");
    else lcd.print("Slot 2 3 4 Free");
  }
  else if (freeSlots == 2) {
    lcd.setCursor(0, 0);
    lcd.print("2 Slots Free");
    lcd.setCursor(0, 1);
    if (d1 > distanceThreshold && d2 > distanceThreshold) lcd.print("Slot 1 & 2 Free");
    else if (d1 > distanceThreshold && d3 > distanceThreshold) lcd.print("Slot 1 & 3 Free");
    else if (d1 > distanceThreshold && d4 > distanceThreshold) lcd.print("Slot 1 & 4 Free");
    else if (d2 > distanceThreshold && d3 > distanceThreshold) lcd.print("Slot 2 & 3 Free");
    else if (d2 > distanceThreshold && d4 > distanceThreshold) lcd.print("Slot 2 & 4 Free");
    else lcd.print("Slot 3 & 4 Free");
  }
  else if (freeSlots == 1) {
    lcd.setCursor(0, 0);
    lcd.print("1 Slot Free");
    lcd.setCursor(0, 1);
    if (d1 > distanceThreshold) lcd.print("Slot 1 is Free");
    else if (d2 > distanceThreshold) lcd.print("Slot 2 is Free");
    else if (d3 > distanceThreshold) lcd.print("Slot 3 is Free");
    else lcd.print("Slot 4 is Free");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("No Slot Free");
    lcd.setCursor(0, 1);
    lcd.print("Parking Full");
  }

  delay(500);
}
