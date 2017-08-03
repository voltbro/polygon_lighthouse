// https://github.com/tinkerspy/Automaton
#include <Automaton.h> 

//https://github.com/cyborg5/IRLib2
#include <IRLibSendBase.h> 
#include <IRLib_P02_Sony.h>   
#include <IRLibCombo.h>

IRsend IRSender;

Atm_step step;
Atm_timer timer;
Atm_led led[3];
Atm_button button;

const unsigned int led_pins[3] = {10,11,12};
const unsigned int button_pin = 2;

byte ir_signals[3] = {0x70, 0x80, 0x90};
byte ir_signal = ir_signals[0];

void step_callback( int idx, int v, int up ) {
  //turn off all leds
  for ( int i = 0; i < 3; i++ ) {
    led[i].off();
  }
  led[v].on(); //turn on step led

  //change IR signal
  ir_signal = ir_signals[v];
  
}

void timer_callback( int idx, int v, int up ) {
  IRSender.send(SONY,ir_signal, 8);
}

void setup() {
  
  step.begin();
  
  for(int i=0; i<3; i++){
    led[i].begin( led_pins[i] ); //Create led`s
    step.onStep( i, step_callback ); //Create callback for steps
  }

  button.begin( button_pin )
    .onPress( step, step.EVT_STEP ); // And a button event

  step.trigger( step.EVT_STEP );// Do first step

  timer.begin( 300 )
    .repeat(-1)
    .onTimer( timer_callback )
    .start();

}

void loop() {
  automaton.run();
}
