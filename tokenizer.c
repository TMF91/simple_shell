#include "shell.h"

/**
 * **strtow - Function divides strings into words & ignores repeated delimeters
 * @str: identifies input string
 * @d: Identifies delimeter string
 * Return: A pointer to an array of strings, otherwise NULL on failure
 */

char **strtow(char *str, char *d)
{
	int l, m, n, o, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
		if (!is_delim(str[l], d) && (is_delim(str[l + 1], d) || !str[l + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, m = 0; m < numwords; m++)
	{
		while (is_delim(str[l], d))
			l++;
		n = 0;
		while (!is_delim(str[l + n], d) && str[l + n])
			n++;
		s[m] = malloc((n + 1) * sizeof(char));
		if (!s[m])
		{
			for (n = 0; n < m; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			s[m][o] = str[l++];
		s[m][o] = 0;
	}
	s[m] = NULL;
	return (s);
}

/**
 * **strtow2 - Function divides string into words
 * @d: Delimeter
 * @str: String input
 * Return: Pointer to an array of strings, or on failure NULL
 */
char **strtow2(char *str, char d)
{
	int l, m, n, o, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
		if ((str[l] != d && str[l + 1] == d) ||
				    (str[l] != d && !str[l + 1]) || str[l + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, m = 0; m < numwords; m++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		n = 0;
		while (str[l + n] != d && str[l + n] && str[l + n] != d)
			n++;
		s[m] = malloc((n + 1) * sizeof(char));
		if (!s[m])
		{
			for (n = 0; n < m; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			s[m][o] = str[l++];
		s[m][o] = 0;
	}
	s[m] = NULL;
	return (s);
}
