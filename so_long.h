/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:27:11 by ykoseki           #+#    #+#             */
/*   Updated: 2023/11/20 19:50:05 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
#include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <sys/errno.h>
# include <stdio.h>
#include <fcntl.h>

//png size 30*24
# define SQUARE_SIZE 32
# define WINDOW_NAME	"so_long"
# define EMPTY_PATH "./textures/grass.xpm"
# define EMPTY2_PATH "./textures/shinji.xpm"
# define WALL_PATH "./textures/wall.xpm"
# define WALL2_PATH "./textures/seele.xpm"
# define PLAYER1_PATH "./textures/player.xpm"
# define PLAYER2_PATH "./textures/player2.xpm"
# define ENEMY_PATH "./textures/enemy.xpm"
# define COLLECT_PATH "./textures/collect.xpm"
# define EXIT_PATH "./textures/exit.xpm"
# define BEAM_PATH "./textures/beam.xpm"

typedef enum e_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}					t_event;

typedef enum e_keycode
{
	ESC = 65307,
	UP = 119,
	DOWN = 115,
	LEFT = 97,
	RIGHT = 100
}				t_keycode;

// typedef

typedef struct s_maps {
	char 	**grid;
	size_t 	row;
	size_t 	column;
}				t_maps;

typedef struct s_textures
{
	void *wall;
	void *empty;
	void *player;
	void *enemy;
	void *collect;
}				t_textures;

typedef struct s_player_pos
{
	size_t x_pos;
	size_t y_pos;
}				t_player_pos;

typedef struct s_char_counters
{
	int player_counter;
	int collect_counter;
	int exit_counter;
}				t_char_counters;

typedef struct s_manager
{
    void *mlx;
	void *win;
	t_player_pos 	player_pos;
	t_textures  	textures;
	t_maps			maps;
	int collect_flag;
	size_t move_count;
	t_char_counters char_counters;
}               t_manager;


int ft_close(t_manager *mgr);
size_t count_rows(char *map_filepath);
char **read_ber_file(t_manager *mgr, char *map_filepath);
void ft_create_map(t_manager *mgr, char *map_filepath);
void ft_read_xpmfile(t_manager *mgr, size_t idx);
void ft_put_image(void *img, t_maps *maps);
void ft_read_management(t_manager *mgr);
int ft_init_put_map(t_manager *mgr, size_t y, size_t x);
int ft_render_map(t_manager *mgr);
int	ft_event_handler(int keycode, t_manager *mgr);
void ft_update_put_map(t_manager *mgr, size_t y, size_t x);
void ft_update_render_map (t_manager *mgr);
int ft_refresh_map(t_manager *mgr);
int ft_move_player(int keycode, t_manager *mgr);
void	ft_update_position(t_manager *mgr, size_t x, size_t y);
int is_square_wall(t_manager *mgr);



#endif