#include "ft_printf.h"
#include "libft.h"

#define AND_FLAG(x) (part->flags & x)
#define AND_INFO(x) (part->info & x)

#define ABS(x) (x < 0 ? -x : x)

#define STR_EMPTY (nbr == 0 && AND_INFO(PNUM_MASK) && precision == 0)

#define INT_HAS_PREFIX (nbr < 0 || AND_FLAG(PLUS_MASK) || AND_FLAG(SPAC_MASK))
#define INT_LEN_PLUS_PREFIX ((int)ft_strlen(str) + (INT_HAS_PREFIX ? 1 : 0))

#define OCT_HAS_PREFIX ((AND_FLAG(HASH_MASK)) && nbr != 0)
#define OCT_LEN_PLUS_PREFIX ((int)ft_strlen(str) + (OCT_HAS_PREFIX ? 1 : 0))

#define HEX_HAS_PREFIX (AND_FLAG(HASH_MASK) && nbr != 0)
#define HEX_LEN_PLUS_PREFIX ((int)ft_strlen(str) + (HEX_HAS_PREFIX ? 2 : 0))

#define TEST (nbr == 0 && precision == 0 && AND_INFO(PNUM_MASK) && width != 0 && !AND_FLAG(HASH_MASK))

/*
** %d %i
*/
int		build_nbr_1(t_printf_part *part, va_list *args) //%d %i
{
	int		width;
	int		precision;
	long long int		nbr;
	char*	str;

	width = AND_INFO(WSTA_MASK) ? va_arg(*args, int) : part->width;
	precision = AND_INFO(PSTA_MASK) ? va_arg(*args, int) : part->precision;
	nbr = ft_get_sints_varg(part->length, args);
	str = STR_EMPTY ? (char*)ft_strdup("") : ft_lutoa_d(ABS(nbr), 10);	//cas particulier du 0 pour PRE 0
		
	if (precision > 0 && precision > (int)ft_strlen(str)) // pad le début avec des 0
		str = ft_pad_string(str, '0', precision, 1);
	else if ((!AND_INFO(PNUM_MASK) || precision < 0) && AND_FLAG(ZERO_MASK) && !AND_FLAG(MINU_MASK) && width > INT_LEN_PLUS_PREFIX)
		str = ft_pad_string(str, '0', width - (INT_HAS_PREFIX ? 1 : 0), 1);

	if (nbr < 0) // prefix les nombres ('-' '+' ' ')
		str = ft_pad_string(str, '-', (int)ft_strlen(str) + 1, 1);
	else if (AND_FLAG(PLUS_MASK) || AND_FLAG(SPAC_MASK)) // met les prefixs + et ' '
		str = ft_pad_string(str, AND_FLAG(PLUS_MASK) ? '+' : ' ', (int)ft_strlen(str) + 1, 1);

	if (width < 0 && ABS(width) > (int)ft_strlen(str)) // pad à droite, dans cas 1		si width < 0, et |width| suffisament grand
		str = ft_pad_string(str, ' ', width, 1);
	else if (AND_FLAG(MINU_MASK) && width > (int)ft_strlen(str)) // pad à droite, dans cas 2
		str = ft_pad_string(str, ' ', -width, 1);
	else if (width > (int)ft_strlen(str)) // pad à gauche, dans cas 3
		str = ft_pad_string(str, ' ', width, 1);

	part->nbr_ptr = str;
	return (1);
}

/*
** %u
*/
int		build_nbr_3(t_printf_part *part, va_list *args) //%u
{
	int		width;
	int		precision;
	t_ulli	nbr;
	char*	str;

	width = AND_INFO(WSTA_MASK) ? va_arg(*args, int) : part->width;
	precision = AND_INFO(PSTA_MASK) ? va_arg(*args, int) : part->precision;
	nbr = ft_get_uints_varg(part->length, args);
	str = STR_EMPTY ? (char*)ft_strdup("") : ft_lutoa_d(nbr, 10);	//cas particulier du 0 pour PRE 0
	if (precision > 0 && precision > (int)ft_strlen(str)) // pad le début avec des 0
		str = ft_pad_string(str, '0', precision, 1);
	else if ((!AND_INFO(PNUM_MASK) || precision < 0) && AND_FLAG(ZERO_MASK) &&
	!AND_FLAG(MINU_MASK) && width > (int)ft_strlen(str))
		str = ft_pad_string(str, '0', width, 1);
	if (width < 0 && ABS(width) > (int)ft_strlen(str)) // pad à droite, dans cas 1		si width < 0, et |width| suffisament grand
		str = ft_pad_string(str, ' ', width, 1);
	else if (AND_FLAG(MINU_MASK) && width > (int)ft_strlen(str)) // pad à droite, dans cas 2		
		str = ft_pad_string(str, ' ', -width, 1);
	else if (width > (int)ft_strlen(str)) // pad à gauche, dans cas 3
		str = ft_pad_string(str, ' ', width, 1);
	part->nbr_ptr = str;
	return (1);
}

/*
** %o
*/
int		build_nbr_4(t_printf_part *part, va_list *args)
{
	int		width;
	int		precision;
	t_ulli	nbr;
	char*	str;

	width = AND_INFO(WSTA_MASK) ? va_arg(*args, int) : part->width;
	precision = AND_INFO(PSTA_MASK) ? va_arg(*args, int) : part->precision;
	nbr = ft_get_uints_varg(part->length, args);
	str = TEST ? (char*)ft_strdup("") : ft_lutoa_d(nbr, 8);	//cas particulier du 0 pour PRE 0
	if (precision > 0 && precision > OCT_LEN_PLUS_PREFIX) // pad le début avec des 0
		str = ft_pad_string(str, '0', precision - (OCT_HAS_PREFIX ? 1 : 0), 1);
	else if ((!AND_INFO(PNUM_MASK) || precision < 0) && AND_FLAG(ZERO_MASK) &&
	!AND_FLAG(MINU_MASK) && width > OCT_LEN_PLUS_PREFIX)
		str = ft_pad_string(str, '0', width - (OCT_HAS_PREFIX ? 1 : 0), 1);
	if (OCT_HAS_PREFIX) // prefix les nombres ('-' '+' ' ')
		str = (char*)ft_strjoinfree("0", str, 0, 1);
	if (width < 0 && ABS(width) > (int)ft_strlen(str)) // pad à droite, dans cas 1		si width < 0, et |width| suffisament grand
		str = ft_pad_string(str, ' ', width, 1);
	else if (AND_FLAG(MINU_MASK) && width > (int)ft_strlen(str)) // pad à droite, dans cas 2		
		str = ft_pad_string(str, ' ', -width, 1);
	else if (width > (int)ft_strlen(str)) // pad à gauche, dans cas 3
		str = ft_pad_string(str, ' ', width, 1);
	part->nbr_ptr = str;
	return (1);
}

/*
** %x
*/
int		build_nbr_5(t_printf_part *part, va_list *args)
{
	int		width;
	int		precision;
	t_ulli	nbr;
	char*	str;

	width = AND_INFO(WSTA_MASK) ? va_arg(*args, int) : part->width;
	precision = AND_INFO(PSTA_MASK) ? va_arg(*args, int) : part->precision;
	nbr = ft_get_uints_varg(part->length, args);
	str = STR_EMPTY ? (char*)ft_strdup("") : ft_lutoa_d(nbr, 16); //cas particulier du 0 pour PRE 0
	if (precision > 0 && precision > (int)ft_strlen(str)) // pad le début avec des 0
		str = ft_pad_string(str, '0', precision, 1);
	else if ((!AND_INFO(PNUM_MASK) || precision < 0) && AND_FLAG(ZERO_MASK) &&
	!AND_FLAG(MINU_MASK) && width > HEX_LEN_PLUS_PREFIX)
		str = ft_pad_string(str, '0', width - (HEX_HAS_PREFIX ? 2 : 0), 1);
	if (HEX_HAS_PREFIX) // prefix les nombres ('-' '+' ' ')
		str = (char*)ft_strjoinfree("0x", str, 0, 1);
	if (width < 0 && ABS(width) > (int)ft_strlen(str)) // pad à droite, dans cas 1		si width < 0, et |width| suffisament grand
		str = ft_pad_string(str, ' ', width, 1);
	else if (AND_FLAG(MINU_MASK) && width > (int)ft_strlen(str)) // pad à droite, dans cas 2		
		str = ft_pad_string(str, ' ', -width, 1);
	else if (width > (int)ft_strlen(str)) // pad à gauche, dans cas 3
		str = ft_pad_string(str, ' ', width, 1);
	part->nbr_ptr = str;
	return (1);
}

/*
** %p
*/
int		build_nbr_17(t_printf_part *part, va_list *args)
{
	int		width;
	int		precision;
	t_ulli	nbr;
	char*	str;

	part->flags = part->flags | HASH_MASK;
	width = AND_INFO(WSTA_MASK) ? va_arg(*args, int) : part->width;
	precision = AND_INFO(PSTA_MASK) ? va_arg(*args, int) : part->precision;
	nbr = (t_ulli)va_arg(*args, unsigned int);
	str = STR_EMPTY ? (char*)ft_strdup("") : ft_lutoa_d(nbr, 16); //cas particulier du 0 pour PRE 0
	if (precision > 0 && precision > (int)ft_strlen(str)) // pad le début avec des 0
		str = ft_pad_string(str, '0', precision, 1);
	else if ((!AND_INFO(PNUM_MASK) || precision < 0) && AND_FLAG(ZERO_MASK) &&
	!AND_FLAG(MINU_MASK) && width > ((int)ft_strlen(str) + 2))
		str = ft_pad_string(str, '0', width - 2, 1);
	str = (char*)ft_strjoinfree("0x", str, 0, 1);
	if (width < 0 && ABS(width) > (int)ft_strlen(str)) // pad à droite, dans cas 1		si width < 0, et |width| suffisament grand
		str = ft_pad_string(str, ' ', width, 1);
	else if (AND_FLAG(MINU_MASK) && width > (int)ft_strlen(str)) // pad à droite, dans cas 2		
		str = ft_pad_string(str, ' ', -width, 1);
	else if (width > (int)ft_strlen(str)) // pad à gauche, dans cas 3
		str = ft_pad_string(str, ' ', width, 1);
	part->nbr_ptr = str;
	return (1);
}