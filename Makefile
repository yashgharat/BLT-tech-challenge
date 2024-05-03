default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o challenge.o challenge.c
	avr-gcc -o challenge.bin challenge.o
	avr-objcopy -O ihex -R .eeprom challenge.bin challenge.hex
	avrdude -v -V -c arduino -p ATMEGA328P -P /dev/cu.usbserial-10 -b 115200 -U flash:w:challenge.hex