// ----------------------------------------------------------------------------
// MouseReachRotaryController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "MouseReachRotaryController.h"


using namespace mouse_reach_rotary_controller;

void MouseReachRotaryController::setup()
{
  // Parent Setup
  StepperController::setup();

  // Reset Watchdog
  resetWatchdog();

  // Event Controller Setup
  // event_controller_.setup();

  // Clients Setup

  // Variable Setup
  pellet_index_ = 0;
  // pellet_repeating_ = false;

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.removeHardware();
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.property(step_dir_controller::constants::channel_count_property_name);
  channel_count_property.disableFunctors();
  channel_count_property.setDefaultValue(constants::channel_count);
  channel_count_property.setRange(constants::channel_count,constants::channel_count);
  channel_count_property.reenableFunctors();

  modular_server::Property & steps_per_position_units_property = modular_server_.property(step_dir_controller::constants::steps_per_position_units_property_name);
  steps_per_position_units_property.disableFunctors();
  steps_per_position_units_property.setDefaultValue(constants::steps_per_position_units_default);
  steps_per_position_units_property.reenableFunctors();

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setDefaultValue(constants::velocity_max_default);

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & steps_per_revolution_property = modular_server_.createProperty(constants::steps_per_revolution_property_name,constants::steps_per_revolution_default);
  steps_per_revolution_property.setRange(constants::steps_per_revolution_min,constants::steps_per_revolution_max);
  steps_per_revolution_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::updateTravelDurationRangeHandler));

  modular_server::Property & pellets_per_revolution_property = modular_server_.createProperty(constants::pellets_per_revolution_property_name,constants::pellets_per_revolution_default);
  pellets_per_revolution_property.setRange(constants::pellets_per_revolution_min,constants::pellets_per_revolution_max);
  pellets_per_revolution_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::updateTravelDurationRangeHandler));

  modular_server::Property & travel_duration_property = modular_server_.createProperty(constants::travel_duration_property_name,constants::travel_duration_default);
  travel_duration_property.setUnits(constants::duration_units);

  modular_server::Property & reverse_direction_property = modular_server_.createProperty(constants::reverse_direction_property_name,constants::reverse_direction_default);

  modular_server::Property & tone_frequency_property = modular_server_.createProperty(constants::tone_frequency_property_name,constants::tone_frequency_default);
  tone_frequency_property.setRange(constants::tone_frequency_min,constants::tone_frequency_max);
  tone_frequency_property.setUnits(constants::frequency_units);

  modular_server::Property & tone_duration_property = modular_server_.createProperty(constants::tone_duration_property_name,constants::tone_duration_default);
  tone_duration_property.setRange(constants::tone_duration_min,constants::tone_duration_max);
  tone_duration_property.setUnits(constants::duration_units);

  modular_server::Property & play_tone_before_move_property = modular_server_.createProperty(constants::play_tone_before_move_property_name,constants::play_tone_before_move_default);

  // modular_server::Property & pellet_repeat_property = modular_server_.createProperty(constants::pellet_repeat_property_name,constants::pellet_repeat_default);

  // modular_server::Property & pellet_repeat_period_property = modular_server_.createProperty(constants::pellet_repeat_period_property_name,constants::pellet_repeat_period_default);
  // pellet_repeat_period_property.setRange(constants::pellet_repeat_period_min,constants::pellet_repeat_period_max);
  // pellet_repeat_period_property.setUnits(constants::duration_units);

  updateTravelDurationRangeHandler();

  // Parameters

  // Functions
  modular_server::Function & get_pellet_index_function = modular_server_.createFunction(constants::get_pellet_index_function_name);
  get_pellet_index_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::getPelletIndexHandler));
  get_pellet_index_function.setResultTypeLong();

  // modular_server::Function & get_position_function = modular_server_.createFunction(constants::get_position_function_name);
  // get_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::getPositionHandler));
  // get_position_function.setResultTypeLong();

  // modular_server::Function & pellet_repeating_function = modular_server_.createFunction(constants::pellet_repeating_function_name);
  // pellet_repeating_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::pelletRepeatingHandler));
  // pellet_repeating_function.setResultTypeBool();

  modular_server::Function & stop_function = modular_server_.function(step_dir_controller::constants::stop_function_name);
  stop_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::stopHandler));

  // modular_server::Function & stop_all_function = modular_server_.function(step_dir_controller_simple::constants::stop_all_function_name);
  // stop_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::stopAllHandler));

  // Callbacks
  modular_server::Callback & move_to_next_pellet_callback = modular_server_.createCallback(constants::move_to_next_pellet_callback_name);
  move_to_next_pellet_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseReachRotaryController::moveToNextPelletHandler));
  move_to_next_pellet_callback.addProperty(travel_duration_property);
  move_to_next_pellet_callback.addProperty(reverse_direction_property);
  // move_to_next_pellet_callback.addProperty(play_tone_before_move_property);

  modular_server::Callback & play_tone_callback = modular_server_.createCallback(constants::play_tone_callback_name);
  play_tone_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseReachRotaryController::playToneHandler));
  play_tone_callback.addProperty(tone_frequency_property);
  play_tone_callback.addProperty(tone_duration_property);

  enable(constants::channel);
  zero(constants::channel);

  // audio_controller_.setup();
}

void MouseReachRotaryController::moveToNextPellet(const long travel_duration,
  const bool reverse_direction,
  const bool play_tone_before_move)
{
  if (getVelocity(constants::channel) > 0)
  {
    return;
  }
  long microsteps_per_step;
  modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name).getElementValue(constants::channel,microsteps_per_step);

  long steps_per_revolution;
  modular_server_.property(constants::steps_per_revolution_property_name).getValue(steps_per_revolution);

  long pellets_per_revolution;
  modular_server_.property(constants::pellets_per_revolution_property_name).getValue(pellets_per_revolution);

  long pellet_position_delta;
  pellet_position_delta = (steps_per_revolution*microsteps_per_step)/pellets_per_revolution;
  if (!reverse_direction)
  {
    ++pellet_index_;
  }
  else
  {
    --pellet_index_;
    pellet_position_delta *= -1;
  }
  long speed = (steps_per_revolution*microsteps_per_step*1000)/(travel_duration*pellets_per_revolution);
  // if (play_tone_before_move)
  // {
  //   playTone();
  // }
  // moveByAt(constants::channel,pellet_position_delta,speed);
  moveBy(constants::channel,pellet_position_delta);
}

void MouseReachRotaryController::moveToNextPellet()
{
  long travel_duration;
  modular_server_.property(constants::travel_duration_property_name).getValue(travel_duration);
  bool reverse_direction;
  modular_server_.property(constants::reverse_direction_property_name).getValue(reverse_direction);
  bool play_tone_before_move;
  modular_server_.property(constants::play_tone_before_move_property_name).getValue(play_tone_before_move);
  moveToNextPellet(travel_duration,reverse_direction,play_tone_before_move);
}

long MouseReachRotaryController::getPelletIndex()
{
  return pellet_index_;
}

// bool MouseReachRotaryController::pelletRepeating()
// {
//   return pellet_repeating_;
// }

void MouseReachRotaryController::playTone(long frequency,
  long duration)
{
  // audio_controller_.addTonePwm(frequency,&(audio_controller::constants::speaker_all),10,duration,duration,1);
  audio_controller_.addTonePwmAt(5000,
    &(audio_controller::constants::speaker_all),
    50,
    10,
    200,
    200,
    1);
}

// void MouseReachRotaryController::startPelletRepeat()
// {
//   long pellet_repeat_period;
//   modular_server_.property(constants::pellet_repeat_period_property_name).getValue(pellet_repeat_period);
//   event_id_pair_ = event_controller_.addInfinitePwmUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::repeatPelletHandler),
//                                                               makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::dummyHandler),
//                                                               constants::pellet_repeat_period_delay,
//                                                               pellet_repeat_period,
//                                                               pellet_repeat_period/2,
//                                                               0);
//   event_controller_.addStartFunctor(event_id_pair_,makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::startPelletRepeatHandler));
//   event_controller_.addStopFunctor(event_id_pair_,makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::stopPelletRepeatHandler));
//   event_controller_.enable(event_id_pair_);
// }

// void MouseReachRotaryController::stopPelletRepeat()
// {
//   event_controller_.remove(event_id_pair_);
// }

void MouseReachRotaryController::setupDriver(size_t channel)
{
  StepperController::setupDriver(channel);
  enable(channel);
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

// void MouseReachRotaryController::startPelletRepeatHandler(int index)
// {
//   pellet_repeating_ = true;
// }

// void MouseReachRotaryController::stopPelletRepeatHandler(int index)
// {
//   pellet_repeating_ = false;
// }

void MouseReachRotaryController::getPelletIndexHandler()
{
  modular_server_.response().returnResult(getPelletIndex());
}

// void MouseReachRotaryController::pelletRepeatingHandler()
// {
//   modular_server_.response().returnResult(pelletRepeating());
// }

void MouseReachRotaryController::stopHandler()
{
  // stopPelletRepeat();
  stop(constants::channel);
}

// void MouseReachRotaryController::stopAllHandler()
// {
//   // stopPelletRepeat();
//   stopAll();
// }

void MouseReachRotaryController::moveToNextPelletHandler(modular_server::Pin * pin_ptr)
{
  // bool pellet_repeat;
  // modular_server_.property(constants::pellet_repeat_property_name).getValue(pellet_repeat);
  // if (!pellet_repeat)
  // {
    moveToNextPellet();
  // }
  // else if (!pellet_repeating_)
  // {
  //   startPelletRepeat();
  // }
  // else
  // {
  //   stopPelletRepeat();
  // }
}

void MouseReachRotaryController::playToneHandler(modular_server::Pin * pin_ptr)
{
  long tone_frequency;
  modular_server_.property(constants::tone_frequency_property_name).getValue(tone_frequency);
  long tone_duration;
  modular_server_.property(constants::tone_duration_property_name).getValue(tone_duration);
  playTone(tone_frequency,tone_duration);
}

// void MouseReachRotaryController::repeatPelletHandler(int index)
// {
//   moveToNextPellet();
// }

// void MouseReachRotaryController::dummyHandler(int index)
// {
// }

void MouseReachRotaryController::updateTravelDurationRangeHandler()
{
  long microsteps_per_step;
  modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name).getElementValue(constants::channel,microsteps_per_step);

  long steps_per_revolution;
  modular_server_.property(constants::steps_per_revolution_property_name).getValue(steps_per_revolution);

  long pellets_per_revolution;
  modular_server_.property(constants::pellets_per_revolution_property_name).getValue(pellets_per_revolution);

  const long travel_duration_min = (steps_per_revolution*microsteps_per_step*1000)/(getVelocityUpperLimit(constants::channel)*pellets_per_revolution);
  const long travel_duration_max = (steps_per_revolution*microsteps_per_step*1000)/pellets_per_revolution;
  modular_server_.property(constants::travel_duration_property_name).setDefaultValue(constants::travel_duration_default);
  modular_server_.property(constants::travel_duration_property_name).setRange(travel_duration_min,travel_duration_max);
}

