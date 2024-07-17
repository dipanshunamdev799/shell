#include "main.h"
int main(int argc, char const *argv[])
{
    char* x = "/bin/ls";
    char* y = "-l";
    char* z = NULL;
    char** arr = (char**) malloc(sizeof(char*)*3);
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    execve(arr[0],arr,NULL);
    return 0;
}
