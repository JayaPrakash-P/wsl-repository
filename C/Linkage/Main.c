#include <stdio.h>

extern int externalLinkageInt;
extern int internalLinkageInt;

void PrintExternalLinkageInt(void);
void ModifyExternalLinkageInt(void);
void PrintInternalLinkageInt(void);
void ModifyInternalLinkageInt(void);

void main()
{
    PrintExternalLinkageInt();
    ModifyExternalLinkageInt();

    PrintInternalLinkageInt();
    ModifyInternalLinkageInt();

    printf("externalLinkageInt(File1) = %d\n", externalLinkageInt);

    //Linker error : undefined reference to `internalLinkageInt'
    //printf("internalLinkageInt(File1) = %d\n", internalLinkageInt);

    externalLinkageInt = 30;

    //Linker error : undefined reference to `internalLinkageInt'
    //internalLinkageInt = 300;

    PrintExternalLinkageInt();
    PrintInternalLinkageInt();
}
