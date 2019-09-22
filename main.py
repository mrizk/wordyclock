import time
import random
import words
from wordclock import WordClock
import constants
from rpi_ws281x import PixelStrip, Color

if __name__ == '__main__':

    wordClock = WordClock()

    print('Press Ctrl-C to quit.')

    try:
        while True:
            wordClock.corner_wipe(10)

    except KeyboardInterrupt:
        wordClock.wipe(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))