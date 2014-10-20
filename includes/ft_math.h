#ifndef FT_MATH_H
# define FT_MATH_H

// # include <stdlib.h>
# define ABS(x) ((x) < 0 ? -(x) : (x))

# ifndef IEEE_DOUBLE_BIG_ENDIAN
#  define IEEE_DOUBLE_BIG_ENDIAN 0
# endif

// # if defined(__ARMEB__)
// #  define IEEE_DOUBLE_MIXED_ENDIAN 0
// #  define IEEE_DOUBLE_BIG_ENDIAN 1
// # elif defined(__VFP_FP__)
// #  define IEEE_DOUBLE_MIXED_ENDIAN 0
// #  define IEEE_DOUBLE_BIG_ENDIAN 0
// # else
// #  define IEEE_DOUBLE_BIG_ENDIAN 0
// #  define IEEE_DOUBLE_MIXED_ENDIAN 1
// # endif
   
# if IEEE_DOUBLE_BIG_ENDIAN
typedef union		u_dbl_extract
{
struct
{
	unsigned char	sig:1;
	unsigned short	exp:11;
	unsigned int	manh:20;
	unsigned int	manl:32;
} s;
double d;
}					t_dbl_extract;

typedef union		u_nan_dbl_extract
{
struct
{
	unsigned char	sig:1;
	unsigned short	exp:11;
	unsigned char	nan:1;
	unsigned int	manh:19;
	unsigned int	manl:32;
} s;
double d;
}					t_nan_dbl_extract;

typedef union		u_dbl_shape
{
struct
{
	unsigned int	manh:32;
	unsigned int	manl:32;
} s;
double d;
}					t_dbl_shape;

# else
typedef union		u_dbl_extract
{
struct
{
	unsigned int	manl:32;
	unsigned int	manh:20;
	unsigned short	exp:11;
	unsigned char	sig:1;
} s;
double d;
}					t_dbl_extract;

typedef union		u_nan_dbl_extract
{
struct
{
	unsigned int	manl:32;
	unsigned int	manh:19;
	unsigned char	nan:1;
	unsigned short	exp:11;
	unsigned char	sig:1;
} s;
double d;
}					t_nan_dbl_extract;

typedef union		u_dbl_shape
{
struct
{
	unsigned int	manl:32;
	unsigned int	manh:32;
} s;
double d;
}					t_dbl_shape;
# endif


// typedef union		u_dbl_full
// {
// unsigned long long	ll;
// double d;
// }					t_dbl_full;

// typedef unsigned long int		t_uint4;
// typedef uint64_t	uint64_t;
// typedef long int				t_int4;
// typedef int64_t			t_int8;


# define M_INFINITY (1.0/0.0)
# define M_MINFINITY (-1.0/0.0)
# define M_NAN (0.0/0.0)

#endif