// #include "stb_image_write.h"
// #include "stb_image.h"
#include <iostream>
#include <string>

#ifndef convert_hpp
#define convert_hpp


struct Image{
    std::string inPath;
    std::string outPath;
    std::string type;
    unsigned int quality;
    bool canResize;
    unsigned int resizeValue;
    unsigned int colorChannels;
};

struct ImgData{
    /**
     * @param newImage encapsulated image for processing
     */
    bool IMGConverter(Image& newImage);
    void what() const;
};



//bool IMGConverter(std::string const& inPath, std::string const& dest,std::string& type ,unsigned int const& qual, bool const& canResize,int rzVal,int colorChannels);

void GausianImage();

void CustomFormat();


//Helper funcs

/**
 * @param item the item file location
 */
std::string GetExtension(std::string const&);

/**
 * @param inStr string to lowercase
 */
std::string ToLower(std::string& inStr);
#endif