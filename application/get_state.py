#!/bin/python3

import serial
from datetime import timedelta, datetime

ser = serial.Serial('COM4', 115200, timeout=1)

ser.write(b'*****S')

while True:
    line = ser.readline()
    if line and len(line) > 0:
        print(line)
    else:
        break
