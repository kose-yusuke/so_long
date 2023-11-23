
#include "so_long.h"

int ft_close(t_manager *mgr)
{
	mlx_destroy_window(mgr->mlx, mgr->win);
	return (0);
}

