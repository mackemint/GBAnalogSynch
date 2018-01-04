/*
 * This version of Arduinoboy has functionality to use a Note message to the Teensy trigger an analog sync clock
 * Simply set your sequencer to output note CLOCK_NOTE (default C-3) on MIDI channel MIDI_CHANNEL (default channel 16) 
 * and the Gameboy sync mode to Analog sync, and the Gameboy will slave to the pulses originating from the Teensy.
 */

const unsigned int LED = 13;
const unsigned int CLOCK_NOTE = 0;
const unsigned int MIDI_CHANNEL = 16;

// Gameboy Analog sync in pin
const unsigned int pinGBSerialOut = 17;

// State of Analog sync pin
bool pinState = LOW;

// Init times
unsigned long timeStampOnNoteOn = 0; //Set when OnNoteOn event is triggered
unsigned long pulseLength = 15; // 15ms pulse length (timer interrupt in microseconds)

void setup() 
{
  //Set listener
  usbMIDI.setHandleNoteOn(OnNoteOn);
  pinMode(pinGBSerialOut, OUTPUT);     
  pinMode(LED, OUTPUT);    
}

void loop() 
{
  usbMIDI.read(MIDI_CHANNEL); // USB MIDI receive 
  isTimeOut(millis()); //Time to give a LOW?
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

