function getWebSocket(ip, port, ws_url) {

    // open a websocket to the server
    var url = `ws://${ip}:${port}/${ws_url}`;
    Socket = new WebSocket(url);
    Socket.onopen = function () {
        console.log(`opened WS`);
    };
    return Socket;
}

function create_color_canvas(canvas_element_id) {

    // create, and fill the color display canvas
    var default_canvas_size = [20, 20, 150, 100];
    var default_canvas_color = 'rgba(255, 165, 0, 1)';
    var canvas = document.getElementById(canvas_element_id);
    var canvas_context = canvas.getContext("2d");

    // create a rectangle, and fill it
    canvas_context.beginPath();
    canvas_context.rect(...default_canvas_size);
    canvas_context.fillStyle = default_canvas_color;
    canvas_context.fill();
}

function readURL(input) {

    // get the image's URL
    if (input.files && input.files[0]) {
        var reader = new FileReader();

        reader.onload = function (e) {
            $('#img').attr('src', e.target.result);
        };

        reader.readAsDataURL(input.files[0]);
    }
}

function send_rgb_to_server(picked_color_header_id) {

    // function to display the picked color, when the image is clicked
    var picked_rgb = pixelData[0] + ',' + pixelData[1] + ',' + pixelData[2];
    var picked_color_element = document.getElementById(picked_color_header_id);
    picked_color_element.innerHTML = 'Picked Color: rgb(' + picked_rgb + ')';

    // onclick, send the RGB values to the server, using a WS
    Socket.send(picked_rgb);
}

function display_image(img_element_id) {

    // if the image hasn't been displayed yet, create a canvas for it
    // and display it inside
    var img_element = document.getElementById(img_element_id);
    if (!img_element.canvas) {
        img_element.canvas = $('<canvas />')[0];
        img_element.canvas.width = img_element.width;
        img_element.canvas.height = img_element.height;

        // if you hover over the tiny image, it breaks the code. this will prevent it.
        try {
            img_element.canvas.getContext('2d').drawImage(img_element, 0, 0, img_element.width, img_element.height);
        }
        catch (err) {
            document.getElementById(img_element_id).canvas = null;
        }
    }
}

function display_hovered_color(img_element_id, canvas_id) {

    // load uploaded image on screen
    display_image(img_element_id);

    // fill the rectangle with the hovered over color
    var img_element = document.getElementById(img_element_id);
    pixelData = img_element.canvas.getContext('2d').getImageData(event.offsetX, event.offsetY, 1, 1).data;

    var canvas = document.getElementById(canvas_id);
    var canvas_context = canvas.getContext("2d");

    canvas_context.fillStyle = 'rgb(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ')';
    canvas_context.fill();

    var current_color = document.getElementById("current_color");

    current_color.innerHTML = 'Current Color: rgb(' + pixelData[0] + ', ' + pixelData[1] + ', ' + pixelData[2] + ')';


}


// MAIN ////////////////////////////////////////////////////////////////////////////////

// server values
var port = "8888";
var ip = "127.0.0.1";
var ws_url = "send_rgb";

// fill the color display canvas
var img_element_id = "img";
var canvas_element_id = "color_display_canvas";
var picked_color_header_id = "picked_color";
create_color_canvas(canvas_element_id);

// open a WS to the server
var Socket = getWebSocket(ip, port, ws_url);

// when the image changes, change it's 'src' tag, in order to re-display it
$("#image_input").change(function () {
    // get the image's URL
    readURL(this);
});

// MAIN ////////////////////////////////////////////////////////////////////////////////
