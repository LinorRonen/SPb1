#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC printFunc)
{
	PAdptArray pArrayMalloc = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArrayMalloc == NULL)
		return NULL;
	pArrayMalloc->ArrSize = 0;
	pArrayMalloc->pElemArr = NULL;
	pArrayMalloc->delFunc = delFunc_;
	pArrayMalloc->copyFunc = copyFunc_;
    pArrayMalloc->printFunc =printFunc;
	return pArrayMalloc;
}
void DeleteAdptArray(PAdptArray pArray)
{
	int NowSize=pArray->ArrSize;
	int i;
	if (pArray == NULL)
		return;
	else if(pArray->pElemArr!=NULL)
	{
		for(i = 0; i < NowSize; ++i)
		{
			if(pArray->pElemArr[i]!=NULL)
			{
				pArray->delFunc((pArray->pElemArr)[i]);
			}	
		}
		free(pArray->pElemArr);
	}	
	free(pArray);
}
Result SetAdptArrayAt(PAdptArray pArray, int index, PElement pNewElem)
{
	int size=index+1;
    PElement* newpElemArr;
    if (pArray == NULL)
        return FAIL;

    if (index>= pArray->ArrSize)
    {
        if ((newpElemArr = (PElement*)calloc((size), sizeof(PElement))) == NULL)
            return FAIL;
        if(pArray->pElemArr!=NULL)
        {
            for(int i=0; i<pArray->ArrSize; i++)
            {
                if (pArray->pElemArr[i] != NULL)
                {
                    newpElemArr[i] = pArray->copyFunc(pArray->pElemArr[i]);
                    pArray->delFunc(pArray->pElemArr[i]);
                }
            }
        }
        pArray->ArrSize=size;
        free(pArray->pElemArr);
        pArray->pElemArr = newpElemArr;
    }
    if(pArray->pElemArr[index]!=NULL)
    {
        pArray->delFunc((pArray->pElemArr)[index]);
    }
    pArray->pElemArr[index] = pArray->copyFunc(pNewElem);
    if(pArray->pElemArr[index]==NULL) 
    {
        return FAIL;
    }
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray pArray , int index)
{
	if(pArray==NULL || index<0 || index>=pArray->ArrSize)
	{
		return NULL;
	}
	if(pArray->pElemArr[index] != NULL)
	{
		return (pArray->copyFunc(pArray->pElemArr[index]));
	}
	else
	{
		return NULL;
	}
}
int GetAdptArraySize(PAdptArray pArray)
{
	int NowSize=pArray->ArrSize;
	if (pArray==NULL)
	{
		return -1;
	}
	return NowSize;
}
void PrintDB(PAdptArray pArray)
{
	int NowSize=pArray->ArrSize;
	if (pArray == NULL)
		return;
	else
	{
		for(int i=0; i<NowSize; i++)
    	{
			if(pArray->pElemArr[i]!=NULL)
			{
				pArray->printFunc((pArray->pElemArr)[i]);
			}
   		}
	}   
}