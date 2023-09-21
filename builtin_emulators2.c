#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @infostruct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *infostruct)
{
	print_list(infostruct->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @infostruct: parameter struct
 * @stra: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *infostruct, char *stra)
{
	char *p, c;
	int ret;

	p = _strchr(stra, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(infostruct->alias),
		get_node_index(infostruct->alias, node_starts_with(infostruct->alias, stra, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @infostruct: parameter struct
 * @stra: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *infostruct, char *stra)
{
	char *p;

	p = _strchr(stra, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(infostruct, stra));

	unset_alias(infostruct, stra);
	return (add_node_end(&(infostruct->alias), stra, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->stra, '=');
		for (a = node->stra; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @infostruct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *infostruct)
{
	int x = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (infostruct->argc == 1)
	{
		node = infostruct->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; infostruct->argv[x]; x++)
	{
		p = _strchr(infostruct->argv[x], '=');
		if (p)
			set_alias(infostruct, infostruct->argv[x]);
		else
			print_alias(node_starts_with(infostruct->alias, infostruct->argv[x], '='));
	}

	return (0);
}
