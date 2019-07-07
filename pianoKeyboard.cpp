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
//    D30-D34 (port PC, 7-3): five strobe lines for control buttons
//    D42-D47 (port PL, 7-2): six strobe lines for keyboard
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
  for(int i=0; i<6; i++) theKeyBits[i] = 0;
  for(int i=0; i<4; i++) theButtonBits[i] = 0;
}


inline int kbencode(int strobe, int dataLine) { return (strobe<<8) + dataLine; }

// Strobe a set of strobes and report on the keys pressed.
// New version, for multi-key tracking
// Each call to checkKeys will check the appropriate set of ports.
//   Each key state is checked against the previous key states.
//   As soon as it finds a change, it
//		sets m_keyChanged to true
//		saves the key and the state
//		updates the bit in bits
//	If nothing is found, m_keyChanged will remain false.
//
// From the user's perspective:
//		Call pollForEvent until an event is detected.  pollForEvent will call checkKeys.
//		After an event is detected, use key() and keyDown() to figure out what the key
//			is and how it has changed.
//		Subsequent calls to pollForEvent() will clear the previously saved key/updown
//			(they will not be available to key() and keyDown().  The states will still be
//			preserved internally.
void PianoKeyboard::checkKeys(int strobePorts[], byte* bits) {
  int thisKey;
  byte stat;

  m_keyChanged = false;
  // perform one cycle of strobing all strobe lines and sensing all data lines for activity
  for(int strobe=0; strobePorts[strobe]>=0; strobe++) {
    // Force the strobe low to actiate it, then check all of the data lines
    digitalWrite(strobePorts[strobe], LOW);
    for(int dataLine=0; dataPorts[dataLine]>=0; dataLine++) {
      // checking data lines...
      stat=digitalRead(dataPorts[dataLine]);
      thisKey = keycodeToKeyVal(kbencode(strobePorts[strobe],dataPorts[dataLine]));
      if(stat==LOW && !isSet(bits, strobe, dataLine)) {
        // key hit, save value, mark as "hit", report results
Serial.print("[LOW "); Serial.print(strobePorts[strobe]); Serial.print(" ");
Serial.print(dataPorts[dataLine]); Serial.print(" ");
Serial.print(kbencode(strobePorts[strobe],dataPorts[dataLine])); Serial.println("]");
	    m_key = thisKey;
	    m_keyDown = true;
	    m_keyChanged = true;
	    setBit(bits, strobe, dataLine);
      } else if(stat==HIGH && isSet(bits, strobe, dataLine)) {
        // key released, mark as unpressed and report the (saved) key as being up
Serial.print("[HIGH "); Serial.print(strobePorts[strobe]); Serial.print(" ");
Serial.print(dataPorts[dataLine]); Serial.print(" ");
Serial.print(kbencode(strobePorts[strobe],dataPorts[dataLine])); Serial.println("]");
		m_keyDown = false;
		m_key = thisKey;
        m_keyChanged = true;
        clearBit(bits, strobe, dataLine);
      }
    } // end for dataPort
    digitalWrite(strobePorts[strobe], HIGH);
  } // end for strobe
}

bool PianoKeyboard::pollForEvent() {
	checkKeys(keyStrobePorts, theKeyBits);
	if(m_keyChanged) return true;
	checkKeys(buttonStrobePorts, theButtonBits);
	return m_keyChanged;
}

