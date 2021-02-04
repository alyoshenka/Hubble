import subprocess
import datetime
import os
import threading
import time
import schedule

mf = "/home/jay/Hubble/log.txt"

def querySensor():
	tf = "/home/jay/Hubble/temp.txt"
	hf = "/home/jay/Hubble/humd.txt"
	
	print("query sensor py")
		
	temp = subprocess.check_output("particle call Medusa temp", shell=True)
	time.sleep(8)
	humd = subprocess.check_output("particle call Medusa humd", shell=True)	
	time.sleep(8)
	
	temp = filter(lambda i: i.isdigit(), temp)
	humd = filter(lambda i: i.isdigit(), humd)	
	
	print("t: ", temp)
	print("h: ", humd)
	
	tfo = open(tf, "w")
	tfo.write(str(temp))
	tfo.close()
	
	hfo = open(hf, "w")
	hfo.write(str(humd))
	hfo.close()
	
	dt = datetime.datetime.now()
	
	mfo = open(mf, "a")
	mfo.write("\n\n" + str(dt))
	mfo.write("\n" + str(temp).rstrip() + " deg")
	mfo.write("\n" + str(humd).rstrip() + " pct")
	mfo.close()
	
	print("\nfinish query sensor py\n")
		
	
def turnOnFan(onTime):
	print("fan on")
	
	os.system("particle call Medusa callFan on")
	
	mfo = open(mf, "a")
	mfo.write("\n\nfan on")
	mfo.close()
	
	th = threading.Thread(target=turnOffFan, args=(onTime,))
	th.start()
	
def turnOffFan(offTime):
	time.sleep(offTime)
	
	print("fan off")
	
	os.system("particle call Medusa callFan off")
	
	mfo = open(mf, "a")
	mfo.write("\n\nfan off")
	mfo.close()
	
def scheduleSensor(queryMin=1, fanOnSec=10, fanOnSpaceHrs=1):
	schedule.every(queryMin).minutes.do(querySensor)
	schedule.every(fanOnSpaceHrs).minutes.do(turnOnFan, onTime=fanOnSec)
	
def run():
	i = 1
	querySensor()
	while True:
		schedule.run_pending()
		time.sleep(1)
		
		t = open("/home/jay/Hubble/test.txt", "a")
		t.write(str(i) + "\n")
		t.close()
		
		i = i + 1

def go():	
	t = open("/home/jay/Hubble/start.txt", "a")
	t.write("go")
	t.close()
		
	scheduleSensor()
	
	t = open("/home/jay/Hubble/start.txt", "a")
	t.write("schedule")
	t.close()
	
	th = threading.Thread(target=run)
	
	t = open("/home/jay/Hubble/start.txt", "a")
	t.write("thread")
	t.close()
	
	th.start()
	
	t = open("/home/jay/Hubble/start.txt", "a")
	t.write("start")
	t.close()
	
	return "ret"
	

	
	
# scheduleSensor(10, 600, 3)
# runSensor()
	
	
