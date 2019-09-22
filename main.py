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
            sentence = words.Its + words.TenM + words.Minutes + words.To + words.Ten
            wordClock.corner_wipe(sentence, 50)
            wordClock.display(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))
            time.sleep(100 / 1000.0)

    except KeyboardInterrupt:
        wordClock.display(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))