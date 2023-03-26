
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ENTRIES 36

struct KeyValuePair
{
	char key;
	int  value;
};

struct KeyValuePair indexLUT[MAX_ENTRIES];

void GenerateLUT()
{
	int startKey = (int)'0';
	for (int i = 0 ; i < MAX_ENTRIES ; ++i)
	{
		indexLUT[i].key   = (char)startKey++;
		indexLUT[i].value = i;
		if(i == 9)
			startKey = (int)'a';
	}
}

void DisplayLUT()
{
	for (int i = 0 ; i < MAX_ENTRIES ; ++i)
		printf("{[%c]:[%d]}\n", indexLUT[i].key, indexLUT[i].value);
}

int GetValueFromLUT(char inChar)
{
    char retVal = 0;
	for (int i = 0 ; i < MAX_ENTRIES ; ++i)
		if(tolower(inChar) == indexLUT[i].key)
        {
            retVal = indexLUT[i].value;
            break;
        }
    return retVal;
}

bool isValid(char inChar)
{
	if( (inChar >= 'a' && inChar <= 'z') ||
	    (inChar >= 'A' && inChar <= 'Z') ||
		(inChar >= (char)0 && inChar <= (char)9) )
		return true;
	else
		return false;
}

void CountCharaters(const char* inputStr)
{
	int countArray[MAX_ENTRIES];
	memset(countArray,0,sizeof(countArray));

	while(*inputStr)
	{
		if(isValid(*inputStr))
			countArray[GetValueFromLUT(*inputStr)]++;
		inputStr++;
	}

    for (int i = 0 ; i < MAX_ENTRIES ; ++i)
    {
        if(countArray[i] != 0)
            printf("{[%c]-[%d]}", indexLUT[i].key, countArray[i]);
    }
    printf("\nBye...\n");
}

int main()
{
    char inputStr[256];
    printf ("Enter the string: ");
    fgets(inputStr,256,stdin);
    GenerateLUT();
    CountCharaters(inputStr);
    return 0;
}