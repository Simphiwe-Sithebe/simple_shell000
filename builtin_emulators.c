#include "shell.h"

/**
 * _myexit - exits the shell
 * @imfostruct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if imfostruct.argv[0] != "exit"
 */
int _myexit(info_t *imfostruct)
{
	int exitchek;

	if (imfostruct->argv[1])  /* If there is an exit arguement */
	{
		exitchek = _erratoi(imfostruct->argv[1]);
		if (exitchek == -1)
		{
			imfostruct->status = 2;
			print_error(imfostruct, "Illegal number: ");
			_eputs(imfostruct->argv[1]);
			_eputchar('\n');
			return (1);
		}
		imfostruct->err_num = _erratoi(imfostruct->argv[1]);
		return (-2);
	}
	imfostruct->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @imfostruct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *imfostruct)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!imfostruct->argv[1])
	{
		dir = _getenv(imfostruct, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(imfostruct, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(imfostruct->argv[1], "-") == 0)
	{
		if (!_getenv(imfostruct, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(imfostruct, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(imfostruct, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(imfostruct->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(imfostruct, "can't cd to ");
		_eputs(imfostruct->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(imfostruct, "OLDPWD", _getenv(imfostruct, "PWD="));
		_setenv(imfostruct, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @imfostruct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *imfostruct)
{
	char **arg_array;

	arg_array = imfostruct->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
