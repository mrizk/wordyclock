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

    
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    print("r: " + str(r))
    print("g: " + str(g))
    print("b: " + str(b))

    try:

            wordClock.colorWipe(words.Its, Color(r, g, b))

            wordClock.colorWipe(words.HappyBirthDay, Color(r, g, b))

            wordClock.colorWipe(words.Five, Color(r, g, b))
            wordClock.colorWipe(words.Ten, Color(r, g, b))
            wordClock.colorWipe(words.Twenty, Color(r, g, b))
            wordClock.colorWipe(words.Minutes, Color(r, g, b))

            wordClock.colorWipe(words.Half, Color(r, g, b))
            wordClock.colorWipe(words.AQuarter, Color(r, g, b))

            wordClock.colorWipe(words.To, Color(r, g, b))
            wordClock.colorWipe(words.Past, Color(r, g, b))

            wordClock.colorWipe(words.One, Color(r, g, b))
            wordClock.colorWipe(words.Two, Color(r, g, b))
            wordClock.colorWipe(words.Three, Color(r, g, b))
            wordClock.colorWipe(words.Four, Color(r, g, b))
            wordClock.colorWipe(words.Five, Color(r, g, b))
            wordClock.colorWipe(words.Six, Color(r, g, b))
            wordClock.colorWipe(words.Seven, Color(r, g, b))
            wordClock.colorWipe(words.Eight, Color(r, g, b))
            wordClock.colorWipe(words.Nine, Color(r, g, b))
            wordClock.colorWipe(words.Ten, Color(r, g, b))
            wordClock.colorWipe(words.Eleven, Color(r, g, b))
            wordClock.colorWipe(words.Noon, Color(r, g, b))
            wordClock.colorWipe(words.Midnight, Color(r, g, b))

            wordClock.colorWipe(words.Oclock, Color(r, g, b))

            wordClock.colorWipe(words.AndXMinutes, Color(r, g, b))

            time.sleep(10000)
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
        wordClock.colorWipe(words.indeciesFromMatrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))