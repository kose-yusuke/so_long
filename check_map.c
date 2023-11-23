
#include "so_long.h"

//rectangular and wall closed
int is_square_wall(t_manager *mgr)
{
    size_t x;
    size_t y;

    x = 0;
    y = 0;
    while (mgr->maps.row > y)
    {
        if (mgr->maps.grid[y][0] != '1' || mgr->maps.grid[y][mgr->maps.column - 1] != '1')
            return (0);
        y++;
    }
    while (mgr->maps.column > x)
    {
        if (mgr->maps.grid[0][x] != '1' || mgr->maps.grid[mgr->maps.row - 1][x] != '1')
            return (0);
        x++;
    }
    return (1);
}

//ゴールにたどり着く方法がなかったらエラーを吐く

//複数のcollectの場合に, emptyに変換するすべがない.
//Error\nの後、任意のエラーメッセージを吐く