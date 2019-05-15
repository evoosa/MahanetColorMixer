import config


def hex_to_rgb(rgb_hex: str) -> tuple:
    rgb_hex = rgb_hex.lstrip('#')
    return tuple(int(rgb_hex[i:i + 2], 16) for i in (0, 2, 4))


def rgb_to_cmy(rgb: tuple) -> dict:
    def rgb_to_cmy_single(rgb_val):
        return int(config.cmy_max_val - rgb_val / config.rgb_cmy_convert_val)

    return {
        'c': rgb_to_cmy_single(rgb[0]),
        'm': rgb_to_cmy_single(rgb[1]),
        'y': rgb_to_cmy_single(rgb[2])
    }


def cmy_to_volume(cmy_triplet: dict) -> dict:
    pass
