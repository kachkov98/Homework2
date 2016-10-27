#include "tagged_pointer.h"

namespace TaggedPointer
{
intptr_t SetupTag (intptr_t pointer)
{
	return pointer | 1;
}

intptr_t ClearTag (intptr_t pointer)
{
	return (pointer) & ~static_cast<intptr_t>(1);
}

bool CheckTag (intptr_t  pointer)
{
	return pointer & 1;
}
}
