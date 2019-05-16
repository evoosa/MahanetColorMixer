import os
from Tamburia.utils.tamburia import runTamburia
from threading import activeCount
import tornado.ioloop
import tornado.web
import tornado.websocket

STATIC_DIRNAME = "static"
port = 8885


class GetColorFromScale(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/pick_color_from_scale.html".format(STATIC_DIRNAME))


class WebSocketRGBHandler(tornado.websocket.WebSocketHandler):
    def check_origin(self, origin):
        return True

    def on_message(self, message):
        print("Received RGB: ", message, '\n')
        if activeCount() == 1:
            new_thread = runTamburia(message)
            new_thread.start()
        elif activeCount() == 2:
            print("\n[ XXX ] Tamburia is already running! GO FUCK YOURSELF\n")
        else:
            print("ERROR WTF", activeCount())


def make_app():
    settings = {
        "static_path": os.path.join(os.path.dirname(__file__), STATIC_DIRNAME),
        "static_url_prefix": "/{}/".format(STATIC_DIRNAME),
    }
    return tornado.web.Application([
        (r"/", GetColorFromScale),
        (r"/send_rgb", WebSocketRGBHandler)], **settings)


if __name__ == "__main__":
    app = make_app()
    app.listen(port=port)
    print("[ !!! ] listening on port {}\n".format(port))
    tornado.ioloop.IOLoop.instance().start()
