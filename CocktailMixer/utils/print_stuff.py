from threading import Thread

from CocktailMixer.utils.send_to_arduino import send_to_ardi


class printDrink(Thread):
    def __init__(self, pump_times):
        Thread.__init__(self)
        self.drink_value = pump_times

    def run(self):
        """
        Run the CoctailMixer!
        Literally pump the colors to the cup.
        """

        print("[ VVV ] CoctailMixer is running!")
        send_to_ardi(self.drink_value)
        print("[ !!! ] CoctailMixer is done!")
