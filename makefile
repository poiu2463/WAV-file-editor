wave: project4.c wave.c
	gcc wave.c project4.c -o wave

clean:
	rm -f *.o wave
