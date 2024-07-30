/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoseki <ykoseki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:42:54 by ykoseki           #+#    #+#             */
/*   Updated: 2024/03/06 20:33:02 by ykoseki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_error_message_handler(char *message)
{
	ft_printf("%s\n", message);
	return (0);
}

char	**ft_error_message_handler_null(char *message)
{
	ft_printf("%s\n", message);
	return (NULL);
}

bool	ft_count_pec(t_manager *mgr)
{
	if (!mgr->char_counters.player_counter || !mgr->char_counters.exit_counter
		|| !mgr->char_counters.collect_counter)
	{
		ft_error_message_handler_null("Error\nOne Player and"
			" one Exit, at least one Collectable, must be in the map");
		return (false);
	}
	else
		return (true);
}

int	ft_ber_checker(char *filename)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_strlen_s(filename);
	j = i - 4;
	tmp = filename;
	while (j)
	{
		tmp++;
		j--;
	}
	if (!(*tmp == '.'))
		return (ft_error_message_handler("Error\nInvalid filename"));
	tmp++;
	if (!(*tmp == 'b'))
		return (ft_error_message_handler("Error\nInvalid filename"));
	tmp++;
	if (!(*tmp == 'e'))
		return (ft_error_message_handler("Error\nInvalid filename"));
	tmp++;
	if (!(*tmp == 'r'))
		return (ft_error_message_handler("Error\nInvalid filename"));
	return (1);
}
