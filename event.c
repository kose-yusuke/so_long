/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:08:40 by koseki.yusu       #+#    #+#             */
/*   Updated: 2023/11/26 17:15:54 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

//when pressed key, player move
int ft_move_player(int keycode, t_manager *mgr)
{
    if (keycode == UP)
        ft_update_position(mgr, mgr->player_pos.x_pos, mgr->player_pos.y_pos - 1);
    else if (keycode == DOWN)
        ft_update_position(mgr, mgr->player_pos.x_pos, mgr->player_pos.y_pos + 1);
    else if (keycode == LEFT)
        ft_update_position(mgr, mgr->player_pos.x_pos - 1, mgr->player_pos.y_pos);
    else if (keycode == RIGHT) 
        ft_update_position(mgr, mgr->player_pos.x_pos + 1, mgr->player_pos.y_pos);
    return (0);
}

//if pressed ESC, window closed
int ft_event_handler(int keycode, t_manager *mgr)
{
    if (keycode == ESC)
        ft_close(mgr);
    else
        ft_move_player(keycode, mgr);
    return (0);
}

//update position of player and update collectible status
void	ft_update_position(t_manager *mgr, int x, int y)
{
	if (mgr->maps.grid[y][x] != '1')
	{
        mgr->player_pos.x_pos = x;
        mgr->player_pos.y_pos = y;
        mgr->move_count++;
        if (mgr->maps.grid[y][x] == 'C')
        {
            mgr->char_counters.collect_counter--;
            mgr->maps.grid[y][x] = '0';
        }
        ft_printf("Move: %d\n", mgr->move_count);
    }
}

//destroy window
int ft_close(t_manager *mgr)
{
	mlx_destroy_window(mgr->mlx, mgr->win);
    exit(0);
}