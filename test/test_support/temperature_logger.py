import serial
import time

class device:
    def __init__(self):
        TIMEOUT_SECONDS = 10
        self.comms = serial.Serial(
            '/dev/ttyS5', 115200, timeout=TIMEOUT_SECONDS)

    def is_running(self):
        cmd = b'*****ISRUN\n'
        self.comms.write(cmd)
        resp = self.comms.readline()
        resp = resp.decode('UTF-8')
        return resp == "OK\n"

    def reset(self):
        cmd = b'*****RESET\n'
        self.comms.write(cmd)

    def has_reset(self):
        resp = self.comms.readline()
        resp = resp.decode('UTF-8')[1:]
        return resp == "TPL-ON\n"

    def get_info(self):
        cmd = b'******INFO\n'
        self.comms.write(cmd)
        resp = self.comms.readline()
        resp = resp.decode('UTF-8')[1:]
        return resp[:-1]

