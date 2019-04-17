// pianoKeyboard implemenation
//  April 2019
//  Simple analysis for cheap piano keyboard
//  Two cables to the keyboard itself: 8 and 6 lines
//  Four additional lines.

//
//  Current assumption:
//    8 lines are response lines
//    6 lines are strobes to keyboard
//    45 lines are strobes to the keyboard unit's "rhythm" etc. buttons

//
// Coded for a mega.  We would have liked to use a Nano, but the digital line
// count was a little tight.  If only all of the analog lines could be used for digital...
//

// Port usage:
//    D22-D29 (port PA, 0-7): eight data return lines
//    D30-D33 (port PC, 7-4): four strobe lines for control keys
//    D42-D47 (port PL, 7-2): six strobe lines for keyboard
#include <arduino.h>
#include "pianoKeyboard.h"

static int dataPorts[] = {22, 23, 24, 25, 26, 27, 28, 29, -1};
static int keyStrobePorts[] = {42, 43, 44, 45, 46, 47, -1};
static int buttonStrobePorts[] = {30, 31, 32, 33, 34, -1};

static void initStrobeLines(int lines[]) {
  // lines is a -1-terminated array of ports.  They are set to output.
  for(int i=0; lines[i]>=0; i++) {
    pinMode(lines[i], OUTPUT);
    digitalWrite(lines[i],HIGH);
  }
}
static void initDataLines(int lines[]) {
  // lines is a -1-terminated array of ports.  They are set to input.
  for(int i=0; lines[i]>=0; i++)
    pinMode(lines[i], INPUT_PULLUP);
}

PianoKeyboard::PianoKeyboard(): m_keyDown(false), m_key(KNONE), m_keyChanged(false) {
  initDataLines(dataPorts);
  initStrobeLines(keyStrobePorts);
  initStrobeLines(buttonStrobePorts);
}


inline int kbencode(int strobe, int dataLine) { return (strobe<<8) + dataLine; }

// Strobe a set of strobes and report on the keys pressed.
// Only one key pressed at a time
//bool keyPressed = false;
//int lastKey = 0;
//bool keyChanged;

void PianoKeyboard::checkKeys(int strobePorts[]) {
  int stat;
  int thisKey;

  m_keyChanged = false;
  // perform one cycle of strobing all strobe lines and sensing all data lines for activity
  for(int strobe=0; strobePorts[strobe]>=0; strobe++) {
    // Force the strobe low to actiate it, then check all of the data lines
    digitalWrite(strobePorts[strobe], LOW);
    for(int dataLine=0; dataPorts[dataLine]>=0; dataLine++) {
      // checking data lines...
      stat=digitalRead(dataPorts[dataLine]);
      thisKey = keycodeToKeyVal(kbencode(strobePorts[strobe],dataPorts[dataLine]));
      if(stat==LOW && !m_keyDown) {
        // key hit, save value, mark as "hit", report results
	    m_key = thisKey;
	    m_keyDown = true;
	    m_keyChanged = true;
      } else if(stat==HIGH && m_keyDown && thisKey==m_key) {
        // key released, mark as unpressed and report the (saved) key as being up
        m_keyDown = false;
        m_keyChanged = true;
      }
    } // end for dataPort
    digitalWrite(strobePorts[strobe], HIGH);
  } // end for strobe
}

bool PianoKeyboard::pollForEvent() {
	checkKeys(keyStrobePorts);
	if(m_keyChanged) return true;
	checkKeys(buttonStrobePorts);
	return m_keyChanged;
}

