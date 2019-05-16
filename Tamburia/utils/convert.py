from Tamburia.utils import config


def hex_to_rgb(rgb_hex: str) -> dict:
    """
    Convert RGB hex value to RGB triplet
    """
    rgb_hex = rgb_hex.lstrip('#')
    return {['r', 'g', 'b'][i]: int(rgb_hex[i * 2:i * 2 + 2], 16) for i in range(3)}


def rgb_to_cmy(rgb: dict) -> dict:
    """
    Convert RGB triplet to CMY triplet
    """

    def rgb_to_cmy_single(rgb_val):
        return int(config.cmy_max_val - rgb_val / config.rgb_cmy_convert_val)

    return {
        'c': rgb_to_cmy_single(rgb['r']),
        'm': rgb_to_cmy_single(rgb['g']),
        'y': rgb_to_cmy_single(rgb['b'])
    }


def cmy_to_pump_time(cmy_triplet: dict) -> dict:
    """
    Convert a C / M / Y value to the duration of time the pump needs to pump liquid.
    """

    def cmy_val_to_pump_dur(cmy_val, cmy_total):
        pump_dur = (cmy_val * config.cup_volume_ml) / (config.pump_rate_ml_s * cmy_total)
        return pump_dur

    cmy_total = sum(cmy_triplet.values())

    return {key: (cmy_val_to_pump_dur(value, cmy_total)) for key, value in cmy_triplet.items()}


def rgb_hex_to_pump_time(rgb_hex: str) -> dict:
    """
    RGB hex > RGB triplet > CMY triplet > pump duration triplet
    """
    rgb_triplet = hex_to_rgb(rgb_hex)
    cmy_triplet = rgb_to_cmy(rgb_triplet)
    return cmy_to_pump_time(cmy_triplet)
