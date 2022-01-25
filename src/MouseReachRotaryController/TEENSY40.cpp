// ----------------------------------------------------------------------------
// TEENSY40.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "TEENSY40.h"


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
namespace mouse_reach_rotary_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1145,
  .version_major=1,
  .version_minor=2,
};

const size_t controller_count = 1;

HardwareSerial * driver_serial_ptrs[CHANNEL_COUNT_MAX] =
{
  &Serial1,
  &Serial3,
  &Serial4,
};

// Pins

// Units

// Properties
const long channel_count_default = CHANNEL_COUNT_MAX;

const long steps_per_position_units_default[CHANNEL_COUNT_MAX] =
{
  steps_per_position_units_element_default,
  steps_per_position_units_element_default,
  steps_per_position_units_element_default,
};

const long velocity_max_default[CHANNEL_COUNT_MAX] =
{
  velocity_max_element_default,
  velocity_max_element_default,
  velocity_max_element_default,
};

const long velocity_min_default[CHANNEL_COUNT_MAX] =
{
  velocity_min_element_default,
  velocity_min_element_default,
  velocity_min_element_default,
};

const long acceleration_max_default[CHANNEL_COUNT_MAX] =
{
  acceleration_max_element_default,
  acceleration_max_element_default,
  acceleration_max_element_default,
};

const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX] =
{
  enable_polarity_element_default,
  enable_polarity_element_default,
  enable_polarity_element_default,
};

const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX] =
{
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
};

const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX] =
{
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
};

const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX] =
{
  switch_soft_stop_enabled_element_default,
  switch_soft_stop_enabled_element_default,
  switch_soft_stop_enabled_element_default,
};

const long home_velocity_default[CHANNEL_COUNT_MAX] =
{
  home_velocity_element_default,
  home_velocity_element_default,
  home_velocity_element_default,
};

const bool invert_driver_direction_default[CHANNEL_COUNT_MAX] =
{
  invert_driver_direction_element_default,
  invert_driver_direction_element_default,
  invert_driver_direction_element_default,
};

const long run_current_default[CHANNEL_COUNT_MAX] =
{
  run_current_element_default,
  run_current_element_default,
  run_current_element_default,
};

const long hold_current_default[CHANNEL_COUNT_MAX] =
{
  hold_current_element_default,
  hold_current_element_default,
  hold_current_element_default,
};

const long hold_delay_default[CHANNEL_COUNT_MAX] =
{
  hold_delay_element_default,
  hold_delay_element_default,
  hold_delay_element_default,
};

const long microsteps_per_step_default[CHANNEL_COUNT_MAX] =
{
  microsteps_per_step_element_default,
  microsteps_per_step_element_default,
  microsteps_per_step_element_default,
};

const ConstantString * const standstill_mode_ptr_default[CHANNEL_COUNT_MAX] =
{
  standstill_mode_ptr_element_default,
  standstill_mode_ptr_element_default,
  standstill_mode_ptr_element_default,
};

const bool automatic_current_scaling_default[CHANNEL_COUNT_MAX] =
{
  automatic_current_scaling_element_default,
  automatic_current_scaling_element_default,
  automatic_current_scaling_element_default,
};

const bool automatic_gradient_adaptation_default[CHANNEL_COUNT_MAX] =
{
  automatic_gradient_adaptation_element_default,
  automatic_gradient_adaptation_element_default,
  automatic_gradient_adaptation_element_default,
};

const long cool_step_lower_threshold_default[CHANNEL_COUNT_MAX] =
{
  cool_step_lower_threshold_element_default,
  cool_step_lower_threshold_element_default,
  cool_step_lower_threshold_element_default,
};

const long cool_step_upper_threshold_default[CHANNEL_COUNT_MAX] =
{
  cool_step_upper_threshold_element_default,
  cool_step_upper_threshold_element_default,
  cool_step_upper_threshold_element_default,
};

const long cool_step_duration_threshold_default[CHANNEL_COUNT_MAX] =
{
  cool_step_duration_threshold_element_default,
  cool_step_duration_threshold_element_default,
  cool_step_duration_threshold_element_default,
};

const ConstantString * const cool_step_current_increment_ptr_default[CHANNEL_COUNT_MAX] =
{
  cool_step_current_increment_ptr_element_default,
  cool_step_current_increment_ptr_element_default,
  cool_step_current_increment_ptr_element_default,
};

const ConstantString * const cool_step_measurement_count_ptr_default[CHANNEL_COUNT_MAX] =
{
  cool_step_measurement_count_ptr_element_default,
  cool_step_measurement_count_ptr_element_default,
  cool_step_measurement_count_ptr_element_default,
};

const bool cool_step_enabled_default[CHANNEL_COUNT_MAX] =
{
  cool_step_enabled_element_default,
  cool_step_enabled_element_default,
  cool_step_enabled_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
