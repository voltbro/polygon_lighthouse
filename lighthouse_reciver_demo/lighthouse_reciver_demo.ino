//https://github.com/cyborg5/IRLib2
#include <IRLibDecodeBase.h> 
#include <IRLib_P02_Sony.h>  
#include <IRLibCombo.h>

IRdecode myDecoder;

// Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop
#include <IRLibRecv.h> 
IRrecv myReceiver(2);  //pin number for the receiver

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}
void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) { 
    myDecoder.decode();           //Decode it
    if(myDecoder.protocolNum == SONY){
      Serial.println(myDecoder.value,HEX);
    }
    //myDecoder.dumpResults(true);
    myReceiver.enableIRIn();      //Restart receiver
  }
}
