#include "sh.h"

/**
 * It skips over whitespace and returns true if the next character is in the string toks
 * 
 * @param ps pointer to the string to be parsed
 * @param es end of string
 * @param toks a string of characters that we want to match
 * 
 * @return a non-zero value if the next character in the string is one of the characters in the toks
 * string.
 */
int	peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while(s < es && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}
