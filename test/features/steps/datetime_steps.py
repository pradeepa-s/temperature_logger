from behave import *
import serial
from datetime import datetime, timezone


def set_device_time(dev_time):
    ser = serial.Serial('COM5', 115200, timeout=1)
    command_start = b'*****T'
    year = dev_time.year
    month = dev_time.month
    day = dev_time.day
    hour = dev_time.hour
    minute = dev_time.minute
    second = dev_time.second
    packed_bytes = struct.pack(
        "cccccc", bytes([year]), bytes([month]), bytes([day]),
        bytes([hour]), bytes([minute]), bytes([second]))


def get_current_time():
    return time.time()

@given('datetime is set to current time')
def step_impl(context):
    current_time = datetime.now(timezone.utc)
    set_device_time(current_time)

@when('datetime is requested')
def step_impl(context):
    context.datetime = get_current_time()

@then('datetime shall be set to current time')
def step_impl(context):
    assert context.datetime == time.time(), "Exp: {}, Act: {}".format(
        context.datetime, time.time())

