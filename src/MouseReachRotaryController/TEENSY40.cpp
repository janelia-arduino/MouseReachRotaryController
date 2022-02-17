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
  .part_number=2035,
  .version_major=1,
  .version_minor=2,
};

// Pins
const size_t signal_a_pin_number = 22;

const size_t signal_b_pin_number = 4;

const size_t signal_c_pin_number = 3;

const size_t signal_d_pin_number = 2;

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
