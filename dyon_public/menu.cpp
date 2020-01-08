#include "menu.h"
#include "d3d.h"
#include "memory.h"
//https://github.com/biesigrr/phoenix-cf
Menu::Menu()
{
	this->width_ = 190;
}

Menu::~Menu()
{

}
//
void Menu::AddItem(int32_t *status, char item_description[32], char *status_description[], int32_t num_status_descriptions)
{
	// better not look at this code
	this->items_[this->num_items_].status = status;
	this->items_[this->num_items_].num_status_descriptions = num_status_descriptions;
	junkasm
	strcpy_s(this->items_[this->num_items_].item_description, item_description);

	for (int32_t i = 0; i < num_status_descriptions; i++)
	{
		junkasm
		memcpy_s(reinterpret_cast<void*>(this->items_[this->num_items_].status_description + i * 16), 16, reinterpret_cast<void*>(status_description[i]), 16);
	}

	this->num_items_++;
	this->height_ = this->num_items_ * 20 + 30;
}

void Menu::Render(LPDIRECT3DDEVICE9 device)
{
	// if menu is hidden, simply don't draw it
	if (this->hidden_)
		return;

	if (this->font_)
	{
		this->font_->Release();
		this->font_ = nullptr;
	}

	if (!this->font_)
		D3DXCreateFont(device, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &this->font_);

	DrawBox(10, 10, this->width_, this->height_, 0xC0000000, COLOR_RED, device);
	DrawBorder(10, 10, this->width_, 25, 1, COLOR_RED, device);
	WriteText(90, 15, COLOR_YELLOW, "Dyon Public Hack", DT_CENTER, this->font_);

	junkasm
	for (int32_t i = 0; i < this->num_items_; i++)
	{
		DWORD color = COLOR_WHITE;
		if (i == this->current_index_)
			color = COLOR_YELLOW;

		WriteText(20, 40 + i * 20, color, this->items_[i].item_description, DT_LEFT, this->font_);
		junkasm

		// this is pure magic
		char* status_desc = reinterpret_cast<char*>(this->items_[i].status_description + *this->items_[i].status * 16);
		WriteText(this->width_, 40 + i * 20, color, status_desc, DT_RIGHT, this->font_);
	}
}

void Menu::Navigate()
{
	junkasm
	if (GetAsyncKeyState(VK_INSERT) & 1)
		this->hidden_ = !this->hidden_;

	// arrow down
	if (GetAsyncKeyState(VK_DOWN) & 1)
	{
		// fancy calculation of next element
		this->current_index_ = (this->current_index_ + 1) % this->num_items_;
	}

	// arrow up
	if (GetAsyncKeyState(VK_UP) & 1)
	{
		if (this->current_index_ > 0)
			this->current_index_ -= 1;
		else
			this->current_index_ = this->num_items_ - 1;
	}

	junkasm
	// arrow right
	if (GetAsyncKeyState(VK_RIGHT) & 1)
	{
		if (*this->items_[this->current_index_].status < this->items_[this->current_index_].num_status_descriptions - 1)
			*this->items_[this->current_index_].status += 1;
	}

	// arrow left
	if (GetAsyncKeyState(VK_LEFT) & 1)
	{
		junkasm
		if (*this->items_[this->current_index_].status > 0)
			*this->items_[this->current_index_].status -= 1;
	}
}