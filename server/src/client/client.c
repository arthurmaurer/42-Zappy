/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 22:44:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 03:13:07 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <libft.h>
#include <stdlib.h>

t_client	*client_create(t_tile *position)
{
	static t_uint	id;
	t_client		*client;
	t_client		*clients;

	if (id == 0)
		id = 1;
	client = malloc(sizeof(t_client));
	ft_bzero(client, sizeof(t_client));
	client->hunger = FOOD_DURATION;
	client->id = id++;
	client->life = CLIENT_BASE_LIFE;
	client->authenticated = 0;
	client_move_to(client, position);
	clients = g_zappy.clients;
	if (clients == NULL)
		g_zappy.clients = client;
	else
		DLIST(append, void, g_zappy.clients, (t_dlist*)clients);
	g_zappy.client_count++;
	return (client);
}

void	client_delete(t_client *client_to_delete)
{
	g_zappy.clients = DLIST(remove, t_client*, client_to_delete);
	client_to_delete->position->client_count--;
	client_queue_free(client_to_delete);
	free(client_to_delete);
	g_zappy.client_count--;
}

void	client_set_team(t_client *client, const char *team_name)
{
	t_team	*team;

	team = team_get(team_name);
	if (team == NULL)
		team = team_create(team_name);
	client->team = team;
}
