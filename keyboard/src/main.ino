#define LED_PIN 13

#define BUTTONMAP_END 255

struct buttonMap_t
{
  char key;
  int pin;
  bool last;
};

buttonMap_t buttonMapping[] =
{
  {'a', 14},
  {'d',  15},
  {'w', 16},
  {'s',  17},
  {'e', 12},
  {'q', 11},
  {'r', 10},
  {'f', 9},
  {'z', 8},
  {'x', 7},
  {'1', 6},
  {'2', 5},
  {BUTTONMAP_END, BUTTONMAP_END}
};

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  buttonMap_t * bm = buttonMapping;
  while (bm->key != BUTTONMAP_END && bm->pin != BUTTONMAP_END)
  {
    pinMode(bm->pin, INPUT_PULLUP);
    bm->last = false;

    bm++;
  }
}

void loop()
{
  buttonMap_t * bm = buttonMapping;
  while (bm->key != BUTTONMAP_END && bm->pin != BUTTONMAP_END)
  {
    bool pressed = (digitalRead(bm->pin) == LOW);

    if (pressed != bm->last)
    {
      if (pressed)
        Keyboard.press(bm->key);
      else
        Keyboard.release(bm->key);
    }
    bm->last = pressed;

    bm++;
  }

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  delay(5);
}
