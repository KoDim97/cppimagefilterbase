#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include "stb_image_write.h"
#include "png_toolkit.h"

png_toolkit::png_toolkit()
{
}

png_toolkit::~png_toolkit()
{
    stbi_image_free(imgData.pixels);
}

bool png_toolkit::load( const std::string &pictureName )
{
    imgData.pixels = stbi_load(pictureName.c_str(), &imgData.w, &imgData.h, &imgData.compPerPixel, 0);
    return imgData.pixels != nullptr;
}

bool png_toolkit::save( const std::string &pictureName )
{
    return stbi_write_png(pictureName.c_str(),
                   imgData.w, imgData.h,
                   imgData.compPerPixel,
                          imgData.pixels, 0) != 0;
}

void png_toolkit::myFirstFilter() {
	for (int i = imgData.h / 2 * imgData.w * imgData.compPerPixel; i < imgData.h * imgData.w * imgData.compPerPixel; i+=4) {
		imgData.pixels[i] = 255;
		imgData.pixels[i+1] = 0;
		imgData.pixels[i+2] = 0;
	}
}
image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}
