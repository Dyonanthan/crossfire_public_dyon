#pragma once

#include "stdafx.h"

struct MenuItem
{
public:
	int32_t *status;
	char item_description[32];
	int32_t num_status_descriptions;
	char status_description[64];
};