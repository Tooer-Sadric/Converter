// #include "stb_image_write.h"
// #include "stb_image.h"
#include <iostream>
#include <string>

#ifndef convert_hpp
#define convert_hpp


/**
 * @param inPath the entry for images to be converted
 * @param dest   the destination for the image to go tos
 * @param type   the type of img to convert to
 * @param qual   the quality of image to retains
 * @param canResize give the ability to resize image and essentially downscale
 */
bool IMGConverter(std::string const& inPath, std::string const& dest,std::string& type ,unsigned int const& qual, bool const& canResize);

void CustomFormat();


//Helper funcs
std::string GetExtension(std::string const&);

#endif