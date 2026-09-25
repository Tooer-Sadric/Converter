#include "Converter.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image_resize2.h"
#include "stb_image.h"
#include <algorithm>
#include <vector>

//FORWARD DECALS
std::string ToLower(std::string& inStr);

bool IMGConverter(std::string const& inPath, std::string const& dest,std::string& type ,unsigned int const& qual,
                  bool const& canResize)
{
    int width, height, channel;
    //gna assume sbti store the values of the width and all after checking the file.
    unsigned char* img{stbi_load(inPath.c_str(),&width,&height,&channel,0)};
    if(!img){
        std::cerr << "Failed to load " << inPath << ": " << stbi_failure_reason() << '\n';
    }

    std::string exten{GetExtension(inPath)};
    type = ToLower(type);
    
    int ok{0};

    if(type == exten){
        std::cerr << "Attempting to convert to the same file format\n";
    }
    else if(type == "png"){
        std::cout << "png selected\n";
        if(canResize){
            unsigned int newWidth = width / 2;
            unsigned int newHeight = height / 2;

            std::vector<unsigned char> resized(newWidth * newHeight * channel);

            stbir_resize_uint8_linear(img, width, height, 0, resized.data(), newWidth, newHeight, 0,(stbir_pixel_layout)channel);
            ok = stbi_write_png(dest.c_str(),newWidth,newHeight,channel,resized.data(), newWidth * channel);
            std::cout << "Image Resized\n";
        }else{
            //default conversion
            ok = stbi_write_png(dest.c_str(),width,height,channel,img, width * channel);
        }
    }
    else if(type == "jpeg" || type == "jpg"){
        std::cout << "jpg or jpeg selected\n";
        ok = 1;
    }
    else{
        std::cerr << "Unsupported format ." << type << '\n';
        ok = 1;
    }

    stbi_image_free(img);
    return (ok != 0);
}

void CustomFormat(){
    std::cout << "Stub function for the case of custom format\n";
}

//if for some reason we ever need ts
std::string GetExtension(std::string const& item){
    std::size_t dotPos{item.find_last_of('.')};
    //no dot position found.
    if(dotPos == std::string::npos)return "";
    //extract 1 after the dot pos
    std::string extension{item.substr(dotPos+1)};
    //lowercase the extension
    std::transform(extension.begin(),extension.end(),extension.begin(),[](unsigned char c){
        return std::towlower(c);
    });

    return extension;
}

std::string ToLower(std::string& inStr){
    std::transform(inStr.begin(),inStr.end(),inStr.begin(),[](unsigned char c){
        return std::towlower(c);
    });
    return inStr;
}