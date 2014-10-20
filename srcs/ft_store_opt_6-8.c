#include "ft_printf.h"
#include "libft.h"

//ft_store_opt_6-8.c
int		ft_store_opt_6(char c, t_printf_part *part)
{
	part->length = (unsigned char)ft_strcharlen(CHARS_LENGTH, c) + 1;
	return (1);
}

//ft_store_opt_6-8.c
int		ft_store_opt_7(char c, t_printf_part *part)
{
	unsigned char	plength;
	size_t			const_len;

	plength = part->length;
	const_len = (int)ft_strlen(CHARS_LENGTH);
	if (plength > const_len - NUM_DBL_CHAR_LEN)
		part->length = plength + NUM_DBL_CHAR_LEN;
	else
		return (0);
	return (1);
}

//ft_store_opt_6-8.c
int		ft_store_opt_8(char c, t_printf_part *part)
{
	part->specifier = (unsigned char)ft_strcharlen(CHARS_SPECIFIERS, c) + 1;
	return (1);
}
