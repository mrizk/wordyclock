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
        wordClock.set_time_words()
        wordClock.corner_wipe(50)
        while True:
            wordClock.display(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))
            wordClock.set_time_words()
            if wordClock.clock_updated:
                wordClock.display(wordClock.time_words, Color(255, 255, 255))
            time.sleep(50 / 1000.0)


    except KeyboardInterrupt:
        wordClock.display(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))