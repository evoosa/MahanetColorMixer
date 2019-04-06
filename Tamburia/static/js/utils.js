/**
 * Created by evoosa on 02/04/2019.
 */

// -----------------------------------------------//

var picked_rgb_hex = "#8080c0";

// server values
var port = "8888";
var ip = "127.0.0.1";
var ws_url = "send_rgb";

// open a global WS to the server
Socket = getWebSocket(ip, port, ws_url);

// -----------------------------------------------//

function change_background_color(rgb_hex_val) {
    //document.getElementById(color_picker_id).value = rounded_rgb_hex;
    document.getElementById("html").style = `background-color:${rgb_hex_val};`;
}

function handle_color_pick(rgb_hex_value) {
    // rounds the RGB hex value
    var rounded_rgb_hex = round_rgb_hex_val(rgb_hex_value);

    // colors the background with the chosen color
    console.log("Picked Color:", rgb_hex_value);
    change_background_color(rounded_rgb_hex);

    // saves the picked color in a global variable
    picked_rgb_hex =  rounded_rgb_hex
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

function send_cmy_to_server() {
    // calculate CMY values from the picked rgb hex
    var picked_cmy_triplet = rgb_to_rounded_cmy(hexToRgb(picked_rgb_hex));
    picked_cmy_triplet = JSON.stringify(picked_cmy_triplet);

    console.log("Sending Color To Server");
    console.log("RGB hex:", picked_rgb_hex);
    console.log("CMY Triplet:", picked_cmy_triplet);

    // onclick, send the RGB values to the server, using a WS
    Socket.send(picked_cmy_triplet);
}
