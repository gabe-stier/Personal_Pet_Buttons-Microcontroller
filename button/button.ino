const byte buttons_used = 6;
// char const LF[] = "\n";
// uint8_t switchPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
//                         A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
uint8_t switchPins[] = {2, 3, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                        A0, A1, A2, A3, A4, A5, A6, A7, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const byte pinCount = sizeof(switchPins) / sizeof(byte);
byte lastButtonState[pinCount]; // the debounced state of the button
byte currentState[pinCount];    // current state of buttons, not debounced yet
unsigned long lastDebounceTime[pinCount];
const unsigned long debounceDelay = 60; // button must be pressed this many milliseconds before being seen as "off" or "on"

void send_signal_to_raspberry_pi(byte pin)
{
  switch (pin)
  {
  case 2:
    Serial.print("Red has been pushed");
    Serial.print("\n");
     break;
  case 3:
    Serial.print("Yellow has been pushed");
    Serial.print("\n"); 
    break;
  case 22:
    Serial.println();
    break;
  case 23:
    Serial.println();
    break;
  case 24:
    Serial.println();
    break;
  case 25:
    Serial.println();
    break;
  case 26:
    Serial.println();
    break;
  case 27:
    Serial.println();
    break;
  case 28:
    Serial.println();
    break;
  case 29:
    Serial.println();
    break;
  default:
    Serial.println(pin);
    Serial.println(F("Unknown Action"));
    break;
  }
}

void loop()
{
  byte internalLED = LOW;
  for (byte thisPin = 0; thisPin < pinCount && thisPin < buttons_used; thisPin++)
  {
    int reading = digitalRead(switchPins[thisPin]);
    if (reading != lastButtonState[thisPin])
    {
      lastDebounceTime[thisPin] = millis();
    }
    if ((millis() - lastButtonState[thisPin]) > debounceDelay)
    {
      if (reading != currentState[thisPin])
      {
        currentState[thisPin] = reading;
        if (currentState[thisPin] == LOW)
        {
          send_signal_to_raspberry_pi(switchPins[thisPin]);
        }
      }
    }
    if (reading == LOW)
    {
      internalLED = HIGH;
    }
    lastButtonState[thisPin] = reading;
  }
  digitalWrite(LED_BUILTIN, internalLED);
}
void setup()
{
  Serial.begin(115200);
  Serial.print("I am alive");
  Serial.print("\n");
      // intialize all input pins that are hooked to buttons
      for (byte thisPin = 0; thisPin < pinCount && thisPin < buttons_used; thisPin++)
  {
    pinMode(switchPins[thisPin], INPUT_PULLUP); // use internal pull up resistors
    lastButtonState[thisPin] = HIGH;            // assume all buttons are not pressed at the start
    lastDebounceTime[thisPin] = millis();       // init last pressed time for all buttons
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // // Run thru and flash each button as a test?
  // for (byte thisPin = 0; thisPin < pinCount && thisPin < buttons_used; thisPin++)
  // {
  //   pinMode(switchPins[thisPin], OUTPUT);
  //   digitalWrite(switchPins[thisPin], LOW);
  //   delay(150);
  //   digitalWrite(switchPins[thisPin], HIGH);
  //   pinMode(switchPins[thisPin], INPUT_PULLUP); // put back to input again
  //   delay(100);
  // }
}
