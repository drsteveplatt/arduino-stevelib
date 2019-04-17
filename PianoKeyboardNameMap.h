// name map for PianoKeyboard keys
// Requires pianoKeyboard.h
#if !defined(__PIANOKEYBOARDNAMEMAPDEFINED)
#define __PIANOKEYBOARDNAMEMAP

#define MAP(key) {PianoKeyboard::key,#key}
class PianoKeyboardNameMap {
	private:
	public:
	PianoKeyboardNameMap() { }
	char* operator[](PianoKeyboard::KeyVals);
};

extern PianoKeyboardNameMap pianoKeyboardNameMap;

#endif