/*
 * This version of Arduinoboy has functionality to use a Note message to the Teensy trigger an analog sync clock
 * Simply set your sequencer to output note CLOCK_NOTE (default C-3) on MIDI channel MIDI_CHANNEL (default channel 16) 
 * and the Gameboy sync mode to Analog sync, and the Gameboy will slave to the pulses originating from the Teensy.
 */


// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
const unsigned int LED = 13;
const unsigned int CLOCK_NOTE = 36;
const unsigned int MIDI_CHANNEL = 15;

// Gameboy Clock pin TODO
const unsigned int pinGBSerialOut = 17;

// Flag for incoming Note message
bool pinState = LOW;

// Init time stamps
unsigned long timeStampOnNoteOn = 0; //Set when OnNoteOn event is triggered
unsigned long pulseLength = 15; // 15ms pulse length (timer interrupt in microseconds)

void setup() 
{
  usbMIDI.setHandleNoteOn(OnNoteOn);
  pinMode(pinGBSerialOut, OUTPUT);     
  pinMode(LED, OUTPUT);    
}

void loop() 
{
  usbMIDI.read(MIDI_CHANNEL); // USB MIDI receive 
  isTimeOut(millis());
}

void isTimeOut(unsigned long currentTimeMillis)
{
  if((currentTimeMillis - timeStampOnNoteOn) > pulseLength) 
  {
    pinState = LOW;
  }
  digitalWrite(pinGBSerialOut, pinState);
  digitalWrite(LED, pinState);
  
}

void OnNoteOn(byte channel, byte note, byte velocity) 
{
  if (channel == MIDI_CHANNEL && note == CLOCK_NOTE && velocity > 0)
  {
    timeStampOnNoteOn = millis();    
    pinState = HIGH;
  }
}

