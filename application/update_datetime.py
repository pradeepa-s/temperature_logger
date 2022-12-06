#!/bin/python3.7

import serial
import struct
from datetime import datetime, timezone
import time

ser = serial.Serial('COM4', 115200, timeout=1)
current_dt = datetime.now()
year = (current_dt.year % 100)
month = current_dt.month
day = current_dt.day
hour = current_dt.hour
minute = current_dt.minute
second = current_dt.second

# *****T<year><month><day><hour><minute><seconds>
packed_bytes = struct.pack("cccccc", bytes([year]), bytes([month]), bytes([day]), bytes([hour]), bytes([minute]), bytes([second]))
command_start = b'*****T'

full_command = command_start + packed_bytes
ser.write(full_command)

while True:
    line = ser.readline()
    if line and len(line) > 0:
        print(line)
        print("\n\rDone!")
        break
    else:
        print(".", end='', flush=True)
        time.sleep(1)