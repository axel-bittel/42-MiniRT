/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:25:59 by abittel           #+#    #+#             */
/*   Updated: 2021/11/02 11:53:01 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

int				ft_atoi(const char *nprt);
void			ft_bzero(void	*s, size_t n);
void			*ft_calloc(size_t nmeb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void	*s, int c, size_t n);
void			ft_putchar_fd(char s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(char *s, int c);
char			*ft_strdup(char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free_s1(char *s1, char const *s2);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *to_find, int n);
char			*ft_strrchr(char *s, int c);
char			*ft_strtrim(char const *s, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			ft_putfloat_fd(float n, int fd, int precision);
char			*ft_strjoin2(char *s1, char *s2);
char			*ft_strjoin3(char *s1, char *s2);
char			*ft_free_ptr(char *ptr);
void			ft_free_tab(char **tab);
int				is_sep(char a, char *sep);
int				ft_wordcount(char *str, char *charset);
char			**ft_wordalloc(char *str, char *charset);
char			**ft_split_charset(char *str, char *charset);
char			**ft_add_line_tab(char **tab, char *line);
char			**ft_copy_tab(char **tab);
int				ft_tab_len(char **tab);
int				ft_str_isdigit(char *str);

typedef struct s_args_idx
{
	int	i;
	int	j;
	int	k;
}	t_args_idx;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstprint(t_list *lst, void (*print)(void *));
#endif
