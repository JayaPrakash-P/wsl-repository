#include <stdlib.h>

int main()
{
    int* intPtr = (int*) malloc (sizeof(int));
    free(intPtr);
    return 0;
}