#pragma once

#define BETTER_ENUMS_CONSTEXPR_TO_STRING
#define BETTER_ENUMS_DEFAULT_CONSTRUCTOR(Enum) \
public:                                        \
	Enum() = default;

#include <better-enums/enum.h>
