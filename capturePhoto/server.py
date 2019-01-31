import tornado.ioloop
import tornado.web
import tornado.websocket
import os
from server_functions.pikood_exec import PikoodExec

STATIC_DIRNAME = 'static'


class Capture(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/capture.html".format(STATIC_DIRNAME))


def make_app():
    settings = {
        "static_path": os.path.join(os.path.dirname(__file__), STATIC_DIRNAME),
        "static_url_prefix": "/{}/".format(STATIC_DIRNAME),
    }
    return tornado.web.Application([
        (r"/", Capture)],
        **settings)


if __name__ == "__main__":
    app = make_app()
    app.listen(port=80)
    tornado.ioloop.IOLoop.instance().start()
