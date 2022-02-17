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

enum{EVENT_COUNT_MAX=16};

extern const double velocity_max_scale_factor;

extern const long initialize_trigger_delay;

// Pins
enum{PIN_COUNT_MAX=4};

extern ConstantString signal_a_pin_name;
extern const size_t signal_a_pin_number;

extern ConstantString signal_b_pin_name;
extern const size_t signal_b_pin_number;

extern ConstantString signal_c_pin_name;
extern const size_t signal_c_pin_number;

extern ConstantString signal_d_pin_name;
extern const size_t signal_d_pin_number;

// Units
extern ConstantString frequency_units;
extern ConstantString percent_units;
extern ConstantString duration_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long channel_count;

extern const long steps_per_position_units_default[CHANNEL_COUNT];

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
extern const long travel_duration_min;
extern const long travel_duration_max;
extern const long travel_duration_default;

extern ConstantString reverse_direction_property_name;
extern const bool reverse_direction_default;

extern ConstantString crosstalk_suppression_duration_property_name;
extern const long crosstalk_suppression_duration_min;
extern const long crosstalk_suppression_duration_max;
extern const long crosstalk_suppression_duration_default;

extern ConstantString retrigger_suppression_duration_property_name;
extern const long retrigger_suppression_duration_min;
extern const long retrigger_suppression_duration_max;
extern const long retrigger_suppression_duration_default;

extern ConstantString tone_frequency_property_name;
extern const long tone_frequency_min;
extern const long tone_frequency_max;
extern const long tone_frequency_default;

extern ConstantString tone_volume_property_name;
extern const long tone_volume_min;
extern const long tone_volume_max;
extern const long tone_volume_default;

extern ConstantString tone_duration_property_name;
extern const long tone_duration_min;
extern const long tone_duration_max;
extern const long tone_duration_default;

// Parameters

// Functions
extern ConstantString get_pellet_index_function_name;

// Callbacks
extern ConstantString dispense_callback_name;
extern ConstantString play_tone_callback_name;

// Errors
}
}
#include "TEENSY40.h"
#endif
