/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 16:31:17 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/04 01:15:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <limits.h>
#include <stdlib.h>

short	client_add_item(t_client *client, int item)
{
	if (item < 0 || item >= ITEM_COUNT)
		return (0);
	if (client->items[item] == UINT_MAX)
		return (0);
	client->items[item]++;
	return (1);
}

short	client_remove_item(t_client *client, int item)
{
	if (item < 0 || item >= ITEM_COUNT)
		return (0);
	if (client->items[item] == 0)
		return (0);
	client->items[item]--;
	return (1);
}

short	client_pick(t_client *client, int item)
{
	if (client_add_item(client, item))
	{
		if (tile_remove_item(client->position, item))
		{
			gfx_client_pick(client, item);
			return (1);
		}
		client_remove_item(client, item);
	}
	return (0);
}

short	client_drop(t_client *client, int item)
{
	if (client_remove_item(client, item))
	{
		if (tile_add_item(client->position, item))
		{
			gfx_client_drop(client, item);
			return (1);
		}
		client_add_item(client, item);
	}
	return (0);
}

char	*client_inventory(t_client *client)
{
	char	*str;

	str = calloc(200, sizeof(char));
	snprintf(str, 200, "food %u, linemate %u, deraumere %u, sibur %u, "
		"mendiane %u, phiras %u, thystame %u",
		client->items[0],
		client->items[1],
		client->items[2],
		client->items[3],
		client->items[4],
		client->items[5],
		client->items[6]
	);
	return (str);
}