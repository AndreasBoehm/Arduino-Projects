/*
 * Build your own 'One-For-All HC8300 Light Control' with your Arduino!
 * Version 0.2
 *
 * This sketch lets you control wireless outlets with your Logitech Harmony Remote.
 * You need to add a 'One-For-All HC8300 Light Control'-Device to your Harmony,
 * because the IR-codes from this devices remote are used here.
 */
#include "One_For_All_HC_8300_IR_Codes.h"

// Libraries
#include <IRremote.h>
#include <RCSwitch.h>
#define RCSwitchDisableReceiving

// PIN Configuration
#define IR_SENSOR_DATA 2
#define RF_TRANSMITTER_DATA 4

// RF Socket Configuration
char rfSystemCode[] = "00001";
char rfSocket1[] = "10000"; // Main Poweroutlet
char rfSocket2[] = "01000"; // Couch Lamps
char rfSocket3[] = "00100"; // TV Lamp

// Delay
unsigned long powerOffDelay = 180000; // 3 mins

decode_results results;
long lastIRCode;

IRrecv irrecv(IR_SENSOR_DATA);
RCSwitch rcSwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(1);
  rcSwitch.enableTransmit(RF_TRANSMITTER_DATA);
}

void loop() {
  if (irrecv.decode(&results)) {

    // REPEAT last IR code
    if(results.value != REPEAT) {
      lastIRCode = results.value;
    }

    Serial.print("Received code ");
    Serial.println(lastIRCode, HEX);

    switch(lastIRCode) {
      case HC8300_1ON: // Socket1 ON
        Serial.println("Switching Main-Poweroutlet on");
        rcSwitch.switchOn(rfSystemCode, rfSocket1);
        break;

      case HC8300_1OFF: // Socket1 OFF
        Serial.println("Switching Main-Poweroutlet off");
        rcSwitch.switchOff(rfSystemCode, rfSocket1);
        break;

      case HC8300_2ON: // Socket2 ON
        Serial.println("Switching Couch Lamps on");
        rcSwitch.switchOn(rfSystemCode, rfSocket2);
        break;

      case HC8300_2OFF: // Socket2 OFF
        Serial.println("Switching Couch Lamps off");
        rcSwitch.switchOff(rfSystemCode, rfSocket2);
        break;

      case HC8300_3ON: // Socket3 ON
        Serial.println("Switching TV Lamp on");
        rcSwitch.switchOn(rfSystemCode, rfSocket3);
        break;

      case HC8300_3OFF: // Socket3 OFF
        Serial.println("Switching TV Lamp off");
        rcSwitch.switchOff(rfSystemCode, rfSocket3);
        break;

      case HC8300_9ON: // ALL ON
        rcSwitch.switchOn(rfSystemCode, rfSocket1);
        rcSwitch.switchOn(rfSystemCode, rfSocket2);
        rcSwitch.switchOn(rfSystemCode, rfSocket3);
        break;

      case HC8300_9OFF: // ALL OFF
        Serial.println("Switching All OFF");
        rcSwitch.switchOff(rfSystemCode, rfSocket3);
        rcSwitch.switchOff(rfSystemCode, rfSocket2);
        rcSwitch.switchOff(rfSystemCode, rfSocket1);
        break;

      case HC8300_B1Off: // ALL OFF with Delay
        delay(powerOffDelay);
        Serial.println("Switching All OFF");
        rcSwitch.switchOff(rfSystemCode, rfSocket3);
        rcSwitch.switchOff(rfSystemCode, rfSocket2);
        rcSwitch.switchOff(rfSystemCode, rfSocket1);
        break;

      default:
        break;
    }

    irrecv.resume();
  }
}
