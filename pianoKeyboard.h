//
// Header for piano keyboard
//

class PianoKeyboard {
	public:
	enum KeyVals {
		// buttons, have no correspondance to anything real
		BT1, BT2, BT3, BT4, BT5, BT6, BT7, BT8, BVolUp, BVolDn,
		BDog, BFrog, BDuck, BBird, BNoAnimal,
		BStop, BDEMOA, BDEMOC, BRec, BPlay,
		BTempoUp, BTempoDn, BR1, BR2, BR3, BR4, BR5, BR6, BR7, BR8,
		// keyboard keys, values correspond to MIDI note numbers
		KF2=41, KFS2, KG2, KGS2, KA2, KAS2, KB2,
		KC3, KCS3, KD3, KDS3, KE3, KF3, KFS3, KG3, KGS3, KA3, KAS3, KB3,
		KC4, KCS4, KD4, KDS4, KE4, KF4, KFS4, KG4, KGS4, KA4, KAS4, KB4,
		KC5, KCS5, KD5, KDS5, KE5, KF5,
		KNONE=99
	};
	private:
	bool m_keyDown;
	bool m_keyChanged;
	KeyVals m_key;
	struct KeyTranslations { int keycode; KeyVals keyval; };
	KeyTranslations keyTranslations[67] = {
		{7704, BDEMOA}, {7705,BNoAnimal}, {7706,BBird}, {7707,BDuck}, {7708,BFrog}, {7709,BDog},		// B0: 6 items
		{8214,BT8}, {8215,BT7}, {8216,BT6}, {8217,BT5}, {8218,BT4}, {8219,BT3}, {8220,BT2}, {8221,BT1},	// B2: 8 items
		{8471,BPlay},{8472,BRec},{8473,BStop},{8474,BVolDn},{8475,BVolUp},{8476,BTempoDn},{8477,BTempoUp},	// B3: 7 items
		{8726,BR8}, {8727,BR7}, {8728,BR6}, {8729,BR5}, {8730,BR4}, {8731,BR3}, {8732,BR2}, {8733, BR1},	// B4: 8 items
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
