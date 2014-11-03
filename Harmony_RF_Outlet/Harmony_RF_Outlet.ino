/*
 * Build your own 'One-For-All HC8300 Light Control' with your Arduino!
 * Version 0.1
 *
 * This sketch let you control wireless outlets with your Logitech Harmony Remote.
 * You need to add a 'One-For-All HC8300 Light Control'-Device to your Harmony,
 * because the IR-codes from this devices remote are used here.
 */
#include <RCSwitch.h>
#include <IRremote.h>

#define RCSwitchDisableReceiving
#define IR_PIN 2
#define RF_PIN 4

/**
 * RF Socket Configuration
 */
char* rfSystemCode = "00001";
char* rfSocket1 = "01000";

/**
 * IR Code Configuration
 */
const unsigned long socket1On = 3895178441;
const unsigned long socket1Off = 254685380;
const unsigned long socket2On = 326842813;
const unsigned long socket2Off = 981317048;

decode_results results;

IRrecv irrecv(IR_PIN);
RCSwitch rcSwitch = RCSwitch();

void setup() {
  irrecv.enableIRIn();
  irrecv.blink13(1);
  rcSwitch.enableTransmit(RF_PIN);
}

void loop() {
  if (irrecv.decode(&results)) {

    switch(results.value) {
      case socket1On:
        rcSwitch.switchOn(rfSystemCode, rfSocket1);
        break;
      case socket1Off:
        rcSwitch.switchOff(rfSystemCode, rfSocket1);
        break;
      default:
        break;
    }

    irrecv.resume();
  }

}
