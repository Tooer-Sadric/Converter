#include "Converter.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image_resize2.h"
#include "stb_image.h"
#include <algorithm>
#include <vector>
#include <cctype>

//FORWARD DECALS
int Resize(unsigned char* data, int width, int height, int channel, int rzValue, std::string const& dest);


bool IMGConverter(std::string const& inPath, std::string const& dest,std::string& type ,unsigned int const& qual,
                  bool const& canResize, int rzVal)
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
    //type checking
    if(type == exten){
        std::cerr << "Attempting to convert to the same file format\n";
    }
    else if(type == "png"){
        std::cout << "png selected\n";
        if(canResize){
            ok = Resize(img,width,height,channel,rzVal,dest);
            std::cout << "Image Resized\n";
        }else{
            //default conversion
            ok = stbi_write_png(dest.c_str(),width,height,channel,img, width * channel);
        }
    }
    else if(type == "jpeg" || type == "jpg"){
        std::cout << "jpg or jpeg selected\n";
        //ok = 1;
        ok = stbi_write_jpg(dest.c_str(),width,height,channel,img,qual);
    } //if other file types needed to be added here.
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

int Resize(unsigned char* data, int width, int height, int channel, int rzValue, std::string const& dest){
    //assuming rzValue will be 75, 50, 25
    //do some math regarding rzValue to be equal to be each requisite
    unsigned int newWidth = static_cast<unsigned int>(width  * rzValue / 100);
    unsigned int newHeight = static_cast<unsigned int>(height * rzValue / 100);
    std::vector<unsigned char> resized(newWidth * newHeight * channel);
    stbir_resize_uint8_linear(data, width, height, 0, resized.data(), newWidth, newHeight, 0,(stbir_pixel_layout)channel);
    return stbi_write_png(dest.c_str(),newWidth,newHeight,channel,resized.data(), newWidth * channel);
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
        return std::tolower(c);
    });

    return extension;
}

std::string ToLower(std::string& inStr){
    std::transform(inStr.begin(),inStr.end(),inStr.begin(),[](unsigned char c){
        return std::tolower(c);
    });
    return inStr;
}