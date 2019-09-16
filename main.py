import time
from rpi_ws281x import PixelStrip, Color
from wordclock import *

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

    setup = LedSetup(brightness=50)
    wordClock = WordClock(12, 12, constants.ORIGIN_TOP_RIGHT, setup)

    print('Press Ctrl-C to quit.')

    try:

        while True:
            wordClock.colorWipe(wordClock.indeciesFromMatrix(0, 3, 0, 3), Color(255, 0, 0))
            wordClock.colorWipe(wordClock.indeciesFromMatrix(2, 5, 2, 5), Color(0, 255, 0))
            wordClock.colorWipe(wordClock.indeciesFromMatrix(4, 7, 4, 7), Color(0, 0, 255))
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

    except KeyboardInterrupt:
        wordClock.colorWipe(wordClock.indeciesFromMatrix(0, 11, 0, 11), Color(0, 0, 0))