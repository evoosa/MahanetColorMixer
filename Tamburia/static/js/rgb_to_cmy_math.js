/**
 * Created by evoosa on 26/01/2019.
 */

var max_color_diversity = 10;
var max_cmy_val = 100;
var rgb_cmy_convert_val = 2.55;
var color_picker_id = "rgb";

function hexToRgb(hex) {
    // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
    var shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i;
    hex = hex.replace(shorthandRegex, function (m, r, g, b) {
        return r + r + g + g + b + b;
    });

    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}

function rgbToHex(rgb_triplet) {
    return "#" + ((1 << 24) + (rgb_triplet['r'] << 16) + (rgb_triplet['g'] << 8) + rgb_triplet['b']).toString(16).slice(1);
}

function rgb_to_cmy_single_value(value) {
    // converts a single R/G/B value, to a single C/M/Y value
    return max_cmy_val - value / rgb_cmy_convert_val
}

function rgb_to_cmy(rgb_triplet) {
    return {
        c: rgb_to_cmy_single_value(rgb_triplet['r']),
        m: rgb_to_cmy_single_value(rgb_triplet['g']),
        y: rgb_to_cmy_single_value(rgb_triplet['b'])
    }
}

function round_cmy_single_value(value) {
    return Math.round(value / max_color_diversity) * max_color_diversity
}

function round_cmy_triplet(cmy_triplet) {
    return {
        c: round_cmy_single_value(cmy_triplet['c']),
        m: round_cmy_single_value(cmy_triplet['m']),
        y: round_cmy_single_value(cmy_triplet['y'])
    }
}

function rgb_to_rounded_cmy(rgb_triplet) {
    return round_cmy_triplet(rgb_to_cmy(rgb_triplet))
}

function cmy_to_rgb(cmy_triplet) {
    return {
        r: Math.round(rgb_cmy_convert_val * (max_cmy_val - cmy_triplet["c"])),
        g: Math.round(rgb_cmy_convert_val * (max_cmy_val - cmy_triplet["m"])),
        b: Math.round(rgb_cmy_convert_val * (max_cmy_val - cmy_triplet["y"]))
    }
}

function round_rgb_hex_val(rgb_hex_val) {
    // convert to a rounded CMY
    var rounded_cmy_triplet = rgb_to_rounded_cmy(hexToRgb(rgb_hex_val));
    // convert back to RGB Hex code
    var rounded_rgb_hex = rgbToHex(cmy_to_rgb(rounded_cmy_triplet));
    return rounded_rgb_hex
}

