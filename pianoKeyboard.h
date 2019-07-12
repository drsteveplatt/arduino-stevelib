//
// Header for piano keyboard
//

#define CASIOKEYBOARD

#ifdef BIGFUNKEYBOARD
#define NUMBUTTONS	30
#define NUMKEYS		37
#endif
#ifdef CASIOKEYBOARD
#define NUMBUTTONS	24
#define	NUMKEYS		44
#endif

#include <arduino.h>

class PianoKeyboard {
	public:
	enum KeyVals {
#ifdef BIGFUNKEYBOARD
		// buttons, have no correspondance to anything real
		BT1, BT2, BT3, BT4, BT5, BT6, BT7, BT8, BVolUp, BVolDn,
		BDog, BFrog, BDuck, BBird, BNoAnimal,
		BStop, BDEMOA, BDEMOC, BRec, BPlay,
		BTempoUp, BTempoDn, BR1, BR2, BR3, BR4, BR5, BR6, BR7, BR8,
#endif
#ifdef CASIOKEYBOARD
		// switch panel
		SW00, SW01, SW02, SW03, SW04, SW05, SW06, SW07,		// all named SW<strobe><sense>
		SW10, SW11, SW12, SW13, SW14, SW15, SW16, SW17,
		SW20, SW21, SW22, SW23, SW24, SW25, SW26, SW27,
#endif
		// keyboard keys, values correspond to MIDI note numbers
		KF2=41, KFS2, KG2, KGS2, KA2, KAS2, KB2,
		KC3, KCS3, KD3, KDS3, KE3, KF3, KFS3, KG3, KGS3, KA3, KAS3, KB3,
		KC4, KCS4, KD4, KDS4, KE4, KF4, KFS4, KG4, KGS4, KA4, KAS4, KB4,
		KC5, KCS5, KD5, KDS5, KE5, KF5,
#ifdef CASIOKEYBOARD
		KFS5, KG5, KGS5, KA5, KAS5, KB5, KC6,
#endif
		KNONE=99
	};
	private:
	// single-key-poll (old) version
	bool m_keyDown;
	bool m_keyChanged;
	KeyVals m_key;
	// event-driven (new) version
	// track the reported states of the keys.  One byte for all of the Sense responses for each strobe
	inline bool isSet(byte* bits, int strIndex, int bit) { return (bits[strIndex]&(1<<bit))!=0; }
	inline bool setBit(byte* bits, int strIndex, int bit) { bits[strIndex] |= (1<<bit); }
	inline bool clearBit(byte* bits, int strIndex, int bit) { bits[strIndex] &= (~(1<<bit)); }
	byte theKeyBits[6];
	byte theButtonBits[5];
	// translating a key to a keycode
	struct KeyTranslations { int keycode; KeyVals keyval; };
	KeyTranslations keyTranslations[NUMBUTTONS+NUMKEYS+1] = {
#ifdef BIGFUNKEYBOARD
		{7702, BDog}, {7703,BFrog}, {7704,BDuck}, {7705,BBird}, {7706,BNoAnimal}, {7707,BDEMOA},	// B0: 6 items
		{7958,BT1}, {7959,BT2}, {7960,BT3}, {7961,BT4}, {7962,BT5}, {7963,BT6}, {7964,BT7}, {7965,BT8},		// B1: 8 items
		{8214, BTempoUp}, {8215, BTempoDn}, {8216, BVolUp}, {8217, BVolDn}, {8218, BStop}, 			// B2: 8 items
			{8219, BRec}, {8220, BPlay}, {8221, BDEMOC},
		{8470,BR1}, {8471,BR2}, {8472,BR3}, {8473,BR4}, {8474,BR5}, {8475,BR6}, {8476,BR7}, {8477, BR8},	// B4: 8 items
#endif
#ifdef CASIOKEYBOARD
		{7702,SW00}, {7703,SW01}, {7704,SW02}, {7705,SW03}, {7706,SW04}, {7707,SW05}, {7708,SW06}, {7709,SW07},
		{7958,SW10}, {7959,SW11}, {7960,SW12}, {7961,SW13}, {7962,SW14}, {7963,SW15}, {7964,SW16}, {7965,SW17},
		{8214,SW20}, {8215,SW21}, {8216,SW22}, {8217,SW23}, {8218,SW24}, {8219,SW25}, {8220,SW26}, {8221,SW27},
#endif
		{10774,KF2}, {10775,KFS2}, {10776,KG2}, {10777,KGS2}, {10778,KA2}, {10779,KAS2}, {10780,KB2}, {10781,KC3},	// Strobe0: 8 items
		{11030,KCS3}, {11031,KD3}, {11032,KDS3}, {11033,KE3}, {11034,KF3}, {11035,KFS3}, {11036,KG3}, {11037,KGS3},	// Strobe1: 8 items
		{11286,KA3}, {11287,KAS3}, {11288,KB3}, {11289,KC4}, {11290,KCS4}, {11291,KD4}, {11292,KDS4}, {11293,KE4},	// Strobe2: 8 items
		{11542,KF4}, {11543,KFS4}, {11544,KG4}, {11545,KGS4}, {11546,KA4}, {11547,KAS4}, {11548,KB4}, {11549,KC5},	// Strobe3: 8 items
		{11798,KCS5}, {11799,KD5}, {11800,KDS5}, {11801,KE5}, {11802,KF5}, {11803,KFS5}, {11804,KG5}, {11805,KGS5},	// Strobe4: 8 items
		{12054,KA5}, {12055,KAS5}, {12056,KB5}, {12057,KC6},
		{32767,KNONE}																				// 1 item
	};

	KeyVals keycodeToKeyVal(int keycode){
		int i;
		for(i=0; this->keyTranslations[i].keyval!=KNONE; i++) {
			if(keycode==this->keyTranslations[i].keycode) break;
		}
		return keyTranslations[i].keyval;
	}

	public:
	PianoKeyboard();
	bool pollForEvent();
	bool keyDown() { return m_keyDown; }
	KeyVals key() { return m_key; }

	private:
	void checkKeys(int* strobeports, byte* bits);
};
