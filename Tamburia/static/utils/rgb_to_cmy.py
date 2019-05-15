import config


def hex_to_rgb(rgb_hex: str) -> tuple:
    """
    Convert RGB hex value to RGB triplet
    """
    rgb_hex = rgb_hex.lstrip('#')
    return tuple(int(rgb_hex[i:i + 2], 16) for i in (0, 2, 4))


def rgb_to_cmy(rgb: tuple) -> dict:
    """
    Convert RGB triplet to CMY triplet
    """

    def rgb_to_cmy_single(rgb_val):
        return int(config.cmy_max_val - rgb_val / config.rgb_cmy_convert_val)

    return {
        'c': rgb_to_cmy_single(rgb[0]),
        'm': rgb_to_cmy_single(rgb[1]),
        'y': rgb_to_cmy_single(rgb[2])
    }


def cmy_to_pump_time(cmy_triplet: dict) -> dict:
    """
    Convert a C / M / Y value to the duration of time the pump needs to pump liquid.
    """

    def cmy_val_to_pump_dur(cmy_val, cmy_total):
        pump_dur = (cmy_val * config.cup_volume_ml) / (config.pump_rate_ml_s * cmy_total)
        return pump_dur

    cmy_total = sum(cmy_triplet.values())

    return {key: int(cmy_val_to_pump_dur(value, cmy_total)) for key, value in cmy_triplet.items()}
