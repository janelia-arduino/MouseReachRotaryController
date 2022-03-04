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

#include <EventController.h>

#include <AudioApparatus.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>

#include "MouseReachRotaryController/Constants.h"


class MouseReachRotaryController : public StepperController
{
public:
  virtual void setup();

  void dispense(long distance_between_pellets,
    long crosstalk_suppression_duration,
    long retrigger_suppression_duration);
  void dispense();
  long getPelletIndex();
  void zeroPelletIndex();
  void adjustPelletPosition(long percentage_of_distance_between_pellets,
    long distance_between_pellets);
  void playTone(long frequency,
    long volume,
    long tone_duration,
    long crosstalk_suppression_duration,
    long retrigger_suppression_duration);
  void playTone();

protected:
  virtual void setupDriver(size_t channel);

private:
  modular_server::Pin pins_[mouse_reach_rotary_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[mouse_reach_rotary_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[mouse_reach_rotary_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[mouse_reach_rotary_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[mouse_reach_rotary_controller::constants::CALLBACK_COUNT_MAX];

  modular_server::Pin * dispense_pin_ptr_;
  const ConstantString * dispense_pin_mode_ptr_;
  modular_server::Pin * play_tone_pin_ptr_;
  const ConstantString * play_tone_pin_mode_ptr_;

  long pellet_index_;

  long getDistanceBetweenPellets();

  EventController<mouse_reach_rotary_controller::constants::EVENT_COUNT_MAX> event_controller_;

  AudioApparatus<mouse_reach_rotary_controller::constants::EVENT_COUNT_MAX> audio_apparatus_;

  bool dispensing_;
  bool playing_tone_;

  // Handlers
  void updateVelocityMaxHandler();
  void getPelletIndexHandler();
  void adjustPelletPositionHandler();
  void initializeDispenseTriggerHandler(int index);
  void dispenseHandler(modular_server::Pin * pin_ptr);
  void endDispenseCrosstalkSuppressionHandler(int index);
  void initializePlayToneTriggerHandler(int index);
  void playToneHandler(modular_server::Pin * pin_ptr);
  void endPlayToneCrosstalkSuppressionHandler(int index);
  void zeroPelletIndexHandler(modular_server::Pin * pin_ptr);
};

#endif
