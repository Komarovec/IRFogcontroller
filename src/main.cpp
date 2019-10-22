#include <Arduino.h>
#include <IRremote.h>

//IR Receiver pin
constexpr int RECV_PIN = 2;

//Relay HIGH --> OFF; LOW --> ON (FOGGING)
constexpr int FOG_PIN = 4;

//Power pin for IR Decoder
constexpr int POWER_PIN = 3;

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

//Is fog pin on ?
bool isFogging = false;

//Fog timer
constexpr int FOG_DELAY = 1000;
unsigned long wait_time = 0;

void endFog() {
  //End fog
  isFogging = false;
  digitalWrite(FOG_PIN, HIGH);
}

void startFog() {
  //Start fog
  isFogging = true;
  digitalWrite(FOG_PIN, LOW);

  //Increase timer for fogging
  wait_time = millis() + FOG_DELAY;
}

void setup(){
  //Prepare power pin
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);

  //Do not fog when started
  pinMode(FOG_PIN, OUTPUT);
  digitalWrite(FOG_PIN, HIGH);
  isFogging = false;

  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  //Check timer
  if(wait_time < millis() and isFogging) {
    endFog();
  }

  //Decode
  if (irrecv.decode(&results)){
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        //Switch between few values --> If ever needed... now all does the same.
        switch(results.value){
          case 0xFF6897:
            startFog();
            break ;  
          case 0xFF30CF:
            startFog();
            break ;
          case 0xFF18E7:
            startFog();
            break ;
          case 0xFF7A85:
            startFog();
            break ;
          case 0xFF10EF:
            startFog();
            break ;
          case 0xFF38C7:
            startFog();
            break ;
          case 0xFF5AA5:
            startFog();
            break ;
          case 0xFF42BD:
            startFog();
            break ;
          case 0xFF4AB5:
            startFog();
            break ;
          case 0xFF52AD:
            startFog();
            break ;      
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}
