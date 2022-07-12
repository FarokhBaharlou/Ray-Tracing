
#pragma once

#include <fstream>
#include <iostream>
#include <cmath>

class PPM
{
public:
	struct RGB
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};
public:
	PPM() = default;
	PPM(int height, int width);
	~PPM();

	void set_width(int width) { this->width = width; };
	void set_height(int height) { this->height = height; };
	void set_version(std::string version) { this->version = version; };

	void save(std::string file_name);
	void read(std::string file_name);

	void horizontal_flip();
	void vertical_flip();
	void grey_scale();
	void resize(int height, int width);

	void delete_image();
public:
	RGB** image = nullptr;
private:
	int width = 0;
	int height = 0;
	std::string version = "P3";
private:
	void create_image();
};

PPM::PPM(int height, int width)
{
	set_height(height);
	set_width(width);
	create_image();
}

PPM::~PPM()
{
	delete_image();
}

void PPM::save(std::string file_name)
{
	std::ofstream output(file_name, std::ios::binary);
	if (output.is_open())
	{
		output << version << std::endl;
		output << width << std::endl;
		output << height << std::endl;
		output << 255 << std::endl;

		if (version == "P3")
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					output << (int)image[i][j].r << ' ';
					output << (int)image[i][j].g << ' ';
					output << (int)image[i][j].b << '\n';
				}
			}
		}
		else
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					output.write((char*)&image[i][j], sizeof(RGB));
				}
			}
		}
		output.close();
	}
}

void PPM::read(std::string file_name)
{
	std::ifstream input(file_name, std::ios::binary);
	if (input.is_open())
	{
		int color;
		char ver[3];

		input.read(ver, 2);
		version = ver;
		input >> width;
		input >> height;
		input >> color;
		input.read(ver, 1);

		create_image();

		int box;
		if (version == "P3")
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					input >> box;
					image[i][j].r = box;

					input >> box;
					image[i][j].g = box;

					input >> box;
					image[i][j].b = box;
				}
			}
		}
		else
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					input.read((char*)&image[i][j], sizeof(RGB));
				}
			}
		}
		input.close();
	}
}

void PPM::create_image()
{
	if (image != nullptr)
	{
		delete_image();
	}

	image = new RGB* [height];

	for (int i = 0; i < height; i++)
	{
		image[i] = new RGB[width];
		for (int j = 0; j < width; j++)
		{
			image[i][j].r = 255;
			image[i][j].g = 255;
			image[i][j].b = 255;
		}
	}
}

void PPM::horizontal_flip()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < (width / 2); j++)
		{
			std::swap(image[i][j], image[i][width - 1 - j]);
		}
	}
}

void PPM::vertical_flip()
{
	for (int i = 0; i < (height / 2); i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::swap(image[i][j], image[height - 1 - i][width]);
		}
	}
}

void PPM::grey_scale()
{
	constexpr float r = 0.299f;
	constexpr float g = 0.587f;
	constexpr float b = 0.114f;
	float greyscaleValue;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			greyscaleValue = image[i][j].r * r + image[i][j].g * g + image[i][j].b * b;
			image[i][j].r = greyscaleValue;
			image[i][j].g = greyscaleValue;
			image[i][j].b = greyscaleValue;
		}
	}
}

void PPM::delete_image()
{
	if (image != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			delete image[i];
		}
		delete image;
	}
}

void PPM::resize(int height, int width)
{
	RGB** resized_image = new RGB* [height];
	for (int i = 0; i < height; i++)
	{
		resized_image[i] = new RGB[width];
		for (int j = 0; j < width; j++)
		{
			resized_image[i][j].r = 255;
			resized_image[i][j].g = 255;
			resized_image[i][j].b = 255;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			resized_image[i][j] = image[i * this->height / height][j * this->width / width];
		}
	}

	delete_image();
	image = resized_image;
	this->height = height;
	this->width = width;
}