import tornado.ioloop
import tornado.web
import tornado.websocket
import os


class GetColorPicker(tornado.web.RequestHandler):
    def get(self):
        self.render("/color_pasten.html")


def make_app():
    return tornado.web.Application([
        (r"/", GetColorPicker),
    ])


if __name__ == "__main__":
    app = make_app()
    app.listen(port=8888)
    tornado.ioloop.IOLoop.instance().start()
