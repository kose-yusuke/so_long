/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:27:28 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/03/06 20:38:35 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_init(t_manager *mgr, char *map_filepath)
{
	mgr->collect_flag = 0;
	mgr->move_count = 0;
	mgr->char_counters.player_counter = 0;
	mgr->char_counters.collect_counter = 0;
	mgr->char_counters.exit_counter = 0;
	mgr->maps.row = count_rows(mgr, map_filepath);
	if (mgr->maps.row < 1)
		return (ft_error_message_handler("Error\nThere are no file or empty"));
	return (1);
}

int	ft_init_render(t_manager *mgr)
{
	mgr->mlx = mlx_init();
	mgr->win = mlx_new_window(mgr->mlx, mgr->maps.column * 32,
			mgr->maps.row * 32, WINDOW_NAME);
	ft_read_management(mgr);
	if (!ft_render_map(mgr))
		return (0);
	mlx_hook(mgr->win, ON_KEYDOWN, 1L << 0, ft_event_handler, mgr);
	mlx_hook(mgr->win, ON_DESTROY, 1L << 17, ft_close, mgr);
	mlx_loop_hook(mgr->mlx, ft_update_render_map, mgr);
	mlx_loop(mgr->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_manager	mgr;

	if (argc != 2)
		return (ft_error_message_handler("Error\nInvalid argument number"));
	if (!ft_ber_checker(argv[1]))
		return (0);
	if (!ft_init(&mgr, argv[1]))
		return (0);
	mgr.maps.grid = read_ber_file(&mgr, argv[1]);
	if (!mgr.maps.grid)
		return (ft_error_message_handler("Error\nCreating grid is Failed"));
	mgr.maps.dfs_map = read_ber_file_for_dfs(&mgr, argv[1]);
	if (!mgr.maps.dfs_map)
		return (ft_error_message_handler("Error\nCreating dfs_map is Failed"));
	if (!is_square_wall(&mgr))
		return (ft_error_message_handler("Error\nMap must be closed by wall"));
	if (!is_possible_goal(&mgr, mgr.player_pos.x_pos, mgr.player_pos.y_pos))
		return (ft_error_message_handler("Error\nMap must be able to goal"));
	ft_clean_dfs_map(&mgr, argv[1]);
	if (!is_possible_collectible_manager(&mgr, argv[1]))
		return (ft_error_message_handler("Error\nMap must be collectable"));
	ft_init_render(&mgr);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q so_long");
// }
