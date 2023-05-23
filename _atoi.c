#include "shell.h"

/**
 * interactive - will return true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if in interactive mode, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimeter
 * @c: character to be checked
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - is checking for alphabetic characters
 * @c: inputed charactered
 * Return: 1 if c is alphabetic, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converting a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, otherwise convert number
 */

int _atoi(char *s)
{
	int i, sign = 1, fg = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && fg != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
