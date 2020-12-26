#include<iostream>
#include"Muxing.h"

extern "C" {
#include<libavcodec/codec.h>
}



int main(int argc, char** argv) {

	char* ptr = nullptr;
	char abc[2];
	ptr = abc;


	initMuxing(argc, argv);

	//std::cout << avcodec_get_name(AV_CODEC_ID_PNG) << std::endl;


	std::cin.get();

	return 0;
}
