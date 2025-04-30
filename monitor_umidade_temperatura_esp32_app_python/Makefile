BOARD?=esp32:esp32:esp32
PORT?=COM12
BAUDRATE=115200
BUILD=build
# Arduino CLI version 0.14.0 is used.

.PHONY: default lint all flash clean

default: lint all flash clean

#lint:
#	cpplint --extensions=ino --filter=-legal/copyright *.ino

all:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD) ./

flash:
	arduino-cli upload --fqbn $(BOARD) --port $(PORT) --input-dir $(BUILD)

clean:
	rm -r build

monitor:
	arduino-cli monitor --fqbn $(BOARD) --port $(PORT) --config $(BAUDRATE)