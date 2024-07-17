#include "main.h"
int main(int argc, char const *argv[])
{
    // Stop compiler warning
    (void)argc, (void)argv;

    //shell functionality
    while (true)
    {
        std::cout << "myshell$";

        //input buffer
        std::string buffer;
        getline(std::cin,buffer);

        if(buffer.length()){
            std::cout<<buffer<<std::endl;
            buffer.clear();
        }
    }

    // 0 for success
    return 0;
}
