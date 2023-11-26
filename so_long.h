/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:27:11 by ykoseki           #+#    #+#             */
/*   Updated: 2023/11/26 11:37:46 by koseki.yusu      ###   ########.fr       */
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

//png size 30*30
# define SQUARE_SIZE 32
# define WINDOW_NAME	"so_long"

//texture path
# define EMPTY_PATH "./textures/grass.xpm"
# define EMPTY2_PATH "./textures/shinji.xpm"
# define WALL_PATH "./textures/wall2.xpm"
# define WALL2_PATH "./textures/seele.xpm"
# define PLAYER1_PATH "./textures/gendou.xpm"
# define PLAYER2_PATH "./textures/player2.xpm"
# define ENEMY_PATH "./textures/enemy.xpm"
# define COLLECT_PATH "./textures/collect.xpm"
# define EXIT_PATH "./textures/exit.xpm"
# define BEAM_PATH "./textures/beam.xpm"

//valid char
#define WALL '1'
#define EMPTY '0'
#define PLAYER 'P'
#define EXIT 'E'
#define COLLECTABLE 'C'

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

typedef struct s_maps {
	char 	**grid;
	char **dfs_map;
	int 	row;
	int 	column;
}				t_maps;

typedef struct s_textures
{
	void *wall;
	void *empty;
	void *player;
	void *enemy;
	void *collect;
}				t_textures;

typedef struct s_pos
{
	int x_pos;
	int y_pos;
}				t_pos;

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
	t_pos 	player_pos;
	t_pos 	exit_pos;
	t_textures  	textures;
	t_maps			maps;
	t_char_counters char_counters;
	int collect_flag;
	int move_count;
}               t_manager;


int ft_close(t_manager *mgr);
size_t count_rows(t_manager *mgr, char *map_filepath);
char **read_ber_file(t_manager *mgr, char *map_filepath);
void ft_create_map(t_manager *mgr, char *map_filepath);
void ft_read_xpmfile(t_manager *mgr, int idx);
void ft_put_image(void *img, t_maps *maps);
void ft_read_management(t_manager *mgr);
int ft_init_put_map(t_manager *mgr, int y, int x);
int ft_render_map(t_manager *mgr);
int	ft_event_handler(int keycode, t_manager *mgr);
void ft_update_put_map(t_manager *mgr, int y, int x);
int ft_update_render_map (t_manager *mgr);
int ft_move_player(int keycode, t_manager *mgr);
void	ft_update_position(t_manager *mgr, int x, int y);
int is_square_wall(t_manager *mgr);
int is_possible_goal(t_manager *mgr, int x, int y);
int ft_error_message_handler(char *message);
char **ft_error_message_handler_null(char *message);
char **read_ber_file_for_dfs(t_manager *mgr, char *map_filepath);
int is_possible_collectible_manager(t_manager *mgr, char *map_filepath);
int ft_clean_dfs_map(t_manager *mgr, char *map_filepath);
int is_possible_collectible(t_manager *mgr, int x, int y, int collect_pos_x, int collect_pos_y);
void ft_init(t_manager *mgr, char* map_filepath);
int ft_init_render(t_manager *mgr);

#endif