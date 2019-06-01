/**
 * Created by evoosa on 02/04/2019.
 */

// -----------------------------------------------//

var picked_drink_values = [50, 50, 50];

// server values
var port = "8881";
var ip = "10.100.102.6";
var ws_url = "ws";

// open a global WS to the server
Socket = getWebSocket(ip, port, ws_url);

// -----------------------------------------------//

function getWebSocket(ip, port, ws_url) {
    // open a websocket to the server
    var url = `ws://${ip}:${port}/${ws_url}`;
    Socket = new WebSocket(url);
    Socket.onopen = function () {
        console.log(`opened WS`);
    };

    return Socket;
}

function set_drink_values(value, position) {
    picked_drink_values[position] = value;
    console.log(value, position);
}

function send_mono_drink_to_server(position) {
    picked_drink_values = [0, 0, 0];
    picked_drink_values[position] = 100;
    send_drink_values_to_server();
}

function send_drink_values_to_server() {

    console.log("Sending Drink Values To Server");
    drink_values = picked_drink_values.join();
    console.log("RGB hex:", drink_values);

    // onclick, send the picked drink values to the server, using a WS
    Socket.send(drink_values);
}
