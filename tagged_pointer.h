#pragma once
#include <stdint.h>

namespace TaggedPointer
{
intptr_t SetupTag (intptr_t pointer);
intptr_t ClearTag (intptr_t pointer);
bool CheckTag (intptr_t  pointer);
}
