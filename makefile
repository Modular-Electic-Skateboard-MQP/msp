CC = msp430-gcc
CFLAGS=-Os -Wall -Wno-unknown-pragmas -g -mmcu=msp430f5529

ppm: ppm_demo.o 
	$(CC) $(CFLAGS) -o ppm_demo.elf ppm_demo.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf main.elf *.o
