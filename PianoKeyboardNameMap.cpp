//
// PianoKeyboardNameMap implementation
//
// A variable and a lookup function for PianoKeyboardNameMap


#include "pianoKeyboard.h"
#include "pianoKeyboardNameMap.h"
struct PKNMap { PianoKeyboard::KeyVals kv; char* name; };
static struct PKNMap m_map[99] = {
#ifdef	BIGFUNKEYBOARD
		MAP(BT1), MAP(BT2), MAP(BT3), MAP(BT4), MAP(BT5), MAP(BT6), MAP(BT7), MAP(BT8), MAP(BVolUp), MAP(BVolDn),
		MAP(BDog), MAP(BFrog), MAP(BDuck), MAP(BBird), MAP(BNoAnimal),
		MAP(BStop), MAP(BDEMOA), MAP(BDEMOC), MAP(BRec), MAP(BPlay),
		MAP(BTempoUp), MAP(BTempoDn), MAP(BR1), MAP(BR2), MAP(BR3), MAP(BR4), MAP(BR5), MAP(BR6), MAP(BR7), MAP(BR8),
#endif
#ifdef	CASIOKEYBOARD
		MAP(SW00), MAP(SW01), MAP(SW02), MAP(SW03), MAP(SW04), MAP(SW05), MAP(SW06), MAP(SW07),
		MAP(SW10), MAP(SW11), MAP(SW12), MAP(SW13), MAP(SW14), MAP(SW15), MAP(SW16), MAP(SW17),
		MAP(SW20), MAP(SW21), MAP(SW22), MAP(SW23), MAP(SW24), MAP(SW25), MAP(SW26), MAP(SW27),
#endif
		MAP(KF2), MAP(KFS2), MAP(KG2), MAP(KGS2), MAP(KA2), MAP(KAS2), MAP(KB2),
		MAP(KC3), MAP(KCS3), MAP(KD3), MAP(KDS3), MAP(KE3), MAP(KF3), MAP(KFS3), MAP(KG3), MAP(KGS3), MAP(KA3), MAP(KAS3), MAP(KB3),
		MAP(KC4), MAP(KCS4), MAP(KD4), MAP(KDS4), MAP(KE4), MAP(KF4), MAP(KFS4), MAP(KG4), MAP(KGS4), MAP(KA4), MAP(KAS4), MAP(KB4),
		MAP(KC5), MAP(KCS5), MAP(KD5), MAP(KDS5), MAP(KE5), MAP(KF5),
#ifdef	CASIOKEYBOARD
		MAP(KFS5), MAP(KG5), MAP(KGS5), MAP(KA5), MAP(KAS5), MAP(KB5), MAP(KC6),
#endif
		MAP(KNONE)
};

PianoKeyboardNameMap pianoKeyboardNameMap;

char* PianoKeyboardNameMap::operator[](PianoKeyboard::KeyVals kv) {
	int i;
	for(i=0; m_map[i].kv!=PianoKeyboard::KNONE; i++) {
		if(kv==m_map[i].kv) break;
	}
	return m_map[i].name;
}



