#include "string.h"
#include "types.h"

void memcpy(unsigned char *des, const unsigned char *src, unsigned int len)
{
 for (; len != 0; len--)
  *des++ = *src++;
}

void memset(void *des, unsigned char val, unsigned int len)
{
 unsigned char *cp = (unsigned char *)des;
 for (; len != 0; len--)
  *cp++ = val;
}

void bzero(void *des, unsigned int len)
{
 memset(des, 0, len);
}

int strcmp(const char *str1, const char *str2)
{
 while (*str1 == *str2)
 {
  if (*str1 == '\0')
   return 0;
  str1++, str2++;
 }
 return *str1 - *str2;
}

char *strcpy(char *des, const char *src)
{
 if (des == NULL || src == NULL)
  return NULL;
 char *cp = des;
 while ((*cp++ = *src++))
  ;
 return des;
}

char *strcat(char *des, const char *src)
{
 if (des == NULL || src == NULL)
  return NULL;
 char *cp = des;
 while (*cp++)
  ;
 strcpy(cp, src);
 return des;
}

int strlen(const char *src)
{
 const char *cp = src;
 while (*cp++)
  ;
 return cp - src - 1;
}