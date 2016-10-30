#pragma once
#include <stdint.h>

namespace TaggedPointer
{
static inline intptr_t SetupTag (intptr_t pointer)
{
	return pointer | 1;
}

static inline intptr_t ClearTag (intptr_t pointer)
{
	return (pointer) & ~static_cast<intptr_t>(1);
}

static inline bool CheckTag (intptr_t  pointer)
{
	return pointer & 1;
}
}
