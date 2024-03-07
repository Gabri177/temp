/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:22:24 by yugao             #+#    #+#             */
/*   Updated: 2024/03/06 10:18:28 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quote_check(char *str)
{
	int	little;
	int	big;
	int	i;

	little = 0;
	big = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
			little ++;
		if (str[i] == 39)
			big ++;
	}
	if (little > 0 && little % 2 != 0)
		return (FALSE);
	if (big > 0 && big % 2 != 0)
		return (FALSE);
	return (TRUE);
}

char	**arg_abordar(char *ori)
{
	char	**new_arvs;

	if (!ori)
		return (NULL);//error
	if (!ori[0])
		return (NULL);//null context
	if (!quote_check (ori))
		return (NULL);//error
	new_arvs = NULL;
	split_args (&new_arvs, ori);
	return (new_arvs);
}
/*
int main (void)
{
	// situacion como ||||||| o >>>>>> o <<<<<<<< o <> ><   >>>>le3 中间的">>"被当成文件了 所以le3没有被删除
	char	test[]=" ls >file1 >>file2 -la arg1[1] arg2[1]|grep >file >>fill| cat -d arg1[3] | cd | ls arg1[4] arg2[4]";//write a checker to theck the ilegal situation
	char	**ori_args;
	char	**outfile;
	char	**cmds;
	char	***argss;
	//char	**no_cmds;

	ori_args = arg_abordar (test);
	if (!ori_args)
		printf ("empty");
	//=======================================
	printf ("original args:\n");
	arry_display (ori_args);
	//=======================================
	outfile = args_to_outfile (&ori_args);
	printf ("outfile:\n");
	arry_display (outfile);
	//=======================================
	printf ("args sin outfiles:\n");
	arry_display (ori_args);
	//=======================================
	printf ("simple commands:\n");
	cmds = args_to_cmds (&ori_args);
	arry_display (cmds);
	arry_display (ori_args);
	//=======================================
	printf ("argumentossss:\n");
	argss = args_to_args (&ori_args);
	


	argss_destory (argss);
	arry_destory (cmds);
	arry_destory (ori_args);
	arry_destory (outfile);
	system ("leaks -q minishell");
	return 0;
}*/