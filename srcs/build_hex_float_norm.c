#include "ft_printf.h"
#include "libft.h"
#include "ft_math.h"

#include <math.h> //-42
#include <stdlib.h> //-42

#define HEX_FLOAT_HAS_PREFIX ((type % 2) == 0 || AND_FLAG(PLUS_MASK) || AND_FLAG(SPAC_MASK))
#define HEX_FLOAT_LEN_PLUS_PREFIX ((int)ft_strlen(str) + (HEX_FLOAT_HAS_PREFIX ? 1 : 0))

#define AND_FLAG(x) (part->flags & x)
#define AND_INFO(x) (part->info & x)
#define WID part->width
#define PRE part->precision

// #define ABS(x) (x < 0 ? -x : x)

#define GET_CHAR(DELTA) ((*ptr)[pre + (DELTA)])
#define PRECISION_SET(REL) (AND_INFO(PSTA_MASK) && PRE REL)


#define NEWWAY


static void	ft_build_norm_strings(double dbl, char **mant, char **exp)
{
#ifndef NEWWAY
	long long int	i;
	long long int	j;
	t_ulli			temp_nbr;

	i = ft_getbitarray((unsigned char*)&(dbl), 52, 62) - 1023;
	*exp = i < 0 ? (char*)ft_strjoinfree("p-", ft_lutoa_d(-i, 10), 0, 1) :
	(char*)ft_strjoinfree("p+", ft_lutoa_d(i, 10), 0, 1);
	temp_nbr = ft_getbitarray((unsigned char*)&(dbl), 0, 51);
	if (temp_nbr == 0)
	{
		*mant = (char*)ft_strdup("");
		return ;
	}
	i = -1;
	while (++i < 51 && !(temp_nbr & 1))
		temp_nbr = temp_nbr >> 1;
	temp_nbr = temp_nbr >> 1;
	j = llpowi(2, 51 - i);
	i = (j % 8) == 0 ? j / 8 : j / 8 + 1;
	i = (int)ceil(log((double)i) / log(16) + 1);
	j = llpowi(16, (int)i) / j / 2;
	*mant = ft_lutoa_d(temp_nbr * j * 2 + j, 16);
	// if (i > (long long int)ft_strlen(*mant))
		*mant = ft_pad_string(*mant, '0', i, 1);
#else
	int				i;
	t_dbl_extract	u;
	char			*ptr;

	u.d = dbl;
	i = u.s.exp - 1023;
	*exp = i < 0 ? (char*)ft_strjoinfree("p-", ft_lutoa_d(-i, 10), 0, 1) :
	(char*)ft_strjoinfree("p+", ft_lutoa_d(i, 10), 0, 1);
	*mant = (char*)malloc(14);
	(*mant)[13] = '\0';
	i = 14;
	ptr = ((char*)(&u.d)) + 6;
	u.s.exp = 0;
	while (--i)
	{
		(*mant)[13 - i] = *ptr >= 10 ? *ptr + 'a' - 10 : *ptr + '0';
		if (i == 9)
			u.s.manh = u.s.manl >> 16;
		if (i == 5)
			u.s.manh = u.s.manl << 16 >> 16;
		u.s.manh = u.s.manh << 4;
	}
	while ((i = ft_strlen(*mant)) > 0 && (*mant)[i - 1] == '0')
		(*mant)[i - 1] = '\0';
#endif
}



char	*ft_build_normalized(double nbr, t_printf_part *part, int type)
{
	char	*ret;
	char	*temp_str;
	char	first_decimal;
	int		j;

	ft_build_norm_strings(nbr, &temp_str, &ret);
	first_decimal = *temp_str;
	j = 0;
	if (PRECISION_SET(>= 0) && PRE < (int)ft_strlen(temp_str))
		round_mantissa_b16(&temp_str, PRE, &j);
	else if (PRE > 0 && PRE > (int)ft_strlen(temp_str))
		temp_str = ft_pad_string(temp_str, '0', -PRE, 1);
	ret = (char*)ft_strjoinfree(temp_str, ret, 0, 1);
	if ((int)ft_strlen(temp_str) > 0 || AND_FLAG(HASH_MASK))
		ret = (char*)ft_strjoinfree(".", ret, 0, 1);
	if ((first_decimal >= '8' && (int)ft_strlen(temp_str) == 0) || j)
		ret = (char*)ft_strjoinfree("2", ret, 0, 1);
	else
		ret = (char*)ft_strjoinfree("1", ret, 0, 1);
	// free(temp_str); //j'arrive pas a free temp_str marche pas
	return (ret);
}