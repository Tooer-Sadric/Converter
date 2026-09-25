#include "Converter.hpp"
//compile line g++ -Iinclude src/main.cpp src/converter.cpp -o build/program


int main(){
    std::cout << "entry point\n";
    std::string input{"test/test.jpg"};
    std::string outputType{"png"};
    std::string dest{"test/test." + outputType};
    bool resize{true};
    int quality {100};
    if(IMGConverter(input,dest,outputType,quality,resize)){
        std::cout << "Image converted successfully\n";
    }
    //CustomFormat();
    std::cin.get();
}