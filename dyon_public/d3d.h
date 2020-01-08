#pragma once

#include "stdafx.h"
#define COLOR_GREEN		0xFF00FF00
#define COLOR_BLUE		0xFF0000FF
#define COLOR_RED		0xFFFF0000
#define COLOR_WHITE		0xFFFFFFFF
#define COLOR_BLACK		0xFF000000
#define COLOR_YELLOW	0xFFFFFF00

struct Vertex
{
	float x;
	float y;
	float w;
	float h;
	D3DCOLOR color;
};

void FillRectangle(int32_t x, int32_t y, int32_t w, int32_t h, D3DCOLOR color, LPDIRECT3DDEVICE9 device);
void DrawBorder(int32_t x, int32_t y, int32_t w, int32_t h, int32_t p, D3DCOLOR color, LPDIRECT3DDEVICE9 device);
void DrawBox(int32_t x, int32_t y, int32_t w, int32_t h, D3DCOLOR back_color, D3DCOLOR border_color, LPDIRECT3DDEVICE9 device);
void DrawLine(float X, float Y, float X2, float Y2, DWORD dwColor, LPDIRECT3DDEVICE9 pDevice);
void WriteText(int32_t x, int32_t y, DWORD color, char *text, uint32_t alignment, LPD3DXFONT font);