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

#define CLOCK_WIDTH  12
#define CLOCK_HEIGHT 13
#define CLOCK_ORIGIN ORIGIN_TOP_RIGHT

bool LEDS[N_LEDS];

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
int Birthdays[NumberOfBirthdays][4] = {
  {26, 1, 0, 0},
  {24, 10, 0, 0},
};
bool ShowBirthdayMsg;

const int NumberOfAnniversaries = 3;
int Anniversaries[][4] = {
  {26, 1, 20, 0},
  {30, 11, 0, 0},
  {30, 8, 8, 0},
};
bool ShowAnniversaryMsg;


// 5x8 Serialized Digits
const int DigitsDisplay_WIDTH = 5;
const int DigitsDisplay_HEIGHT = 8;
bool Digits[10][40] = {
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 0
  {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0}, // 1
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}, // 2
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 3
  {0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, // 4
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 5
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 6
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 7
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 8
  {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}, // 9
};

const int numReadings = 30;

int dimmerReadings[numReadings];
int dimmerReadIndex = 0;
int dimmerTotal = 0;
int pastBrightness = 0;
int currentBrightness = 0;

int colorReadings[numReadings];
int colorReadIndex = 0;
int colorTotal = 0;
int currentWordsColor = 0;
int pastWordsColor = 0;

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

const int DelayInterval = 50;
unsigned long timer;
unsigned long countdownTimer;

const int CornerWipeWidth = 3;
const int CountdownFrom = 30; // max 60

int previousEnableState, currentEnableState;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(2));

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
        TheaterChaseCountdown(DelayInterval, CountdownFrom, strip.Color(255, 255, 255), strip.Color(255, 0, 0));
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
  
  DateTime now = rtc.now();
  int month = now.month();
  int day = now.day();
  if ((month == 9 && day >= 21) || month == 10 || month == 11 || (month == 12 && day < 21)) {
    RainAnimation(30, 80, 11, 50, RainPrinter);
  } else if ((month == 12 && day >= 21) || month == 1 || month == 2 || (month == 3 && day < 21)) {
    RainAnimation(30, 80, 11, 50, SnowPrinter);
  } else if ((month == 3 && day >= 21) || month == 4 || month == 5 || (month == 6 && day < 21)) {
    RainAnimation(30, 80, 11, 50, MatrixPrinter);
  } else if ((month == 6 && day >= 21) || month == 7 || month == 8 || (month == 9 && day < 21)) {
    RainAnimation(30, 80, 11, 50, SunsetRainPrinter);
  }
  CornerWipe(DelayInterval, 3, false);
}

void Shutdown() {
  CornerWipe(DelayInterval, 3, true);
  
  ClearStrip();
  strip.show();
  digitalWrite(LED_POWER, LOW);
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

void IndeciesFromMatrix(int* arr, int arrSize, int xStart, int xEnd, int yStart, int yEnd) {
  int i = 0;
  for (int y = 0; y < CLOCK_HEIGHT; y++){
    if (y >= yStart && y <= yEnd){
      int yPos = y;

      for (int x = 0; x < CLOCK_WIDTH; x++){
        if (x >= xStart && x <= xEnd){
          int xPos = x;
          if ((CLOCK_ORIGIN == ORIGIN_TOP_RIGHT && y % 2 == 0) || (CLOCK_ORIGIN == ORIGIN_TOP_LEFT && y % 2 == 1)){
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

int IndexFromCoordinates(int x, int y) {
  int index = y * CLOCK_WIDTH;
  if (CLOCK_ORIGIN == ORIGIN_TOP_LEFT) {
    if (y%2 == 0) {
      index += x;
    } else {
      index += CLOCK_WIDTH - x - 1;
    }
  } else if (CLOCK_ORIGIN == ORIGIN_TOP_RIGHT) {
    if (y%2 == 0) {
      index += CLOCK_WIDTH - x - 1;
    } else {
      index += x;
    }
  }
  return index;
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

    ShowBirthdayMsg = CheckPastEvent(Birthdays, NumberOfBirthdays);
    ShowAnniversaryMsg = CheckPastEvent(Anniversaries, NumberOfAnniversaries);

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

void GetBrightnessValue() {
  dimmerTotal = dimmerTotal - dimmerReadings[dimmerReadIndex];
  dimmerReadings[dimmerReadIndex] = analogRead(DIMMER);
  dimmerTotal = dimmerTotal + dimmerReadings[dimmerReadIndex];
  
  dimmerReadIndex = dimmerReadIndex + 1;
  if (dimmerReadIndex >= numReadings)
    dimmerReadIndex = 0;
  
  currentBrightness = map(dimmerTotal / numReadings, 0, 1023, 0, 255);
  
  if (currentBrightness < 1)
    currentBrightness = 1;
  
  if (TooDifferent(currentBrightness, pastBrightness))
    stripUpdated = true;
}

void GetColorValue() {
  colorTotal = colorTotal - colorReadings[colorReadIndex];
  colorReadings[colorReadIndex] = analogRead(COLOR);
  colorTotal = colorTotal + colorReadings[colorReadIndex];
  
  colorReadIndex = colorReadIndex + 1;
  if (colorReadIndex >= numReadings)
    colorReadIndex = 0;
  
  currentWordsColor = map(colorTotal / numReadings, 0, 1023, 0, 255);
  
  if (TooDifferent(currentWordsColor, pastWordsColor))
    stripUpdated = true;
}

void UpdateTime() {
  DateTime now = rtc.now();
  rtc.adjust(DateTime(now + TimeSpan(0, hourOffset, minuteOffset, -now.second()+1)));
  hourOffset = 0;
  minuteOffset = 0;
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

void TurnOn(int* wordArray, int wordArray_SIZE) {
  if (currentWordsColor >= 254) {
    for (int i = 0; i < wordArray_SIZE; i++) {
      strip.setPixelColor(wordArray[i], 255, 255, 255);
      LEDS[wordArray[i]] = true;
    }
  } else {
    for (int i = 0; i < wordArray_SIZE; i++) {
      strip.setPixelColor(wordArray[i], Wheel(currentWordsColor));
      LEDS[wordArray[i]] = true;
    }
  }
}

void TurnOff(int* wordArray, int wordArray_SIZE) {
  for (int i = 0; i < wordArray_SIZE; i++) {
    strip.setPixelColor(wordArray[i], strip.Color(0, 0, 0));
    LEDS[wordArray[i]] = false;
  }
}

void ClearStrip() {
  for (int i = 0; i < N_LEDS; i++) {
    LEDS[i] = false;
  }
  strip.clear();
}

bool CheckPastEvent(int dates[][4], int numDates) {
  DateTime now = rtc.now();
  for (int i = 0; i < numDates; i++) {
    if (dates[i][0] == now.day() && dates[i][1] == now.month() && dates[i][2] <= now.hour() && dates[i][3] <= now.minute()) {
      return true;
    }
  }
  return false;
}

bool CheckFutureEvent(int dates[][4], int numDates) {
  DateTime future = DateTime(rtc.now() + TimeSpan(0, 0, 1, 0));
  for (int i = 0; i < numDates; i++) {
    if (dates[i][0] == future.day() && dates[i][1] == future.month() && dates[i][2] == future.hour() && dates[i][3] == future.minute()) {
      return true;
    }
  }
  return false;
}

bool StartCountdown(int counter) {
  DateTime now = rtc.now();
  if (CheckFutureEvent(Birthdays, NumberOfBirthdays) || CheckFutureEvent(Anniversaries, NumberOfAnniversaries)) {
    if (now.second() == (60 - counter)) {
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
  for (int i = 0; i < Happy_SIZE; i++) {
    strip.setPixelColor(Happy[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
    colorIndex++;
  }

  if (birthday) {
    for (int i = 0; i < Birth_SIZE; i++) {
      strip.setPixelColor(Birth[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
    for (int i = 0; i < Day_SIZE; i++) {
      strip.setPixelColor(Day[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
  }

  if (birthday && anniversary) {
    for (int i = 0; i < And_SIZE; i++) {
      strip.setPixelColor(And[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
  }

  if (anniversary) {
    for (int i = 0; i < Anniversary_SIZE; i++) {
      strip.setPixelColor(Anniversary[i], Wheel(((colorIndex * 255 / totalSize) + rainbowColorIndex) & 255));
      colorIndex++;
    }
  }
  
  rainbowColorIndex--;
}

uint32_t Wheel(int wheelPos) {
  wheelPos = 255 - wheelPos;

  int threshold1 = 85;
  int threshold2 = 170;
  
  int r, g, b;

  if (wheelPos < threshold1) {
    r = 255 - wheelPos * 3;
    g = 0;
    b = wheelPos * 3;
  }
  else if (wheelPos < threshold2) {
    wheelPos -= threshold1;
    r = 0;
    g = wheelPos * 3;
    b = 255 - wheelPos * 3;
  }
  else {
    wheelPos -= threshold2;
    r = wheelPos * 3;
    g = 255 - wheelPos * 3;
    b = 0;
  }
  return strip.Color(r, g, b);
}

void CornerWipe(unsigned long wait, int cornerWipeWidth, bool wipe) {
  int index = 0;
  int colorIndex = 255;
  
  if (!wipe) {
    SetTime(true);
  }
  
  while (true) {
    int rowIndex = index;
    for (int y = 0; y < CLOCK_HEIGHT; y++) {
      for (int x = 0; x < CLOCK_WIDTH; x++) {
        int ledPos = IndexFromCoordinates(x, y);
        if (y == CLOCK_HEIGHT - 1) {
          ledPos -= AndXMinutes_SIZE;
          if (ledPos < N_LEDS - AndXMinutes_SIZE) continue;
        }
        if (ledPos >= N_LEDS) continue;
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

void DisplayDigit(int digit, int offsetX, int offsetY, uint32_t color, bool overlay) {
  for (int i = 0; i < DigitsDisplay_WIDTH; i++) {
    for (int j = 0; j < DigitsDisplay_HEIGHT; j++) {
      if (offsetX+i >= 0 && offsetX+i < CLOCK_WIDTH && offsetY+j >= 0 && offsetY+j < CLOCK_HEIGHT) {
        int index = IndexFromCoordinates(offsetX+i, offsetY+j);
        bool pixelOn = Digits[digit][(j*DigitsDisplay_WIDTH)+i];
        if (overlay) {
          if (pixelOn) {
            strip.setPixelColor(index, color);
            LEDS[index] = true;
          }
        } else {
          if (pixelOn) {
            TurnOn(&index, 1);
          } else {
            TurnOff(&index, 1);
          }
        }
      }
    }
  }
}

void RainbowCountdown(unsigned long wait, int counter) {
  countdownTimer = millis();
  uint32_t color = strip.Color(255, 255, 255);
  while (true) {
    for (long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for (int i = 0; i < N_LEDS; i++) { 
        int pixelHue = firstPixelHue + (i * 65536L / N_LEDS);
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      if (millis() - countdownTimer >= 1000) {
        counter--;
        countdownTimer = millis();
        if (counter == 0) return;
      }
      if (counter >= 10) {
        DisplayDigit(counter/10, 0, 2, color, true);
        DisplayDigit(counter%10, 7, 2, color, true);
      } else {
        DisplayDigit(counter, 4, 2, color, true);
      }
      strip.show();
      delay(wait);
    }
  }
}

void TheaterChaseCountdown(unsigned long wait, int counter, uint32_t color, uint32_t countdownColor) {
  countdownTimer = millis();
  while (true) {
    for (int a = 0; a < 10; a++) { 
      for (int b = 0; b < 3; b++) { 
        strip.clear();
        for (int c = b; c < N_LEDS; c += 3) {
          strip.setPixelColor(c, color);
        }
        if (millis() - countdownTimer >= 1000) {
          counter--;
          countdownTimer = millis();
          if (counter == 0) return;
        }
        if (counter >= 10) {
          DisplayDigit(counter/10, 0, 2, countdownColor, true);
          DisplayDigit(counter%10, 7, 2, countdownColor, true);
        } else {
          DisplayDigit(counter, 4, 2, countdownColor, true);
        }
        strip.show();
        delay(wait);
      }
    }
  }
}

void MatrixPrinter(int pixelValue, int index, int beamID, int beamLength) {
  if (pixelValue == beamLength) {
    strip.setPixelColor(index, 128, 128, 128);
  } else if (pixelValue > 0) {
    strip.setPixelColor(index, 0, (255*pixelValue/beamLength), 0);
  } else {
    strip.setPixelColor(index, 0, 0, 0);
  }
}

void RainPrinter(int pixelValue, int index, int beamID, int beamLength) {
  if (pixelValue > 0) {
    strip.setPixelColor(index, 0, 0, (255*pixelValue/beamLength));
  } else {
    strip.setPixelColor(index, 0, 0, 0);
  }
}

void SunsetRainPrinter(int pixelValue, int index, int beamID, int beamLength) {
  int sunsetColors = 5;
  uint32_t sunsetColor[5] = {Wheel(14), Wheel(23), Wheel(34), Wheel(196), Wheel(214)};
  int i = 0;
  if (beamID > sunsetColors) {
    i = beamID % sunsetColors;
  } else {
    i = sunsetColors % beamID;
  }
  if (pixelValue > 0) {
    strip.setPixelColor(index, sunsetColor[i]);
  } else {
    strip.setPixelColor(index, 0, 0, 0);
  }
}

void SunriseRainPrinter(int pixelValue, int index, int beamID, int beamLength) {
  int sunriseColors = 6;
  uint32_t sunriseColor[6] = {Wheel(193), Wheel(187), Wheel(126), Wheel(40), Wheel(32), Wheel(21)};
  int i = 0;
  if (beamID > sunriseColors) {
    i = beamID % sunriseColors;
  } else {
    i = sunriseColors % beamID;
  }
  if (pixelValue > 0) {
    strip.setPixelColor(index, sunriseColor[i]);
  } else {
    strip.setPixelColor(index, 0, 0, 0);
  }
}

void SnowPrinter(int pixelValue, int index, int beamID, int beamLength) {
  if (pixelValue == beamLength) {
    strip.setPixelColor(index, 128, 128, 128);
  } else {
    strip.setPixelColor(index, 0, 0, 0);
  }
}

const int RainSpeed_SIZE = 5;
int RainSpeed[RainSpeed_SIZE] = {0, 0, 1, 2, 2};

void RainAnimation(unsigned long wait, int rainProbability, int beamLength, int maxBeamCount, void(*printRain)(int, int, int, int)) {

  int width = CLOCK_WIDTH;
  int height = CLOCK_HEIGHT - 1;
  int pixels[width][height];
  int beamDelay[width];
  int beamDelayTracker[width];
  int beamID[width];
  bool beamDropping[width];
  for (int i = 0; i < width; i++) {
    beamDelay[i] = RainSpeed[random(RainSpeed_SIZE)];
    beamDelayTracker[i] = beamDelay[i];
    beamDropping[i] = false;
    beamID[i] = 0;
    for (int j = 0; j < height; j++) {
      pixels[i][j] = 0;
    }
  }

  int beamCount = 0;
  bool allBeamsDone = false;
  while(beamCount <= maxBeamCount && !allBeamsDone) {
    allBeamsDone = true;

    for (int column = 0; column < width; column++) {
      bool emptyColumn = true;
      for (int row = height-1; row >= 0; row--) {
        bool newBeam = false;
        if (row == 0 && !beamDropping[column] && beamCount < maxBeamCount) {
          if (random(100) >= rainProbability) {
            newBeam = true;
            pixels[column][row] = beamLength;
            beamDropping[column] = true;
            beamCount++;
            beamID[column] = beamCount;
          }
        }
        if (pixels[column][row] > 0) {
          emptyColumn = false;
        }
        if (pixels[column][row] == beamLength) {
          if (beamDelayTracker[column] >= 0) {
            beamDelayTracker[column]--;
            break;
          }
          beamDelayTracker[column] = beamDelay[column];
        }
        if (!newBeam){
          if (pixels[column][row] > 0 && pixels[column][row] < beamLength) {
            pixels[column][row]--;
          }
          if (pixels[column][row] == beamLength) {
            if (row+1 < height) {
              pixels[column][row+1] = pixels[column][row];
            }
            pixels[column][row]--;
          }
        }
      }
      
      if (emptyColumn) {
        beamDropping[column] = false;
        beamDelay[column] = RainSpeed[random(RainSpeed_SIZE)];
      } else {
        allBeamsDone = false;
      }
    }

    for (int column = 0; column < width; column++) {
      for (int row = 0; row < height; row++) {
        int index = IndexFromCoordinates(column, row);
        printRain(pixels[column][row], index, beamID[column], beamLength);
      }
    }
    strip.show();
    delay(wait);
  }
}