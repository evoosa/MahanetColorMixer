import tornado.ioloop
import tornado.web
import tornado.websocket
import os

STATIC_DIRNAME = "static"
port = 8888


class GetColorFromScale(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/pick_color_from_scale.html".format(STATIC_DIRNAME))


class GetColorFromImage(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/pick_color_from_image.html".format(STATIC_DIRNAME))


class WebSocketRGBHandler(tornado.websocket.WebSocketHandler):
    def check_origin(self, origin):
        return True

    def on_message(self, message):
        print(message)


def make_app():
    settings = {
        "static_path": os.path.join(os.path.dirname(__file__), STATIC_DIRNAME),
        "static_url_prefix": "/{}/".format(STATIC_DIRNAME),
    }
    return tornado.web.Application([
        (r"/scale", GetColorFromScale),
        (r"/image", GetColorFromImage),
        (r"/send_rgb", WebSocketRGBHandler)], **settings)


if __name__ == "__main__":
    app = make_app()
    app.listen(port=port, address="127.0.0.1")
    tornado.ioloop.IOLoop.instance().start()
