from CocktailMixer.utils import config


def convert_msg_to_pump_times(msg):
    drink_percentages = [int(val) for val in msg.split(",")]

    def drink_percentage_to_pump_time(perc_val, perc_tot):
        pump_time = round((perc_val * config.CUP_VOLUME_ML) / (config.PUMP_RATE_ML_S * perc_tot), 2)
        return pump_time

    per_total = sum(drink_percentages)
    return ",".join([str(drink_percentage_to_pump_time(perc_val, per_total)) for perc_val in drink_percentages])
