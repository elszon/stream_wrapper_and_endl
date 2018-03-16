#include <iostream>
#include <fstream>

#include "StreamWrapper.h"


int main()
{
    OStreamWrapper s(std::make_unique<std::ostringstream>());
    s << "asdb" << std::endl;


    OStreamWrapper file(std::make_unique<std::ofstream>("file.txt"));

    file << "file out sdfasd" << std::endl;


    return 0;
}
