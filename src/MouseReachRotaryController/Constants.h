// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_REACH_ROTARY_CONTROLLER_CONSTANTS_H
#define MOUSE_REACH_ROTARY_CONTROLLER_CONSTANTS_H
#include "ConstantVariable.h"
#include "StepDirController.h"
#include "StepperController.h"


namespace mouse_reach_rotary_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=9};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

enum{CHANNEL_COUNT=1};
extern const size_t channel;
// extern const size_t speaker_pin;

// enum{EVENT_COUNT_MAX=2};

extern const long pellet_repeat_period_delay;

// Interrupts

// Units
extern ConstantString duration_units;
extern ConstantString frequency_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long channel_count;

extern const long steps_per_position_units_default[CHANNEL_COUNT];

extern const long velocity_max_default[CHANNEL_COUNT];

extern const long velocity_min_default[CHANNEL_COUNT];

extern const long acceleration_max_default[CHANNEL_COUNT];

extern ConstantString steps_per_revolution_property_name;
extern const long steps_per_revolution_min;
extern const long steps_per_revolution_max;
extern const long steps_per_revolution_default;

extern ConstantString pellets_per_revolution_property_name;
extern const long pellets_per_revolution_min;
extern const long pellets_per_revolution_max;
extern const long pellets_per_revolution_default;

extern ConstantString travel_duration_property_name;
extern const long travel_duration_default;

extern ConstantString reverse_direction_property_name;
extern const bool reverse_direction_default;

extern ConstantString tone_frequency_property_name;
extern const long tone_frequency_min;
extern const long tone_frequency_max;
extern const long tone_frequency_default;

extern ConstantString tone_duration_property_name;
extern const long tone_duration_min;
extern const long tone_duration_max;
extern const long tone_duration_default;

extern ConstantString play_tone_before_move_property_name;
extern const bool play_tone_before_move_default;

// extern ConstantString pellet_repeat_property_name;
// extern const bool pellet_repeat_default;

// extern ConstantString pellet_repeat_period_property_name;
// extern const long pellet_repeat_period_min;
// extern const long pellet_repeat_period_max;
// extern const long pellet_repeat_period_default;

// Parameters

// Functions
extern ConstantString get_pellet_index_function_name;
// extern ConstantString get_position_function_name;
// extern ConstantString pellet_repeating_function_name;

// Callbacks
extern ConstantString move_to_next_pellet_callback_name;
extern ConstantString play_tone_callback_name;

// Errors
}
}
#include "TEENSY40.h"
#endif
