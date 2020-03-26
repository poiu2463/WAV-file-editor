#include <string.h>
#include "wave.h" //wittman's header file (MUST BE COMPILED)

void reverse (short* channel, int length); //prototype functions
/**
 * Function: 	getShort (short)
 * Returns: 	an int, read from standard input. 
 **/

short getShort() {
  int firstByte = getchar();
  int secondByte = getchar();

  short temp = secondByte<<8 | firstByte; //due to little endian file format (biggest byte is second)
  
  return temp;
}

/*
short writeBytes() {
  int firstByte = getchar();
  int secondByte = getchar();

  short temp = secondByte<<8 | firstByte; //due to little endian file format (biggest byte is second)
  
  return temp;
}
*/

int main (int argc, char** argv){
  WaveHeader header;
  readHeader(&header);
  int length = header.dataChunk.size/4; 
  // divide into two channels and then into shorts

  short* left = (short*)malloc(sizeof(short)*length);
  short* right = (short*)malloc(sizeof(short)*length);

  for(int i = 0; i < length; ++i){
    left[i] = getShort();
    right[i] = getShort();
  }
  
	for(int i = 1; i < argc; ++i){
		char* currentArgV = argv [i];
		
		if(strcmp(currentArgV, "-r") == 0){
			//reverse sound here	
			reverse(left, length);
			reverse(right, length);
		}else if(strcmp(currentArgv, "-s") == 0){
			//speed change here	
		}else if(strcmp(currentArgv, "-f") == 0){
			//flip channels here
		}else if(strcmp(currentArgv, "-o") == 0){
			//fade out here
		}else if(strcmp(currentArgv, "-i") == 0){
			//fade in here
		}else if(strcmp(currentArgv, "-v") == 0){
			//change volume here
		}else if(strcmp(currentArgv, "-e") == 0){
			//echo here
		}else{
			//Command line error message here
			fprintf("Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
		}

	}
  //here we need to writeHeader
  //output all left/right channel data by doing the opposite of the above input blocks of code: read two shorts in left and right channel and output the bytes 
  
	return 0;
	
}

void reverse (short* channel, int length) {
	for(int i = 0; i < length/2; i++){ // divide by 4 to get half of each channel
		short temp = channel[length -i];
		channel[length-i] = channel[i];
		channel[i] = temp;	
	}
	
}

