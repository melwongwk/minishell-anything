/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:05:53 by melwong           #+#    #+#             */
/*   Updated: 2025/10/24 05:22:07 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# define QSORT_THRESHOLD 16

# define WHITESPACE "\t\n\v\f\r "

int			ft_abs(int nbr);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
int			ft_atoi(const char *nptr);
int			ft_atoi_safe(const char *str, int *out);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_count_words(const char *s, char c);
int			ft_count_words_charset(const char *s, const char *charset);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t dsize);
size_t		ft_strlcat(char *dest, const char *src, size_t dsize);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strjoin_free(char *s1, char *s2, int to_free);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(const char *s, char c);
char		**ft_split_charset(const char *str, const char *charset);
int			*ft_split_int(const char *str, int *count);
char		*ft_ultoa_base(unsigned long nbr, const char *base);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_swap(void *a, void *b, size_t size);
void		ft_quick_sort(int *arr, int low, int high);
void		ft_bubblesort_asc(int *tab, int size);
char		*get_next_line(int fd);
int			ft_printf(const char *format, ...);

#endif
