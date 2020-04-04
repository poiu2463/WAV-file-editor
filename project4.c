#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "wave.h" //wittman's header file (MUST BE COMPILED)


#define BYTE_SIZE 8
#define BYTE_MASK 255
#define SAMPLE_RATE 44100

void reverse (short* channel, int length); //prototype functions

void fadeIn(short* channel, int length, double seconds);

void fadeOut(short* channel, int length, double time);

short* changeSpeed(short* channel, int length, int factor);
//prototype for changing the speed
//I know we need length but not sure about how we get the factor

void volumeChange(short* left, short* right, double scale, int length);
//prototype for volume change
short clamp (double value);
//prototype of clamp

void echo(double delay, double scale, short* channel, int length);

/**
 * Function:  getShort (short)
 * Returns:   a byte.
 **/
short getShort() {
  int firstByte = getchar();
  int secondByte = getchar();

  short temp = secondByte<<BYTE_SIZE | firstByte; //due to little endian file format (biggest byte is second)
  
  return temp;
}

/**
 * Function:  writeBytes 
 * Returns:   a char, made up of two bytes
 **/
void writeBytes(short output) {
  int secondByte = output>>BYTE_SIZE;  // high byte
  int firstByte = output & BYTE_MASK;
  
  putchar(firstByte);
  putchar(secondByte);
}


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
fprintf(stderr, "Reversing\n");
reverse(left, length);
reverse(right, length);
}else if(strcmp(currentArgV, "-s") == 0){
//speed change here 
++i;
double factor = atof(argv[i]);
left = changeSpeed(left, length, factor);
right = changeSpeed(right, length, factor);

length = length/factor;

}else if(strcmp(currentArgV, "-f") == 0){
//flip channels here
short* temp = right;
  right = left;
  left = temp;
}else if(strcmp(currentArgV, "-o") == 0){
//fade out here
}else if(strcmp(currentArgV, "-i") == 0){
//fade in here
++i;
double seconds = atof(argv[i]);
fadeIn(left, length, seconds);
fadeIn(right, length, seconds);

}else if(strcmp(currentArgV, "-v") == 0){
//change volume here
++i;
double scale = atof(argv[i]);
volumeChange(left, right, scale, length);

}else if(strcmp(currentArgV, "-e") == 0){
//echo(delay, scale, channel, length);
//echo here
}else{
//Command line error message here
fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
}

}
header.dataChunk.size = length * 4;
header.size = header.dataChunk.size + 36;
  //here we need to writeHeader
  //output all left/right channel data by doing the opposite of the above input blocks of code: read two shorts in left and right channel and output the bytes 
writeHeader(&header);

for(int i = 0; i < length; ++i){
    writeBytes(left[i]);
    writeBytes(right[i]);
  }
return 0;

}

void reverse (short* channel, int length) {
for(int i = 0; i < length/2; i++){ // divide by 4 to get half of each channel
short temp = channel[length-1-i];
channel[length-1-i] = channel[i];
channel[i] = temp; 
}
}

short* changeSpeed(short* channel, int length, int factor){
 short* newChannel = (short*)malloc(sizeof(short)*length/factor);

 for(int i = 0; i < length/factor; i++){
newChannel[i] = channel[i*factor];
 }
 free(channel);
 return newChannel;
  }

void fadeIn(short* channel, int length, double seconds) {
int sampleNumber = SAMPLE_RATE * seconds;
for(int i = 0; i < sampleNumber && i < length; ++i) {
channel[i] *= (i/(double)sampleNumber)*(i/(double)sampleNumber);
}
}

void fadeOut(short* channel, int length, double time) {
int sampleNumber = SAMPLE_RATE * time;
for(int i = 0; i < sampleNumber && i >= time; ++i) {
channel[i] *= (i/(double)sampleNumber)*(i/(double)sampleNumber);

} 
}
  
 
void volumeChange(short* left, short* right, double scale, int length){
for(int i = 0; i < length; i++){
int leftNum = left[i];
int rightNum = right[i];
leftNum *= scale;
rightNum *= scale;
left[i] = clamp(leftNum);
right[i] = clamp(rightNum);
}
}

short clamp (double value){
if(value < SHRT_MIN)
return (short) SHRT_MIN;
if(value > SHRT_MAX)
return (short) SHRT_MAX;
return (short) value;
}

void echo(double delay, double scale, short* channel, int length){
int sampleNumber = delay * SAMPLE_RATE;
short* newRightSound = (short*)malloc(sizeof(short)*sampleNumber);
short* newLeftSound = (short*)malloc(sizeof(short)*sampleNumber);

int i =0;
while(i < sizeof(short)*sampleNumber){
if( i < delay){
newRightSound[i] = channel[i];
newLeftSound[i] = channel[i];
}
else{
newRightSound[i] = (channel[i]+delay)*scale;
newLeftSound[i] = (channel[i]+delay)*scale;
} 
}
}

