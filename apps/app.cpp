#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
    std::ifstream file(argv[1]);
    std::string line;

    std::cout << argc << std::endl;

    if(file.is_open())
    {
        while (getline(file,line)) 
        {
            std::cout << line << std::endl;
        }
        file.close();        
    } else
    {
        std::cout << "Error opening the file." << std::endl;
    }  

    return 0;
}