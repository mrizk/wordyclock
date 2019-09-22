import time
import constants
import words
from rpi_ws281x import PixelStrip, Color

class WordClock:

    def __init__(self):
        self.brightness = 50
        # self.color = Color(255, 0, 0)
        self.corner_wipe_width = 3

        self.strip = PixelStrip(
            constants.CLOCK_WIDTH * constants.CLOCK_HEIGHT,
            constants.LED_PIN,
            constants.LED_FREQ,
            constants.LED_DMA,
            constants.LED_INVERT,
            self.brightness,
            constants.LED_CHANNEL )
        self.strip.begin()

    def wipe(self, indecies, color, wait_ms=50):
        """Wipe color across display a pixel at a time."""
        for i in indecies:
            self.strip.setPixelColor(i, color)
            self.strip.show()
            time.sleep(wait_ms / 1000.0)

    def display(self, indecies, color):
        """Wipe color across display a pixel at a time."""
        for i in indecies:
            self.strip.setPixelColor(i, color)
        self.strip.show()


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
    
    def corner_wipe(self, wait_ms=50):
        index = 0
        row_index = index
        while True:
            for y in range(0, constants.CLOCK_HEIGHT):
                for x in range(0, constants.CLOCK_WIDTH):
                    if x <= row_index and x >= row_index - self.corner_wipe_width:
                        self.display(words.indecies_from_matrix(x, x, y, y), Color(255, 255, 255))
                    else:
                        self.display(words.indecies_from_matrix(x, x, y, y), Color(0, 0, 0))
                row_index -= 1
            index += 1
            time.sleep(wait_ms / 1000.0)