
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ENTRIES 36
typedef struct KeyVal
{
	char key;
	int value;
}KeyVal;

typedef struct Map
{
	KeyVal mapEntries[MAX_ENTRIES];
}Map;

Map indexLUT;

void GenerateLUT()
{
	int index = 0;
	for (int i = (int)'0' ; i <= (int)'9' ; ++i)
	{
		indexLUT.mapEntries[index].key   = (char)i;
		indexLUT.mapEntries[index++].value = ((char)i-'0');
	}
	for (int i = (int)'a' ; i <= (int)'z' ; ++i)
	{
		indexLUT.mapEntries[index].key   = (char)i;
		indexLUT.mapEntries[index++].value = ((char)i - 'a')+10;
	}
}

void DisplayLUT()
{
	for (int i = 0 ; i < MAX_ENTRIES ; ++i)
		printf("{[%c]:[%d]}\n", indexLUT.mapEntries[i].key, indexLUT.mapEntries[i].value);
}

int GetValueFromLUT(char inChar)
{
    char retVal = 0;
	for (int i = 0 ; i < MAX_ENTRIES ; ++i)
		if(tolower(inChar) == indexLUT.mapEntries[i].key)
        {
            retVal = indexLUT.mapEntries[i].value;
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
            printf("[%c-%d]", indexLUT.mapEntries[i].key, countArray[i]);
    }
    printf("\nBye...\n");
}

int main()
{
    char inputStr[256];
    printf ("Enter the string: ");
    fgets(inputStr,256,stdin);
    GenerateLUT();
    //DisplayLUT();
    CountCharaters(inputStr);
    return 0;
}