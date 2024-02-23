/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:42:17 by yugao             #+#    #+#             */
/*   Updated: 2024/02/23 19:36:38 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	info_init(t_data *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, info->win_x,
			info->win_y, "MinilibX Window");
	info->ctr_x = 0;
	info->ctr_y = 0;
	info->img_x = 50;
	info->img_y = 50;
	info->img_bk = mlx_xpm_file_to_image (info->mlx,
			IMAG_BK, &info->img_x, &info->img_y);
	info->img_ctr = mlx_xpm_file_to_image (info->mlx,
			IMAG_CTR, &info->img_x, &info->img_y);
	info->img_wal = mlx_xpm_file_to_image (info->mlx,
			IMAG_WAL, &info->img_x, &info->img_y);
	info->img_exit = mlx_xpm_file_to_image (info->mlx,
			IMAG_EXIT, &info->img_x, &info->img_y);
	info->img_coin = mlx_xpm_file_to_image (info->mlx,
			IMAG_COIN, &info->img_x, &info->img_y);
	if (!info->img_bk || !info->img_ctr || !info->img_wal
		|| !info->img_exit || !info->img_coin)
		e_exit (ERR_IMG);
	info->n_mov = -1;
}

int	key_hook(int key, void *param)
{
	t_data	*info;

	info = (t_data *)param;
	if (key == 13 || key == 126)
		dw_mov(info, info->ctr_x, info->ctr_y - 1, &info->mrx);
	if (key == 1 || key == 125)
		dw_mov(info, info->ctr_x, info->ctr_y + 1, &info->mrx);
	if (key == 0 || key == 123)
		dw_mov(info, info->ctr_x - 1, info->ctr_y, &info->mrx);
	if (key == 2 || key == 124)
		dw_mov(info, info->ctr_x + 1, info->ctr_y, &info->mrx);
	if (key == 53)
		s_exit (SCS_EXE);
	return (0);
}

int	cls_win(void *param)
{
	(void)param;
	s_exit (SCS_EXE);
	return (0);
}

static void	invalid_line_check(int fd)
{
	char	*line;

	line = get_next_line (fd);
	if (!line)
		e_exit (ERR_RED);
	while (*line == '\n')
		line = get_next_line (fd);
	while (line && *line != '\n')
		line = get_next_line (fd);
	while (line)
	{
		if (*line != '\n')
			e_exit (ERR_MAP);
		line = get_next_line (fd);
	}
	close (fd);
}

int	main(int arc, char **argv)
{
	t_data	info;

	if (arc != 2)
		e_exit (ERR_ARG);
	if (!ft_strnstr (argv[1], ".ber", ft_strlen (argv[1])))
		e_exit (ERR_ARG);
	invalid_line_check (r_fd (argv[1]));
	r_size (&info, r_fd (argv[1]));
	info_init (&info);
	m_init (&info.mrx, info);
	r_to_mrx (&info, r_fd (argv[1]), &info.mrx);
	dw_mov(&info, info.ctr_x, info.ctr_y, &info.mrx);
	mlx_key_hook (info.win, key_hook, (void *)&info);
	mlx_hook (info.win, 17, 0, cls_win, NULL);
	mlx_loop (info.mlx);
	return (0);
}
