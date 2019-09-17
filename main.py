import signal
import sys
import time
import threading
import random
import words
from wordclock import WordClock
import constants
from rpi_ws281x import PixelStrip, Color

# def theaterChase(strip, color, wait_ms=50, iterations=10):
#     """Movie theater light style chaser animation."""
#     for j in range(iterations):
#         for q in range(3):
#             for i in range(0, strip.numPixels(), 3):
#                 strip.setPixelColor(i + q, color)
#             strip.show()
#             time.sleep(wait_ms / 1000.0)
#             for i in range(0, strip.numPixels(), 3):
#                 strip.setPixelColor(i + q, 0)


# def rainbow(strip, wait_ms=20, iterations=1):
#     """Draw rainbow that fades across all pixels at once."""
#     for j in range(256 * iterations):
#         for i in range(strip.numPixels()):
#             strip.setPixelColor(i, wheel((i + j) & 255))
#         strip.show()
#         time.sleep(wait_ms / 1000.0)


# def rainbowCycle(strip, wait_ms=20, iterations=5):
#     """Draw rainbow that uniformly distributes itself across all pixels."""
#     for j in range(256 * iterations):
#         for i in range(strip.numPixels()):
#             strip.setPixelColor(i, wheel(
#                 (int(i * 256 / strip.numPixels()) + j) & 255))
#         strip.show()
#         time.sleep(wait_ms / 1000.0)


# def theaterChaseRainbow(strip, wait_ms=50):
#     """Rainbow movie theater light style chaser animation."""
#     for j in range(256):
#         for q in range(3):
#             for i in range(0, strip.numPixels(), 3):
#                 strip.setPixelColor(i + q, wheel((i + j) % 255))
#             strip.show()
#             time.sleep(wait_ms / 1000.0)
#             for i in range(0, strip.numPixels(), 3):
#                 strip.setPixelColor(i + q, 0)

wordClock = WordClock()

def signal_handler(signal, frame):
    print('You pressed Ctrl+C!')
    wordClock.colorWipe(words.indeciesFromMatrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))
    sys.exit(0)


signal.signal(signal.SIGINT, signal_handler)
print('Press Ctrl-C to quit.')

# Main program logic follows:
if __name__ == '__main__':

    # while True:
    wordClock.colorWipe(words.Its, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.HappyBirthDay, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.FiveM, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.TenM, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.TwentyM, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Minutes, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.Half, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.AQuarter, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.To, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Past, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.One, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Two, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Three, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Four, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Five, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Six, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Seven, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Eight, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Nine, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Ten, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Eleven, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Noon, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
    wordClock.colorWipe(words.Midnight, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.Oclock, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    wordClock.colorWipe(words.AndXMinutes, Color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))

    forever = threading.Event()
    forever.wait()
    #     print('Color wipe animations.')
    #     colorWipe(strip, Color(255, 0, 0))  # Red wipe
    #     colorWipe(strip, Color(0, 255, 0))  # Blue wipe
    #     colorWipe(strip, Color(0, 0, 255))  # Green wipe
    #     print('Theater chase animations.')
    #     theaterChase(strip, Color(127, 127, 127))  # White theater chase
    #     theaterChase(strip, Color(127, 0, 0))  # Red theater chase
    #     theaterChase(strip, Color(0, 0, 127))  # Blue theater chase
    #     print('Rainbow animations.')
    #     rainbow(strip)
    #     rainbowCycle(strip)
    #     theaterChaseRainbow(strip)
