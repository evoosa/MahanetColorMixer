import tornado.ioloop
import tornado.web
import tornado.websocket
import os
import ast

STATIC_DIRNAME = "static"
port = 8888



class GetColorFromScale(tornado.web.RequestHandler):
    def get(self):
        self.render("{}/pick_color_from_scale.html".format(STATIC_DIRNAME))


class WebSocketRGBHandler(tornado.websocket.WebSocketHandler):
    def check_origin(self, origin):
        return True

    def on_message(self, message):
        print("Received CMY: ", ast.literal_eval(message))

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
    tornado.ioloop.IOLoop.instance().start()
