//
// Header for piano keyboard
//

#ifdef BIGFUNKEYBOARD
#define NUMBUTTONS	30
#define NUMKEYS		37
#endif
#ifdef CASIOKEYBOARD
#define NUMBUTTONS	24
#define	NUMKEYS		44
#endif

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
		// button panel
		B00, B01, B02, B03, B04, B05, B06, B07,		// all named B<strobe><sense>
		B10, B11, B12, B13, B14, B15, B16, B17,
		B20, B21, B22, B23, B24, B25, B26, B27,
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
	bool m_keyDown;
	bool m_keyChanged;
	KeyVals m_key;
	struct KeyTranslations { int keycode; KeyVals keyval; };
	KeyTranslations keyTranslations[NUMBUTTONS+NUMANIMALS+1] = {
#ifdef BIGFUNKEYBOARD
		{7702, BDog}, {7703,BFrog}, {7704,BDuck}, {7705,BBird}, {7706,BNoAnimal}, {7707,BDEMOA},	// B0: 6 items
		{7958,BT1}, {7959,BT2}, {7960,BT3}, {7961,BT4}, {7962,BT5}, {7963,BT6}, {7964,BT7}, {7965,BT8},		// B1: 8 items
		{8214, BTempoUp}, {8215, BTempoDn}, {8216, BVolUp}, {8217, BVolDn}, {8218, BStop}, 			// B2: 8 items
			{8219, BRec}, {8220, BPlay}, {8221, BDEMOC},
		{8470,BR1}, {8471,BR2}, {8472,BR3}, {8473,BR4}, {8474,BR5}, {8475,BR6}, {8476,BR7}, {8477, BR8},	// B4: 8 items
#endif
#ifdef CASIOKEYBOARD
#endif
		{10774,KD5}, {10775,KCS5}, {11035,KF5}, {11036,KE5}, {11037,KDS5},										// K0, K1: 5 items
		{11286,KC5}, {11287,KB4}, {11288,KAS4}, {11289,KA4}, {11290,KGS4}, {11291,KG4}, {11292,KFS4}, {11293,KF4},	// K2: 8 items
		{11542,KE4}, {11543,KDS4}, {11544,KD4}, {11545,KCS4}, {11546,KC4}, {11547,KB3}, {11548,KAS3}, {11549,KA3},	// K3: 8 items
		{11798,KGS3}, {11799,KG3}, {11800,KFS3}, {11801,KF3}, {11802,KE3}, {11803,KDS3}, {11804,KD3}, {11805,KCS3},	// K4: 8 items
		{12054,KC3}, {12055,KB2}, {12056,KAS2}, {12057,KA2}, {12058,KGS2}, {12059,KG2}, {12060,KFS2}, {12061,KF2}, 	// K5: 8 items
		{32767,KNONE}																								// 1 item
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
	void checkKeys(int[]);
};
