#include "shell.h"
/**
 * interactive - True if shell is interactive
 *
 * @info: struct adrs
 * @info_t: info
 *
 * Return: if not interactive mode 0  else 1  
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - used to confirm if char is delimeter
 * @c: the char in question
 * @delta: ---- --
 * Return: 1 if true  else 0
 */
int is_delim(char c, char *delta)
{
	while (*delim)
		if (*delim++ == c)
			return (t);
	return (0);
}

/**
 * _isalpha - confirms if a char is an alphabet
 * @c: char inquestion
 * Return: 1 if @c is alphabet, 0 if not
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - turn str to int
 * @s: str in question
 * Return: 0 if not converted, else converted result
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '_')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '0')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
