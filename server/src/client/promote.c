/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 22:01:38 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 20:09:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <string.h>

t_uint		g_promotion_needs[MAX_LEVEL][ITEM_COUNT] = {
	{ 1, 1, 0, 0, 0, 0, 0 },
	{ 2, 1, 1, 1, 0, 0, 0 },
	{ 2, 2, 0, 1, 0, 2, 0 },
	{ 4, 1, 1, 2, 0, 1, 0 },
	{ 4, 1, 2, 1, 3, 0, 0 },
	{ 6, 1, 2, 3, 0, 1, 0 },
	{ 6, 2, 2, 2, 2, 2, 1 }
};

int			check_for_victory(const t_team *team)
{
	t_lstiter	iter;
	t_client	*client;
	unsigned	i;

	i = 0;
	init_iter(&iter, g_zappy.clients, increasing);
	while (lst_iterator_next(&iter))
	{
		client = (t_client*)iter.data;
		if (client->team != team)
			continue ;
		if (client->level == MAX_LEVEL - 1)
			i++;
	}
	if (i >= 6)
		return (i);
	return (0);
}

short		client_can_promote(t_client *client)
{
	t_uint		i;
	t_lstiter	iter;
	t_tile		*tile;
	t_uint		clients_count;

	if (client->level >= MAX_LEVEL - 1)
		return (0);
	tile = client->position;
	clients_count = 0;
	init_iter(&iter, &tile->clients, increasing);
	while (lst_iterator_next(&iter))
	{
		if (((t_client*)iter.data)->level == client->level)
			clients_count++;
	}
	if (clients_count < g_promotion_needs[client->level][0])
		return (0);
	i = 1;
	while (i < ITEM_COUNT)
	{
		if (g_promotion_needs[client->level][i] > tile->items[i])
			return (0);
		i++;
	}
	return (1);
}

short		client_promote(t_client *client)
{
	t_uint	i;

	client->level++;
	gfx_client_promote(client);
	i = check_for_victory(client->team);
	if (i > 0)
	{
		printf("victory %s with %u\n", client->team->name, i);
		zappy_pause(NULL);
		gfx_victory(client->team);
	}
	return (1);
}
