/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 00:33:28 by amaurer           #+#    #+#             */
/*   Updated: 2015/06/03 21:34:33 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include "dlist.h"
#include <libft.h>

t_command	g_commands[] = {
	{ "avance", 7, command_move },
	{ "gauche", 7, command_left },
	{ "droite", 7, command_right },
	{ "prend", 7, command_pick },
	{ "pose", 7, command_drop },
	{ "pause", 0, command_pause },
	{ "continuer", 0, command_resume },
	{ "inventaire", 1, command_inventory },
	{ "connect_nbr", 0, command_connect_count },
	{ NULL, 0, NULL }
};

static void			move_client_to_list(t_client *client, t_lst *from, t_lst *to)
{
	size_t	index;

	index = lst_index_of(from, client);
	lst_push_back(to, lst_remove(from, index));
}

static void	gfx_send_map(t_client *client)
{
	t_uint	x;
	t_uint	y;
	t_uint	i;
	t_uint	j;

	y = 0;
	while (y < g_zappy.height)
	{
		x = 0;
		while (x < g_zappy.width)
		{
			i = 0;
			while (i < ITEM_COUNT)
			{
				j = 0;
				while (j < g_zappy.map[y][x]->items[i])
				{
					gfx_tile_add(client, g_zappy.map[y][x], i);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	authenticate_gfx_client(t_client *client)
{
	char		str[20];

	move_client_to_list(client, g_zappy.anonymous_clients, g_zappy.gfx_clients);

	client->status = STATUS_GFX;
	client->position = NULL;

	snprintf(str, 20, "%u %u", g_zappy.width, g_zappy.height);
	network_send(client, str, 0);
	snprintf(str, 20, "%u", g_zappy.time.cycle_duration);
	network_send(client, str, 0);

	gfx_send_map(client);
}

static char	authenticate(t_client *client, char *input)
{
	t_team	*team;
	char	str[100];
	size_t	client_count;

	if (strcmp(input, "g") == 0)
	{
		authenticate_gfx_client(client);
		return (1);
	}

	team = team_get(input);
	if (team == NULL)
	{
		network_send(client, "m8 dat team doesnt exist ya fool", 0);
		return (0);
	}
	client_count = team_clients_count(team);
	if (client_count >= team->max_clients)
	{
		network_send(client, "clubs full buddy, gtfo", 0);
		network_client_disconnect(client);
		return (1);
	}

	client->team = team;
	client->status = STATUS_PLAYER;

	move_client_to_list(client, g_zappy.anonymous_clients, g_zappy.clients);

	client_set_team(client, input);
	snprintf(str, 100, "%lu\n%u %u", team->max_clients - client_count, g_zappy.width, g_zappy.height);
	network_send(client, str, 0);

	gfx_client_connect(client);

	return (0);
}

char	command_parse(t_client *client, char *input)
{
	char	**splits;
	t_uint	split_count;
	t_uint	i;

	if (client->status == STATUS_UNKNOWN)
		return authenticate(client, input);

	splits = ft_strsplit(input, ' ');
	split_count = ft_splits_count(splits);

	i = 0;
	while (split_count > 0 && g_commands[i].name != NULL)
	{
		if (strcmp(g_commands[i].name, splits[0]) == 0)
		{
			if (client->status == STATUS_GFX)
				g_commands[i].func(client, split_count, splits);
			else if (!client_queue_push(client, &(g_commands[i]), splits))
				network_send(client, "shits too fast", 0);
			return (0);
		}
		i++;
	}

	network_send(client, "dunno dat command lol", 0);
	return (0);
}
