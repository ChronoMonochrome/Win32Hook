#include "hook.hpp"

Hook::Hook(void *origFuncPtr, void *hookPtr) :
	mOrigFuncPtr(origFuncPtr),
	mHookPtr(hookPtr),
	mHooked(false)
{
}

Hook::~Hook()
{
}

bool Hook::removeHook()
{
	// restore the first 5 bytes in our hooked function
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)mOrigFuncPtr, mHookData, 5, NULL);

	return true;
}

bool Hook::applyHook()
{
	char patch[5] = {0};

	// save the original 5 bytes in hooked function
	ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<FARPROC>(mOrigFuncPtr), mHookData, 5, NULL);

	// overwrite the first 5 bytes with a jump to our hook function
	auto relativeOffset = ((char*)mHookPtr - (char*)mOrigFuncPtr - 5);

	memcpy(patch, "\xE9", 1);
	memcpy(patch + 1, &relativeOffset, 4);

	WriteProcessMemory(GetCurrentProcess(), (LPVOID)mOrigFuncPtr, patch, 5, NULL);

	// build the trampoline
	if (!mHooked) {
		mTrampolinePtr = VirtualAlloc(NULL, 11, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		auto hookAddress = (DWORD)mOrigFuncPtr + 5;
		memcpy((char*)mTrampolinePtr, &mHookData, 5);
		memcpy((char*)mTrampolinePtr + 5, "\x68", 1);
		memcpy((char*)mTrampolinePtr + 6, &hookAddress, 4);
		memcpy((char*)mTrampolinePtr + 10, "\xC3", 1);

		mHooked = true;
	}

	return true;
}