#include "ft_printf.h"
#include "libft.h"



#define AND_FLAG(x) (part->flags & x)
#define AND_INFO(x) (part->info & x)


#define ABS(x) (x < 0 ? -x : x)

//build_capitals.c
int		build_nbr_6(t_printf_part *part, va_list *args) //%X
{
	int		i;
	char	c;

	build_nbr_5(part, args);
	i = 0;
	while (c = (part->nbr_ptr)[i])
		(part->nbr_ptr)[i++] = ((c >= 'a' && c <= 'f') || c == 'x') ? c - 32 : c; //use les fonctions de la libft (besoin ?)
	return (1);
}

int		build_nbr_14(t_printf_part *part, va_list *args) //A
{
	int		i;
	char	c;
	// ft_putstr("s");
	build_nbr_13(part, args);
	i = 0;
	// if (!strcmp(part->nbr_ptr, "nan"))
		// ft_putstr(part->nbr_ptr);
	while (c = (part->nbr_ptr)[i])
	{
		// if (!strcmp(part->nbr_ptr, "nan"))
			// ft_putnbr(i);
		(part->nbr_ptr)[i++] = ((c >= 'a' && c <= 'z')) ? c - 32 : c; //use les fonctions de la libft (besoin ?)
	}
	// ft_putstr("e");
	return (1);
}

