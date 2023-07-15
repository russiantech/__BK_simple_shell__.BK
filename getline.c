#include "shell.h"

/**
 * input_buf - will buffers chained command
 * @info: param struct
 * @buf: adrs of buffer
 * @len: adrs of len var
 *
 * Return: bytes that was read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill . */
	{
		/* bfree((void **)info->cmd_buf); (prottype) */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - get line newline exempted
 * @info: param struct
 *
 * Return: bytes-read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* ';' command chain buffer*/
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* some commands left in chain buffer */
	{
		j = i; /* init new iterator to current buf position(s) */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to 'semicolon(;)' or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increase past nulled ';'' */
		if (i >= len) /* gotten to end of buffer? */
		{
			i = len = 0; /* reset position/length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /*pass pointer back to current command position*/
		return (_strlen(p)); /*length of current command */
	}

	*buf_p = buf; /* else not a chain, pass buffer back from _getline() */
	return (r); /*length of buffer from _getline() */
}

/**
 * read_buf - will read buffer
 * @info: param struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - get next line of input from STDIN
 * @info: param struct
 * @ptr: adrs of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if != NULL
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - prevents ctrl-C
 * @sig_num: signal num
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

