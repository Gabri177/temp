#include "../../include/parser.h"

//初始化字符串数组, 让每个元素都指向NULL
static void	arry_init(char **ary, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ary[i] = NULL;
		i ++;
	}
}

//计算字符串数组的大小, 因为字符串数组的结尾元素是NULL, 用来判断是否已经结束
static int	arry_count(char **arys)
{
	int	i;

	i = 0;
	if (!arys)
		return (0);
	while (arys[i])
		i ++;
	return (i);
}

//我们这个函数不单单是对原字符串数组的拷贝, 我们申请多一个空间, 然后将原来的字符串数组销毁
static char	**arry_cpy(char **ary) // size + 1
{
	int		i;
	char	**new;

	i = 0;
	new = malloc (sizeof (char *) * (arry_count (ary) + 2));
	if (!new)
		return (NULL);
	arry_init (new, (arry_count (ary) + 2));
	while (i < arry_count (ary))
	{
		new[i] = strdup (ary[i]);
		i ++;
	}
	arry_destory (ary);
	return (new);
}

//给字符串数组arys添加新的字符串元素val, 我们通过复制函数扩容1个单位, 然后加入新元素
//在复制函数中我们销毁了复制之前的字符串数组, 我们释放了内存
//在使用这个函数前 要先创建一个char**类型的指针并初始化
int	arry_add(char ***arys, char *val)
{
	int	i;

	i = 0;
	if (!*arys)
	{
		*arys = malloc (sizeof (char *) * 2);
		if (!*arys)
			return (FALSE);
		(*arys)[0] = strdup (val);
		(*arys)[1] = NULL;
		return (TRUE);
	}
	*arys = arry_cpy (*arys);
	while ((*arys)[i])
		i ++;
	(*arys)[i] = strdup (val);
	return (TRUE);
}
