from utils.convert import rgb_hex_to_pump_time
from utils.pi import run_pumps
from threading import Thread


class runTamburia(Thread):
    def __init__(self, rgb_hex):
        Thread.__init__(self)
        self.rgb_hex = rgb_hex

    def run(self):
        """
        Run the Tamburia!
        Literally pump the colors to the cup.
        """

        print("[ VVV ] Tamburia is running!")
        run_pumps(rgb_hex_to_pump_time(self.rgb_hex))
        print("[ !!! ] Tamburia is done!")
