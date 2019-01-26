/**
 * Created by evoosa on 26/01/2019.
 */

function rgb_to_cmy_single_value(value) {
    return 100 - value / 2.55
}

function rgb_to_cmy(rgb_triplet) {
    return {
        c: rgb_to_cmy_single_value(rgb_triplet['r']),
        m: rgb_to_cmy_single_value(rgb_triplet['g']),
        y: rgb_to_cmy_single_value(rgb_triplet['b'])
    }
}

function round_cmy_single_value(value) {
    var diviser = 10;
    return Math.round(value / diviser) * diviser
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
