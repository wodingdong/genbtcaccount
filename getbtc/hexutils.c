#include <ctype.h>
#include "hexutils.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

void StrToHex(unsigned char *pbDest, char *pszSrc, int nLen)
{
	char h1, h2;
	unsigned char  s1, s2;
	for (int i = 0; i < nLen; i++)
	{
		h1 = pszSrc[2 * i];
		h2 = pszSrc[2 * i + 1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		pbDest[i] = s1 * 16 + s2;
	}
}

void HexToStr(char *pszDest, unsigned char *pbSrc, int nLen)
{
	char	ddl, ddh;
	for (int i = 0; i < nLen; i++)
	{
		ddh = 48 + pbSrc[i] / 16;
		ddl = 48 + pbSrc[i] % 16;
		if (ddh > 57) ddh = ddh + 7;
		if (ddl > 57) ddl = ddl + 7;
		pszDest[i * 2] = ddh;
		pszDest[i * 2 + 1] = ddl;
	}

	pszDest[nLen * 2] = '\0';
}

int ishex(char ch)
{
	if (ch >= '0' && ch <= '9')
		return 1;
	if (ch >= 'A' && ch <= 'F')
		return 1;
	if (ch >= 'a' && ch <= 'f')
		return 1;
	return 0;
}

void printHexData(char * loghea,unsigned char  *pData, int nLen) {
	unsigned char *msg = (char*)malloc((nLen * 2 + 1) * sizeof(unsigned char));
	memset(msg, 0, nLen * 2 + 1);
	HexToStr((char *)msg, pData, nLen);
	printf("%s = %s ,len = %d \n", loghea, msg, nLen * 2);
	free(msg);
	printf("\n");
}
/*
uint8_t *fromhex(const char *str)
{
	static uint8_t buf[128];
	uint8_t c;
	size_t i;
	for (i = 0; i < strlen(str) / 2; i++) {
		c = 0;
		if (str[i * 2] >= '0' && str[i * 2] <= '9') c += (str[i * 2] - '0') << 4;
		if (str[i * 2] >= 'a' && str[i * 2] <= 'f') c += (10 + str[i * 2] - 'a') << 4;
		if (str[i * 2] >= 'A' && str[i * 2] <= 'F') c += (10 + str[i * 2] - 'A') << 4;
		if (str[i * 2 + 1] >= '0' && str[i * 2 + 1] <= '9') c += (str[i * 2 + 1] - '0');
		if (str[i * 2 + 1] >= 'a' && str[i * 2 + 1] <= 'f') c += (10 + str[i * 2 + 1] - 'a');
		if (str[i * 2 + 1] >= 'A' && str[i * 2 + 1] <= 'F') c += (10 + str[i * 2 + 1] - 'A');
		buf[i] = c;
	}
	return buf;
}

char *tohex(const uint8_t *bin, size_t l)
{
	char *buf = (char *)malloc(l * 2 + 1);
	static char digits[] = "0123456789abcdef";
	size_t i;
	for (i = 0; i < l; i++) {
		buf[i * 2] = digits[(bin[i] >> 4) & 0xF];
		buf[i * 2 + 1] = digits[bin[i] & 0xF];
	}
	buf[l * 2] = 0;
	return buf;
}*/

void strtolower(char *str)
{
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] >= 'A'&&str[i] <= 'Z')//表示是大写字母 
			str[i] += 32;
		// else if (a[i] >= 'a'&&a[i] <= 'z')//表示是小写字母 
		//	 a[i] -= 32;
	}

}

/* {{{ 查找字符串首次出现的位置，没有找到返回 -1，两个字符串相等返回 0
在GCC下使用C99：
int strpos(const char *haystack,const char *needle, _Bool ignorecase = 0)
_Bool ignorecase =1 忽略大小写
时间：2012-08-17 By Dewei
*/
int strpos(const char *haystack, const char *needle, bool ignorecase)
{
	register unsigned char c, needc;
	unsigned char const *from, *end;
	int len = strlen(haystack);
	int needlen = strlen(needle);
	from = (unsigned char *)haystack;
	end = (unsigned char *)haystack + len;
	const char *findreset = needle;
	for (int i = 0; from < end; ++i) {
		c = *from++;
		needc = *needle;
		if (ignorecase) {
			if (c >= 65 && c < 97)
				c += 32;
			if (needc >= 65 && needc < 97)
				needc += 32;
		}
		if (c == needc) {
			++needle;
			if (*needle == '\0') {
				if (len == needlen)
					return 0;
				else
					return i - needlen + 1;
			}
		}
		else {
			if (*needle == '\0' && needlen > 0)
				return i - needlen + 1;
			needle = findreset;
		}
	}
	return  -1;
}
/* }}} */

int hexToDec(char ch) {

	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
	else if (ch >= 'A' && ch <= 'F')
	{
		return ch - 'A' + 10;
	}
	else if (ch >= 'a' && ch <= 'f')
	{
		return ch - 'a' + 10;
	}
	return -1;

}