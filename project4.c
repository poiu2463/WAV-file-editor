#include <stdio.h>
#include <stderr.h>
#include <string.h>
#include "wave.h" //wittman's header file (MUST BE COMPILED)

int main (int argc, char** argv){
	for(int i = 0; i < argc - 1; i ++){
    		char [] currentFlag = "-r";
		char [] currentArgV = argv [i];
		
		if(strcmp(currentArgV, currentFlag)){
			//reverse sound here	
		}else if(strcmp(currentArgv, (currentFlag = "-s"))){
			//speed change here	
		}else if(strcmp(currentArgv, (currentFlag = "-f"))){
			//flip channels here
		}else if(strcmp(currentArgv, (currentFlag = "-o"))){
			//fade out here
		}else if(strcmp(currentArgv, (currentFlag = "-i"))){
			//fade in here
		}else if(strcmp(currentArgv, (currentFlag = "-v"))){
			//change volume here
		}else if(strcmp(currentArgv, (currentFlag = "-e"))){
			//echo here
		}else{
			//Command line error message here
			fprintf("Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
		}
	}
  }
	
	return 0;
	
}
