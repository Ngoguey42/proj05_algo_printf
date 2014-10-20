#include "ft_printf.h"
#include "libft.h"

//ft_store_opt_1-5.c
int		ft_store_opt_1(char c, t_printf_part *part)
{
	return (1);
}

//ft_store_opt_1-5.c
int		ft_store_opt_2(char c, t_printf_part *part)
{
	unsigned char bit;
	
	bit = (unsigned char)ft_strcharlen(CHARS_FLAGS, c);
	part->flags = part->flags | (1 << bit);
	
	return (1);
}

//ft_store_opt_1-5.c
int		ft_store_opt_3(char c, t_printf_part *part)
{
	if ((part->info & WSTA_MASK) || (c == '*' && part->width > 0))
		return (0);
	if (c == '*')
		part->info = part->info | WSTA_MASK;
	else
		part->width = part->width * 10 + c - '0';
	return (1);
}

//ft_store_opt_1-5.c
int		ft_store_opt_5(char c, t_printf_part *part)
{
	if ((part->info & PSTA_MASK) || (c == '*' && part->precision > 0))
		return (0);
	if (c == '*')
		part->info = part->info | PSTA_MASK;
	else
		part->precision = part->precision * 10 + c - '0';
	part->info = part->info | PNUM_MASK;
	return (1);
}