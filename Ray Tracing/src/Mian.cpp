
#include <iostream>
#include "PPM_Image.h"
#include "color.h"
#include "vec3.h"

int main()
{
	constexpr int image_width = 256;
	constexpr int image_height = 256;

	PPM test(image_width, image_height);

	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			Color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			write_color(test, image_height - 1 - j, i, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";

	test.set_version("P3");
	test.save("output\\Result.ppm");
	return 0;
}