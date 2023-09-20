#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @infostruct: the parameter struct
 * @charbuf: the char buffer
 * @p: address of current position in charbuf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *infostruct, char *charbuf, size_t *p)
{
	size_t j = *p;

	if (charbuf[j] == '|' && charbuf[j + 1] == '|')
	{
		charbuf[j] = 0;
		j++;
		infostruct->cmd_buf_type = CMD_OR;
	}
	else if (charbuf[j] == '&' && charbuf[j + 1] == '&')
	{
		charbuf[j] = 0;
		j++;
		infostruct->cmd_buf_type = CMD_AND;
	}
	else if (charbuf[j] == ';') /* found end of this command */
	{
		charbuf[j] = 0; /* replace semicolon with null */
		infostruct->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @infostruct: the parameter struct
 * @charbuf: the char buffer
 * @p: address of current position in charbuf
 * @i: starting position in charbuf
 * @len: length of charbuf
 *
 * Return: Void
 */
void check_chain(info_t *infostruct, char *charbuf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (infostruct->cmd_buf_type == CMD_AND)
	{
		if (infostruct->status)
		{
			charbuf[i] = 0;
			j = len;
		}
	}
	if (infostruct->cmd_buf_type == CMD_OR)
	{
		if (!infostruct->status)
		{
			charbuf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @infostruct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *infostruct)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infostruct->alias, infostruct->argv[0], '=');
		if (!node)
			return (0);
		free(infostruct->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infostruct->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @infostruct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *infostruct)
{
	int i = 0;
	list_t *node;

	for (i = 0; infostruct->argv[i]; i++)
	{
		if (infostruct->argv[i][0] != '$' || !infostruct->argv[i][1])
			continue;

		if (!_strcmp(infostruct->argv[i], "$?"))
		{
			replace_string(&(infostruct->argv[i]),
				_strdup(convert_number(infostruct->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infostruct->argv[i], "$$"))
		{
			replace_string(&(infostruct->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infostruct->env, &infostruct->argv[i][1], '=');
		if (node)
		{
			replace_string(&(infostruct->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infostruct->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @oldstr: address of oldstr string
 * @newstr: newstr string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
