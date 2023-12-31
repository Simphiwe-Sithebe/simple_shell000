#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int num)
{
	int x, j;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < num - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < num)
	{
		j = x;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int num)
{
	int x, j;
	char *s = dest;

	x = 0;
	j = 0;
	while (dest[x] != '\0')
		x++;
	while (src[j] != '\0' && j < num)
	{
		dest[x] = src[j];
		x++;
		j++;
	}
	if (j < num)
		dest[x] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
