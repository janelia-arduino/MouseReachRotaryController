// ----------------------------------------------------------------------------
// MouseReachRotaryController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef MOUSE_REACH_ROTARY_CONTROLLER_H
#define MOUSE_REACH_ROTARY_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

// #include <EventController.h>

#include <AudioController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>

#include "MouseReachRotaryController/Constants.h"


class MouseReachRotaryController : public StepperController
{
public:
  virtual void setup();

  void moveToNextPellet(const long travel_duration,
                        const bool reverse_direction,
                        const bool play_tone_before_move);
  void moveToNextPellet();
  long getPelletIndex();
  // bool pelletRepeating();
  void playTone(long frequency,
    long duration);

  // void startPelletRepeat();
  // void stopPelletRepeat();

  // Handlers
  // virtual void startPelletRepeatHandler(int index);
  // virtual void stopPelletRepeatHandler(int index);

protected:
  virtual void setupDriver(size_t channel);

private:
  modular_server::Pin pins_[mouse_reach_rotary_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[mouse_reach_rotary_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[mouse_reach_rotary_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[mouse_reach_rotary_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[mouse_reach_rotary_controller::constants::CALLBACK_COUNT_MAX];

  long pellet_index_;

  AudioController audio_controller_;

  // bool pellet_repeating_;

  // EventController<mouse_reach_rotary_controller::constants::EVENT_COUNT_MAX> event_controller_;
  // EventIdPair event_id_pair_;

  // Handlers
  void getPelletIndexHandler();
  // void pelletRepeatingHandler();
  void stopHandler();
  // void stopAllHandler();
  void moveToNextPelletHandler(modular_server::Pin * pin_ptr);
  void playToneHandler(modular_server::Pin * pin_ptr);
  // void repeatPelletHandler(int index);
  // void dummyHandler(int index);
  void updateTravelDurationRangeHandler();
};

#endif
