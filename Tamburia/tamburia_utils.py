import config
tamburia_is_running = False


def run_tamburia(colors_pump_duration: dict):
    """
    Run the Tamburia!
    Literally pump the colors to the cup.
    set / unset tamburia_is_running, on startup and on finish
    :param colors_pump_duration: a dict containing info of how much time should the color pump
    :type colors_pump_duration: dict
    :return: FOCKING NOTHING FOR NOW
    """
    # it will set and unset am_i_running when starts / done


def calc_pump_duration(cmy_value: int, cmy_total):
    """
    calculate the amount of time needed to pump the color to the cup,
    according to it's CMY value, and the sum of the CMY triplet.
    :param cmy_total: sum of the CMY triplet
    :param cmy_value: the CMY value to convert to pumping time
    :return: time, in seconds
    """

    pump_duration = (cmy_value * config.cup_volume) / (config.pump_rate * cmy_total)
    return pump_duration


def convert_cmy_to_pump_duration(cmy_triplet: dict):
    """
    Convert a C / M / Y value to the duration of time the pump needs to pump liquid.
    The value is rounded! float -> int !!!!
    :param cmy_triplet: CMY values, picked by the user in the website
    :type cmy_triplet: dict
    :return: my life
    """
    colors_pump_duration = {key: int(calc_pump_duration(value, sum(cmy_triplet.values()))) for key, value in cmy_triplet.items()}

    return colors_pump_duration

# TODO - add more logging in JS and in python!
# TODO - get a fucking RP !!!!!!!!!!!!!!
# TODO - try / except if needed?
# TODO - consider a computer to run the server, in order to handle exceptions and stuff
