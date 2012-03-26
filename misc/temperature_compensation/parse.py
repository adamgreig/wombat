import re

temp_regex = r"^\$\$\$\d,\d{1,2},([\-0-9.]{4,6})\$\$\$$"
freq_regex = r"^<<[0-9\-:TZ]{17} RTTY @ (\d{9})\+(\d{4})>>$"

temperature = 0.0
frequency = 0

with open("wombat_fridge.txt") as f:
    for line in f:
        result = re.match(temp_regex, line)
        if result:
            temperature = float(result.group(1))
        result = re.match(freq_regex, line)
        if result:
            dial_frequency = int(result.group(1))
            offset_frequency = int(result.group(2))
            centre_frequency = dial_frequency + offset_frequency
            print "{0} {1}".format(centre_frequency, temperature)
