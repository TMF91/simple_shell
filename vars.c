#include "shell.h"

/**
 * is_chain - Check current character in buffer if it is a chain delimeter
 * @p: Current address in buffer
 * @info: Structure of parameter
 * @buf: Character buffer
 * Return: On success 1 if it is a chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t h = *p;

	if (buf[h] == '|' && buf[h + 1] == '|')
	{
		buf[h] = 0;
		h++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[h] == '&' && buf[h + 1] == '&')
	{
		buf[h] = 0;
		h++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[h] == ';') /* found end of this command */
	{
		buf[h] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = h;
	return (1);
}

/**
 * check_chain - Further checks to continue chaining based on last status
 * @len: buffer length
 * @p: Current address in buffer
 * @k: Buffer starting position
 * @buf: Character buffer
 * @info: Structure of parameter
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t k, size_t len)
{
	size_t h = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[k] = 0;
			h = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[k] = 0;
			h = len;
		}
	}

	*p = h;
}

/**
 * replace_alias - FUnction which replaces an alias in a tokenized string
 * @info: Structure of parameter
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int k;
	list_t *node;
	char *p;

	for (k = 0; k < 10; k++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Function replaces vars in a tokenized string
 * @info: Structure of Parameter
 * Return: If replace successful return 1, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int k = 0;
	list_t *node;

	for (k = 0; info->argv[k]; k++)
	{
		if (info->argv[k][0] != '$' || !info->argv[k][1])
			continue;

		if (!_strcmp(info->argv[k], "$?"))
		{
			replace_string(&(info->argv[k]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[k], "$$"))
		{
			replace_string(&(info->argv[k]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[k][1], '=');
		if (node)
		{
			replace_string(&(info->argv[k]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Function replaces string
 * @new: new string which replaces old string
 * @old: identifies old string to be replaced
 * Return:If replaced return 1, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
