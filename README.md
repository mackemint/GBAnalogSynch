This Arduino sketch accepts MIDI note 0 (C-2) on MIDI channel 16 and will transmit a 15 ms pulse that can be used as an analog sync signal to slave Volcas, 
POs and LSDJ from a sequencer that doesn't support MIDI sync such as Sunvox, etc.
This is compatible with Arduinoboy for Teensy and has so far only been tested with Teensy 3.1.
