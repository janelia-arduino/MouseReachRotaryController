#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "TimerThree.h"
#include "EventController.h"

#include "ModularClient.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "StepDirControllerSimple.h"
#include "RotaryPelletControllerSimple.h"


RotaryPelletControllerSimple dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
