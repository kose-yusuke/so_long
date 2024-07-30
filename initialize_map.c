/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:02:56 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/03/06 20:37:01 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//count rows of map
size_t	count_rows(t_manager *mgr, char *map_filepath)
{
	int		fd;
	int		count_row;
	char	*row;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
		return (0);
	count_row = 0;
	while (true)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		if (count_row == 0)
			mgr->maps.column = ft_strlen_s(row) - 1;
		free(row);
		row = NULL;
		count_row++;
		if (count_row > 94 || mgr->maps.column > 43)
			return (ft_error_message_handler("Error\nToo Big."));
	}
	close(fd);
	return (count_row);
}

//check weather valid char is used
int	is_valid_char(char c)
{
	return (c == WALL || c == EMPTY || c == PLAYER || c == EXIT
		|| c == COLLECTABLE);
}

//check valid char and valid number
int	ft_c_checker(t_manager *mgr, char **grid, size_t row_idx, int count)
{
	while (count > 0)
	{
		if (grid[row_idx][count - 1] == 'P')
		{
			mgr->char_counters.player_counter++;
			if (mgr->char_counters.player_counter >= 2)
				return (ft_error_message_handler("Error\nInvalid Playernumber"));
			mgr->player_pos.x_pos = count - 1;
			mgr->player_pos.y_pos = row_idx;
		}
		else if (grid[row_idx][count - 1] == 'E')
		{
			mgr->char_counters.exit_counter++;
			if (mgr->char_counters.exit_counter >= 2)
				return (ft_error_message_handler("Error\nInvalid Exit number"));
			mgr->exit_pos.x_pos = count - 1;
			mgr->exit_pos.y_pos = row_idx;
		}
		else if (grid[row_idx][count - 1] == 'C')
			mgr->char_counters.collect_counter++;
		if (!is_valid_char(grid[row_idx][count - 1]))
			return (ft_error_message_handler("Error\nInvalid char in the map"));
		count--;
	}
	return (1);
}

//read ber file
char	**read_ber_file(t_manager *mgr, char *map_filepath)
{
	char	**grid;
	char	*row;
	int		fd;
	int		row_idx;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
		return (ft_error_message_handler_null("Error\nfile can't open"));
	grid = (char **)ft_calloc(mgr->maps.row + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	row_idx = 0;
	while (row_idx < mgr->maps.row)
	{
		row = get_next_line(fd);
		grid[row_idx] = row;
		if (!ft_c_checker(mgr, grid, row_idx, mgr->maps.column) || *row == '\n')
			return (NULL);
		row = NULL;
		row_idx++;
	}
	if (!ft_count_pec(mgr))
		return (NULL);
	close(fd);
	return (grid);
}

//read ber file for dfs grid
char	**read_ber_file_for_dfs(t_manager *mgr, char *map_filepath)
{
	char	**grid;
	char	*row;
	int		fd;
	int		row_idx;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	grid = (char **)ft_calloc(mgr->maps.row + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	row_idx = 0;
	while (row_idx < mgr->maps.row)
	{
		row = get_next_line(fd);
		grid[row_idx] = row;
		if (row_idx == 0)
			mgr->maps.column = ft_strlen_s(row) - 1;
		row = NULL;
		row_idx++;
	}
	close(fd);
	return (grid);
}
