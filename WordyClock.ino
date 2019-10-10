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

const int Its_SIZE = 3;
int Its[Its_SIZE];

const int HappyBirthDay_SIZE = 13;
const int HappyAnniversary_SIZE = 13;
const int Happy_SIZE = 5;
int Happy[Happy_SIZE];
const int Birth_SIZE = 5;
int Birth[Birth_SIZE];
const int Day_SIZE = 3;
int Day[Day_SIZE];
const int And_SIZE = 1;
int And[And_SIZE];
const int Anniversary_SIZE = 11;
int Anniversary[Anniversary_SIZE];

const int FiveMin_SIZE = 4;
int FiveMin[FiveMin_SIZE];
const int TenMin_SIZE = 3;
int TenMin[TenMin_SIZE];
const int TwentyMin_SIZE = 6;
int TwentyMin[TwentyMin_SIZE];
const int Minutes_SIZE = 7;
int Minutes[Minutes_SIZE];

const int Half_SIZE = 4;
int Half[Half_SIZE];
const int A_SIZE = 1;
int A[A_SIZE];
const int Quarter_SIZE = 7;
int Quarter[Quarter_SIZE];

const int To_SIZE = 2;
int To[To_SIZE];
const int Past_SIZE = 4;
int Past[Past_SIZE];

const int One_SIZE = 3;
int One[One_SIZE];
const int Two_SIZE = 3;
int Two[Two_SIZE];
const int Three_SIZE = 5;
int Three[Three_SIZE];
const int Four_SIZE = 4;
int Four[Four_SIZE];
const int Five_SIZE = 4;
int Five[Five_SIZE];
const int Six_SIZE = 3;
int Six[Six_SIZE];
const int Seven_SIZE = 5;
int Seven[Seven_SIZE];
const int Eight_SIZE = 5;
int Eight[Eight_SIZE];
const int Nine_SIZE = 4;
int Nine[Nine_SIZE];
const int Ten_SIZE = 3;
int Ten[Ten_SIZE];
const int Eleven_SIZE = 6;
int Eleven[Eleven_SIZE];
const int Noon_SIZE = 4;
int Noon[Noon_SIZE];
const int Midnight_SIZE = 8;
int Midnight[Midnight_SIZE];

const int Oclock_SIZE = 6;
int Oclock[Oclock_SIZE];

const int AndXMinutes_SIZE = 4;
int AndXMinutes[AndXMinutes_SIZE];

const int NumberOfBirthdays = 2;
int Birthdays[NumberOfBirthdays][2] = {
  {10, 10},
  {24, 8}
};
bool ShowBirthdayMsg;

const int NumberOfAnniversaries = 1;
int Anniversaries[][2] = {
  {28, 9},
};
bool ShowAnniversaryMsg;

const int numReadings = 30;

int dimmerReadings[numReadings];
int dimmerReadIndex = 0;
int dimmerTotal = 0;
int dimmerAverage = 0;
int brightnessValue = 0;
float floatBrightnessValue = 0.0;
int pastBrightness = 0;
int currentBrightness = 0;

int colorReadings[numReadings];
int colorReadIndex = 0;
int colorTotal = 0;
int colorAverage = 0;
int currentWordsColor = 0;
float floatColorValue = 0.0;
int pastWordsColor = 0;
int colorValue = 0;

int rainbowColorIndex = 255;

int currentHour, currentMinute;
int pastHour, pastMinute;
int hourToShow;

RTC_DS3231 rtc;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, STRIP, NEO_GRB + NEO_KHZ800);
Rotary hourRotary = Rotary(HOUR_PINA, HOUR_PINB);
Rotary minuteRotary = Rotary(MINUTE_PINA, MINUTE_PINB);

volatile int hourOffset;
volatile int minuteOffset;

bool stripUpdated = false;

unsigned long delayInterval = 50;
unsigned long timer;

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
  
  if (millis() - timer >= delayInterval) {

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
  CornerWipe(3, 40, false);
}

void Shutdown() {
  CornerWipe(3, 40, true);
  
  ClearStrip();
  strip.show();
  digitalWrite(LED_POWER, LOW);
}

void IndeciesFromMatrix(int* arr, int arrSize, int xStart, int xEnd, int yStart, int yEnd) {
  int i = 0;
  for (int y = 0; y < CLOCK_HEIGHT; y++){
    if (y >= yStart && y <= yEnd){
      int yPos = y;

      if (CLOCK_ORIGIN == ORIGIN_BOTTOM_LEFT || CLOCK_ORIGIN == ORIGIN_BOTTOM_RIGHT) {
        yPos = CLOCK_HEIGHT - yPos;
      }

      for (int x = 0; x < CLOCK_WIDTH; x++){
        if (x >= xStart && x <= xEnd){
          int xPos = x;
          if ((CLOCK_ORIGIN == ORIGIN_TOP_RIGHT || CLOCK_ORIGIN == ORIGIN_BOTTOM_RIGHT) && y % 2 == 0){
            xPos = (CLOCK_WIDTH - 1) - xPos;
          } else if ((CLOCK_ORIGIN == ORIGIN_TOP_LEFT || CLOCK_ORIGIN == ORIGIN_BOTTOM_LEFT) && y % 2 == 1){
            xPos = (CLOCK_WIDTH - 1) - xPos;
          }
          arr[i] = (yPos * CLOCK_WIDTH) + xPos;
          i++;
        }
      }
    }
  }
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

bool CheckEvent(int dates[][2], int numDates) {
  DateTime now = rtc.now();
  for (int i = 0; i < numDates; i++) {
    if (dates[i][0] == now.day() && dates[i][1] == now.month()) {
      return true;
    }
  }
  return false;
}

bool TooDifferent(int a, int b) {
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

    ShowBirthdayMsg = CheckEvent(Birthdays, NumberOfBirthdays);
    ShowAnniversaryMsg = CheckEvent(Anniversaries, NumberOfAnniversaries);

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
      int* ptr_minute = &AndXMinutes[i];
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

void TurnOn(int* wordArray, int wordArray_SIZE) {
  if (currentWordsColor >= 254) {
    for(int i = 0; i < wordArray_SIZE; i++) {
      strip.setPixelColor(wordArray[i], 255, 255, 255);
      LEDS[wordArray[i]] = true;
    }
  } else {
    for(int i = 0; i < wordArray_SIZE; i++) {
      strip.setPixelColor(wordArray[i], Wheel(((i * 256) + currentWordsColor) & 255));
      LEDS[wordArray[i]] = true;
    }
  }
}

// TODO: make this work better with wipe
void RainbowCycle(bool birthday, bool anniversary) {
  if (rainbowColorIndex == 0)
    rainbowColorIndex = 255;

  int totalSize = Happy_SIZE;
  if (birthday) {
    totalSize += Birth_SIZE + Day_SIZE;
  }
  if (anniversary) {
    totalSize += Anniversary_SIZE;
  }

  int colorIndex;
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
  currentBrightness = 255 - (int)floatBrightnessValue;
  
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
  currentWordsColor = 255 - (int)floatColorValue;
  
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

void CornerWipe(int cornerWipeWidth, int wait, bool wipe) {
  int index = 0;
  int colorIndex = 255;
  
  if (!wipe) {
    SetTime(true);
  }
  
  while (true) {
    int rowIndex = index;
    for (int y = 0; y < CLOCK_HEIGHT; y++) {
      for (int x = 0; x < CLOCK_WIDTH; x++) {
        int* ledPos;
        IndeciesFromMatrix(ledPos, 1, x, x, y, y);
        if (x <= rowIndex && x > rowIndex - cornerWipeWidth) {
            strip.setPixelColor(*ledPos, Wheel((((y * 255) / CLOCK_HEIGHT) + colorIndex) & 255));
        } else {
          if (wipe) {
            if (x <= rowIndex - cornerWipeWidth) {
              strip.setPixelColor(*ledPos, strip.Color(0, 0, 0));
            }
          } else {
            if (x <= rowIndex - cornerWipeWidth && LEDS[*ledPos]) {
              strip.setPixelColor(*ledPos, Wheel(currentWordsColor));
            } else {
              strip.setPixelColor(*ledPos, strip.Color(0, 0, 0));
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