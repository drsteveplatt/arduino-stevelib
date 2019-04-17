//
// PianoKeyboardNameMap implementation
//
// A variable and a lookup function for PianoKeyboardNameMap

#include "pianoKeyboard.h"
#include "pianoKeyboardNameMap.h"

PianoKeyboardNameMap pianoKeyboardNameMap;

char* PianoKeyboardNameMap::operator[](PianoKeyboard::KeyVals kv) {
	int i;
	for(i=0; m_map[i].kv!=PianoKeyboard::KNONE; i++) {
		if(kv==m_map[i].kv) break;
	}
	return m_map[i].name;
}



