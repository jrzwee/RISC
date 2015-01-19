#!/usr/bin/env python
# + LOGFILE + LED
import serial
import RPi.GPIO as GPIO
import MySQLdb as mdb
import time

#Pinnummern als Variable
ledgruen = 26
ledrot = 24

GPIO.setmode(GPIO.BOARD)
GPIO.setup(ledgruen, GPIO.OUT)
GPIO.setup(ledrot, GPIO.OUT)

GPIO.output(ledgruen, False)
GPIO.output(ledrot, False)

GPIO.setwarnings(False) 

userid = []
getaccess = False
end = ""

ser = serial.Serial("/dev/ttyAMA0", 9600, timeout=0.1)

con = mdb.connect('localhost', 'az', 'inikruz', 'users');

with con:
    cur = con.cursor()
    cur.execute("SELECT * FROM Information")

    for i in range(cur.rowcount):
        row = cur.fetchone()
        userid.append(row[1])

		
con.close()

print 
print ("START MONITORING")
print 

print (" *** DEBUG START *** ")

for i in range(cur.rowcount):
	print userid[i]
	
print (" *** DEBUG END *** ")
print 

try:
        while 1:
			response = ser.readline()
			for i in range(cur.rowcount):
			
				cleaned = response.strip()
				if len(cleaned) >= 12:
					end = cleaned[1:13]
					if end == userid[i]:
						getaccess = True
						#print end + " YES"
						GPIO.output(ledgruen, True)
						GPIO.output(ledrot, False)
					else:
						getaccess = False
						#print end + " NO"
						GPIO.output(ledgruen, True)
						GPIO.output(ledrot, False)
					
					if getaccess == True:
						
						print end + " YES"
						
						# Get DATE and TIME
						logdate = time.strftime("%Y-%m-%d")
						logtime = time.strftime("%H:%M:%S")
						
						# Write in LOGFILE
						log = open("LOG/access.log","a")
						log.write(logdate + " | " + logtime + " | " + end + "\n")
						log.close()
					
except KeyboardInterrupt:
	ser.close()
	GPIO.cleanup()  
	print
	print
	print "Program Closed"
	
