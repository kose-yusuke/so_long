/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:07:00 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/03/06 17:05:29 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//check rectangular and wall closed and not irregular kaigyo
int	is_square_wall(t_manager *mgr)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (mgr->maps.row > y)
	{
		if (mgr->maps.grid[y][0] != '1' || mgr->maps.grid[y][mgr->maps.column
			- 1] != '1')
			return (0);
		y++;
	}
	while (mgr->maps.column > x)
	{
		if (mgr->maps.grid[0][x] != '1' || mgr->maps.grid[mgr->maps.row
			- 1][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

//init dfs_map
int	ft_clean_dfs_map(t_manager *mgr, char *map_filepath)
{
	int	i;

	i = 0;
	while (i < mgr->maps.row)
	{
		free(mgr->maps.dfs_map[i]);
		i++;
	}
	free(mgr->maps.dfs_map);
	mgr->maps.dfs_map = read_ber_file_for_dfs(mgr, map_filepath);
	return (1);
}

int	is_possible_collectible_manager(t_manager *mgr, char *map_filepath)
{
	int	i;
	int	j;

	i = 0;
	while (i < mgr->maps.row)
	{
		j = 0;
		while (j < mgr->maps.column)
		{
			if (mgr->maps.grid[i][j] == 'C')
			{
				mgr->collect_pos.x_pos = j;
				mgr->collect_pos.y_pos = i;
				if (!is_possible_collectible(mgr, mgr->player_pos.x_pos,
						mgr->player_pos.y_pos))
					return (0);
				ft_clean_dfs_map(mgr, map_filepath);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// use dfs to check it's possible to collect
int	is_possible_collectible(t_manager *mgr, int x, int y)
{
	if (x == mgr->collect_pos.x_pos && y == mgr->collect_pos.y_pos)
		return (1);
	if (mgr->maps.dfs_map[y][x] == '1')
		return (0);
	mgr->maps.dfs_map[y][x] = '1';
	if (is_possible_collectible(mgr, x + 1, y)
		|| is_possible_collectible(mgr, x - 1, y)
		|| is_possible_collectible(mgr, x, y + 1)
		|| is_possible_collectible(mgr, x, y - 1))
		return (1);
	return (0);
}

// use dfs to check it's possible to exit
int	is_possible_goal(t_manager *mgr, int x, int y)
{
	if (mgr->maps.grid[y][x] == 'E')
		return (1);
	if (mgr->maps.dfs_map[y][x] == '1')
		return (0);
	mgr->maps.dfs_map[y][x] = '1';
	if (is_possible_goal(mgr, x + 1, y) || is_possible_goal(mgr, x - 1, y)
		|| is_possible_goal(mgr, x, y + 1) || is_possible_goal(mgr, x, y - 1))
		return (1);
	return (0);
}
