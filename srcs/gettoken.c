#include "sh.h"

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


