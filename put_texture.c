/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:27:17 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/03/02 17:36:46 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_read_management(t_manager *mgr)
{
	int	idx;

	idx = 1;
	while (idx < 6)
	{
		ft_read_xpmfile(mgr, idx);
		idx++;
	}
}

void	ft_read_xpmfile(t_manager *mgr, int idx)
{
	int	img_width;
	int	img_height;

	if (idx == 1)
	{
		mgr->textures.wall = mlx_xpm_file_to_image(mgr->mlx, WALL_PATH,
				&img_width, &img_height);
	}
	else if (idx == 2)
		mgr->textures.empty = mlx_xpm_file_to_image(mgr->mlx, EMPTY2_PATH,
				&img_width, &img_height);
	else if (idx == 3)
		mgr->textures.player = mlx_xpm_file_to_image(mgr->mlx, PLAYER1_PATH,
				&img_width, &img_height);
	else if (idx == 4)
		mgr->textures.enemy = mlx_xpm_file_to_image(mgr->mlx, EXIT_PATH,
				&img_width, &img_height);
	else if (idx == 5)
		mgr->textures.collect = mlx_xpm_file_to_image(mgr->mlx, COLLECT_PATH,
				&img_width, &img_height);
}

int	ft_init_put_map(t_manager *mgr, int y, int x)
{
	if (mgr->maps.grid[y][x] == '1')
		mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.wall, x
			* SQUARE_SIZE, y * SQUARE_SIZE);
	else if (mgr->maps.grid[y][x] == 'P')
	{
		mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.player, x
			* SQUARE_SIZE, y * SQUARE_SIZE);
		mgr->maps.grid[y][x] = '0';
	}
	else if (mgr->maps.grid[y][x] == '0')
		mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.empty, x
			* SQUARE_SIZE, y * SQUARE_SIZE);
	else if (mgr->maps.grid[y][x] == 'E')
	{
		mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.enemy, x
			* SQUARE_SIZE, y * SQUARE_SIZE);
	}
	else if (mgr->maps.grid[y][x] == 'C')
	{
		mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.collect, x
			* SQUARE_SIZE, y * SQUARE_SIZE);
	}
	return (1);
}

int	ft_render_map(t_manager *mgr)
{
	int	row_idx;
	int	column_idx;

	row_idx = 0;
	while (row_idx < mgr->maps.row)
	{
		column_idx = 0;
		while (column_idx < mgr->maps.column)
		{
			if (!ft_init_put_map(mgr, row_idx, column_idx))
				return (0);
			column_idx++;
		}
		row_idx++;
	}
	return (1);
}

void	ft_update_put_map(t_manager *mgr, int y, int x)
{
	if (mgr->player_pos.x_pos == x && mgr->player_pos.y_pos == y)
	{
		if (mgr->maps.grid[y][x] == 'E'
			&& mgr->char_counters.collect_counter == 0)
		{
			ft_close(mgr);
		}
		mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.player, x
			* SQUARE_SIZE, y * SQUARE_SIZE);
	}
	else
	{
		if (mgr->maps.grid[y][x] == '1')
			mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.wall, x
				* SQUARE_SIZE, y * SQUARE_SIZE);
		else if (mgr->maps.grid[y][x] == '0')
			mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.empty, x
				* SQUARE_SIZE, y * SQUARE_SIZE);
		else if (mgr->maps.grid[y][x] == 'E')
			mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.enemy, x
				* SQUARE_SIZE, y * SQUARE_SIZE);
		else if (mgr->maps.grid[y][x] == 'C' && mgr->collect_flag == 0)
			mlx_put_image_to_window(mgr->mlx, mgr->win, mgr->textures.collect, x
				* SQUARE_SIZE, y * SQUARE_SIZE);
	}
}
