#include "ft_printf.h"
#include "libft.h"

#include <math.h> //-42
#include <stdlib.h> //-42

#define HEX_FLOAT_HAS_PREFIX ((type % 2) == 0 || AND_FLAG(PLUS_MASK) || AND_FLAG(SPAC_MASK))
#define HEX_FLOAT_LEN_PLUS_PREFIX ((int)ft_strlen(str) + (HEX_FLOAT_HAS_PREFIX ? 1 : 0))

#define AND_FLAG(x) (part->flags & x)
#define AND_INFO(x) (part->info & x)
#define WID part->width
#define PRE part->precision

#define ABS(x) (x < 0 ? -x : x)

#define GET_CHAR(DELTA) ((*ptr)[pre + (DELTA)])
#define PRECISION_SET(REL) (AND_INFO(PSTA_MASK) && PRE REL)


// simili lib
int is_pair(char c)
{
	if ((ft_isdigit(c) && (c % 2 == 0)) || (!ft_isdigit(c) && (c % 2 == 1)))
		return (1);
	return (0);
}

// simili lib
long long int	llpowi(long long int n, unsigned int p)
{
	long long int	total;

	if (!p)
		return (1);
	total = 1;
	while(p--)
		total *= n;
	return (total);
}

// A - 4 static
void		round_mantissa_b16(char **ptr, int pre, int *int_part_two)
{
	int	i;

	if (((int)ft_strlen((*ptr)) - 1) == pre && GET_CHAR(0) <= '8' &&
	is_pair(GET_CHAR(-1)))
		;
	else if (GET_CHAR(0) >= '8')
	{
		if (GET_CHAR(-1) == 'f')
		{
			i = -1;
			while((pre - 1 - ++i) >= 0 && GET_CHAR(-1 - i) == 'f')
				GET_CHAR(-1 - i) = '0';
			if ((pre - 1 - i) >= 0)
				GET_CHAR(-1 - i) += (GET_CHAR(-1 - i) == '9') ? 40 : 1;
			else
				*int_part_two = 1;
		}
		else
			GET_CHAR(-1) += (GET_CHAR(-1) == '9') ? 40 : 1;
	}
	GET_CHAR(0) = '\0';
}

// A - 3 static
static char		*build_zero(double nbr, t_printf_part *part, int precision)
{
	char	*str;

	str = ft_strdup("p+0");
	if (precision > 0)
		str = ft_pad_string(str, '0', precision + 3, 1);
	if (precision > 0 || AND_FLAG(HASH_MASK))
		str = (char*)ft_strjoinfree(".", str, 0, 1);
	str = (char*)ft_strjoinfree("0", str, 0, 1);
	return (str);
}

// A - 2 static
static char		*build_hex_sci(double nbr, t_printf_part *part, int type)
{
	char	*str;

	if (type <= 2)
		str = ft_build_normalized(nbr, part, type);
	else if (type >= 9)
		str = ft_strdup("nan");
	else if (type >= 7)
		str = ft_strdup("inf");
	else if (type >= 5)
		str = build_zero(nbr, part, PRE);
	else
		str = ft_build_unnormalized(nbr, part, type);
	if (type <= 6 && AND_FLAG(ZERO_MASK) && !AND_FLAG(MINU_MASK) &&
	WID > (HEX_FLOAT_LEN_PLUS_PREFIX + 2))
		str = ft_pad_string(str, '0', WID - (HEX_FLOAT_HAS_PREFIX ? 1 : 0) - 2
		, 1);
	if (type <= 6)
		str = (char*)ft_strjoinfree("0x", str, 0, 1);
	if ((type % 2) == 0 && type != 10)
		str = (char*)ft_strjoinfree("-", str, 0, 1);
	else if (AND_FLAG(PLUS_MASK) || AND_FLAG(SPAC_MASK))
		str = (char*)ft_strjoinfree(AND_FLAG(PLUS_MASK) ? "+" : " ", str, 0, 1);
	return (str);
}

// A - 1 ft_
int		build_nbr_13(t_printf_part *part, va_list *args) //%a
{
	char	*str;
	double	nbr;

	WID = AND_INFO(WSTA_MASK) ? va_arg(*args, int) : WID;
	PRE = AND_INFO(PSTA_MASK) ? va_arg(*args, int) : PRE;
	nbr = va_arg(*args, double);
	str = build_hex_sci(nbr, part, ft_dbltype(nbr));
	if (WID > 0 && WID > (int)ft_strlen(str))
	{
		if (part->flags & MINU_MASK)
			str = ft_pad_string(str, ' ', -WID, 1);
		else
			str = ft_pad_string(str, ' ', WID, 1);
	}
	else if (WID < 0 && ABS(WID) > (int)ft_strlen(str))
		str = ft_pad_string(str, ' ', WID, 1);
	part->nbr_ptr = str;
	return (1);
}

