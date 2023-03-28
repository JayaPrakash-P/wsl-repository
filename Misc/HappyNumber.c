// Example program
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



union Digits
{
	char wholeNumber[8];
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
	printf("sizeof(uDigits) : %lu\n",sizeof(uDigits));
	for(auto c : uDigits.wholeNumber)
		printf("c : %c\n",c);
    if(isHappy(inputNum))
        printf("%d is a HAPPY number!!!\n",inputNum);
    else
        printf("%d is NOT a HAPPY number!!!\n",inputNum);
}