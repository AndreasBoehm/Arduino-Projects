#include <SD.h>
#include "DHT.h"

#define DHT_SENSOR_DATA_PIN 2
#define DHT_SENSOR_POWER_PIN 4

#define SD_CS_PIN 10

DHT dht;

void setup() {
    Serial.begin(9600);
    pinMode(DHT_SENSOR_POWER_PIN, OUTPUT);
    pinMode(SD_CS_PIN, OUTPUT);

    if(!SD.begin(SD_CS_PIN)) {
        //Serial.println("Card failed, or not present");
        return;
    }
    //Serial.println("Card initialized!");
}

void loop() {
    digitalWrite(DHT_SENSOR_POWER_PIN, HIGH);
    //Serial.println("Powered DHT Sensor - waiting some seconds...");
    delay(1000);

    //Serial.println("Setup DHTLib - waiting 15 seconds...");
    dht.setup(DHT_SENSOR_DATA_PIN);
    delay(dht.getMinimumSamplingPeriod());
    delay(15000);

    String dataString = "";
    dataString += dht.getStatusString();
    dataString += "\t";
    dataString += dht.getHumidity();
    dataString += "\t";
    dataString += dht.getTemperature();

    Serial.println(dataString);

    File logFile = SD.open("datalog.txt", FILE_WRITE);

    if(logFile) {
        logFile.println(dataString);
        logFile.close();
    } else {
      //  Serial.println("error opening datalog.txt");
    }

    digitalWrite(DHT_SENSOR_POWER_PIN, LOW);
    //Serial.println("Unpowered DHT Sesnsor - waiting 120 seconds...");
    delay(120000);
}

