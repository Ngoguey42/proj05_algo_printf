#include "ft_printf.h"
#include "libft.h"
/*
0		none		
1		percent			1char max
2		flags			erreur si doublon	0-5 char
3		width			n char
4		dot				erreur sans precision	1char max
5		precision		n char
6		length			1char max
7		length 2		1char max
8		specifier		1char max
*/

//ft_parse_format.c
static t_printf_part	*new_part(const char *str)
{
	t_printf_part	*new;

	new = malloc(sizeof(t_printf_part));	//using malloc
	if (!new)
		exit(0);	//using exit
	new->str_ptr = str;
	new->nbr_ptr = "";
	new->next = NULL;
	new->flags = 0;
	new->info = 0;
	new->width = 0;
	new->precision = 0;
	new->length = 0;
	new->specifier = 0;
	new->error = 0;
	return (new);
}

//ft_parse_format.c
static char get_control_char(char c, char p_opt) // valide l'ordre des options
{
	if (p_opt == 0 && c == '%')
		return (1);
	if (ft_strchr(CHARS_FLAGS, c) && p_opt < 3) //les 0 sont hook ici
		return (2);
	if ((ft_isdigit(c) || c == '*') && p_opt < 6)
	{
		if (p_opt < 4)
			return (3);
		else
			return (5);
	}
	if (c == '.' && p_opt < 4)
		return (4);
	if (ft_strchr(CHARS_LENGTH, c) && p_opt < 7)
	{
		if (p_opt < 6)
			return (6);
		else
			return (7);
	}
	if (ft_strchr(CHARS_SPECIFIERS, c) && p_opt < 8)
		return (8);
	return (0);
}

//ft_parse_format.c
static void		populate_store_tab(int(*store_opt[9])(char c, t_printf_part *part))
{
	store_opt[0] = ft_store_opt_1;
	store_opt[1] = ft_store_opt_1;
	store_opt[4] = ft_store_opt_1;

	store_opt[2] = ft_store_opt_2;
	store_opt[3] = ft_store_opt_3;
	store_opt[5] = ft_store_opt_5;
	store_opt[6] = ft_store_opt_6;
	store_opt[7] = ft_store_opt_7;
	store_opt[8] = ft_store_opt_8;
}

//ft_parse_format.c
static int parse_part(t_printf_part *part)
{
	const char	*str;
	char		opt;
	char		p_opt;
	int			(*store_opt[9])(char c, t_printf_part *part);

	populate_store_tab(store_opt);
	part->str_size = ft_strcharlen(part->str_ptr, '%');
	str = part->str_ptr + part->str_size;
	p_opt = 0;
	while (opt = get_control_char(*str, p_opt))
	{
		if (!store_opt[opt]((char)*str, part)) //valide chaque options
			return (0);
		p_opt = opt;
		str++;
	}
	(void) p_opt;
	if (*str != '\0')
		part->next = new_part(str);

	
	return (1);
}

//ft_parse_format.c
int			ft_parse_format(const char *format, t_printf_part **beginning)
{
	t_printf_part *current;

	current = new_part(format);
	*beginning = current;
	if (!parse_part(current))
		return (-1);
	while (current = current->next)
	{
		if (!parse_part(current))
			return (-1);
	}
	return (1);
}
