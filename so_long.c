/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:27:28 by koseki.yusu       #+#    #+#             */
/*   Updated: 2023/11/26 17:28:06 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

int ft_error_message_handler(char *message)
{
	ft_printf("%s\n",message);
	return (0);
}

char **ft_error_message_handler_null(char *message)
{
	ft_printf("%s\n",message);
	return (NULL);
}

void ft_init(t_manager *mgr, char* map_filepath)
{
	mgr->collect_flag = 0;
	mgr->move_count = 0;
	mgr->char_counters.player_counter = 0;
	mgr->char_counters.collect_counter = 0;
	mgr->char_counters.exit_counter = 0;
	mgr->maps.row = count_rows(mgr, map_filepath);
}

int ft_init_render(t_manager *mgr)
{
	mgr->mlx = mlx_init();
	mgr->win = mlx_new_window(mgr->mlx, 500, 500, WINDOW_NAME);

	ft_read_management(mgr);
	if(!ft_render_map(mgr))
		return (0);
	mlx_hook(mgr->win, ON_KEYDOWN, 1L << 0, ft_event_handler, mgr);
	mlx_hook(mgr->win, ON_DESTROY, 1L << 17, ft_close, mgr);
	mlx_loop_hook(mgr->mlx, ft_update_render_map, mgr);
	mlx_loop(mgr->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_manager mgr;

	ft_init(&mgr, argv[1]);	
	if (argc != 2)
		return (ft_error_message_handler("Error\nInvalid argument number"));
	mgr.maps.grid = read_ber_file(&mgr, argv[1]);
	if (!mgr.maps.grid)
		return(ft_error_message_handler("Error\nCreating grid is Failed"));
	mgr.maps.dfs_map = read_ber_file_for_dfs(&mgr, argv[1]);
	if (!mgr.maps.dfs_map)
		return(ft_error_message_handler("Error\nCreating dfs_map is Failed"));
	if (!is_square_wall(&mgr))
		return (ft_error_message_handler("Error\nMap must be enclosed in a wall"));
	if (!is_possible_goal(&mgr, mgr.player_pos.x_pos, mgr.player_pos.y_pos))
		return (ft_error_message_handler("Error\nMap must be able to goal"));
	ft_clean_dfs_map(&mgr, argv[1]);
	if (!is_possible_collectible_manager(&mgr, argv[1]))
		return (ft_error_message_handler("Error\nMap must be collectable to goal"));
	ft_init_render(&mgr);
	return (0);
}

// //リーク処理をしよう
// //テスター通す
// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q so_long");
// }
