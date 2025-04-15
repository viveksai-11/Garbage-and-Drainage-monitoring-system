#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "Airtel Fiber";
const char* pass = "Fiber@1509";

const char* server = "grts.in";

WiFiClient client;

#define echoPin1 D7
#define trigPin1 D6

#define water A0

int wlevel;

TinyGPS gps;

float flat, flon;
unsigned long age;

long duration, distance, bin1, bin2;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(water, INPUT);
  delay(20);
  lcd.clear();
  lcd.print(" SMART DUSTBIN ");
  lcd.setCursor(0, 1);
  lcd.print("    SYSTEM    ");
  delay(1500);
  lcd.clear();
  lcd.print("    using    ");
  lcd.setCursor(0, 1);
  lcd.print("ESP8266 & GPS");
  delay(1000);
  lcd.clear();
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  lcd.clear();
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print("Successfully");
  delay(1500);
  lcd.clear();
  lcd.print("Searching ");
  lcd.setCursor(0, 1);
  lcd.print("GPS Network.....");
  delay(10000);
  lcd.clear();
  lcd.print("**System Ready**");
  delay(1500);
}

String binLevel;

void loop() {
  lcd.clear();
  lcd.print(" Smart Dustbin ");
  lcd.setCursor(0, 1);
  lcd.print("    System    ");
  delay(100);

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (gps.encode(c))
        newData = true;
    }
  }
  //////////////////////////////////////////////////////////////////
  if (newData)
  {
    lcd.clear();
    gps.f_get_position(&flat, &flon, &age);
    lcd.print("LAT:");
    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    lcd.setCursor(0, 1);
    lcd.print("LON:");
    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(1000);
  }

  SonarSensor(trigPin1, echoPin1);
  bin1 = distance;
  lcd.clear();
  lcd.print("Bin 1:");
  lcd.print(bin1);
  lcd.print(" CM");
  delay(1000);

  if (bin1 < 10)
  {
    binLevel = "FULL";

  }
  if (bin1 > 10 && bin1 < 20)
  {
    binLevel = "MEDIUM";
    delay(500);
  }
  if (bin1 > 20 && bin1 < 50)
  {
    binLevel = "EMPTY";
    delay(500);
  }
  int level = analogRead(water);
  delay(500);
  if (level > 900)
  {
    wlevel = 4;
  }
  if (level > 800 && level < 900)
  {
    wlevel = 3;
  }
  if (level > 500 && level < 600)
  {
    wlevel = 2;
  }
  if (level < 600)
  {
    wlevel = 1;
  }

  lcd.clear();
  lcd.print("Bin 1:");
  lcd.print(binLevel);
  lcd.setCursor(0, 1);
  lcd.print("Water Level: ");
  lcd.print(wlevel);
  delay(500);

  if (client.connect(server, 80))
  {
    client.print("GET http://grts.in/iotprojects/ArduinoIOT/PN20/write.php?a1=");
    client.print(String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6));
    client.print("&a2=");
    client.print(String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6));
    client.print("&a3=");
    client.print(String(binLevel));
    client.print("&a4=");
    client.print(String(wlevel));
    client.println();
    delay(1000);
    lcd.setCursor(0, 1);  lcd.print("-- Data Sent -- ");
    delay(1000);
  }
  else
  {
    lcd.setCursor(0, 1);  lcd.print("-- Data Error --");
    delay(1000);
  }
  client.stop();
  delay(500);
}

void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}
