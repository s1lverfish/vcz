#include <bits/stdc++.h>

using namespace std;

struct Canvas{
	int width, height, zoom;
};

unsigned int SIZE, BITSPERPIXEL = 24, PIXELDATAOFFSET = 54, BITMAPINFOHEADER = 40;
char file[1000];
int bytes[256];

void init(){

}


int main(int args, char** argv){

	iota(bytes, bytes+256, 0);

	ofstream out;

	strcpy("default.bmp", file);
	if(args > 1){
		strcpy(argv[1], file);
		strncat(file, ".bmp", strlen(argv[1]));
		puts(file);
	}



	out.open(file, ios::binary | ios::out);

	//Specify file type : "BM"
	out.write((char*)&bytes[66], 1);
	out.write((char*)&bytes[77], 1);

	//Size of file in bytes
	SIZE = WIDTH*HEIGHT*ZOOM*BitsPerPixel/8 + 54;
	out.write((char*)&SIZE, 4);

	//Tldr: should be 0
	out.write((char*)&bytes[0], 4);

	//Offset to start of image
	out.write((char*)&PixelDataOffset, 4);
	//Size of the bitmap info header
	out.write((char*)&BITMAPINFOHEADER, 4);
	//width 
	int RealW = WIDTH * ZOOM;
	out.write((char*)&RealW, 4);
	//height
	int RealH = HEIGHT * ZOOM;
	out.write((char*)&RealH, 4);
	
	//Planes: should be 1
	out.write((char*)&bytes[1], 2);
	//Bits per pixel
	out.write((char*)&BitsPerPixel, 2);

	//Tldr: should be 0
	for(int i = 0; i < 6; ++i) out.write((char*)&bytes[0], 4);


	for(int i = 0; i < RealH; ++i){
		for(int j = 0; j < RealW; ++j){
			if(i < RealH/3){
				out.write((char*)&bytes[0], 1);
				out.write((char*)&bytes[150], 1);
				out.write((char*)&bytes[0], 1);
			}else if(i < RealH/3 * 2){
				out.write((char*)&bytes[255], 1);
				out.write((char*)&bytes[255], 1);
				out.write((char*)&bytes[255], 1);
			}else{
				out.write((char*)&bytes[0], 1);
				out.write((char*)&bytes[0], 1);
				out.write((char*)&bytes[200], 1);
			}
		}
	}

	
	out.close();
}
