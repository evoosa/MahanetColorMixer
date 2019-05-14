#! /usr/bin/python3.5
import time
import RPi.GPIO as io

# Set the time all pumps will work for each cup in seconds
total_pump_time = 5

# The pins to which the pumps are connected to
pin_list = [40,36,32]

# Function that takes an RGB value and fills the cup accordingly
def run_pumps(RGB):
    io.setmode(io.BOARD)

    for i in range(0,3):
        PIN = pin_list[i]
        TIME = total_pump_time * (RGB[i] / sum(RGB))
        io.setup(PIN, io.OUT)
        io.output(PIN, 1) 
        time.sleep(TIME)
        io.output(PIN, 0)

    io.cleanup()

# Get RGB value from user input for testing
rgb_input=[int(x) for x in input("Enter RGB value like so: 200 100 5     ").split(" ")]

run_pumps(rgb_input)
