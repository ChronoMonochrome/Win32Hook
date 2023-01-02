#include <Windows.h>

class Hook {
public:
	Hook(void *origFuncPtr, void *hookPtr);
	~Hook();
	bool removeHook();
	bool applyHook();

	bool mHooked;
	void *mTrampolinePtr;
private:
	void *mOrigFuncPtr;
	void *mHookPtr;
	char mHookData[5];
};