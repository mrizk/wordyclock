import time
import constants
from rpi_ws281x import PixelStrip, Color

class LedSetup:
    def __init__(self, pin=18, freq=800000, dma=10, brightness=20, invert=False, channel=0):
        self.pin = pin
        self.freq = freq
        self.dma = dma
        self.brightness = brightness
        self.invert = invert
        self.channel = channel

class WordClock:

    def __init__(self, width, height, origin, stripSetup, rowsAlternateDirection = True):
        self.width = width
        self.height = height
        self.origin = origin
        self.brightness = stripSetup.brightness
        self.color = Color(255, 0, 0)
        self.rowsAlternateDirection = rowsAlternateDirection

        self.strip = PixelStrip(
            self.width * self.height,
            stripSetup.pin,
            stripSetup.freq,
            stripSetup.dma,
            stripSetup.invert,
            stripSetup.brightness,
            stripSetup.channel )

        self.strip.begin()

    def indeciesFromMatrix(self, xStart, xEnd, yStart, yEnd):
        """returns indecies of a word from the given matrix, assumes matrix (0, 0) is top left"""
        indecies = []
        for y in range(0, self.height):
            if y < yStart or y > yEnd:
                continue

            yPos = y
            if self.origin == constants.ORIGIN_BOTTOM_LEFT or self.origin == constants.ORIGIN_BOTTOM_RIGHT:
                yPos = self.height - yPos

            for x in range(0, self.width):
                if x < xStart or x > xEnd:
                    continue

                xPos = x
                if self.rowsAlternateDirection and y % 2 == 0:
                    xPos = self.width - xPos
                
                indecies.append((yPos * self.width) + xPos)

        return indecies

    def colorWipe(self, indecies, color, wait_ms=50):
        """Wipe color across display a pixel at a time."""
        for i in indecies:
            self.strip.setPixelColor(i, color)
            self.strip.show()
            time.sleep(wait_ms / 1000.0)

    def wheel(self, pos):
        """Generate rainbow colors across 0-255 positions."""
        if pos < 85:
            return Color(pos * 3, 255 - pos * 3, 0)
        elif pos < 170:
            pos -= 85
            return Color(255 - pos * 3, 0, pos * 3)
        else:
            pos -= 170
            return Color(0, pos * 3, 255 - pos * 3)
    
    def display(self, matrix, color):
        pass