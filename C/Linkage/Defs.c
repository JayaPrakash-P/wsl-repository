#include <stdio.h>

int externalLinkageInt = 10;
static int internalLinkageInt = 100;

void PrintExternalLinkageInt()
{
    printf("externalLinkageInt = %d\n",externalLinkageInt);
}

void PrintInternalLinkageInt()
{
    printf("internalLinkageInt = %d\n",internalLinkageInt);
}

void ModifyExternalLinkageInt()
{
    externalLinkageInt = 20;
    printf("externalLinkageInt(Modified) = %d\n",externalLinkageInt);
}

void ModifyInternalLinkageInt()
{
    internalLinkageInt = 200;
    printf("internalLinkageInt(Modified) = %d\n",internalLinkageInt);
}
