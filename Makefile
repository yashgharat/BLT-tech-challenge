default:
	#Compile the source code 
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o challenge.o challenge.c

	#Create binary and link object file
	avr-gcc -o challenge.bin challenge.o

	#Create HEX file
	avr-objcopy -O ihex -R .eeprom challenge.bin challenge.hex

	#Flash hex to arduino at port
	avrdude -v -V -c arduino -p ATMEGA328P -P /dev/cu.usbserial-10 -b 115200 -U flash:w:challenge.hex