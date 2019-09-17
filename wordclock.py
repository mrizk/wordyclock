import time
import constants
import words
from rpi_ws281x import PixelStrip, Color

class WordClock:

    def __init__(self):
        self.brightness = 100
        # self.color = Color(255, 0, 0)

        self.strip = PixelStrip(
            constants.CLOCK_WIDTH * constants.CLOCK_HEIGHT,
            constants.LED_PIN,
            constants.LED_FREQ,
            constants.LED_DMA,
            constants.LED_INVERT,
            self.brightness,
            constants.LED_CHANNEL )
        self.strip.begin()

    def colorWipe(self, indecies, color, wait_ms=50):
        """Wipe color across display a pixel at a time."""
        print(indecies)
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