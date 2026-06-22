#include <SPI.h>
#include <SD.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define LDR_PIN A0
#define SD_CS 10

DHT dht(DHTPIN, DHTTYPE);
File dataFile;

int sample = 1;

void setup() {
  Serial.begin(9600);

  dht.begin();

  if (!SD.begin(SD_CS)) {
    Serial.println("SD card failed!");
    return;
  }

  Serial.println("Sample,Temperature,Light");

  // Create CSV file and write header
  dataFile = SD.open("data.csv", FILE_WRITE);

  if (dataFile) {
    dataFile.println("Sample,Temperature,Light");
    dataFile.close();
  }
}

void loop() {

  float temp = dht.readTemperature();
  int lightValue = analogRead(LDR_PIN);

  dataFile = SD.open("data.csv", FILE_WRITE);

  if (dataFile) {
  dataFile.print(sample);
  dataFile.print(",");
  dataFile.print(temp);
  dataFile.print(",");
  dataFile.println(lightValue);

  dataFile.close();
}

  // Print same values to Serial Monitor
  Serial.print(sample);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.println(lightValue);

  sample++;

  delay(300);   // Sample every 3 seconds
}
