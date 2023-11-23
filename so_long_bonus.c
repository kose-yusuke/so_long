#include "mlx.h"
#include "so_long.h"

// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// }				t_vars;

// int	render_next_frame(void *YourStruct);

// int	main(void)
// {
// 	void	*mlx;
// 	void *win;
//     void *img;
//     int img_width;
//     int img_height;
// 	// t_vars	vars;
// 	// 引数の数でエラー処理する
// 	// 構造体で初期化する
// 	// マップ情報をファイルから読み込む
// 	// マップをいろいろやる
// 	// loopしたりする
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 1000, 1000, "test");
//     img = mlx_xpm_file_to_image(mlx, "ground.xpm", &img_width, &img_height);
//     printf("img:%p\n", img);
//     printf("width:%d\n", img_width);
//     printf("heigh:%d\n", img_height);
//     mlx_put_image_to_window(mlx, win, img, 0, 0);
// 	// mlx_loop_hook(mlx, render_next_frame, &vars);
// 	mlx_loop(mlx);
// }

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}