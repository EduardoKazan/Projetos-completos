BOARD?=arduino:avr:uno
PORT=COM3
#PORT?=/dev/cu.usbmodem14*
BUILD=build
BAUDRATE=9600

.PHONY: default lint all flash clean

default: lint all flash clean

lint:
	cpplint --extensions=ino --filter=-legal/copyright *.ino

all:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD) ./

flash:
	arduino-cli upload --fqbn $(BOARD) --port $(PORT) --input-dir $(BUILD)

clean:
	rm -r build

monitor:
	arduino-cli monitor --fqbn $(BOARD) --port $(PORT) config baudrate $(BAUDRATE)
