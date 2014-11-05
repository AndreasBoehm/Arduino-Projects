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
#define RF_TRANSMITTER_POWER 7

// RF Socket Configuration
char rfSystemCode[] = "00001";
char rfSocket1[] = "01000";
char rfSocket2[] = "00100";

decode_results results;
long lastIRCode;

IRrecv irrecv(IR_SENSOR_DATA);
RCSwitch rcSwitch = RCSwitch();

void setup() {
  irrecv.enableIRIn();
  irrecv.blink13(1);
  rcSwitch.enableTransmit(RF_TRANSMITTER_DATA);

  // ensure RF transmitter is not powered
  digitalWrite(RF_TRANSMITTER_POWER, LOW);
  pinMode(RF_TRANSMITTER_POWER, INPUT);
}

void loop() {
  if (irrecv.decode(&results)) {

    // REPEAT last IR code
    if(results.value != REPEAT) {
      lastIRCode = results.value;
    }

    switch(lastIRCode) {
      case HC8300_1ON:
        switchSocketOn(rfSocket1);
        break;

      case HC8300_1OFF:
        switchSocketOff(rfSocket1);
        break;

      case HC8300_2ON:
        switchSocketOn(rfSocket2);
        break;

      case HC8300_2OFF:
        switchSocketOff(rfSocket2);
        break;

      default:
        break;
    }

    irrecv.resume();
  }
}

void switchSocketOn(char socketCode[]) {
  switchSocket(true, socketCode);
}

void switchSocketOff(char socketCode[]) {
  switchSocket(false, socketCode);
}

void switchSocket(boolean on, char socketCode[]) {
  // Power the RF Transmitter
  pinMode(RF_TRANSMITTER_POWER, OUTPUT);
  digitalWrite(RF_TRANSMITTER_POWER, HIGH);

  if(on) {
    rcSwitch.switchOn(rfSystemCode, socketCode);
  } else {
    rcSwitch.switchOff(rfSystemCode, socketCode);
  }

  // Unpower the RF Transmitter
  digitalWrite(RF_TRANSMITTER_POWER, LOW);
  pinMode(RF_TRANSMITTER_POWER, INPUT);
}
