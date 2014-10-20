

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h> //DEBUG

// FLAGS
# define MINU_MASK 1
# define PLUS_MASK 2
# define SPAC_MASK 4
# define HASH_MASK 8
# define ZERO_MASK 16

// INFO
# define WSTA_MASK 1
# define PSTA_MASK 2
# define PNUM_MASK 4
# define BSZERO_MASK 8

# define CHARS_FLAGS "-+ #0"
# define CHARS_LENGTH "jztLhl"
# define NUM_DBL_CHAR_LEN 2
# define CHARS_SPECIFIERS "diuoxXfFeEgGaAcspn%"


typedef unsigned long long int		t_ulli;

typedef struct		s_printf_part
{
	const char				*str_ptr;
	size_t					str_size;
	char					*nbr_ptr;
	void					*varg_ptr;

	struct s_printf_part	*next;

	unsigned char			flags;
	unsigned char			info;
	int						width;
	int						precision;
	unsigned char			length;
	unsigned char			specifier;
	unsigned char			error;
}					t_printf_part;

typedef struct		s_float_readable
{
	short			exponant;
	int				mantissa;
	char			*special;
}					t_float_readable;


typedef unsigned char *byte_pointer; //debug de merde
void				inspect_part(t_printf_part *part); //debug
void showbits(byte_pointer x, int bits, int highlightmin, int highlightmax); //debug

int					ft_store_opt_1(char c, t_printf_part *part);
int					ft_store_opt_2(char c, t_printf_part *part);
int					ft_store_opt_3(char c, t_printf_part *part);
int					ft_store_opt_5(char c, t_printf_part *part);
int					ft_store_opt_6(char c, t_printf_part *part);
int					ft_store_opt_7(char c, t_printf_part *part);
int					ft_store_opt_8(char c, t_printf_part *part);
void				populate_build_nbr(int(*build_nbr[20])(t_printf_part *part, va_list *args));
int					ft_getprintf(char **ret, const char *format, va_list *args);
int					ft_parse_format(const char *format, t_printf_part **beginning);

long long int		ft_get_sints_varg(unsigned char length, va_list *args);
t_ulli				ft_get_uints_varg(unsigned char length, va_list *args);

void				round_mantissa_b16(char **ptr, int pre, int *int_part_two);
char				*ft_build_unnormalized(double nbr, t_printf_part *part, int type);
char				*ft_build_normalized(double nbr, t_printf_part *part, int type);
int 				is_pair(char c);
long long int		llpowi(long long int n, unsigned int p);

int		build_nbr_0(t_printf_part *part, va_list *args);
int		build_nbr_1(t_printf_part *part, va_list *args);
int		build_nbr_3(t_printf_part *part, va_list *args);
int		build_nbr_4(t_printf_part *part, va_list *args);
int		build_nbr_5(t_printf_part *part, va_list *args);
int		build_nbr_6(t_printf_part *part, va_list *args);
int		build_nbr_13(t_printf_part *part, va_list *args);
int		build_nbr_14(t_printf_part *part, va_list *args);
int		build_nbr_15(t_printf_part *part, va_list *args);
int		build_nbr_16(t_printf_part *part, va_list *args);
int		build_nbr_17(t_printf_part *part, va_list *args);
int		build_nbr_19(t_printf_part *part, va_list *args);






#endif



