import os
from threading import activeCount

import tornado.ioloop
import tornado.web
import tornado.websocket

from CocktailMixer.utils.print_stuff import printDrink

# ---- Constants---- #

STATIC_DIRNAME = "static"
PORT = 80
ADDRESS = '0.0.0.0'

CM_IS_RUNNING_MSG = "\n[ XXX ] Tamburia is already running! GO FUCK YOURSELF\n"
ERROR_WTF_MSG = "ERROR WTF"


# ---- Request Handlers ---- #

class getUserChoice(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/get_user_choice.html".format(STATIC_DIRNAME))


class getMonoDrink(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/get_mono_drink.html".format(STATIC_DIRNAME))


class getCocktail(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/get_cocktail.html".format(STATIC_DIRNAME))


# ---- WS Handlers ---- #

class wsMonoDrinkHandler(tornado.websocket.WebSocketHandler):
    def check_origin(self, origin):
        return True

    def on_message(self, message):
        print("Received monoDrink: ", message, '\n')
        if activeCount() == 1:
            new_thread = printDrink(message)
            new_thread.start()
        elif activeCount() == 2:
            print(CM_IS_RUNNING_MSG)
        else:
            print(ERROR_WT  F_MSG, activeCount())


class wsCocktailHandler(tornado.websocket.WebSocketHandler):
    def check_origin(self, origin):
        return True

    def on_message(self, message):
        print("Received cocktail: ", message, '\n')
        if activeCount() == 1:
            new_thread = printDrink(message)
            new_thread.start()
        elif activeCount() == 2:
            print(CM_IS_RUNNING_MSG)
        else:
            print(ERROR_WTF_MSG, activeCount())


def make_app():
    settings = {
        "static_path": os.path.join(os.path.dirname(__file__), STATIC_DIRNAME),
        "static_url_prefix": "/{}/".format(STATIC_DIRNAME),
    }
    return tornado.web.Application([
        (r"/", getUserChoice),
        (r"/send_drink", wsMonoDrinkHandler),
        (r"/send_cocktail", wsCocktailHandler),
        (r"/mono_drink", getMonoDrink),
        (r"/cocktail", getCocktail)],
        **settings)


if __name__ == "__main__":
    app = make_app()
    app.listen(port=PORT, address=ADDRESS)
    print("[ !!! ] listening on port {}\n".format(PORT))
    tornado.ioloop.IOLoop.instance().start()
