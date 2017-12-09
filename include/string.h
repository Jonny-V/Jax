#ifndef STRING_H_
#define STRING_H_

void memcpy(unsigned char *des, const unsigned char *src, unsigned int len);

void memset(void *des, unsigned char val, unsigned int len);

void bzero(void *des, unsigned int len);

int strcmp(const char *str1, const char *str2);

char *strcpy(char *des, const char *src);

char *strcat(char *des, const char *src);

int strlen(const char *src);

#endif // !STRING_H_