#pragma once
#include<iostream>
#include<windows.h>
#include"DllLoader.h"

using namespace std;





typedef const char*(*MYPROC)(enum AVCodecID);


typedef void(*funPtr)(const char*);

void display(const char* msg) {
	cout << "display function " << msg << endl;
}



template<typename T>
void passMeFunPtr(T **funPtr) {
	cout << funPtr << endl;

	*funPtr = new T();

	**funPtr = &display;
	cout << **funPtr << endl;
	cout << display << endl;
	//(funPtr)();
	//funPtr = display;
}

template<typename T>
void passMeAnyType(T **i) {
	*i = new T();
	**i = 10;
}


int main() {

	//HINSTANCE hinstLib;
	//MYPROC avcodec_get_name;    // Function pointer
	//hinstLib = (HINSTANCE)LoadLibrary(L"avcodec-58.dll");

	//if (hinstLib == NULL) {
	//	cout << "failed to load libarary" << endl;
	//	return 0;
	//}


	//avcodec_get_name = (MYPROC)GetProcAddress(hinstLib, "avcodec_get_name");
	//if (avcodec_get_name == NULL) {
	//	cout << "failed to read address the of the function." << endl;
	//	return 0;
	//}

	

	//avutil_version()
	//AVCodecID;
	//avutil_version();
	//avcodec_get_name(AV_CODEC_ID_MPEG4);


	/*MYPROC avcodec_get_name = nullptr;

	DllLoader _dllLoader;
	_dllLoader.loadDllFunc(avcodec_get_name, L"avcodec-58.dll", "avcodec_get_name");*/


	//funPtr _funPtr = display;
	//(_funPtr)();

	//funPtr* _funPtr1 = nullptr;
	////_funPtr1 = new funPtr();
	//funPtr** _funPtr2 = &_funPtr1;

	//*_funPtr2 = new funPtr();

	//cout << _funPtr1 << endl;
	//cout << _funPtr2 << endl;
	//cout << *_funPtr2 << endl;
	//cout << **_funPtr2 << endl;

	//**_funPtr2 = &display;

	//(*_funPtr1)();

	
	
	/*funPtr* _funPtr1 = nullptr;
	passMeFunPtr<funPtr>(&_funPtr1);
	(*_funPtr1)("hello world");*/


	MYPROC* _funPtr1 = nullptr;
	//_funPtr1 = new MYPROC();

	cout << "&_funPtr1:\t" <<&_funPtr1 << endl;
	cout << "_funPtr1:\t" << _funPtr1 << endl;
	//cout << "*_funPtr1:\t" << *_funPtr1 << endl;

	cout << endl;
	cout << "&testFunc:\t" << &testFunc << endl;
	MYPROC testProc;
	testProc = &testFunc;
	(testProc)(AV_CODEC_ID_RAWVIDEO);

	/**_funPtr1 = &testFunc;
	(*_funPtr1)(AV_CODEC_ID_RAWVIDEO);*/

	FFmpegDllLoader ffmpegDll;
	ffmpegDll.loadDllFunc<MYPROC>(&_funPtr1, "avcodec_get_name", AVCODEC_DLL);

	if((_funPtr1)) cout << (*_funPtr1)(AV_CODEC_ID_PNG) << endl;



	//cout << _funPtr1 << endl;

	/*int i = 10;
	int* j = &i;
	int** k = &j;*/

	//passMeAnyType<int>(&j);

	//(*_funPtr1)();


	//cout << (avcodec_get_name)(AV_CODEC_ID_RAWVIDEO) << endl;


	/*int i = 10;
	int* j = &i;
	int** k = &j;
	
	cout << &i << endl;

	cout << *j << endl;
	cout << j << endl;
	cout << &j << endl;

	cout << **k << endl;
	cout << *k << endl;
	cout << k << endl;
	cout << &k << endl;*/

	cin.get();

	return 0;
}
