/**
 * Created by evoosa on 26/01/2019.
 */

var max_color_diversity = 10;
var max_cmy_val = 100;


function hexToRgb(hex) {
    // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
    var shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i;
    hex = hex.replace(shorthandRegex, function(m, r, g, b) {
        return r + r + g + g + b + b;
    });

    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}

function rgb_to_cmy_single_value(value) {
    return max_cmy_val - value / 2.55
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
    console.log(round_cmy_triplet(rgb_to_cmy(rgb_triplet)));
    return round_cmy_triplet(rgb_to_cmy(rgb_triplet))
}

//function cmy_to_rgb