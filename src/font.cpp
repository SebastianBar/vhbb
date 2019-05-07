#include "font.h"

std::unordered_map<std::pair<std::string, unsigned int>, vita2d_font*> Font::fontCache;

Font::Font(const std::string &path, unsigned int fSize) {
	//log_printf(DBG_DEBUG, "Looking for size %d, path: %s", fSize, path.c_str());
	auto key = std::make_pair(path, fSize);
	if (fontCache[key]) {
		//log_printf(DBG_DEBUG, "Found it in cache");
		font = fontCache[key];
		size = fSize;
		return;
	}
	//log_printf(DBG_DEBUG, "Storing in cache...");
	font = vita2d_load_font_file(path.c_str());
	fontCache[key] = font;
	size = fSize;
}

int Font::Draw(const Point &pt, const std::string &text, unsigned int color) {
	return vita2d_font_draw_text(font, (int) pt.x, (int) pt.y, color, size, text.c_str());
}

int Font::DrawCentered(const Rectangle &rect, const std::string &text, unsigned int color) {
	//log_printf(DBG_DEBUG, "DrawCentered: %f,%f:%f,%f", rect.topLeft.x, rect.topLeft.y, rect.bottomRight.x, rect.bottomRight.y);
	int width, height;
	vita2d_font_text_dimensions(font, size, text.c_str(), &width, &height);
	//log_printf(DBG_DEBUG, "Dimensions: %d, %d", width, height);

	double posX = rect.topLeft.x + (rect.bottomRight.x - rect.topLeft.x - (double) width)/2;

	// FIXME Should be height/2 but it doesn't look good with it
	double posY = rect.topLeft.y + (rect.bottomRight.y - rect.topLeft.y)/2 + (double) height/3;

	//log_printf(DBG_DEBUG, "Pos: %d, %d", posX, posY);

	return Draw(Point(posX, posY), text, color);
}