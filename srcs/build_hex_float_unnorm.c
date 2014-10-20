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

// #define ABS(x) (x < 0 ? -x : x)

#define GET_CHAR(DELTA) ((*ptr)[pre + (DELTA)])
#define PRECISION_SET(REL) (AND_INFO(PSTA_MASK) && PRE REL)


// UNN - 3 static
static int			ft_get_unnorm_exp(t_ulli nbr)
{
	int				i;
	unsigned char	*ptr;

	ptr = ((unsigned char*)&nbr) + 6;
	i = 51;
	while (i > 0)
	{
		if (*ptr & 0b00001000)
			return (i);
		i--;
		nbr = nbr << 1;
	}
	return (0);
}


// UNN - 2 static
static void	ft_build_unnorm_strings(double nbr, char **temp_str, char **ret)
{
	long long int	i;
	long long int	j;
	t_ulli			temp_nbr;

	temp_nbr = ft_getbitarray((unsigned char*)&(nbr), 0, 51);
	i = (j = ft_get_unnorm_exp(temp_nbr)) - 1023 - 51;
	*ret = (char*)ft_strjoinfree("p-", ft_lutoa_d(-i, 10), 0, 1);
	((unsigned char*)&temp_nbr)[j/8] ^= 1 << (j%8);
	j = llpowi(2, j);
	i = (long long int)ceil(log((double)j) / log(16));
	*temp_str = ft_lutoa_d(temp_nbr * (llpowi(16, (int) i) / j), 16);
	if (i > (long long int)ft_strlen(*temp_str))
		*temp_str = ft_pad_string(*temp_str, '0', i, 1);
}

// UNN - 1 ft_
char	*ft_build_unnormalized(double nbr, t_printf_part *part, int type)
{
	char	*ret;
	char	*temp_str;
	char	first_decimal;
	int		i;

	ft_build_unnorm_strings(nbr, &temp_str, &ret);
	first_decimal = *temp_str;
	while (PRE < 0 && temp_str[i = ((int)ft_strlen(temp_str) - 1)] == '0')
		temp_str[i] = '\0';
	i = 0;
	if (PRECISION_SET(>= 0) && PRE < (int)ft_strlen(temp_str))
		round_mantissa_b16(&temp_str, PRE, &i);
	else if (PRE > 0 && PRE > (int)ft_strlen(temp_str))
		temp_str = ft_pad_string(temp_str, '0', -PRE, 1);
	while (!AND_INFO(PSTA_MASK) && (int)ft_strlen(temp_str) > 0 &&
	temp_str[(int)ft_strlen(temp_str) - 1] == '0')
		temp_str[(int)ft_strlen(temp_str) - 1] = '\0';
	ret = (char*)ft_strjoinfree(temp_str, ret, 0, 1);
	if (!((int)ft_strlen(temp_str) == 0 && !AND_FLAG(HASH_MASK)))
		ret = (char*)ft_strjoinfree(".", ret, 0, 1);
	if ((first_decimal >= '8' && (int)ft_strlen(temp_str) == 0) || i)
		ret = (char*)ft_strjoinfree("2", ret, 0, 1);
	else
		ret = (char*)ft_strjoinfree("1", ret, 0, 1);
	// free(temp_str); //j'arrive pas a free temp_str marche pas
	return (ret);
}