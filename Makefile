all:
	arduino-cli compile --warnings all
	arduino-cli upload

serial:
	arduino-cli monitor --port /dev/ttyUSB0
