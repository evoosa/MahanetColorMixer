/**
 * Created by evoosa on 02/04/2019.
 */

var picked_rgb_hex = null;

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