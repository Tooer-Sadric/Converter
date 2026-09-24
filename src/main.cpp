#include "Converter.hpp"
//compile line g++ -Iinclude src/main.cpp src/converter.cpp -o build/program


int main(){
    std::cout << "entry point\n";
    PNGToJPEG();
    CustomFormat();
    std::cin.get();
}