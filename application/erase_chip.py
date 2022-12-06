#!/bin/python3.7

import serial
import time
from datetime import timedelta, datetime

ser = serial.Serial('COM4', 115200, timeout=1)

ser.write(b'*****E')

while True:
    line = ser.readline()
    if line and len(line) > 0:
        print(line)
        print("\n\rDone!")
        break
    else:
        print(".", end='', flush=True)
        time.sleep(1)

