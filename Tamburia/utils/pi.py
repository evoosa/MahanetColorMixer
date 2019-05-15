from time import sleep
import RPi.GPIO as io
from utils import config

# Set the time all pumps will work for each cup in seconds
full_cup_pump_dur = config.cup_volume_ml / config.pump_rate_ml_s


def run_pumps(pump_times: dict):
    """
    Function that takes a 'CMY pump time' triplet, and fills the cup accordingly
    """

    def run_pump(pin, time):
        # Turn pump on for the duration of 'time'
        io.setup(pin, io.OUT)
        print("pumping '{color}' for {time} seconds...".format(color=color, time=time))
        io.output(pin, 1)
        sleep(time)
        print('done!\n')
        io.output(pin, 0)

        io.setmode(io.BOARD)

    for color, time in pump_times.items():
        pin = config.pins[color]
        run_pump(pin, time)
        sleep(config.idle_time)

        io.cleanup()


