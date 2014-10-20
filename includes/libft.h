

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>

# ifndef T_BOOL
#  define T_BOOL

typedef enum	e_bool
{
	false,
	true
}				t_bool;

# endif

void			ft_myassert(int relation);
int				ft_match(char *s1, char *s2);
int				ft_myputnchar(char *str, int num);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strjoinfree(char *s1, char *s2, int frees1, int frees2);
size_t			ft_strcharlen(const char *str, const char delim);

int				ft_powi(int n, unsigned int p);
unsigned int	ft_sqrtfloor(unsigned int n);
// div_t			ft_pythai(int x, int y);

void			ft_putnbr(int i);
void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);


int				ft_atoi(const char *str);

int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isxdigit(int c);
int				ft_ispunct(int c);
int				ft_isgraph(int c);
int				ft_isprint(int c);
int				ft_isblank(int c);
int				ft_isspace(int c);
int				ft_iscntrl(int c);
int				ft_isascii(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

size_t			ft_strlen(const char *str);
char			*ft_strcpy(char *s1, const char *s2);
char			*ft_strncpy(char *s1, const char *s2, size_t num);
size_t			ft_strlcpy(char *s1, const char *s2, size_t num);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t num);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t size);
char			*ft_strstr(const char *src, const char *tofind);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
size_t			ft_strcspn(const char *s1r, const char *s2r);
size_t			ft_strspn(const char *str1, const char *str2);
void			ft_strdel(char **as);

void			*ft_memmove(void *destination, const void *source, size_t num);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void			ft_memdel(void **ap);
void			*ft_memalloc(size_t size);
void			*ft_memcpy(void *trg, const void *src, size_t nb);
char			*ft_strdup(const char *src);
void			*ft_memset(void *ptr, int c0, size_t nb);
void			ft_bzero(void *ptr, size_t nb);
char			*ft_strnew(size_t size);
void			ft_strclr(char *s);
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2,size_t n);
char			*ft_strtrim(const char *s);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
/*
** math caca
*/

int				ft_abs(int i);
// div_t			ft_div(int num, int denom);
int				ft_subs(int n1, int n2);
int				ft_addi(int n1, int n2);
int				ft_mult(int n1, int n2);
int				ft_divi(int n1, int n2);
int				ft_modu(int n1, int n2);
int				ft_eval_expr(char *str);

uint64_t		ft_getbitarray(unsigned char* nbr, size_t first, size_t last);
int				ft_dbltype(double nbr_ref);

/*
** math
*/

double			ft_log2(double nb);
double			ft_log16(double nb);
double			ft_log10(double nb);
double			ft_ceil(double nb);
double			ft_floor(double nb);

/*
** itoa and co.
*/
char			*ft_pad_string(char *str, char c, int n, int freestr);
void			ft_revstr(char *str);

void			ft_litoa(int64_t value, char *str, int base);
void			ft_lutoa(uint64_t value, char *str, int base);
// void			ft_itoa(int value, char *str, int base);
void			ft_utoa(unsigned int value, char *str, int base);
char			*ft_itoa(int n);

char			*ft_litoa_s(int64_t value, int base);
char			*ft_lutoa_s(uint64_t value, int base);
char			*ft_itoa_s(int value, int base);
char			*ft_utoa_s(unsigned int value, int base);

char			*ft_litoa_d(int64_t value, int base);
char			*ft_lutoa_d(uint64_t value, int base);
char			*ft_itoa_d(int value, int base);
char			*ft_utoa_d(unsigned int value, int base);

#endif