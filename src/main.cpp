#include "display.hpp"

Display display;

void setup()
{
  Serial.begin(115200);

  display.init(2,2, 4);
}

void loop()
{
  display.draw();

  delay(50);
}