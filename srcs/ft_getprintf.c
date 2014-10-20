#include "ft_printf.h"
#include "libft.h"

//ft_getprintf.c
static int			build_nbr_strings(t_printf_part	**beginning, va_list *args)
{
	t_printf_part	*current;
	int				(*build_nbr[20])(t_printf_part *part, va_list *args);
	int				error;
	
	populate_build_nbr(build_nbr);
	current = *beginning;
	while (current)
	{
		if (current->specifier)
			error = build_nbr[current->specifier](current, args);
		current = current->next;
	}
	
	
	// current = *beginning; //debug
	// while (current) //debug
	// {
		// inspect_part(current); //debug
		// current = current->next; //debug
	// }
	
	return (1);
}

//ft_getprintf.c
static int	concat_parts(t_printf_part **beginning, char **ret)
{
	size_t			len;
	char			*str;
	t_printf_part	*current;
	int				i;
	
	current = *beginning;
	len = 0;
	while (current)
	{
		len = len + (int)ft_strlen(current->nbr_ptr) + current->str_size;
		current = current->next;
	}
	current = *beginning;
	str = (char*)malloc(len + 1);	//malloc
	if (!str)
		exit(0);	//exiting
		
	str[0] = '\0';
	*ret = str;
	while (current)
	{
		ft_strlcpy(str, current->str_ptr, current->str_size + 1);
		str = str + current->str_size;
		ft_strcpy(str, current->nbr_ptr);
		str = str + (int)ft_strlen(str);
		if (current->info & BSZERO_MASK)
		{
			i = 0;
			while(i < 1)
			{
				if (str[i] == 1)
				{
					str[i] = 0;
					i = 3;
				}
				i--;
			}
		}
		current = current->next;
	}
	return (len);
}


//ft_getprintf.c
int		ft_getprintf(char **ret, const char *format, va_list *args)
{
	int				error;
	int				len;
	t_printf_part	**beginning;

	beginning = malloc(sizeof(t_printf_part*)); //malloc 
	if (!beginning)
		exit(0); // exiting
	error = ft_parse_format(format, beginning);
	build_nbr_strings(beginning, args);
	len = concat_parts(beginning, ret);
	return (len);
}
