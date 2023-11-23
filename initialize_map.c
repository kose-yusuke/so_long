
#include "so_long.h"
//filepathを受け取って, readする


size_t count_rows(char *map_filepath)
{
	int fd;
	size_t count_row;
	char *row;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
	{
		return (0);
	}
	count_row = 0;
	while(true)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		free(row);
		row = NULL;
		count_row++;
	}
	close(fd);
	return(count_row);
}

char **read_ber_file(t_manager *mgr, char *map_filepath)
{
	char **grid;
	char *row;
	int fd;
	size_t row_idx;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
    mgr->maps.row = count_rows(map_filepath);
	grid = (char **)ft_calloc(mgr->maps.row + 1, sizeof(char *));
	if (!grid)
		return NULL;
    row_idx = 0;
	while (row_idx < mgr->maps.row)
	{
		row = get_next_line(fd);
		grid[row_idx] = row;
        if (row_idx == 0)
            mgr->maps.column = ft_strlen_s(row) - 1;
		row = NULL;
		row_idx++;
	}
	close(fd);
	return (grid);
}
