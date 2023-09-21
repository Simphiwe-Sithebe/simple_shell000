#include "shell.h"

/**
 *_eputs - prints an input string
 * @ptr: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *ptr)
{
	int i = 0;

	if (!ptr)
		return;
	while (ptr[i] != '\0')
	{
		_eputchar(ptr[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character v to stderr
 * @v: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char v)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (v != BUF_FLUSH)
		buf[i++] = v;
	return (1);
}

/**
 * _putfd - writes the character v to given fd
 * @v: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char v, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (v != BUF_FLUSH)
		buf[i++] = v;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @ptr: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *ptr, int fd)
{
	int i = 0;

	if (!ptr)
		return (0);
	while (*ptr)
	{
		i += _putfd(*ptr++, fd);
	}
	return (i);
}
