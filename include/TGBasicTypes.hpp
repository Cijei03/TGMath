#pragma once
#include <cstdint>

#ifndef TGM_NODISCARD
#define TGM_NODISCARD [[nodiscard]]
#define TGM_UNDEFINED 0
#endif

using TGsize = size_t;

using TGi8 = int8_t;
using TGi16 = int16_t;
using TGi32 = int32_t;
using TGi64 = int64_t;

using TGui8 = uint8_t;
using TGui16 = uint16_t;
using TGui32 = uint32_t;
using TGui64 = uint64_t;

using TGf32 = float;
using TGf64 = double;