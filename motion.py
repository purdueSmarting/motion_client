#!/usr/bin/python
# coding=utf8
import time
import datetime
from threading import Timer
import threading
import json
import urllib2
import httplib as http
import requests
import serial

ser = serial.Serial('/dev/ttyACM2', 9600)
ser.open

while 1:
    motion_detect = ser.readline()
    current_time = datetime.datetime.now()

    #Motion Detection
    data = "Time:"+ str(current_time) + " Someone moving? " + str(motion_detect)
    data = json.loads(json.dumps(data))
    print data
    r = requests.post('http://192.168.2.136:7579/trash', json={'data':data})
    time.sleep(2)
