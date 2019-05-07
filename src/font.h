#pragma once

#include <global_include.h>

#include "shapes.h"

#define FONT_DIR "ux0:/app/VHBBCLN01/resources/fonts/"
#define FONT_NAME "helvetica.ttf"

class Font {
public:
	Font(const std::string &path, unsigned int fSize);

	int Draw(const Point &pt, const std::string &text, unsigned int color = COLOR_WHITE);
	int DrawCentered(const Rectangle &rect, const std::string &text, int color = COLOR_WHITE);

	static std::unordered_map<std::pair<std::string, unsigned int>, vita2d_font*> fontCache;
private:
	vita2d_font *font;
	unsigned int size;
};