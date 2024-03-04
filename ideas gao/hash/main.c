/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:29:20 by yugao             #+#    #+#             */
/*   Updated: 2024/03/03 02:07:37 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hash.h"

int	main(void)
{
	t_hash	*hash;

	hash = hash_init ();
	hash_push (hash, "test1", "jajajaja");
	hash_push (hash, "cd", "cd direction");
	hash_push (hash, "cat", "cat direction");
	hash_push (hash, "echo", "echo direction");
	printf (">===hash_grep : %s ===\n\n", hash_grep (hash, "tes"));
	printf (">===hash_grep : %s ===\n\n", hash_grep (hash, "cd"));
	printf (">===hash_grep : %s ===\n\n", hash_grep (hash, "echo"));
	printf (">===hash_grep : %s ===\n\n", hash_grep (hash, "cat"));
	hash_grep (hash, "test1");
	hash_grep (hash, "cd");
	hash_grep (hash, "echo");
	hash_grep (hash, "cat");
	hash_del (hash, "test1");
	hash_grep (hash, "test1");
	hash_destory (hash);
	return (0);
}