#!/bin/python3.7

import serial
from datetime import timedelta, datetime

ser = serial.Serial('/dev/ttyS5', 115200, timeout=1)

ser.write(b'*****R')

def print_as_datetime(text):
    text = text[:-1]
    stuff = text.decode('UTF-8').split(':')
    date_epoch = int(stuff[0], 16)
    temperature_scaled = int(stuff[1], 10)
    d = datetime.fromtimestamp(date_epoch)
    t = temperature_scaled / 10000
    print("{}->{}".format(d,t))


while True:
    line = ser.readline()
    if line and len(line) > 0:
        print_as_datetime(line)
    else:
        break
