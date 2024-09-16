#pragma once

#include <stdint.h>

//! Maximum length of CAN frame payload in bytes
#define CONF_LIMIT_MAX_DLC 8

//! The highest possible bit position based on MAX Data size
#define CONF_LIMIT_HIGHEST_BIT_POSITION (CONF_LIMIT_MAX_DLC * 8u) - 1u
