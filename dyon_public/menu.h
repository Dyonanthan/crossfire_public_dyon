#pragma once

#include "stdafx.h"
#include "menuitem.h"

class Menu
{
public:
	Menu();
	~Menu();

	void AddItem(int32_t *status, char item_description[32], char *status_description[], int32_t num_status_descriptions);
	void Render(LPDIRECT3DDEVICE9 device);
	void Navigate();

private:
	LPD3DXFONT font_;
	MenuItem items_[32];
	int32_t num_items_ = 0;
	int32_t current_index_ = 0;
	int32_t width_;
	int32_t height_;
	bool hidden_ = false;
};