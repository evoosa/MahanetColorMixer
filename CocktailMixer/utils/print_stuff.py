from threading import Thread

from CocktailMixer.utils.convert import convert_msg_to_pump_times
from CocktailMixer.utils.send_to_arduino import send_to_ardi


class printDrink(Thread):
    def __init__(self, msg):
        Thread.__init__(self)
        self.msg = msg
        self.pump_times = None

    def run(self):
        """
        Run the CocktailMixer!
        Literally pump the colors to the cup.
        """

        print("[ VVV ] CocktailMixer is running!")
        self.pump_times = convert_msg_to_pump_times(self.msg)
        send_to_ardi(self.pump_times)
        print("[ !!! ] CocktailMixer is done!")
