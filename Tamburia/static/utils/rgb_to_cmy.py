# Cup volume in milliliters
cup_volume_ml = 200

# Pump rate in milliliters per second
pump_rate_ml_s = 10 # FIXME


def hex_to_rgb(rgb_hex: str) -> tuple:
    rgb_hex = rgb_hex.lstrip('#')
    return tuple(int(rgb_hex[i:i + 2], 16) for i in (0, 2, 4))


h = input()
print(hex_to_rgb(h))


def rgb_hex_to_cmy(rgb_hex: str) -> dict:
    pass


def cmy_to_volume(cmy_triplet: dict) -> dict:
    pass
