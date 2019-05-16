/**
 * Created by evoosa on 02/04/2019.
 */

// -----------------------------------------------//

var picked_rgb_hex = "#8080c0";

// server values
var port = "8885";
var ip = "127.0.0.1";
var ws_url = "send_rgb";

// open a global WS to the server
Socket = getWebSocket(ip, port, ws_url);

// -----------------------------------------------//

function change_background_color(rgb_hex_val) {
    //document.getElementById(color_picker_id).value = rounded_rgb_hex;
    document.getElementById("html").style = `background-color:${rgb_hex_val};`;
}

function handle_color_pick(rgb_hex_val) {

    // colors the background with the chosen color
    console.log("Picked Color:", rgb_hex_val);
    change_background_color(rgb_hex_val);

    // saves the picked color in a global variable
    picked_rgb_hex = rgb_hex_val
}

function getWebSocket(ip, port, ws_url) {
    // open a websocket to the server
    var url = `ws://${ip}:${port}/${ws_url}`;
    Socket = new WebSocket(url);
    Socket.onopen = function () {
        console.log(`opened WS`);
    };

    return Socket;
}

function send_rgb_hex_to_server() {

    console.log("Sending Color To Server");
    console.log("RGB hex:", picked_rgb_hex);

    // onclick, send the RGB values to the server, using a WS
    if (picked_rgb_hex === "#ffffff") {
        alert("Don't pick WHITE color !!!!!")
    }
    else {
        Socket.send(picked_rgb_hex);
    }
}
