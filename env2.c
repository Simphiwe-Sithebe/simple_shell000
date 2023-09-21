#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @stvar: the string env stvar property
 */
int _unsetenv(info_t *inf, char *stvar)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *p;

	if (!node || !stvar)
		return (0);

	while (node)
	{
		p = starts_with(node->str, stvar);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @stvar: the string env stvar property
 * @value: the string env stvar value
 *  Return: Always 0
 */
int _setenv(info_t *inf, char *stvar, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!stvar || !value)
		return (0);

	buf = malloc(_strlen(stvar) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, stvar);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = inf->env;
	while (node)
	{
		p = starts_with(node->str, stvar);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
