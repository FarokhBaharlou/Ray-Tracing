#pragma once

#include "Vec3.h"
#include <iostream>
#include "PPM_Image.h"

void write_color(PPM& img,size_t xIdx, size_t yIdx, Color c)
{
	const int ir = static_cast<int>(255.999 * c.x());
	const int ig = static_cast<int>(255.999 * c.y());
	const int ib = static_cast<int>(255.999 * c.z());
	img.image[xIdx][yIdx] = PPM::RGB(ir, ig, ib);
}