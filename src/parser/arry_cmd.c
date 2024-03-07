/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arry_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:09:45 by javgao            #+#    #+#             */
/*   Updated: 2024/03/07 01:26:05 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//将comand 和后面的flag 合并在一起 并将修改作用到原来的数组中 无泄漏
static void	args_merge_cmds(char ***args, int keep_ori)
{
	int		i;
	char	*tem;
	char	*tem_join;

	i = 0;
	if (!*args || !**args)
		return ;
	while ((*args)[i])
	{
		if (i > 0 && (*args)[i][0] == '-' && (*args)[i - 1])
		{
			tem = (*args)[i - 1];
			tem_join = ft_strjoin (" ", (*args)[i]);
			(*args)[i - 1] = ft_strjoin (tem, tem_join);
			free (tem);
			free (tem_join);
			if (keep_ori == TRUE)
				arry_del (args, i);
			i --;
		}
		i ++;
	}
}

//这里传入的args必须是已经删除了输入重定向和输出重定向的二维数组, 输出一个单纯的有命令和flag还有管道符组成的数组
char	**args_to_cmds(char ***args)
{
	char	**new;
	int		i;

	new = NULL;
	i = 1;
	if (!*args || !**args)
		return (NULL);
	args_merge_cmds (args, TRUE);
	arry_add (&new, (*args)[0]);
	while ((*args)[i])
	{
		if (is_strsame ((*args)[i], "|") && (*args)[i + 1])
		{
			arry_add (&new, "|");
			arry_add (&new, (*args)[i + 1]);
		}
		i ++;
	}
	return (new);
}

//计算ori_arg中要分割成几个二维数组
int	count_args(char **args)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	//printf ("========这是计算没有cmd但是有管道符号的数组中 我们总共要分成多少个二位数组的函数\n");
	if (!args || !*args)
		return (n);
	while (args[i])
	{
		if (is_strsame (args[i], PIPES))
			n ++;
		i ++;
	}
	//printf ("========这是计算没有cmd但是有管道符号的数组中 我们总共要分成多少个二位数组的函数: %d\n", n);
	return (n);
}

void	argss_display(char ***args)
{
	int i;

	i = 0;
	if(!args || !*args)
		return ;
	while (args[i])
	{
		arry_display (args[i]);
		i ++;
	}
}

//传入合并命令后的ori数组 一般在用完args_to_cmd后使用, 我们会得到去掉simple command后的ori_args数组
void	args_no_cmds(char ***args)
{
	int	i;

	i = 0;
	if (!*args || !**args)
	{
		printf ("nulll!!!!!\n");
		return ;
	}
	//printf ("这是没有命令的数组内部， 下面我们先打印传入的参数看看如何\n");
	arry_display (*args);
	//printf ("上面就是我们传入args no cmd的数组\n");
	if ((*args)[0] && !is_strsame ((*args)[0], PIPES))
		arry_del (args, 0);
	//printf ("如果第一个元素存在而且， 第一个元素不为管道符号， 我们已经执行了删除操作\n");
	while (*args && (*args)[i] && arry_count (*args))
	{
		if (is_strsame ((*args)[i], PIPES) && (*args)[i + 1]
			&& !is_strsame ((*args)[i + 1], PIPES))
			arry_del (args, i + 1);
		i ++;
	}
	//printf ("这意味着no cmd函数已经结束, 我们从这里退出这个函数\n");
}

//根据没有基础命令的数组进行参数的获取, 生成二维数组, 每获取一个数据就会删除一个数据
char	**get_args(char ***args)
{
	char	**new;

	new = NULL;
	if (!*args || !**args)
		return (arry_add(&new, "NULL"), new);
	if ((*args)[0] && is_strsame ((*args[0]), PIPES))
	{
		arry_del (args, 0);
		arry_add(&new, "NULL");
		return (new);
	}
	while ((*args)[0] && !is_strsame ((*args[0]), PIPES))
	{
		arry_add (&new, (*args)[0]);
		arry_del (args, 0);
		if (is_strsame ((*args[0]), PIPES))
		{
			arry_del (args, 0);
			break ;
		}
	}
	return (new);
	// if ((*args)[0] && is_strsame ((*args)[0], PIPES))
	// {
	// 	arry_add (&new, "NULL");
	// 	arry_del (args, 0);
	// 	return (new);
	// }
	
}

//销毁三维数组
void	argss_destory(char ***argss)
{
	int	i;

	i = 0;
	if (!argss || !*argss)
		return ;
	while (argss[i])
	{
		arry_destory (argss[i]);
		i ++;
	}
	free (argss);
}

//这个函数是用来将没有基础命令且包含管道符号的数组进行处理, 并根据index返回一个三维数组, 每个数组都是对应命令的参数
char	***args_to_args(char ***args)
{
	char	***new;
	int		i;
	int		len;

	if (!*args || !**args)
		return (NULL);
	//printf ("**这是args转换函数的开始 我们先输出看看这个函数存储的东西\n");
	//arry_display (*args);
	//printf ("**这是args转换函数的内部 我们刚刚结束了传入参数的打印\n\n");
	new = NULL;
	i = 0;
	//printf ("这是args转换函数的内部 我们下面运行去掉参数中命令的函数\n");
	args_no_cmds (args);
	//arry_display (*args);
	//printf ("这是args转换函数的内部 我们已经结束了no cmd函数的运行 下面我们计算转换函数结束后的数组长度\n\n");
	len = count_args (*args);
	//printf ("这是args转换函数的内部 我们已经求出了no cmd函数运行后的数组长度为 》 %d\n", len);
	if (!*args || len == 0)
		return (NULL);
	new = malloc (sizeof (char **) * (len + 1));
	while (i < len)
		new[i++] = NULL;
	i = 0;
	while (i < len)
	{
		new[i] = get_args (args);
		i ++;
	}
	// i = 0;
	// while (i < len)
	// {
	// 	printf ("\n+++++++++我们下面输出一下我们生成的arg数组++++++++++[%d]:\n", i);
	// 	arry_display (new[i]);
	// 	i ++;
	// }
	return (new);
}
