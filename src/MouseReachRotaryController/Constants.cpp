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

const long pellet_repeat_period_delay = 20;

// Interrupts

// Units
CONSTANT_STRING(duration_units,"ms");
CONSTANT_STRING(frequency_units,"Hz");

// Properties
const long channel_count = CHANNEL_COUNT;

const long steps_per_position_units_default[CHANNEL_COUNT] =
{
  1,
};

const long velocity_max_default[CHANNEL_COUNT] =
{
  200000,
};

const long velocity_min_default[CHANNEL_COUNT] =
{
  20000,
};

const long acceleration_max_default[CHANNEL_COUNT] =
{
  200000,
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
const long travel_duration_default = 160;

CONSTANT_STRING(reverse_direction_property_name,"reverseDirection");
const bool reverse_direction_default = false;

CONSTANT_STRING(tone_frequency_property_name,"toneFrequency");
const long tone_frequency_min = 850;
const long tone_frequency_max = 20000;
const long tone_frequency_default = 5000;

CONSTANT_STRING(tone_duration_property_name,"toneDuration");
const long tone_duration_min = 1;
const long tone_duration_max = 10000;
const long tone_duration_default = 200;

CONSTANT_STRING(play_tone_before_move_property_name,"playToneBeforeMove");
const bool play_tone_before_move_default = false;

// CONSTANT_STRING(pellet_repeat_property_name,"pelletRepeat");
// const bool pellet_repeat_default = false;

// CONSTANT_STRING(pellet_repeat_period_property_name,"pelletRepeatPeriod");
// const long pellet_repeat_period_min = 100;
// const long pellet_repeat_period_max = 10000;
// const long pellet_repeat_period_default = 2000;

// Parameters

// Functions
CONSTANT_STRING(get_pellet_index_function_name,"getPelletIndex");
// CONSTANT_STRING(get_position_function_name,"getPosition");
// CONSTANT_STRING(pellet_repeating_function_name,"pelletRepeating");

// Callbacks
CONSTANT_STRING(move_to_next_pellet_callback_name,"moveToNextPellet");
CONSTANT_STRING(play_tone_callback_name,"playTone");

// Errors
}
}
