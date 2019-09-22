import time
import datetime
import constants
import words
from rpi_ws281x import PixelStrip, Color

class WordClock:

    def __init__(self):
        self.brightness = 50
        # self.color = Color(255, 0, 0)
        self.corner_wipe_width = 3
        self.time_words = None
        self.past_hour = None
        self.past_minute = None
        self.clock_updated = False

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
        color_index = 255
        height = constants.CLOCK_HEIGHT - 1
        width = constants.CLOCK_WIDTH
        while True:
            row_index = index
            for y in range(0, height):
                for x in range(0, width):
                    led_pos = words.indecies_from_matrix(x, x, y, y)[0]
                    if x <= row_index and x > row_index - self.corner_wipe_width:
                        color = self.wheel((((y * 255) / (width)) + color_index) & 255)
                        self.strip.setPixelColor(led_pos, color)
                    else:
                        if x < row_index - self.corner_wipe_width and led_pos in self.time_words:
                            self.strip.setPixelColor(led_pos, Color(255, 255, 255))
                        else:
                            self.strip.setPixelColor(led_pos, Color(0, 0, 0))
                row_index -= 1
            time.sleep(wait_ms / 1000.0)
            self.strip.show()
            index += 1
            color_index -= 1
            if color_index == 0:
                color_index = 255
            if index == width + height + 3:
                return

    def set_time_words(self):
        now = datetime.datetime.now()
        if now.hour != self.past_hour or now.minute != self.past_minute:
            self.clock_updated = True
            self.past_hour = now.hour
            self.past_minute = now.minute

            self.display(words.indecies_from_matrix(0, constants.CLOCK_WIDTH-1, 0, constants.CLOCK_HEIGHT-1), Color(0, 0, 0))

            time_words = words.Its

            if now.minute <= 4 and now.hour != 0 and now.hour != 12:
                time_words += words.Oclock

            elif (now.minute >= 5 and now.minute < 10) or (now.minute >= 55 and now.minute < 60):
                time_words += words.FiveM + words.Minutes

            elif (now.minute >= 10 and now.minute < 15) or (now.minute >= 50 and now.minute < 55):
                time_words += words.TenM + words.Minutes

            elif (now.minute >= 15 and now.minute < 20) or (now.minute >= 45 and now.minute < 50):
                time_words += words.AQuarter

            elif (now.minute >= 20 and now.minute < 25) or (now.minute >= 40 and now.minute < 45):
                time_words += words.TwentyM + words.Minutes

            elif (now.minute >= 25 and now.minute < 30) or (now.minute >= 35 and now.minute < 40):
                time_words += words.TwentyM + words.FiveM + words.Minutes

            elif now.minute >= 30 and now.minute < 35:
                time_words += words.Half
            
            for i in range(0, now.minute % 5):
                time_words += words.AndXMinutes[i]

            hour_to_show = now.hour
            if now.minute > 4:
                if now.minute <= 34:
                    time_words += words.Past
                    hour_to_show = now.hour
                else:
                    time_words += words.To
                    hour_to_show = now.hour + 1
            
            if hour_to_show != 12:
                hour_to_show = hour_to_show % 12
            
            if hour_to_show == 0:
                time_words += words.Midnight
            elif hour_to_show == 1:
                time_words += words.One
            elif hour_to_show == 2:
                time_words += words.Two
            elif hour_to_show == 3:
                time_words += words.Three
            elif hour_to_show == 4:
                time_words += words.Four
            elif hour_to_show == 5:
                time_words += words.Five
            elif hour_to_show == 6:
                time_words += words.Six
            elif hour_to_show == 7:
                time_words += words.Seven
            elif hour_to_show == 8:
                time_words += words.Eight
            elif hour_to_show == 9:
                time_words += words.Nine
            elif hour_to_show == 10:
                time_words += words.Ten
            elif hour_to_show == 11:
                time_words += words.Eleven
            elif hour_to_show == 12:
                time_words += words.Noon
            
            self.time_words = time_words