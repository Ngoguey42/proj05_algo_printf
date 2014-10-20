#include "ft_printf.h"
// #include "libft.h"


// char	*ft_litoa_d(int64_t value, int base)
// {
	// char*	str;

	// str = (char*)malloc(sizeof(int64_t) * 8 + 1); //malloc
	// if (!str)
		// return (NULL);
	// ft_litoa(value, str, base);
	// return (str);
// }

// void	ft_litoa(int64_t value, char *str, int base)
// {
	// int	i;

 	// if (value < 0)
	// {
		// *(str++) = '-';
		// // value = -value; //faut t'il le remettre?
	// }
	// if (value == 0)
		// *(str++) = '0';
	// i = 0;
	// while (value != 0)
	// {
		// str[i++] = BASE_NBRS[value % base];
		// value /= base;
	// }
	// str[i] = '\0';
	// ft_revstr(str);
// }










//"diuoxX fFeEgGaA cspn%"
//build_nbr.c
void	populate_build_nbr(int(*build_nbr[20])(t_printf_part *part, va_list *args))
{
	build_nbr[0] = build_nbr_0;
	build_nbr[1] = build_nbr_1;
	build_nbr[2] = build_nbr_1;
	build_nbr[3] = build_nbr_3;
	build_nbr[4] = build_nbr_4;
	build_nbr[5] = build_nbr_5;
	build_nbr[6] = build_nbr_6;
	build_nbr[7] = build_nbr_0;
	build_nbr[8] = build_nbr_0;
	build_nbr[9] = build_nbr_0;
	build_nbr[10] = build_nbr_0;
	build_nbr[11] = build_nbr_0;
	build_nbr[12] = build_nbr_0;
	build_nbr[13] = build_nbr_13;
	build_nbr[14] = build_nbr_14;
	build_nbr[15] = build_nbr_15;
	build_nbr[16] = build_nbr_16;
	build_nbr[17] = build_nbr_17;
	build_nbr[18] = build_nbr_0;
	build_nbr[19] = build_nbr_19;
}