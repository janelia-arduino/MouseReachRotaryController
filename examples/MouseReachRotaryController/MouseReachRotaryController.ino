#include <MouseReachRotaryController.h>


MouseReachRotaryController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
