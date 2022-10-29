#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("incorrect number of arguements!, expected 1 but got: %d\n", argc);
        return -1;
    }
    int factor = atoi(argv[1]);
    printf("multiply by %d\n", factor);
    int i;
    while (1)
    {
        scanf("%d", &i);
        printf("%d\n", i*factor);
    }
    return 0;
}
