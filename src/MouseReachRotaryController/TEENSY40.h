// ----------------------------------------------------------------------------
// TEENSY40.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef MOUSE_REACH_ROTARY_CONTROLLER_TEENSY40_CONSTANTS_H
#define MOUSE_REACH_ROTARY_CONTROLLER_TEENSY40_CONSTANTS_H
#include "Constants.h"


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
namespace mouse_reach_rotary_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum{CHANNEL_COUNT_MAX=3};

extern HardwareSerial * driver_serial_ptrs[CHANNEL_COUNT_MAX];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[CHANNEL_COUNT_MAX];

extern const long velocity_max_default[CHANNEL_COUNT_MAX];

extern const long velocity_min_default[CHANNEL_COUNT_MAX];

extern const long acceleration_max_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX];

extern const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const long home_velocity_default[CHANNEL_COUNT_MAX];

extern const bool invert_driver_direction_default[CHANNEL_COUNT_MAX];

extern const long run_current_default[CHANNEL_COUNT_MAX];

extern const long hold_current_default[CHANNEL_COUNT_MAX];

extern const long hold_delay_default[CHANNEL_COUNT_MAX];

extern const long microsteps_per_step_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const standstill_mode_ptr_default[CHANNEL_COUNT_MAX];

extern const bool automatic_current_scaling_default[CHANNEL_COUNT_MAX];

extern const bool automatic_gradient_adaptation_default[CHANNEL_COUNT_MAX];

extern const long cool_step_lower_threshold_default[CHANNEL_COUNT_MAX];

extern const long cool_step_upper_threshold_default[CHANNEL_COUNT_MAX];

extern const long cool_step_duration_threshold_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const cool_step_current_increment_ptr_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const cool_step_measurement_count_ptr_default[CHANNEL_COUNT_MAX];

extern const bool cool_step_enabled_default[CHANNEL_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
#endif
