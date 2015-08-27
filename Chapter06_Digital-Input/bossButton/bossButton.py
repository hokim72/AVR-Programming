BOSS_SITE = "http://www.cartalk.com/content/boss-redirect"
XKCD = "http://xkcd.com/353/"

SERIAL_PORT = "/dev/ttyUSB0"
BAUD_RATE = 9600

import serial
import webbrowser

sp = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout = 5)
sp.flush()
print ("Boss Button")

while(1):				# Sit and wait forever
	response = sp.read(1)	# get one byte
	if response == "O":
		print "Got OK Byte.  Waiting for button press."
	elif response == "X":
		print "Got Boss Byte!  Alarm!"
		webbrowser.open(BOSS_SITE)
	else:
		print "Got nothing.  Still waiting."
