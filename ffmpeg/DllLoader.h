#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
using namespace std;


extern "C" {
#include<libavcodec/codec.h>
}

const char* testFunc(enum AVCodecID);



#define TASK_SUCCESS 0
#define TASK_FAILURE 1




enum FFMPEG_LIB_ID
{
	AVCODEC_DLL,
	AVFORMATE_DLL
};

#define GET_VARIABLE_NAME(Variable) (#Variable)

class FFmpegDllLoader {
private:
	HINSTANCE hinstLib;
	HINSTANCE hinstAVcodec;
	HINSTANCE hinstAVformate;
	LPCWSTR ffmpegDllArr[2] = {L"AVCODEC_DLL", L"AVFORMATE_DLL"};

	HINSTANCE loadDllLibrary(LPCWSTR dllName);
	HINSTANCE getLibInst(FFMPEG_LIB_ID libID);

public:
	FFmpegDllLoader();
	template<typename T>
	errno_t loadDllFunc(T **funcPtr, LPCSTR funcName, FFMPEG_LIB_ID libID);
	void test();
};



template<typename T>
inline errno_t FFmpegDllLoader::loadDllFunc(T **funcPtr, LPCSTR funcName, FFMPEG_LIB_ID libID)
{

	HINSTANCE hinstLib = this->getLibInst(libID);

	if (hinstLib == NULL) {
		wcout << L"Failded to load the dll instance (" << this->ffmpegDllArr[libID];
		cout << ") for function: " << funcName << endl;
		return TASK_FAILURE;
	}

	*funcPtr = new T();
	**funcPtr = (T)GetProcAddress(hinstLib, funcName);

	if (**funcPtr == NULL) {
		cout << "Failed to read the address of the function (" << funcName << ") from: ";
		wcout << this->ffmpegDllArr[libID] << endl;
		return TASK_FAILURE;
	}

	return TASK_SUCCESS;

    /*this->hinstLib = (HINSTANCE)LoadLibrary(dllName);
	if (hinstLib == NULL) {

		wcout << L"failed to load the libarary: ";
		wcout << dllName << endl;
		return TASK_FAILURE;
	}

	funcPtr = GetProcAddress(hinstLib, funcName);

	if (funcPtr == NULL) {
		cout << "Failed to read address the of the function (" << funcName << ") from ";
		wcout << dllName << endl;
		return TASK_FAILURE;
	}*/





}