#include "DllLoader.h"



HINSTANCE FFmpegDllLoader::loadDllLibrary(LPCWSTR dllName)
{
	HINSTANCE hinstLib = (HINSTANCE)LoadLibrary(dllName);
	if (hinstLib == NULL) {

		wcout << L"failed to load the libarary: ";
		wcout << dllName << endl;
		return NULL;
	}

	return hinstLib;
}

HINSTANCE FFmpegDllLoader::getLibInst(FFMPEG_LIB_ID libId)
{
	switch (libId)
	{
	case AVFORMATE_DLL:
		return this->hinstAVformate;
	case AVCODEC_DLL:
		return this->hinstAVcodec;
	default:
		return NULL;
	}
}

FFmpegDllLoader::FFmpegDllLoader()
{
	this->hinstAVformate = this->loadDllLibrary(L"avformat-58.dll");
	this->hinstAVcodec = this->loadDllLibrary(L"avcodec-58.dll");
}

void FFmpegDllLoader::test()
{

}

const char* testFunc(enum AVCodecID) {
	cout << "testFunc called." << endl;
	return "";
}