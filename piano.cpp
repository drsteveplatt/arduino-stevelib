// PianoAnalyzer
//  April 2019
//  Simple analysis for cheap piano keyboard
//  Two cables to the keyboard itself: 8 and 6 lines
//  Four additional lines.

//
// Version 0.2:  Simple keyboard probe and Serial output test
// Version 0.1:  Has enough capacity to test out tha we are picking the correct ports on the Mega
//
//  Current assumption:
//    8 lines are response lines
//    6 lines are strobes to keyboard
//    4 lines are strobes to the keyboard unit's "rhythm" etc. buttons

//
// Coded for a mega.  We would have liked to use a Nano, but the digital line
// count was a little tight.  If only all of the analog lines could be used for digital...
//

// Port usage:
//    D22-D29 (port PA, 0-7): eight data return lines
//    D30-D33 (port PC, 7-4): four strobe lines for control keys
//    D42-D47 (port PL, 7-2): six strobe lines for keyboard

#include "Streaming.h"

int dataPorts[] = {22, 23, 24, 25, 26, 27, 28, 29, -1};
int keyStrobePorts[] = {42, 43, 44, 45, 46, 47, -1};
int buttonStrobePorts[] = {30, 31, 32, 33, 34, -1};

void setup() {
  // Set mode on all ports
  Serial.begin(9600);
  Serial << "Running." << endl;
  initDataLines(dataPorts);
  initStrobeLines(keyStrobePorts);
  initStrobeLines(buttonStrobePorts);

}

void initDataLines(int lines[]) {
  // lines is a -1-terminated array of ports.  They are set to input.
  for(int i=0; lines[i]>=0; i++)
    pinMode(lines[i], INPUT_PULLUP);
}

void initStrobeLines(int lines[]) {
  // lines is a -1-terminated array of ports.  They are set to output.
  for(int i=0; lines[i]>=0; i++) {
    pinMode(lines[i], OUTPUT);
    digitalWrite(lines[i],HIGH);
  }
}

// Strobe a set of strobes and report on the keys pressed.
// Only one key pressed at a time
bool keyPressed = false;
int lastKey = 0;
inline int kbencode(int strobe, int dataLine) { return (strobe<<8) + dataLine; }
void checkKeys(char prefix, int strobePorts[]) {
  int stat;
  int thisKey;
  // perform one cycle of strobing all strobe lines and sensing all data lines for activity
  for(int strobe=0; strobePorts[strobe]>=0; strobe++) {
    // Force the strobe low to actiate it, then check all of the data lines
    digitalWrite(strobePorts[strobe], LOW);
    for(int dataLine=0; dataPorts[dataLine]>=0; dataLine++) {
      // checking data lines...
      stat=digitalRead(dataPorts[dataLine]);
      thisKey = kbencode(strobePorts[strobe],dataPorts[dataLine]);
      if(stat==LOW && !keyPressed) {
        // key hit, save value, mark as "hit", report results
        keyPressed = true;
        lastKey = thisKey;
        Serial << "Down: " << prefix << strobe << " " << dataLine << " " << thisKey
//          << (stat==LOW?" LOW ":" HIGH ") << (keyPressed?"pressed ":"!pressed ")
//          << lastKey << " " << thisKey
          << endl;
      } else if(stat==HIGH && keyPressed && thisKey==lastKey) {
        // key released, mark as unpressed and report the (saved) key as being up
        keyPressed = false;
        Serial << "Up: " << prefix << strobe << " " << dataLine
 //         << (stat==LOW?" LOW ":" HIGH ") << (keyPressed?"pressed ":"!pressed ")
 //         << lastKey << " " << thisKey
          << endl;
      }
    } // end for dataPort
    digitalWrite(strobePorts[strobe], HIGH);
  } // end for strobe
}

void loop() {
  checkKeys('K',keyStrobePorts);
  checkKeys('B',buttonStrobePorts);
}
