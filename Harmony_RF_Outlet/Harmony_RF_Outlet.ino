/*
 * Build your own 'One-For-All HC8300 Light Control' with your Arduino!
 * Version 0.1
 *
 * This sketch let you control wireless outlets with your Logitech Harmony Remote.
 * You need to add a 'One-For-All HC8300 Light Control'-Device to your Harmony,
 * because the IR-codes from this devices remote are used here.
 */
#include "One_For_All_HC_8300_IR_Codes.h"

// Libraries
#include <RCSwitch.h>
#include <IRremote.h>
#define RCSwitchDisableReceiving

// PIN configuration
#define IR_SENSOR_PIN 2
#define RF_TRANSMITTER_PIN 4
#define RF_TRANSMITTER_POWER 7

// RF Socket Configuration
char rfSystemCode[] = "00001";
char rfSocket1[] = "01000";

decode_results results;

IRrecv irrecv(IR_SENSOR_PIN);
RCSwitch rcSwitch = RCSwitch();

void setup() {
  irrecv.enableIRIn();
  irrecv.blink13(1);
  rcSwitch.enableTransmit(RF_TRANSMITTER_PIN);
  pinMode(RF_TRANSMITTER_POWER, OUTPUT);
  digitalWrite(RF_TRANSMITTER_POWER, HIGH);
}

void loop() {
  if (irrecv.decode(&results)) {

    switch(results.value) {
      case HC8300_1ON:
        rcSwitch.switchOn(rfSystemCode, rfSocket1);
        break;

      case HC8300_1OFF:
        rcSwitch.switchOff(rfSystemCode, rfSocket1);
        break;

      default:
        break;
    }

    irrecv.resume();
  }

}
