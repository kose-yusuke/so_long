/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:36:25 by ykoseki           #+#    #+#             */
/*   Updated: 2024/03/02 17:36:50 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_update_render_map(t_manager *mgr)
{
	int	row_idx;
	int	column_idx;

	row_idx = 0;
	while (row_idx < mgr->maps.row)
	{
		column_idx = 0;
		while (column_idx < mgr->maps.column)
		{
			ft_update_put_map(mgr, row_idx, column_idx);
			column_idx++;
		}
		row_idx++;
	}
	return (0);
}
