#include "sh.h"

/**
 * It takes a pointer to a string, a pointer to the end of the string, and two pointers to pointers to
 * characters. It returns a token type, and sets the two pointers to point to the beginning and end of
 * the token
 * 
 * @param ps pointer to the start of the string
 * @param es end of string
 * @param q the start of the token
 * @param eq pointer to the end of the token
 * 
 * @return The type of token.
 */
int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while(s < es && strchr(" \t\r\n\v", *s))
		s++;
	if(q)
		*q = s;
	ret = *s;
	switch(*s)
	{
		case 0:
			break;
		case '|':
		case '(':
		case ')':
		case ';':
		case '&':
		case '<':
			s++;
			break;
		case '>':
			s++;
			if(*s == '>')
			{
				ret = '+';
				s++;
			}
			break;
		default:
			ret = 'a';
			while (s < es && !strchr(" \t\r\n\v", *s) && !strchr("<|>&;()", *s))
				s++;
			break;
	}
	if(eq)
		*eq = s;

	while(s < es && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (ret);
}
