from threading import Thread

from CocktailMixer.utils.send_to_arduino import send_to_ardi


class printDrink(Thread):
    def __init__(self, drink_type, drink_value):
        Thread.__init__(self)
        self.drink_type = drink_type
        self.drink_value = drink_value

    def run(self):
        """
        Run the Tamburia!
        Literally pump the colors to the cup.
        """

        print("[ VVV ] Tamburia is running!")
        send_to_ardi(self.drink_type, self.drink_value)
        print("[ !!! ] Tamburia is done!")
