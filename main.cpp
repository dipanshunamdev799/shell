#include "main.h"
std::string get_path(char* command){

    //In case user gave absolute path
    if(access(command,F_OK)==0 && access(command,X_OK)==0) return std::string(command);

    char *path = getenv("PATH");
    std::stringstream stream(path);
    std::string token;
    while(getline(stream,token,':')){
        token = token + "/" + std::string(command) ;
        if( access(token.c_str(),F_OK)==0 && access(token.c_str(),X_OK)==0){
            return token;
        }
    }
    return nullptr;
}
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

        getline(std::cin, buffer, '\n'); // \n is delimeter for input

        if (buffer.length())
        {
            // PID of the child
            pid_t child_pid = fork();
            /*
            In the parent process, fork() returns the PID of the child process.
            In the child process, fork() returns 0.
            If fork() fails, it returns -1.
            */

            if (child_pid < 0)
            {
                exit(41); // 41 => fork failed
            }
            if (child_pid == 0)
            {
                std::string token;
                std::stringstream stream(buffer);       //stream of the input

                char **tokens = nullptr;        //all tokens collection
                int i = 0;
                tokens = (char **)malloc(sizeof(char *) * i);
                if (tokens == nullptr)
                    exit(7);    // exit code 7 means execution failed of the child process

                while (getline(stream, token, ' '))
                {
                    tokens = (char **)realloc(tokens, sizeof(char *) * (i + 1));
                    if (tokens == nullptr)
                        exit(7);    // exit code 7 means execution failed of the child process

                    tokens[i] = (char *)malloc(sizeof(char) * token.length());
                    if (tokens[i] == nullptr)
                        exit(7);    // exit code 7 means execution failed of the child process

                    strcpy(tokens[i], token.c_str());
                    i++;
                }
                tokens = (char **)realloc(tokens, sizeof(char *) * (i + 1));
                tokens[i] = NULL;

                std::string path = get_path(tokens[0]);    //path to the given executable along with the filename
                if(path.length()==0) exit(7);
                if (execve(path.c_str(), tokens, NULL) == -1)
                {
                    free(tokens);
                    exit(7);    // exit code 7 means execution failed of the child process
                }
                else
                {
                    free(tokens);
                    exit(0);
                }
            }
            else
            {
                wait(NULL); // wait till child is finished
            }
        }
    }
    return 0;  // 0 for success
}
