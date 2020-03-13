wave: project4.c wave.c
	gcc wave.c -o -Wall
	gcc project4.c -o -Wall

clean:
	rm -f *.o wave
