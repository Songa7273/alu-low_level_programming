#include <stdlib.h>
#include <stdio.h>

/**
 * _strdup - Returns a pointer to a new string which is a duplicate of str.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string, or NULL if allocation fails.
 */
char *_strdup(char *str)
{
	char *dup_str;
	int i, len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len])
		len++;

	dup_str = malloc(sizeof(char) * (len + 1));
	if (dup_str == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		dup_str[i] = str[i];
	dup_str[i] = '\0';

	return (dup_str);
}
