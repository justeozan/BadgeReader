#include <Wire.h>
#include <MFRC522.h>
#include <SPI.h>
#include <WiFi.h>

#define RST_PIN 2
#define SS_PIN  6

MFRC522 mfrc522(SS_PIN, RST_PIN);

const char *ssid = "Didine";
const char *password = "hotspotDidine";
const char *raspberryPiIP = "192.168.1.2";
const int raspberryPiPort = 12345;
IPAddress staticIP(192, 168, 1, 3);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

void setup() {
  Serial.begin(921600);
  Serial.println("\nBienvenue");
  Wire.begin();
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  connectToWiFi();
  WiFi.config(staticIP, gateway, subnet, dns);
  Serial.println(WiFi.localIP());
  delay(100);
  Serial.setTimeout(1000);
}

void loop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Carte détectée avec UID : ");
    printUID(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();

    sendDataToRaspberryPi(getUIDString(mfrc522.uid.uidByte, mfrc522.uid.size));

    mfrc522.PICC_HaltA();
  }
}

void printUID(byte* uid, byte size) {
  for (byte i = 0; i < size; i++) {
    Serial.print("0x");
    if (uid[i] < 0x10) Serial.print("0");
    Serial.print(uid[i], HEX);
    if (i < size - 1) Serial.print(", ");
  }
}

String getUIDString(byte* uid, byte size) {
  String uidString = "";
  for (byte i = 0; i < size; i++) {
    if (uid[i] < 0x10) uidString += "0";
    uidString += String(uid[i], HEX);
  }
  return uidString;
}

void connectToWiFi() {
  Serial.println("Tentative de connexion au Wifi");
  WiFi.begin(ssid, password);

  Serial.print("Connexion en cours...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnexion WiFi réussi !");
}

void sendDataToRaspberryPi(String data) {
  Serial.println("Sending data to Raspberry Pi: " + data);
  WiFiClient client;
  if (client.connect(raspberryPiIP, raspberryPiPort)) {
    client.print(data);
    client.println();
    String response = client.readString();
    Serial.println("Response from Raspberry Pi: " + response);

    if (response.indexOf("Access Granted") != -1) {
      Serial.println("Accès autorisé !");
      digitalWrite(3, HIGH);
    } else if (response.indexOf("Access Denied") != -1) {
      Serial.println("Accès refusé !");
      digitalWrite(4, HIGH);
    } else {
      Serial.println("Réponse non reconnue");
      digitalWrite(7, HIGH);
    }

    delay(1000);
    client.stop();
  } else {
    Serial.println("Failed to connect to Raspberry Pi");
    digitalWrite(7, HIGH);
  }
}