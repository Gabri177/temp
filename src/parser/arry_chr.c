#include "../../include/parser.h"

//这是一个创建字符串的文件, 初始化以后, 可以不断添加单个字符, 长度自动扩张.
int	chr_add(char **chrs, char c)
{
	char	*tem;

	if (!*chrs)
	{
		*chrs = malloc (sizeof (char) * 2);
		if (!*chrs)
			return (FALSE);
		(*chrs)[0] = c;
		(*chrs)[1] = '\0';
		return (TRUE);
	}
	tem = malloc (sizeof (char) * (strlen (*chrs) + 2));
	if (!tem)
		return (FALSE);
	strcpy (tem, *chrs);
	tem[strlen (*chrs)] = c;
	tem[strlen(*chrs) + 1] = '\0';
	free (*chrs);
	*chrs = tem;
	return (TRUE);
}

//处理大于号 小于号和 管道符号情况
void	is_chr_special(char c, char ***new_args, char **new_arg)
{
	if (c == LINE || c == BIG || c == LIT)
	{
		if (*new_arg)
			arry_add (new_args, *new_arg);
		if (c == LINE)
			arry_add (new_args, LINES);
		if (c == BIG)
			arry_add (new_args, BIGS);
		if (c == LIT)
			arry_add (new_args, LITS);
		free (*new_arg);
		*new_arg = NULL;
	}
}

void	is_chr_quote(char **c, char ***new_args, char **new_arg)
{
	char	mark;

	if (**c == QUOTE_LIT)
		mark = QUOTE_LIT;
	if (**c == QUOTE_BIG)
		mark = QUOTE_BIG;
	if (**c == mark)
	{
		arry_refresh (new_args, new_arg);
		arry_display (*new_args);//delel
		if (mark == QUOTE_BIG)
			chr_add (new_arg, **c);//这里我加上了引号
		(*c) += 1;
		while (**c != mark && **c)
		{
			chr_add (new_arg, **c);
			(*c) += 1;
		}
		if (mark == QUOTE_BIG)
			chr_add (new_arg, **c);//这里我加上了引号
		arry_refresh (new_args, new_arg);
		(*c) += 1;
	}
}

void	split_args(char ***args, char *ori) //没有检查是否有括号匹配的机制 这个不应该是这个函数的工作
{
	char		*tem;
	static char	*new_arg;
	static char	**new_args;

	if (!ori || !*ori)
	{
		printf ("NULL\n");
		return ;
	}
	tem = ft_strtrim (ori, " ");
	//free(ori);
	printf ("tem : ==%s==\n", tem);
	while (*tem)
	{
		printf ("new_arg : ==%s==\n", new_arg);
		if (*tem == ' ' && new_arg)
		{
			arry_refresh (&new_args, &new_arg);
			printf ("space\n");
			while (*tem && *tem == ' ')
				tem ++;
		}
		is_chr_special (*tem, &new_args, &new_arg);
		is_chr_quote (&tem, &new_args, &new_arg);
		if (*tem != ' ' && *tem != '|' && *tem != '>' && *tem != '<' && *tem != QUOTE_BIG && *tem != QUOTE_LIT)
			chr_add (&new_arg, *tem);
		tem ++;
	}
	arry_refresh (&new_args, &new_arg);
	*args = new_args;
	new_args = NULL;
}
