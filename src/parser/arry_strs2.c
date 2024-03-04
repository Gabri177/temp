#include "../../include/parser.h"

//释放字符串数组申请的内存, 包括每个元素和字符串数组的本身
void	arry_destory(char **ary)
{
	int	i;

	i = 0;
	if (!ary || !*ary)
		return ;
	while (ary[i])
	{
		free (ary[i]);
		i ++;
	}
	free (ary);
}

//输出ary这个字符串数组的元素值
void	arry_display(char **ary)
{
	int	i;

	i = 0;
	if (!ary || !*ary)
		return ;
	printf ("Argumentos Splited: {");
	while (ary[i])
	{
		printf ("\"%s\"", ary[i]);
		i ++;
		if (ary[i])
			printf (", ");
	}
	printf ("}\n");
}

//如果val这个字符串不为空, 我们把他加入到字符串数组arys中, 并释放val内存, 让其指向NULL
void	arry_refresh(char ***arys, char **val)
{
	if (!val || !*val || !arys || !*arys)
		return ;
	arry_add (arys, *val);
	free (*val);
	*val = NULL;
}
