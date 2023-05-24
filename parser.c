#include "shell.h"

/**
 * is_cmd - Identifies an executable command file
 * @path: File path
 * @info: information structure
 * Return: if true 1, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Function that duplicates chars
 * @stop: stopping ind
 * @pathstr: PATH string
 * @start: begining ind
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int l = 0, m = 0;

	for (m = 0, l = start; l < stop; l++)
		if (pathstr[l] != ':')
			buf[m++] = pathstr[l];
	buf[m] = 0;
	return (buf);
}

/**
 * find_path - Locates cmd in PATH string
 * @pathstr:PATH string
 * @cmd: command to find
 * @info: Information structure
 * Return: path of command if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int l = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[l] || pathstr[l] == ':')
		{
			path = dup_chars(pathstr, curr_pos, l);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[l])
				break;
			curr_pos = l;
		}
		l++;
	}
	return (NULL);
}
