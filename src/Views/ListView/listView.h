#pragma once

#include <global_include.h>

#include <Views/View.h>
#include "listItem.h"

#define LIST_MIN_Y 79
#define LIST_MAX_Y 543 // This ordinate is included too
#define LIST_RANGE_Y (LIST_MAX_Y - LIST_MIN_Y)
#define LIST_HEIGHT (LIST_RANGE_Y + 1)

// Max speed px/ms above which selected item is no more selected
#define LIST_SELECTION_MAX_SPEED 0.000070


class ListView: public View {
public:
	explicit ListView(const std::vector<Homebrew>& homebrews);

	int HandleInput(int focus, const Input& input) override;
	int Display() override;

	virtual void SignalSelected() { log_printf(DBG_DEBUG, "ListView::SignalSelected"); };
	virtual void SignalDeselected() { log_printf(DBG_DEBUG, "ListView::SignalDeselected"); };
	virtual bool IsReadyToShow() { return true; };

protected:
	std::vector<ListItem> listItems;

private:
	Font font_43;

	int posY = 0; //!< Position in the list of homebrews if we consider it as a texture
	int preSelectedItem = -1;
	int selectedItem = -1;
	int itemHighlightAlpha = 255;
	int itemHighlightSpeed = 7;
	int itemHighlightDirection = 1;
	int resetHighlight();
	
	double scrollSpeed = 0;

	unsigned int itemPosY(unsigned int i);
	unsigned int firstDisplayedItem();
	unsigned int lastDisplayedItem();
	unsigned int firstFullyDisplayedItem();
	unsigned int lastFullyDisplayedItem();
	int coordinateToItem(double coordY);
	int updateScrollSpeed(double &scrollSpeed, unsigned long timeDif);
};
