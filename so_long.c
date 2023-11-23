#include "so_long.h"

//リーク処理

int	main(int argc, char **argv)
{
	t_manager mgr;

	mgr.collect_flag = 0;
	mgr.move_count = 0;
	mgr.char_counters.player_counter = 0;
	mgr.char_counters.collect_counter = 0;
	mgr.char_counters.exit_counter = 0;
	if (argc != 2)
		return (0);
	//berの情報を取得して, gridに読み込む
	mgr.maps.grid = read_ber_file(&mgr, argv[1]);
	if (!mgr.maps.grid)
		return (0);
	if (!is_square_wall(&mgr))
	{
		return (0);
	}
	mgr.mlx = mlx_init();
	mgr.win = mlx_new_window(mgr.mlx, 500, 500, WINDOW_NAME);

	//xpmファイルを読み込んでmgrに格納する.
	ft_read_management(&mgr);

	//画面にmapを並べる
	if(!ft_render_map(&mgr))
		return (0);

	mlx_hook(mgr.win, ON_KEYDOWN, 1L << 0, ft_event_handler, &mgr);
	mlx_hook(mgr.win, ON_DESTROY, 1L << 17, ft_close, &mgr);
	mlx_loop_hook(mgr.mlx, ft_refresh_map, &mgr);
	mlx_loop(mgr.mlx);
	return (0);
}