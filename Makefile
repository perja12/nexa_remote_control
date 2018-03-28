.DEFAULT_GOAL := build

SKETCH = nexa_remote_control.ino
BOARD = attiny:avr:ATtinyX5:cpu=attiny85,clock=internal1
BIN_FOLDER = bin

build:
	arduino --verify $(CURDIR)/$(SKETCH) --board $(BOARD) --pref build.path=$(CURDIR)/$(BIN_FOLDER)

upload:
	arduino --upload $(CURDIR)/$(SKETCH) --board $(BOARD) --useprogrammer --pref build.path=$(CURDIR)/$(BIN_FOLDER)

clean:
	rm -r bin/*
