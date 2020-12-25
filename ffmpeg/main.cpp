#pragma once
#include<iostream>
#include<windows.h>
#include"DllLoader.h"

using namespace std;


typedef const char*(*MYPROC)(enum AVCodecID);
typedef void(*funPtr)(const char*);





int main() {

	cout << avcodec_get_name(AV_CODEC_ID_PNG) << endl;

	/*MYPROC* _funPtr1 = nullptr;
	FFmpegDllLoader ffmpegDll;
	ffmpegDll.loadDllFunc<MYPROC>(&_funPtr1, "avcodec_get_name", AVCODEC_DLL);

	if((_funPtr1)) cout << (*_funPtr1)(AV_CODEC_ID_PNG) << endl;*/



	cin.get();

	return 0;
}
