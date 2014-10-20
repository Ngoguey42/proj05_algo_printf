#include "ft_printf.h"
#include "libft.h"

#define INF_VALUE 0x7FF0000000000000

#define ZERO_VALUE 0x0000000000000000

#define DENORM_ARRAY_MAX 0x000FFFFFFFFFFFFF
#define DENORM_ARRAY_MIN 0x0000000000000001

#define NORM_ARRAY_MAX 0x7FEFFFFFFFFFFFFF
#define NORM_ARRAY_MIN 0x0010000000000000



long long int	ft_get_sints_varg(unsigned char length, va_list *args)
{
	if (length == 0) // none
		return ((long long int)(int)va_arg(*args, long long int));
	else if (length == 1) // j
		return ((long long int)(intmax_t)va_arg(*args, long long int));
	else if (length == 2) // z
		return ((long long int)(int)va_arg(*args, long long int));
	else if (length == 3) // t
		return ((long long int)(ptrdiff_t)va_arg(*args, long long int));
	else if (length == 4) // L
		return ((long long int)(int)va_arg(*args, long long int));
	else if (length == 5) // h
		return ((long long int)(short int)va_arg(*args, long long int));
	else if (length == 6) // l
		return ((long long int)(long int)va_arg(*args, long long int));
	else if (length == 7) // hh
		return ((long long int)(char)va_arg(*args, long long int));
	else if (length == 8) // ll
		return ((long long int)va_arg(*args, long long int));
}

t_ulli	ft_get_uints_varg(unsigned char length, va_list *args)
{	
	if (!length) // none
		return ((t_ulli)(unsigned int)va_arg(*args, t_ulli));
	else if (length == 1) // j
		return ((t_ulli)(uintmax_t)va_arg(*args, t_ulli));
	else if (length == 2) // z
		return ((t_ulli)(size_t)va_arg(*args, t_ulli));
	else if (length == 3) // t
		return ((t_ulli)(unsigned int)va_arg(*args, t_ulli)); //pas réussi autrement...
	else if (length == 4) // L
		return ((t_ulli)(unsigned int)va_arg(*args, t_ulli));
	else if (length == 5) // h
		return ((t_ulli)(unsigned short int)va_arg(*args, t_ulli));
	else if (length == 6) // l
		return ((t_ulli)(unsigned long int)va_arg(*args, t_ulli));
	else if (length == 7) // hh
		return ((t_ulli)(unsigned char)va_arg(*args, t_ulli));
	else if (length == 8) // ll
		return ((t_ulli)va_arg(*args, t_ulli));
}