import time
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


# Main program logic follows:
if __name__ == '__main__':

    wordClock = WordClock()

    print('Press Ctrl-C to quit.')

    try:
        while True:
            wordClock.corner_wipe(50)

    except KeyboardInterrupt:
        wordClock.wipe(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))