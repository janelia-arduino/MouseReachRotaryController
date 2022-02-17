// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace mouse_reach_rotary_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"mouse_reach_rotary_controller");

CONSTANT_STRING(firmware_name,"MouseReachRotaryController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

CONSTANT_STRING(hardware_name,"mouse_reach_controller");

const size_t channel = 0;

const double velocity_max_scale_factor = 1.4;

const long initialize_trigger_delay = 2000;

// Pins
CONSTANT_STRING(signal_a_pin_name,"signal_a");

CONSTANT_STRING(signal_b_pin_name,"signal_b");

CONSTANT_STRING(signal_c_pin_name,"signal_c");

CONSTANT_STRING(signal_d_pin_name,"signal_d");

// Units
CONSTANT_STRING(frequency_units,"Hz");
CONSTANT_STRING(percent_units,"%");
CONSTANT_STRING(duration_units,"ms");

// Properties
const long channel_count = CHANNEL_COUNT;

const long steps_per_position_units_default[CHANNEL_COUNT] =
{
  1,
};

const long velocity_min_default[CHANNEL_COUNT] =
{
  100,
};

const long acceleration_max_default[CHANNEL_COUNT] =
{
  1000000,
};

CONSTANT_STRING(steps_per_revolution_property_name,"stepsPerRevolution");
const long steps_per_revolution_min = 1;
const long steps_per_revolution_max = 10000;
const long steps_per_revolution_default = 200;

CONSTANT_STRING(pellets_per_revolution_property_name,"pelletsPerRevolution");
const long pellets_per_revolution_min = 1;
const long pellets_per_revolution_max = 255;
const long pellets_per_revolution_default = 30;

CONSTANT_STRING(travel_duration_property_name,"travelDuration");
const long travel_duration_min = 1;
const long travel_duration_max = 10000;
const long travel_duration_default = 160;

CONSTANT_STRING(reverse_direction_property_name,"reverseDirection");
const bool reverse_direction_default = false;

CONSTANT_STRING(crosstalk_suppression_duration_property_name,"crosstalkSuppressionDuration");
const long crosstalk_suppression_duration_min = 1;
const long crosstalk_suppression_duration_max = 20;
const long crosstalk_suppression_duration_default = 4;

CONSTANT_STRING(retrigger_suppression_duration_property_name,"retriggerSuppressionDuration");
const long retrigger_suppression_duration_min = 10;
const long retrigger_suppression_duration_max = 10000;
const long retrigger_suppression_duration_default = 1000;

CONSTANT_STRING(tone_frequency_property_name,"toneFrequency");
const long tone_frequency_min = 850;
const long tone_frequency_max = 20000;
const long tone_frequency_default = 5000;

CONSTANT_STRING(tone_volume_property_name,"toneVolume");
const long tone_volume_min = 0;
const long tone_volume_max = 100;
const long tone_volume_default = 25;

CONSTANT_STRING(tone_duration_property_name,"toneDuration");
const long tone_duration_min = 1;
const long tone_duration_max = 10000;
const long tone_duration_default = 200;

// Parameters

// Functions
CONSTANT_STRING(get_pellet_index_function_name,"getPelletIndex");

// Callbacks
CONSTANT_STRING(dispense_callback_name,"dispense");
CONSTANT_STRING(play_tone_callback_name,"playTone");

// Errors
}
}
