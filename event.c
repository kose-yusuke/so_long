
#include "so_long.h"

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

int ft_event_handler(int keycode, t_manager *mgr)
{
    if (keycode == ESC)
        ft_close(mgr);
    else
        ft_move_player(keycode, mgr);
    return (0);
}

void	ft_update_position(t_manager *mgr, size_t x, size_t y)
{
	if (mgr->maps.grid[y][x] != '1')
	{
        mgr->player_pos.x_pos = x;
		mgr->player_pos.y_pos = y;
        mgr->move_count++;
        printf("Move: %zu\n", mgr->move_count);
    }
    
}

int ft_refresh_map(t_manager *mgr)
{
    ft_update_render_map(mgr);
    return (0);
}

