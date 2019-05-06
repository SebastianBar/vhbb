#include "splash.h"
#include <texture.h>
#include <algorithm>

extern unsigned char _binary_assets_spr_img_splash_png_start;


Splash::Splash() :
	vhbb_splash(Texture(&_binary_assets_spr_img_splash_png_start))
{
}

int Splash::Display()
{
	Texture splashes[] = {
		vhbb_splash
	};

	if (splash_index >= 1) {
		request_destroy = true;
		return true;
	}

	splashes[splash_index].DrawExt(Point(0, 0), alpha);

	switch(step) {
		case STEP_FADING_IN:
			alpha = std::min<unsigned int>(255, alpha + SPLASH_FADING_STEP_SIZE);
			if (alpha >= 255) {
				step = STEP_STATIC;
				alpha = 255;
				frame_count = 0;
			}
			break;
		case STEP_STATIC:
			if (frame_count >= SPLASH_STATIC_DURATION_IN_FRAMES) {
				step = STEP_FADING_OUT;
			}
			frame_count += 1;
			break;
		case STEP_FADING_OUT:
			alpha = (unsigned int) std::max<int>(0, ((int)alpha) - SPLASH_FADING_STEP_SIZE);
			if (alpha <= 0) {
				alpha = 0;
				splash_index += 1;
				step = STEP_FADING_IN;
			}
			break;
		default:
			break;
	}

	return 0;
}
