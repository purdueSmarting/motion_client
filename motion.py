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

ser = serial.Serial('/dev/ttyACM2', 9600, timeout=2)
ser.open

while True:
    motion_detect = ser.readline()
    current_time = str(datetime.datetime.now())
    #Motion Detection
    payload = {'time':current_time,'someone moving' : motion_detect}
    jsonString = json.dumps(payload)
    print (jsonString)
    requests.post('http://192.168.2.136:7579/motion', data=payload)
    print "request posted"
    time.sleep(2)
