#include "main.h"
int main(int argc, char const *argv[])
{
    // Stop compiler warning
    (void)argc, (void)argv;

    // shell functionality
    while (true)
    {
        std::cout << "myshell$";

        // input buffer
        std::string buffer;
        getline(std::cin, buffer,'\n');     // \n is delimeter

        if (buffer.length())
        {
            // PID of the child
            pid_t child_pid = fork();
            /*
            

            fork() returns a pid_t, which is an integer type.
            In the parent process, fork() returns the PID of the child process.
            In the child process, fork() returns 0.
            If fork() fails, it returns -1.
            
            */

            if(child_pid<0){
                std::cout<<"Fork failed"<<std::endl;
                exit(41); // 41 => fork failed
            }
            if(child_pid==0){
                // std::cout<< "Fork creation & execution successful"<<std::endl;

                std::string token;
                std::stringstream stream(buffer);
                std::vector<std::string> tokens;
                while(getline(stream,token,' ')){
                    tokens.push_back(token);
                }

                

                exit(0);
            }else{
                wait(NULL);         //wait till child is finished
                std::cout<< "now we are back to the parent"<<std::endl;
            }
        }
        buffer.clear();
    }

    // 0 for success
    return 0;
}
