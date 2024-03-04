/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:24:13 by yugao             #+#    #+#             */
/*   Updated: 2024/03/03 02:04:25 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define HASH_SIZE 100

typedef int		t_bool;
typedef struct s_node
{
	char			*key;
	int				id;
	char			*val;
	struct s_node	*next;
}				t_node;
typedef struct s_hash
{
	t_node	*bucket[HASH_SIZE];
}				t_hash;

// utils.c
char	*ft_strdup(const char *str);
t_bool	is_strsame(char *s1, char *s2);
int		ft_strlen(char	*str);
int		hash_func(char *key);

//hash_list
t_node	*list_init(void);
t_bool	list_push(t_node *l, char *key, char *val);
t_bool	list_del(t_node *l, char *key);
t_bool	list_grep(t_node *l, char *key);
t_bool	list_destory(t_node *l);
void	list_print(t_node *l);

//hash
t_hash	*hash_init(void);
t_bool	hash_push(t_hash *h, char *key, char *val);
char	*hash_grep(t_hash *h, char *key);
t_bool	hash_destory(t_hash	*h);
t_bool	hash_del(t_hash	*h, char *key);

#endif