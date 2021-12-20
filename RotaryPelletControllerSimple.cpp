// ----------------------------------------------------------------------------
// RotaryPelletControllerSimple.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "RotaryPelletControllerSimple.h"


using namespace rotary_pellet_controller_simple;

RotaryPelletControllerSimple::RotaryPelletControllerSimple()
{
}

RotaryPelletControllerSimple::~RotaryPelletControllerSimple()
{
  disable(constants::channel);
}

void RotaryPelletControllerSimple::setup()
{
  // Parent Setup
  StepDirControllerSimple::setup();
  enable(constants::channel);

  // Variable Setup
  pellet_index_ = 0;
  moving_ = false;
  // pellet_repeating_ = false;

  // Event Controller Setup
  // event_controller_.setup();

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  // modular_server::Property & microsteps_per_step_property = modular_server_.createProperty(constants::microsteps_per_step_property_name,constants::microsteps_per_step_default);
  // microsteps_per_step_property.setRange(constants::microsteps_per_step_min,constants::microsteps_per_step_max);
  // microsteps_per_step_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::updateTravelDurationRangeHandler));

  // modular_server::Property & steps_per_revolution_property = modular_server_.createProperty(constants::steps_per_revolution_property_name,constants::steps_per_revolution_default);
  // steps_per_revolution_property.setRange(constants::steps_per_revolution_min,constants::steps_per_revolution_max);
  // steps_per_revolution_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::updateTravelDurationRangeHandler));

  modular_server::Property & pellets_per_revolution_property = modular_server_.createProperty(constants::pellets_per_revolution_property_name,constants::pellets_per_revolution_default);
  pellets_per_revolution_property.setRange(constants::pellets_per_revolution_min,constants::pellets_per_revolution_max);
  pellets_per_revolution_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::updateTravelDurationRangeHandler));

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
  get_pellet_index_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::getPelletIndexHandler));
  get_pellet_index_function.setResultTypeLong();

  // modular_server::Function & get_position_function = modular_server_.createFunction(constants::get_position_function_name);
  // get_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::getPositionHandler));
  // get_position_function.setResultTypeLong();

  // modular_server::Function & pellet_repeating_function = modular_server_.createFunction(constants::pellet_repeating_function_name);
  // pellet_repeating_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::pelletRepeatingHandler));
  // pellet_repeating_function.setResultTypeBool();

  modular_server::Function & stop_function = modular_server_.function(step_dir_controller_simple::constants::stop_function_name);
  stop_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::stopHandler));

  // modular_server::Function & stop_all_function = modular_server_.function(step_dir_controller_simple::constants::stop_all_function_name);
  // stop_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&RotaryPelletControllerSimple::stopAllHandler));

  // Callbacks
  modular_server::Callback & move_to_next_pellet_callback = modular_server_.createCallback(constants::move_to_next_pellet_callback_name);
  move_to_next_pellet_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&RotaryPelletControllerSimple::moveToNextPelletHandler));
  move_to_next_pellet_callback.addProperty(travel_duration_property);
  move_to_next_pellet_callback.addProperty(reverse_direction_property);
  move_to_next_pellet_callback.addProperty(play_tone_before_move_property);
#if defined(__AVR_ATmega2560__)
  move_to_next_pellet_callback.attachTo(step_dir_controller_simple::constants::int_stepper_interrupt_name,modular_server::interrupt::mode_falling);
#endif

  modular_server::Callback & play_tone_callback = modular_server_.createCallback(constants::play_tone_callback_name);
  play_tone_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&RotaryPelletControllerSimple::playToneHandler));
  play_tone_callback.addProperty(tone_frequency_property);
  play_tone_callback.addProperty(tone_duration_property);
#if defined(__AVR_ATmega2560__)
  play_tone_callback.attachTo(step_dir_controller_simple::constants::int_aux_interrupt_name,modular_server::interrupt::mode_falling);
#endif

}

void RotaryPelletControllerSimple::moveToNextPellet(const long travel_duration,
                                                    const bool reverse_direction,
                                                    const bool play_tone_before_move)
{
  if (moving_)
  {
    return;
  }
  // long microsteps_per_step;
  // modular_server_.property(constants::microsteps_per_step_property_name).getValue(microsteps_per_step);
  // long steps_per_revolution;
  // modular_server_.property(constants::steps_per_revolution_property_name).getValue(steps_per_revolution);
  long microsteps_per_step = constants::microsteps_per_step_default;
  long steps_per_revolution = constants::steps_per_revolution_default;
  long pellets_per_revolution;
  modular_server_.property(constants::pellets_per_revolution_property_name).getValue(pellets_per_revolution);
  long pellet_position_delta;
  if (!reverse_direction)
  {
    ++pellet_index_;
    pellet_position_delta = (steps_per_revolution*microsteps_per_step)/pellets_per_revolution;
  }
  else
  {
    --pellet_index_;
    pellet_position_delta = -(steps_per_revolution*microsteps_per_step)/pellets_per_revolution;
  }
  long speed = (steps_per_revolution*microsteps_per_step*1000)/(travel_duration*pellets_per_revolution);
  if (play_tone_before_move)
  {
    playTone();
  }
  moving_ = true;
  moveByAt(constants::channel,pellet_position_delta,speed);
}

void RotaryPelletControllerSimple::moveToNextPellet()
{
  long travel_duration;
  modular_server_.property(constants::travel_duration_property_name).getValue(travel_duration);
  bool reverse_direction;
  modular_server_.property(constants::reverse_direction_property_name).getValue(reverse_direction);
  bool play_tone_before_move;
  modular_server_.property(constants::play_tone_before_move_property_name).getValue(play_tone_before_move);
  moveToNextPellet(travel_duration,reverse_direction,play_tone_before_move);
}

long RotaryPelletControllerSimple::getPelletIndex()
{
  return pellet_index_;
}

// long RotaryPelletControllerSimple::getPosition()
// {
//   return StepDirControllerSimple::getPosition(constants::channel);
// }

// bool RotaryPelletControllerSimple::pelletRepeating()
// {
//   return pellet_repeating_;
// }

void RotaryPelletControllerSimple::playTone()
{
  long tone_frequency;
  modular_server_.property(constants::tone_frequency_property_name).getValue(tone_frequency);
  long tone_duration;
  modular_server_.property(constants::tone_duration_property_name).getValue(tone_duration);
  tone(constants::speaker_pin,tone_frequency,tone_duration);
}

// void RotaryPelletControllerSimple::startPelletRepeat()
// {
//   long pellet_repeat_period;
//   modular_server_.property(constants::pellet_repeat_period_property_name).getValue(pellet_repeat_period);
//   event_id_pair_ = event_controller_.addInfinitePwmUsingDelay(makeFunctor((Functor1<int> *)0,*this,&RotaryPelletControllerSimple::repeatPelletHandler),
//                                                               makeFunctor((Functor1<int> *)0,*this,&RotaryPelletControllerSimple::dummyHandler),
//                                                               constants::pellet_repeat_period_delay,
//                                                               pellet_repeat_period,
//                                                               pellet_repeat_period/2,
//                                                               0);
//   event_controller_.addStartFunctor(event_id_pair_,makeFunctor((Functor1<int> *)0,*this,&RotaryPelletControllerSimple::startPelletRepeatHandler));
//   event_controller_.addStopFunctor(event_id_pair_,makeFunctor((Functor1<int> *)0,*this,&RotaryPelletControllerSimple::stopPelletRepeatHandler));
//   event_controller_.enable(event_id_pair_);
// }

// void RotaryPelletControllerSimple::stopPelletRepeat()
// {
//   event_controller_.remove(event_id_pair_);
// }

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

// void RotaryPelletControllerSimple::startPelletRepeatHandler(int index)
// {
//   pellet_repeating_ = true;
// }

// void RotaryPelletControllerSimple::stopPelletRepeatHandler(int index)
// {
//   pellet_repeating_ = false;
// }

void RotaryPelletControllerSimple::atPositionHandler(size_t channel, long position)
{
  moving_ = false;
}

void RotaryPelletControllerSimple::getPelletIndexHandler()
{
  modular_server_.response().returnResult(getPelletIndex());
}

// void RotaryPelletControllerSimple::getPositionHandler()
// {
//   modular_server_.response().returnResult(getPosition());
// }

// void RotaryPelletControllerSimple::pelletRepeatingHandler()
// {
//   modular_server_.response().returnResult(pelletRepeating());
// }

void RotaryPelletControllerSimple::stopHandler()
{
  // stopPelletRepeat();
  long channel;
  modular_server_.parameter(step_dir_controller_simple::constants::channel_parameter_name).getValue(channel);
  stop(channel);
}

// void RotaryPelletControllerSimple::stopAllHandler()
// {
//   // stopPelletRepeat();
//   stopAll();
// }

void RotaryPelletControllerSimple::moveToNextPelletHandler(modular_server::Interrupt * interrupt_ptr)
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

void RotaryPelletControllerSimple::playToneHandler(modular_server::Interrupt * interrupt_ptr)
{
  playTone();
}

// void RotaryPelletControllerSimple::repeatPelletHandler(int index)
// {
//   moveToNextPellet();
// }

// void RotaryPelletControllerSimple::dummyHandler(int index)
// {
// }

void RotaryPelletControllerSimple::updateTravelDurationRangeHandler()
{
  // long microsteps_per_step;
  // modular_server_.property(constants::microsteps_per_step_property_name).getValue(microsteps_per_step);
  // long steps_per_revolution;
  // modular_server_.property(constants::steps_per_revolution_property_name).getValue(steps_per_revolution);
  long microsteps_per_step = constants::microsteps_per_step_default;
  long steps_per_revolution = constants::steps_per_revolution_default;
  long pellets_per_revolution;
  modular_server_.property(constants::pellets_per_revolution_property_name).getValue(pellets_per_revolution);
  const long travel_duration_min = (steps_per_revolution*microsteps_per_step*1000)/(getVelocityMax()*pellets_per_revolution);
  const long travel_duration_max = (steps_per_revolution*microsteps_per_step*1000)/pellets_per_revolution;
  modular_server_.property(constants::travel_duration_property_name).setDefaultValue(constants::travel_duration_default);
  modular_server_.property(constants::travel_duration_property_name).setRange(travel_duration_min,travel_duration_max);
}

