// ----------------------------------------------------------------------------
// MouseReachRotaryController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_REACH_ROTARY_CONTROLLER_H
#define MOUSE_REACH_ROTARY_CONTROLLER_H
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

#include "utility/Constants.h"


class MouseReachRotaryController : public StepDirControllerSimple
{
public:
  MouseReachRotaryController();
  ~MouseReachRotaryController();
  virtual void setup();
  void moveToNextPellet(const long travel_duration,
                        const bool reverse_direction,
                        const bool play_tone_before_move);
  void moveToNextPellet();
  long getPelletIndex();
  // long getPosition();
  // bool pelletRepeating();
  void playTone();

  // void startPelletRepeat();
  // void stopPelletRepeat();

  // Handlers
  virtual void atPositionHandler(size_t index, long position);
  // virtual void startPelletRepeatHandler(int index);
  // virtual void stopPelletRepeatHandler(int index);

private:
  modular_server::Property properties_[mouse_reach_rotary_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[mouse_reach_rotary_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[mouse_reach_rotary_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[mouse_reach_rotary_controller::constants::CALLBACK_COUNT_MAX];

  long pellet_index_;
  bool moving_;
  // bool pellet_repeating_;

  // EventController<mouse_reach_rotary_controller::constants::EVENT_COUNT_MAX> event_controller_;
  // EventIdPair event_id_pair_;

  // Handlers
  void getPelletIndexHandler();
  // void getPositionHandler();
  // void pelletRepeatingHandler();
  void stopHandler();
  // void stopAllHandler();
  void moveToNextPelletHandler(modular_server::Interrupt * interrupt_ptr);
  void playToneHandler(modular_server::Interrupt * interrupt_ptr);
  // void repeatPelletHandler(int index);
  // void dummyHandler(int index);
  void updateTravelDurationRangeHandler();
};

#endif
