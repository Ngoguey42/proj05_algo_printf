#include "ft_printf.h"
#include "libft.h"

#define AND_FLAG(x) (part->flags & x)
#define AND_INFO(x) (part->info & x)

#define ABS(x) (x < 0 ? -x : x)
#define PAD_CHAR part->flags & ZERO_MASK ? '0' : ' '

/*
** nothing
*/
int		build_nbr_0(t_printf_part *part, va_list *args)
{
	(void)part;
	(void)args;
	return (1);
}

/*
** %c
*/
int		build_nbr_15(t_printf_part *part, va_list *args)
{
	int		width;
	int		precision;
	char	*str;
	char	c;

	width = part->info & WSTA_MASK ? va_arg(*args, int) : part->width;
	precision = part->info & PSTA_MASK ? va_arg(*args, int) : part->precision;
	str = (char*)malloc(2); //malloc
	c = (char)va_arg(*args, int);
	str[0] = c == 0 ? 1 : c;
	str[1] = '\0';
	if (c == '\0')
		part->info = part->info | BSZERO_MASK;
	if (width > 1)
	{
		if (part->flags & MINU_MASK)
			str = ft_pad_string(str, ' ', -width, 1);
		else
			str = ft_pad_string(str, PAD_CHAR, width, 1);
	}
	else if (width < -1)
		str = ft_pad_string(str, ' ', width, 1);
	part->nbr_ptr = str;
	return (1);
}

/*
** %s
** unable to free mallocs, because real va_arg length unknow
*/
int		build_nbr_16(t_printf_part *part, va_list *args)
{
	int		width;
	int		precision;
	char	*str;

	width = part->info & WSTA_MASK ? va_arg(*args, int) : part->width;
	precision = part->info & PSTA_MASK ? va_arg(*args, int) : part->precision;
	str = (char*)va_arg(*args, char*);
	if (AND_INFO(PNUM_MASK) && precision > 0)
		str[precision - 1] = '\0';
	else if (AND_INFO(PNUM_MASK) && precision == 0)
		str = (char*)ft_strdup("");
	if (width > 0 && width > (int)ft_strlen(str))
	{
		if (part->flags & MINU_MASK)
			str = ft_pad_string(str, ' ', -width, 0);
		else
			str = ft_pad_string(str, PAD_CHAR, width, 0);
	}
	else if (width < 0 && ABS(width) > (int)ft_strlen(str))
		str = ft_pad_string(str, ' ', width, 0);
	part->nbr_ptr = str;
	return (1);
}

/*
** %%
*/
int		build_nbr_19(t_printf_part *part, va_list *args)
{
	int		width;
	int		precision;

	width = part->info & WSTA_MASK ? va_arg(*args, int) : part->width;
	precision = part->info & PSTA_MASK ? va_arg(*args, int) : part->precision;
	if (width > 1)
	{
		if (part->flags & MINU_MASK)
			part->nbr_ptr = ft_pad_string("%", ' ', -width, 0);
		else
			part->nbr_ptr = ft_pad_string("%", PAD_CHAR, width, 0);
	}
	else if (width < -1)
		part->nbr_ptr = ft_pad_string("%", ' ', width, 0);
	else
		part->nbr_ptr = (char*)ft_strdup("%");
	return (1);
}