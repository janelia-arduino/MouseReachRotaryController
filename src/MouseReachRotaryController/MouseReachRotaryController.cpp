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

  event_controller_.setup();
  audio_apparatus_.setup(event_controller_);
  audio_apparatus_.stop();

  // Reset Watchdog
  resetWatchdog();

  // Clients Setup

  // Variable Setup
  pellet_index_ = 0;
  dispensing_ = false;
  playing_tone_ = false;

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.removeHardware();
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Pins
  modular_server::Pin & signal_a_pin = modular_server_.createPin(constants::signal_a_pin_name,
    constants::signal_a_pin_number);
  signal_a_pin.setModeDigitalInputPullup();

  modular_server::Pin & signal_b_pin = modular_server_.createPin(constants::signal_b_pin_name,
    constants::signal_b_pin_number);
  signal_b_pin.setModeDigitalInputPullup();

  modular_server::Pin & signal_c_pin = modular_server_.createPin(constants::signal_c_pin_name,
    constants::signal_c_pin_number);
  signal_c_pin.setModeDigitalInputPullup();

  modular_server::Pin & signal_d_pin = modular_server_.createPin(constants::signal_d_pin_name,
    constants::signal_d_pin_number);
  signal_d_pin.setModeDigitalInputPullup();

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

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & microsteps_per_step_property = modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name);
  microsteps_per_step_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::updateVelocityMaxHandler));

  modular_server::Property & steps_per_revolution_property = modular_server_.createProperty(constants::steps_per_revolution_property_name,constants::steps_per_revolution_default);
  steps_per_revolution_property.setRange(constants::steps_per_revolution_min,constants::steps_per_revolution_max);
  steps_per_revolution_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::updateVelocityMaxHandler));

  modular_server::Property & pellets_per_revolution_property = modular_server_.createProperty(constants::pellets_per_revolution_property_name,constants::pellets_per_revolution_default);
  pellets_per_revolution_property.setRange(constants::pellets_per_revolution_min,constants::pellets_per_revolution_max);
  pellets_per_revolution_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::updateVelocityMaxHandler));

  modular_server::Property & travel_duration_property = modular_server_.createProperty(constants::travel_duration_property_name,constants::travel_duration_default);
  travel_duration_property.setRange(constants::travel_duration_min,constants::travel_duration_max);
  travel_duration_property.setUnits(constants::duration_units);
  travel_duration_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::updateVelocityMaxHandler));

  modular_server::Property & reverse_direction_property = modular_server_.createProperty(constants::reverse_direction_property_name,constants::reverse_direction_default);

  modular_server::Property & crosstalk_suppression_duration_property = modular_server_.createProperty(constants::crosstalk_suppression_duration_property_name,constants::crosstalk_suppression_duration_default);
  crosstalk_suppression_duration_property.setRange(constants::crosstalk_suppression_duration_min,constants::crosstalk_suppression_duration_max);
  crosstalk_suppression_duration_property.setUnits(constants::duration_units);

  modular_server::Property & retrigger_suppression_duration_property = modular_server_.createProperty(constants::retrigger_suppression_duration_property_name,constants::retrigger_suppression_duration_default);
  retrigger_suppression_duration_property.setRange(constants::retrigger_suppression_duration_min,constants::retrigger_suppression_duration_max);
  retrigger_suppression_duration_property.setUnits(constants::duration_units);

  modular_server::Property & tone_frequency_property = modular_server_.createProperty(constants::tone_frequency_property_name,constants::tone_frequency_default);
  tone_frequency_property.setRange(constants::tone_frequency_min,constants::tone_frequency_max);
  tone_frequency_property.setUnits(constants::frequency_units);

  modular_server::Property & tone_volume_property = modular_server_.createProperty(constants::tone_volume_property_name,constants::tone_volume_default);
  tone_volume_property.setRange(constants::tone_volume_min,constants::tone_volume_max);
  tone_volume_property.setUnits(constants::percent_units);

  modular_server::Property & tone_duration_property = modular_server_.createProperty(constants::tone_duration_property_name,constants::tone_duration_default);
  tone_duration_property.setRange(constants::tone_duration_min,constants::tone_duration_max);
  tone_duration_property.setUnits(constants::duration_units);

  updateVelocityMaxHandler();

  // Parameters

  // Functions
  modular_server::Function & get_pellet_index_function = modular_server_.createFunction(constants::get_pellet_index_function_name);
  get_pellet_index_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseReachRotaryController::getPelletIndexHandler));
  get_pellet_index_function.setResultTypeLong();

  // Callbacks
  dispense_pin_ptr_ = &signal_b_pin;
  dispense_pin_mode_ptr_ = &modular_server::constants::pin_mode_interrupt_falling;
  modular_server::Callback & dispense_callback = modular_server_.createCallback(constants::dispense_callback_name);
  dispense_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseReachRotaryController::dispenseHandler));
  dispense_callback.addProperty(travel_duration_property);
  dispense_callback.addProperty(reverse_direction_property);

  play_tone_pin_ptr_ = &signal_d_pin;
  play_tone_pin_mode_ptr_ = &modular_server::constants::pin_mode_interrupt_falling;
  modular_server::Callback & play_tone_callback = modular_server_.createCallback(constants::play_tone_callback_name);
  play_tone_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseReachRotaryController::playToneHandler));
  play_tone_callback.addProperty(tone_frequency_property);
  play_tone_callback.addProperty(tone_volume_property);
  play_tone_callback.addProperty(tone_duration_property);

  enable(constants::channel);
  zero(constants::channel);

  EventId initialize_trigger_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::initializeDispenseTriggerHandler),
    constants::initialize_trigger_delay);
  event_controller_.enable(initialize_trigger_event_id);
  initialize_trigger_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::initializePlayToneTriggerHandler),
    constants::initialize_trigger_delay);
  event_controller_.enable(initialize_trigger_event_id);
}

void MouseReachRotaryController::dispense(long pellet_position_delta,
  bool reverse_direction,
  long crosstalk_suppression_duration,
  long retrigger_suppression_duration)
{
  if (dispensing_)
  {
    return;
  }
  dispensing_ = true;
  if (!reverse_direction)
  {
    ++pellet_index_;
  }
  else
  {
    --pellet_index_;
    pellet_position_delta *= -1;
  }
  moveBy(constants::channel,pellet_position_delta);
  EventId crosstalk_suppression_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::endPlayToneCrosstalkSuppressionHandler),
    crosstalk_suppression_duration);
  event_controller_.enable(crosstalk_suppression_event_id);
  EventId retrigger_suppression_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::initializeDispenseTriggerHandler),
    retrigger_suppression_duration);
  event_controller_.enable(retrigger_suppression_event_id);
}

void MouseReachRotaryController::dispense()
{
  long microsteps_per_step;
  modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name).getElementValue(constants::channel,microsteps_per_step);

  long steps_per_revolution;
  modular_server_.property(constants::steps_per_revolution_property_name).getValue(steps_per_revolution);

  long pellets_per_revolution;
  modular_server_.property(constants::pellets_per_revolution_property_name).getValue(pellets_per_revolution);

  long pellet_position_delta;
  pellet_position_delta = (microsteps_per_step*steps_per_revolution)/pellets_per_revolution;

  bool reverse_direction;
  modular_server_.property(constants::reverse_direction_property_name).getValue(reverse_direction);

  long crosstalk_suppression_duration;
  modular_server_.property(constants::crosstalk_suppression_duration_property_name).getValue(crosstalk_suppression_duration);

  long retrigger_suppression_duration;
  modular_server_.property(constants::retrigger_suppression_duration_property_name).getValue(retrigger_suppression_duration);

  dispense(pellet_position_delta,
    reverse_direction,
    crosstalk_suppression_duration,
    retrigger_suppression_duration);
}

long MouseReachRotaryController::getPelletIndex()
{
  return pellet_index_;
}

void MouseReachRotaryController::playTone(long frequency,
  long volume,
  long tone_duration,
  long crosstalk_suppression_duration,
  long retrigger_suppression_duration)
{
  if (playing_tone_)
  {
    return;
  }
  playing_tone_ = true;

  audio_apparatus_.addTonePwmAt(frequency,
    audio_apparatus::constants::SPEAKER_ALL,
    volume,
    10,
    tone_duration,
    tone_duration,
    1);
  EventId crosstalk_suppression_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::endDispenseCrosstalkSuppressionHandler),
    crosstalk_suppression_duration);
  event_controller_.enable(crosstalk_suppression_event_id);
  EventId retrigger_suppression_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseReachRotaryController::initializePlayToneTriggerHandler),
    retrigger_suppression_duration);
  event_controller_.enable(retrigger_suppression_event_id);
}

void MouseReachRotaryController::playTone()
{
  long tone_frequency;
  modular_server_.property(constants::tone_frequency_property_name).getValue(tone_frequency);

  long tone_volume;
  modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

  long tone_duration;
  modular_server_.property(constants::tone_duration_property_name).getValue(tone_duration);

  long crosstalk_suppression_duration;
  modular_server_.property(constants::crosstalk_suppression_duration_property_name).getValue(crosstalk_suppression_duration);

  long retrigger_suppression_duration;
  modular_server_.property(constants::retrigger_suppression_duration_property_name).getValue(retrigger_suppression_duration);

  playTone(tone_frequency,
    tone_volume,
    tone_duration,
    crosstalk_suppression_duration,
    retrigger_suppression_duration);
}

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

void MouseReachRotaryController::updateVelocityMaxHandler()
{
  long microsteps_per_step;
  modular_server_.property(stepper_controller::constants::microsteps_per_step_property_name).getElementValue(constants::channel,microsteps_per_step);

  long steps_per_revolution;
  modular_server_.property(constants::steps_per_revolution_property_name).getValue(steps_per_revolution);

  long pellets_per_revolution;
  modular_server_.property(constants::pellets_per_revolution_property_name).getValue(pellets_per_revolution);

  long travel_duration;
  modular_server_.property(constants::travel_duration_property_name).getValue(travel_duration);

  long velocity_max = (microsteps_per_step*steps_per_revolution*1000)/(travel_duration*pellets_per_revolution);
  velocity_max = (double)velocity_max * constants::velocity_max_scale_factor;

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setRange(velocity_max,velocity_max);
  velocity_max_property.setElementValue(constants::channel,velocity_max);
}

void MouseReachRotaryController::getPelletIndexHandler()
{
  modular_server_.response().returnResult(getPelletIndex());
}

void MouseReachRotaryController::initializeDispenseTriggerHandler(int index)
{
  dispensing_ = false;
  modular_server_.callback(constants::dispense_callback_name).attachTo(*dispense_pin_ptr_,*dispense_pin_mode_ptr_);
}

void MouseReachRotaryController::dispenseHandler(modular_server::Pin * pin_ptr)
{
  if ((pin_ptr) and (pin_ptr->getValue()))
  {
    return;
  }
  modular_server_.callback(constants::play_tone_callback_name).detachFrom(*play_tone_pin_ptr_);
  modular_server_.callback(constants::dispense_callback_name).detachFrom(*dispense_pin_ptr_);
  dispense();
}

void MouseReachRotaryController::endDispenseCrosstalkSuppressionHandler(int index)
{
  if (not dispensing_)
  {
    modular_server_.callback(constants::dispense_callback_name).attachTo(*dispense_pin_ptr_,*dispense_pin_mode_ptr_);
  }
}

void MouseReachRotaryController::initializePlayToneTriggerHandler(int index)
{
  playing_tone_ = false;
  modular_server_.callback(constants::play_tone_callback_name).attachTo(*play_tone_pin_ptr_,*play_tone_pin_mode_ptr_);
}

void MouseReachRotaryController::playToneHandler(modular_server::Pin * pin_ptr)
{
  if ((pin_ptr) and (pin_ptr->getValue()))
  {
    return;
  }
  modular_server_.callback(constants::dispense_callback_name).detachFrom(*dispense_pin_ptr_);
  modular_server_.callback(constants::play_tone_callback_name).detachFrom(*play_tone_pin_ptr_);
  playTone();
}

void MouseReachRotaryController::endPlayToneCrosstalkSuppressionHandler(int index)
{
  if (not playing_tone_)
  {
    modular_server_.callback(constants::play_tone_callback_name).attachTo(*play_tone_pin_ptr_,*play_tone_pin_mode_ptr_);
  }
}

