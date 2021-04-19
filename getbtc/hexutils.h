#ifndef __HEXUTILS_H__
#define __HEXUTILS_H__

#include <stdbool.h>

void StrToHex(unsigned char *pbDest, char *pszSrc, int nLen);
void HexToStr(char *pszDest, unsigned char *pbSrc, int nLen);
int ishex(char ch);
void printHexData(char * loghea, unsigned char  *pData, int nLen);
void strtolower(char *str);
int strpos(const char *haystack, const char *needle, bool ignorecase);
int hexToDec(char ch);

#endif
