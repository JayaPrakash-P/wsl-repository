// Example program
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

union Digits
{
	char wholeNumber[8];
	int8_t digit0;
	int8_t digit1;
	int8_t digit2;
	int8_t digit3;
	int8_t digit4;
	int8_t digit5;
	int8_t digit6;
	int8_t digit7;
	
} uDigits;

bool isHappy(int input)
{
	static int loopCount = 10;
	
	int newNum = 0;
	while (input)
	{
		int digit = input%10;
		newNum += (digit*digit);
		input = input/10;
	}

	if(newNum == 1)
		return true;
	else if (loopCount == 0)
		return false;
	else
	{
		loopCount--;
		return isHappy(newNum);
	}
}

int main(int argc, char* argv[])
{
	int8_t inputNum = 23;
    if(argc == 2)
        inputNum = atoi(argv[1]);
	sprintf(uDigits.wholeNumber, "%d", inputNum);
	printf("sizeof(uDigits) : %d\n",sizeof(uDigits));
	printf("uDigits.wholeNumber : %s\n",uDigits.wholeNumber);
	printf("uDigits.digit0 : %d\n",uDigits.digit0);
	printf("uDigits.digit1 : %d\n",uDigits.digit1);
	printf("uDigits.digit2 : %d\n",uDigits.digit2);
	printf("uDigits.digit3 : %d\n",uDigits.digit3);
	printf("uDigits.digit4 : %d\n",uDigits.digit4);
	printf("uDigits.digit5 : %d\n",uDigits.digit5);
	printf("uDigits.digit6 : %d\n",uDigits.digit6);
	printf("uDigits.digit7 : %d\n",uDigits.digit7);
    if(isHappy(inputNum))
        printf("%d is a HAPPY number!!!\n",inputNum);
    else
        printf("%d is NOT a HAPPY number!!!\n",inputNum);
}