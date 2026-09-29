#include "Converter.hpp"
#include <algorithm>
//compile line g++ -Iinclude src/main.cpp src/converter.cpp -o build/program
//#define or ||

int main(){
    std::cout << "entry point\n";
    std::cout << "input file location: ";
    std::string input{};
    std::cin >> input;
    std::cout << "input output type: ";
    std::string outputType{};
    std::cin >> outputType;
    std::cout << "your type: " << outputType << std::endl;
    outputType = ToLower(outputType);
    if(outputType != "png" && outputType != "jpg" && outputType != "jpeg"){
        std::cerr << "Unsupported format, defaulting to png" << std::endl;
        outputType = "png";
    }

    std::cout << "input destination folder: example: test/: ";
    std::string dest{};
    std::cin >> dest;
    std::string tmp{};
    std::cout << "input filename: ";
    std::cin >> tmp;
    dest.append(tmp);
    dest.push_back('.');
    dest.append(outputType);
    //total output should be smth like test/test.png
    bool resize{false};
    std::cout << "resize? 1 for yes, 0 for no: ";
    unsigned int rz;
    std::cin >> rz;
    if(rz == 1){resize = true;}else{resize = false;}
    unsigned int quality {};
    std::cout << "Quality: ";
    std::cin >> quality;
    int resizeAmt{};
    if(rz == 1){
        std::cout << "Resized by to what size? 75%, 50%, 25%: ";
        std::cin >> resizeAmt;
    }
    if(resizeAmt <= 0){
        std::cout <<"Nah, 0 or negs not allowed. defaulting to 100 <no resize>" << std::endl;
        resizeAmt = 100;
    }

    if(IMGConverter(input,dest,outputType,quality,resize,resizeAmt)){
        std::cout << "Image converted successfully\n";
    }
    //CustomFormat();
    std::cin.get();
}