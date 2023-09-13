# This script sends the current time and date to the Arduino
#
# @author: F.S. Koulen
# @license: MIT

import serial
import time

arduino_port = '/COM5'
baud_rate = 9600

ser = serial.Serial(arduino_port, baud_rate)
time.sleep(2)  # Allow time for the Arduino to initialize

while True:
    current_time = time.strftime("%H:%M:%S %d/%m/%Y")  # Get the current time and date
    ser.write(current_time.encode('utf-8') + b'\n')  # Send the time and date to Arduino
    time.sleep(1)  # Update every 1 second
