#include <Time.h>
#include <RTClib.h>
#include <Rotary.h>
#include <Adafruit_NeoPixel.h>

#define STRIP         4
#define N_LEDS      148
#define DIMMER       A0
#define COLOR        A1
#define LED_POWER     7
#define ENABLE        6
#define HOUR_PINA     8
#define HOUR_PINB     9
#define MINUTE_PINA  10
#define MINUTE_PINB  11

#define ORIGIN_TOP_LEFT     0
#define ORIGIN_TOP_RIGHT    1
#define ORIGIN_BOTTOM_LEFT  2
#define ORIGIN_BOTTOM_RIGHT 3

#define CLOCK_WIDTH  12
#define CLOCK_HEIGHT 13
#define CLOCK_ORIGIN ORIGIN_TOP_RIGHT

bool LEDS[CLOCK_WIDTH * CLOCK_HEIGHT];

const byte Its_SIZE = 3;
byte Its[Its_SIZE];

const byte HappyBirthDay_SIZE = 13;
const byte HappyAnniversary_SIZE = 13;
const byte Happy_SIZE = 5;
byte Happy[Happy_SIZE];
const byte Birth_SIZE = 5;
byte Birth[Birth_SIZE];
const byte Day_SIZE = 3;
byte Day[Day_SIZE];
const byte And_SIZE = 1;
byte And[And_SIZE];
const byte Anniversary_SIZE = 11;
byte Anniversary[Anniversary_SIZE];

const byte FiveMin_SIZE = 4;
byte FiveMin[FiveMin_SIZE];
const byte TenMin_SIZE = 3;
byte TenMin[TenMin_SIZE];
const byte TwentyMin_SIZE = 6;
byte TwentyMin[TwentyMin_SIZE];
const byte Minutes_SIZE = 7;
byte Minutes[Minutes_SIZE];

const byte Half_SIZE = 4;
byte Half[Half_SIZE];
const byte A_SIZE = 1;
byte A[A_SIZE];
const byte Quarter_SIZE = 7;
byte Quarter[Quarter_SIZE];

const byte To_SIZE = 2;
byte To[To_SIZE];
const byte Past_SIZE = 4;
byte Past[Past_SIZE];

const byte One_SIZE = 3;
byte One[One_SIZE];
const byte Two_SIZE = 3;
byte Two[Two_SIZE];
const byte Three_SIZE = 5;
byte Three[Three_SIZE];
const byte Four_SIZE = 4;
byte Four[Four_SIZE];
const byte Five_SIZE = 4;
byte Five[Five_SIZE];
const byte Six_SIZE = 3;
byte Six[Six_SIZE];
const byte Seven_SIZE = 5;
byte Seven[Seven_SIZE];
const byte Eight_SIZE = 5;
byte Eight[Eight_SIZE];
const byte Nine_SIZE = 4;
byte Nine[Nine_SIZE];
const byte Ten_SIZE = 3;
byte Ten[Ten_SIZE];
const byte Eleven_SIZE = 6;
byte Eleven[Eleven_SIZE];
const byte Noon_SIZE = 4;
byte Noon[Noon_SIZE];
const byte Midnight_SIZE = 8;
byte Midnight[Midnight_SIZE];

const byte Oclock_SIZE = 6;
byte Oclock[Oclock_SIZE];

const byte AndXMinutes_SIZE = 4;
byte AndXMinutes[AndXMinutes_SIZE];

const byte NumberOfBirthdays = 3;
byte Birthdays[NumberOfBirthdays][4] = {
  {26, 1, 0, 0},
  {24, 8, 0, 0},
  {21, 1, 0, 0},
};
bool ShowBirthdayMsg;

const byte NumberOfAnniversaries = 3;
byte Anniversaries[][4] = {
  {26, 1, 20, 0},
  {30, 11, 0, 0},
  {20, 1, 0, 0},
};
bool ShowAnniversaryMsg;


// 5x8 Serialized Digits
const byte DigitsDisplay_WIDTH = 5;
const byte DigitsDisplay_HEIGHT = 8;
bool Digits[10][40] = {
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 0
  {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0}, // 1
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}, // 2
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 3
  {0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, // 4
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 5
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 6
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 7
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 8
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 9
};

const byte numReadings = 30;

byte dimmerReadings[numReadings];
byte dimmerReadIndex = 0;
byte dimmerTotal = 0;
byte dimmerAverage = 0;
byte brightnessValue = 0;
float floatBrightnessValue = 0.0;
byte pastBrightness = 0;
byte currentBrightness = 0;

byte colorReadings[numReadings];
byte colorReadIndex = 0;
byte colorTotal = 0;
byte colorAverage = 0;
byte currentWordsColor = 0;
float floatColorValue = 0.0;
byte pastWordsColor = 0;
byte colorValue = 0;

byte rainbowColorIndex = 255;

byte currentHour, currentMinute;
byte pastHour, pastMinute;
byte hourToShow;

RTC_DS3231 rtc;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, STRIP, NEO_GRB + NEO_KHZ800);
Rotary hourRotary = Rotary(HOUR_PINA, HOUR_PINB);
Rotary minuteRotary = Rotary(MINUTE_PINA, MINUTE_PINB);

volatile byte hourOffset;
volatile byte minuteOffset;

bool stripUpdated = false;

const byte DelayInterval = 50;
unsigned long timer;
unsigned long countdownTimer;

const byte CornerWipeWidth = 3;
const byte CountdownFrom = 30; // max 60

bool previousEnableState, currentEnableState;

void setup() {
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (true);
  }
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // Serial.print(rtc.getTemperature());
  
  SetupWords();

  hourRotary.begin();
  minuteRotary.begin();
  strip.begin();
  
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT4) | (1 << PCINT5) | (1 << PCINT6) | (1 << PCINT7);
  sei();

  pinMode(ENABLE, INPUT);
  pinMode(LED_POWER, OUTPUT);
  
  timer = millis();
}

void loop() {
  GetColorValue();
  GetBrightnessValue();

  if (millis() - timer >= DelayInterval) {

    currentEnableState = digitalRead(ENABLE);
    if (currentEnableState != previousEnableState) {
      delay(50);
      currentEnableState = digitalRead(ENABLE);
      if (currentEnableState != previousEnableState) {
        if (currentEnableState) {
          StartUp();
        } else {
          Shutdown();
        }
        previousEnableState = currentEnableState;
      }
    }

    if (currentEnableState) {
      if (hourOffset != 0 || minuteOffset != 0) {
        UpdateTime();
      }

      if (StartCountdown(CountdownFrom)) {
        TheaterChaseCountdown(DelayInterval, CountdownFrom, strip.Color(255, 255, 255), strip.Color(255, 0, 0)); // Wheel(currentWordsColor)
        CornerWipe(DelayInterval, CornerWipeWidth, false);
      }
      
      SetTime(false);

      if (ShowBirthdayMsg || ShowAnniversaryMsg) {
        stripUpdated = true;
        RainbowCycle(ShowBirthdayMsg, ShowAnniversaryMsg);
      }
      
      if (stripUpdated) {
        strip.show();
        stripUpdated = false;
      }
    }

    timer = millis();
  }
}

void StartUp() {
  ClearStrip();
  strip.show();
  digitalWrite(LED_POWER, HIGH);

  for (int i = 0; i < numReadings; i++) {
    GetColorValue();
    GetBrightnessValue();
    delay(5);
  }
  strip.setBrightness(50); // TODO: remove this when brightness dimmer is connected
  CornerWipe(DelayInterval, 3, false);
}

void Shutdown() {
  CornerWipe(DelayInterval, 3, true);
  
  ClearStrip();
  strip.show();
  digitalWrite(LED_POWER, LOW);
}

void IndeciesFromMatrix(byte* arr, byte arrSize, byte xStart, byte xEnd, byte yStart, byte yEnd) {
  byte i = 0;
  for (int y = 0; y < CLOCK_HEIGHT; y++){
    if (y >= yStart && y <= yEnd){
      byte yPos = y;

      if (CLOCK_ORIGIN == ORIGIN_BOTTOM_LEFT || CLOCK_ORIGIN == ORIGIN_BOTTOM_RIGHT) {
        yPos = CLOCK_HEIGHT - yPos;
      }

      for (int x = 0; x < CLOCK_WIDTH; x++){
        if (x >= xStart && x <= xEnd){
          byte xPos = x;
          if ((CLOCK_ORIGIN == ORIGIN_TOP_RIGHT || CLOCK_ORIGIN == ORIGIN_BOTTOM_RIGHT) && y % 2 == 0){
            xPos = (CLOCK_WIDTH - 1) - xPos;
          } else if ((CLOCK_ORIGIN == ORIGIN_TOP_LEFT || CLOCK_ORIGIN == ORIGIN_BOTTOM_LEFT) && y % 2 == 1){
            xPos = (CLOCK_WIDTH - 1) - xPos;
          }
          if (i >= arrSize)
            return;
          arr[i] = (yPos * CLOCK_WIDTH) + xPos;
          i++;
        }
      }
    }
  }
}

byte IndexFromCoordinates(byte x, byte y) {
  byte index;
  if (CLOCK_ORIGIN == ORIGIN_TOP_LEFT || CLOCK_ORIGIN == ORIGIN_TOP_RIGHT) {
    index += y * CLOCK_WIDTH;
  } else if (CLOCK_ORIGIN == ORIGIN_BOTTOM_LEFT || CLOCK_ORIGIN == ORIGIN_BOTTOM_RIGHT) {
    index += (CLOCK_HEIGHT - y) * CLOCK_WIDTH;
  }
  if (CLOCK_ORIGIN == ORIGIN_TOP_LEFT || CLOCK_ORIGIN == ORIGIN_BOTTOM_LEFT) {
    if (y%2 == 0) {
      index += x;
    } else {
      index += CLOCK_WIDTH - x - 1;
    }
  } else if (CLOCK_ORIGIN == ORIGIN_TOP_RIGHT || CLOCK_ORIGIN == ORIGIN_BOTTOM_RIGHT) {
    if (y%2 == 0) {
      index += CLOCK_WIDTH - x - 1;
    } else {
      index += x;
    }
  }
  return index;
}

void SetupWords() {
  IndeciesFromMatrix(Its,   Its_SIZE,   0, 2, 0, 0);
  
  IndeciesFromMatrix(Happy,       Happy_SIZE,       7, 11, 1,  1);
  IndeciesFromMatrix(Birth,       Birth_SIZE,       7, 11, 4,  4);
  IndeciesFromMatrix(Day,         Day_SIZE,         7, 9,  7,  7);
  IndeciesFromMatrix(And,         And_SIZE,         11,11, 7,  7);
  IndeciesFromMatrix(Anniversary, Anniversary_SIZE, 1, 11, 10, 10);

  IndeciesFromMatrix(FiveMin,   FiveMin_SIZE,   1, 4 , 2, 2);
  IndeciesFromMatrix(TenMin,    TenMin_SIZE,    8, 10, 0, 0);
  IndeciesFromMatrix(TwentyMin, TwentyMin_SIZE, 0, 5,  1, 1);
  IndeciesFromMatrix(Minutes,   Minutes_SIZE,   0, 6,  3, 3);

  IndeciesFromMatrix(Half,    Half_SIZE,    4, 7,  0, 0);
  IndeciesFromMatrix(A,       A_SIZE,       5, 5,  0, 0);
  IndeciesFromMatrix(Quarter, Quarter_SIZE, 5, 11, 2, 2);

  IndeciesFromMatrix(To,   To_SIZE,   8, 9, 3, 3);
  IndeciesFromMatrix(Past, Past_SIZE, 2, 5, 4, 4);

  IndeciesFromMatrix(One,      One_SIZE,      6, 8,  5,  5);
  IndeciesFromMatrix(Two,      Two_SIZE,      9, 11, 5,  5);
  IndeciesFromMatrix(Three,    Three_SIZE,    0, 4 , 5,  5);
  IndeciesFromMatrix(Four,     Four_SIZE,     4, 7,  6,  6);
  IndeciesFromMatrix(Five,     Five_SIZE,     8, 11, 6,  6);
  IndeciesFromMatrix(Six,      Six_SIZE,      9, 11, 8,  8);
  IndeciesFromMatrix(Seven,    Seven_SIZE,    0, 4,  8,  8);
  IndeciesFromMatrix(Eight,    Eight_SIZE,    0, 4,  11, 11);
  IndeciesFromMatrix(Nine,     Nine_SIZE,     5, 8,  8,  8);
  IndeciesFromMatrix(Ten,      Ten_SIZE,      9, 11, 9,  9);
  IndeciesFromMatrix(Eleven,   Eleven_SIZE,   0, 5,  7,  7);
  IndeciesFromMatrix(Noon,     Noon_SIZE,     0, 3,  6,  6);
  IndeciesFromMatrix(Midnight, Midnight_SIZE, 0, 7,  9,  9);

  IndeciesFromMatrix(Oclock,      Oclock_SIZE,      6, 11, 11, 11);
  IndeciesFromMatrix(AndXMinutes, AndXMinutes_SIZE, 8, 11, 12, 12);
}

void ClearStrip() {
  for (int i = 0; i < N_LEDS; i++) {
    LEDS[i] = false;
  }
  strip.clear();
}

void UpdateTime() {
  DateTime now = rtc.now();
  rtc.adjust(DateTime(now + TimeSpan(0, hourOffset, minuteOffset, -now.second())));
  hourOffset = 0;
  minuteOffset = 0;
}

bool CheckEvent(byte dates[][4], byte numDates, byte minOffset) {
  DateTime now = rtc.now();
  for (int i = 0; i < numDates; i++) {
    if (dates[i][0] == now.day() && dates[i][1] == now.month() && dates[i][2] <= now.hour() && (dates[i][3] - minOffset) <= now.minute()) {
      return true;
    }
  }
  return false;
}

bool TooDifferent(byte a, byte b) {
  if (a - b > 1 || b - a > 1) {
    return true;
  }
  return false;
}

void SetTime(bool force){
  DateTime now = rtc.now();
  currentHour = now.hour();
  currentMinute = now.minute();
  
  if (force || currentHour != pastHour || currentMinute != pastMinute || TooDifferent(currentWordsColor, pastWordsColor) || TooDifferent(currentBrightness, pastBrightness)){
    stripUpdated = true;
    
    pastHour = currentHour;
    pastMinute = currentMinute;
    pastWordsColor = currentWordsColor;
    pastBrightness = currentBrightness;

    ShowBirthdayMsg = CheckEvent(Birthdays, NumberOfBirthdays, 0);
    ShowAnniversaryMsg = CheckEvent(Anniversaries, NumberOfAnniversaries, 0);

    strip.setBrightness(currentBrightness);
    
    ClearStrip();
    
    TurnOn(Its, Its_SIZE);
    
    if (currentMinute <= 4) {
      if (currentHour != 0 && currentHour != 12)
        TurnOn(Oclock, Oclock_SIZE);
    }
    else if ((currentMinute >= 5 && currentMinute < 10) || (currentMinute >= 55 && currentMinute < 60)) {
      TurnOn(FiveMin, FiveMin_SIZE);
      TurnOn(Minutes, Minutes_SIZE);
    }
    else if ((currentMinute >= 10 && currentMinute < 15) || (currentMinute >= 50 && currentMinute < 55)) {
      TurnOn(TenMin, TenMin_SIZE);
      TurnOn(Minutes, Minutes_SIZE);
    }
    else if ((currentMinute >= 15 && currentMinute < 20) || (currentMinute >= 45 && currentMinute < 50)) {
      TurnOn(A, A_SIZE);
      TurnOn(Quarter, Quarter_SIZE);
    }
    else if ((currentMinute >= 20 && currentMinute < 25) || (currentMinute >= 40 && currentMinute < 45)) {
      TurnOn(TwentyMin, TwentyMin_SIZE);
      TurnOn(Minutes, Minutes_SIZE);
    }
    else if ((currentMinute >= 25 && currentMinute < 30) || (currentMinute >= 35 && currentMinute < 40)) {
      TurnOn(TwentyMin, TwentyMin_SIZE);
      TurnOn(FiveMin, FiveMin_SIZE);
      TurnOn(Minutes, Minutes_SIZE);
    }
    else if (currentMinute >= 30 && currentMinute < 35) {
      TurnOn(Half, Half_SIZE);
    }
    
    for (int i = 0; i < (currentMinute % 5); i++){
      byte* ptr_minute = &AndXMinutes[i];
      TurnOn(ptr_minute, 1);
    }
    
    if (currentMinute > 4) {
      if (currentMinute <= 34) {
        TurnOn(Past, Past_SIZE);
        hourToShow = currentHour;
      }
      else {
        TurnOn(To, To_SIZE);
        hourToShow = currentHour + 1;
      }
    }
    else {
      hourToShow = currentHour;
    }
    
    if (hourToShow != 12)
      hourToShow = hourToShow % 12;
    
    switch(hourToShow) {
      case 0:
        TurnOn(Midnight, Midnight_SIZE);
        break;
      case 1:
        TurnOn(One, One_SIZE);
        break;
      case 2:
        TurnOn(Two, Two_SIZE);
        break;
      case 3:
        TurnOn(Three, Three_SIZE);
        break;
      case 4:
        TurnOn(Four, Four_SIZE);
        break;
      case 5:
        TurnOn(Five, Five_SIZE);
        break;
      case 6:
        TurnOn(Six, Six_SIZE);
        break;
      case 7:
        TurnOn(Seven, Seven_SIZE);
        break;
      case 8:
        TurnOn(Eight, Eight_SIZE);
        break;
      case 9:
        TurnOn(Nine, Nine_SIZE);
        break;
      case 10:
        TurnOn(Ten, Ten_SIZE);
        break;
      case 11:
        TurnOn(Eleven, Eleven_SIZE);
        break;
      case 12:
        TurnOn(Noon, Noon_SIZE);
        break;
    }
  }
}

void TurnOn(byte* wordArray, byte wordArray_SIZE) {
  if (currentWordsColor >= 254) {
    for(int i = 0; i < wordArray_SIZE; i++) {
      strip.setPixelColor(wordArray[i], 255, 255, 255);
      LEDS[wordArray[i]] = true;
    }
  } else {
    for(int i = 0; i < wordArray_SIZE; i++) {
      strip.setPixelColor(wordArray[i], Wheel(currentWordsColor));
      LEDS[wordArray[i]] = true;
    }
  }
}

void TurnOff(byte* wordArray, byte wordArray_SIZE) {
  for(int i = 0; i < wordArray_SIZE; i++) {
    strip.setPixelColor(wordArray[i], strip.Color(0, 0, 0));
    LEDS[wordArray[i]] = false;
  }
}

void RainbowCycle(bool birthday, bool anniversary) {
  if (rainbowColorIndex == 0)
    rainbowColorIndex = 255;

  byte totalSize = Happy_SIZE;
  if (birthday) {
    totalSize += Birth_SIZE + Day_SIZE;
  }
  if (anniversary) {
    totalSize += Anniversary_SIZE;
  }

  byte colorIndex;
  for(int i = 0; i < Happy_SIZE; i++) {
    strip.setPixelColor(Happy[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
    colorIndex++;
  }

  if (birthday) {
    for(int i = 0; i < Birth_SIZE; i++) {
      strip.setPixelColor(Birth[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
    for(int i = 0; i < Day_SIZE; i++) {
      strip.setPixelColor(Day[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
  }

  if (birthday && anniversary) {
    for(int i = 0; i < And_SIZE; i++) {
      strip.setPixelColor(And[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
  }

  if (anniversary) {
    for(int i = 0; i < Anniversary_SIZE; i++) {
      strip.setPixelColor(Anniversary[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
  }
  
  rainbowColorIndex--;
}

void GetBrightnessValue() {
  dimmerTotal = dimmerTotal - dimmerReadings[dimmerReadIndex];
  dimmerReadings[dimmerReadIndex] = analogRead(DIMMER);
  dimmerTotal = dimmerTotal + dimmerReadings[dimmerReadIndex];
  
  dimmerReadIndex = dimmerReadIndex + 1;
  if (dimmerReadIndex >= numReadings)
    dimmerReadIndex = 0;
  
  dimmerAverage = dimmerTotal / numReadings;
  floatBrightnessValue = (dimmerAverage / 1023.0) * 255.0;
  currentBrightness = 255 - (byte)floatBrightnessValue;
  
  if (currentBrightness < 1)
    currentBrightness = 1;
  
  if (currentBrightness != pastBrightness)
    stripUpdated = true;
}

void GetColorValue() {
  colorTotal = colorTotal - colorReadings[colorReadIndex];
  colorReadings[colorReadIndex] = analogRead(COLOR);
  colorTotal = colorTotal + colorReadings[colorReadIndex];
  
  colorReadIndex = colorReadIndex + 1;
  if (colorReadIndex >= numReadings)
    colorReadIndex = 0;
  
  colorAverage = colorTotal / numReadings;
  floatColorValue = (colorAverage / 1023.0) * 255.0;
  currentWordsColor = 255 - (byte)floatColorValue;
  
  if (currentWordsColor != pastWordsColor)
    stripUpdated = true;
}

uint32_t Wheel(byte wheelPos) {
  wheelPos = 255 - wheelPos;

  byte threshold1 = 85;
  byte threshold2 = 170;
  
  if (wheelPos < threshold1) {
    return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  else if (wheelPos < threshold2) {
    wheelPos -= threshold1;
    return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  else {
    wheelPos -= threshold2;
    return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  }
}

void CornerWipe(unsigned long wait, byte cornerWipeWidth, bool wipe) {
  byte index = 0;
  byte colorIndex = 255;
  
  if (!wipe) {
    SetTime(true);
  }
  
  while (true) {
    byte rowIndex = index;
    for (int y = 0; y < CLOCK_HEIGHT; y++) {
      for (int x = 0; x < CLOCK_WIDTH; x++) {
        byte ledPos = IndexFromCoordinates(x, y);
        if (y == CLOCK_HEIGHT - 1) { // TODO: generalize this
          ledPos -= AndXMinutes_SIZE;
        }
        if (x <= rowIndex && x > rowIndex - cornerWipeWidth) {
            strip.setPixelColor(ledPos, Wheel((((y * 255) / CLOCK_HEIGHT) + colorIndex) & 255));
        } else {
          if (wipe) {
            if (x <= rowIndex - cornerWipeWidth) {
              strip.setPixelColor(ledPos, strip.Color(0, 0, 0));
            }
          } else {
            if (x <= rowIndex - cornerWipeWidth && LEDS[ledPos]) {
              strip.setPixelColor(ledPos, Wheel(currentWordsColor));
            } else {
              strip.setPixelColor(ledPos, strip.Color(0, 0, 0));
            }
          }
        }
      }
      rowIndex--;
    }
    
    delay(wait);
    strip.show();
    
    index++;
    
    colorIndex--;
    if (colorIndex == 0) {
      colorIndex = 255;
    }
    if (index == CLOCK_WIDTH + CLOCK_HEIGHT + 3) {
      break;
    }
  }
}

ISR(PCINT0_vect) {
  unsigned char hourResult = hourRotary.process();
  if (hourResult == DIR_CW) {
    hourOffset++;
  }
  else if (hourResult == DIR_CCW) {
    hourOffset--;
  }
  unsigned char minuteResult = minuteRotary.process();
  if (minuteResult == DIR_CW) {
    minuteOffset++;
  }
  else if (minuteResult == DIR_CCW) {
    minuteOffset--;
  }
}

void DisplayDigit(byte digit, byte offsetX, byte offsetY) {
  for (int i = 0; i < DigitsDisplay_WIDTH; i++) {
    for (int j = 0; j < DigitsDisplay_HEIGHT; j++) {
      if (offsetX+i > 0 && offsetX+i < CLOCK_WIDTH && offsetY+j > 0 && offsetY+j < CLOCK_HEIGHT) {
        byte index = IndexFromCoordinates(offsetX+i, offsetY+j);
        if (Digits[digit][(j*DigitsDisplay_WIDTH)+i]) {
          TurnOn(&index, 1);
        } else {
          TurnOff(&index, 1);
        }
      }
    }
  }
}

void OverlayDigit(byte digit, byte offsetX, byte offsetY, uint32_t color) {
  for (int i = 0; i < DigitsDisplay_WIDTH; i++) {
    for (int j = 0; j < DigitsDisplay_HEIGHT; j++) {
      if (offsetX+i > 0 && offsetX+i < CLOCK_WIDTH && offsetY+j > 0 && offsetY+j < CLOCK_HEIGHT) {
        byte index = IndexFromCoordinates(offsetX+i, offsetY+j);
        if (Digits[digit][(j*DigitsDisplay_WIDTH)+i]) {
          strip.setPixelColor(index, color);
          LEDS[index] = true;
        }
      }
    }
  }
}

bool StartCountdown(byte counter) {
  DateTime now = rtc.now();
  if (CheckEvent(Birthdays, NumberOfBirthdays, 1) || CheckEvent(Anniversaries, NumberOfAnniversaries, 1)) {
    if (now.second() == (60 - counter)) {
      return true;
    }
  }
  return false;
}

void RainbowCountdown(unsigned long wait, byte counter) {
  countdownTimer = millis();
  uint32_t color = strip.Color(255, 255, 255);
  while (true) {
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i<strip.numPixels(); i++) { 
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      if (millis() - countdownTimer >= 1000) {
        counter--;
        countdownTimer = millis();
        if (counter == 0) return;
      }
      if (counter >= 10) {
        OverlayDigit(counter/10, 0, 2, color);
        OverlayDigit(counter%10, 7, 2, color);
      } else {
        OverlayDigit(counter, 4, 2, color);
      }
      strip.show();
      delay(wait);
    }
  }
}

void TheaterChaseCountdown(unsigned long wait, byte counter, uint32_t color, uint32_t countdownColor) {
  countdownTimer = millis();
  while (true) {
    for(int a=0; a<10; a++) { 
      for(int b=0; b<3; b++) { 
        strip.clear();
        for(int c=b; c<strip.numPixels(); c += 3) {
          strip.setPixelColor(c, color);
        }
        if (millis() - countdownTimer >= 1000) {
          counter--;
          countdownTimer = millis();
          if (counter == 0) return;
        }
        if (counter >= 10) {
          OverlayDigit(counter/10, 0, 2, countdownColor);
          OverlayDigit(counter%10, 7, 2, countdownColor);
        } else {
          OverlayDigit(counter, 4, 2, countdownColor);
        }
        strip.show();
        delay(wait);
      }
    }
  }
}