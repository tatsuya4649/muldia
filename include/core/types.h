// <core/types.h> define int type with different number of bits.
//
#ifndef _CORE_TYPES_H
#define _CORE_TYPES_H

#include <name.h>
#include <cstdint>

namespace __md{
	// define various int types
	using int64  = std::int64_t;
	using int32  = std::int32_t;
	using int16  = std::int16_t;
	using int8   = std::int8_t;
	using uint64 = std::int64_t;
	using uint32 = std::int32_t;
	using uint16 = std::int16_t;
	using uint8  = std::int8_t;

	enum class axis{
		NONE = 0,
		ROW,
		COL
	};

	enum class endian : char{
		// 4bytes    00000001 00000010 00000100 00001000
		// +++++++++++++++++++++++++++++++++++++++++++++
		// NATIVE => 00000001 00000010 00000100 00001000
		NATIVE = 0
		// BIG    => 00000001 00000010 00000100 00001000
		BIG,
		// LITTLE => 00001000 00000100 00000010 00000001
		LITTLE
	};
} // namespace __md

#endif // _CORE_TYPES_H
