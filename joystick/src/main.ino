#define LED_PIN 13

#define JOYSTICK_CENTRE 512

enum
{
  BUTTONMAP_X_HIGH = 64,
  BUTTONMAP_X_LOW,
  BUTTONMAP_Y_HIGH,
  BUTTONMAP_Y_LOW,
  BUTTONMAP_END = 255
};

struct buttonMap_t
{
  int button;
  int pin;
};

buttonMap_t buttonMapping[] = {{BUTTONMAP_X_HIGH, 14},
                               {BUTTONMAP_X_LOW, 15},
                               {BUTTONMAP_Y_HIGH, 16},
                               {BUTTONMAP_Y_LOW, 17},
                               {1, 12},
                               {2, 11},
                               {3, 10},
                               {4, 9},
                               {5, 8},
                               {6, 7},
                               {7, 6},
                               {8, 5},
                               {BUTTONMAP_END, BUTTONMAP_END}};

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  Joystick.useManualSend(true);

  buttonMap_t *bm = buttonMapping;
  while (bm->button != BUTTONMAP_END && bm->pin != BUTTONMAP_END)
  {
    pinMode(bm->pin, INPUT_PULLUP);
    bm++;
  }
}

void loop()
{
  int x = JOYSTICK_CENTRE;
  int y = JOYSTICK_CENTRE;

  buttonMap_t *bm = buttonMapping;
  while (bm->button != BUTTONMAP_END && bm->pin != BUTTONMAP_END)
  {
    bool pressed = (digitalRead(bm->pin) == LOW);

    switch (bm->button)
    {
    case BUTTONMAP_X_HIGH:
      if (pressed)
        x = 1023;
      break;

    case BUTTONMAP_X_LOW:
      if (pressed)
        x = 0;
      break;

    case BUTTONMAP_Y_HIGH:
      if (pressed)
        y = 1023;
      break;

    case BUTTONMAP_Y_LOW:
      if (pressed)
        y = 0;
      break;

    default:
      Joystick.button(bm->button, pressed);
      break;
    }

    bm++;
  }

  Joystick.X(x);
  Joystick.Y(y);

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  Joystick.send_now();

  delay(1);
}
