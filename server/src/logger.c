/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/16 01:37:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 21:14:13 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void		logger_init(const char *filename)
{
	g_zappy.logger_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

void		logger_log(const char *message)
{
	if (g_zappy.logger_fd <= 0)
		return ;
	write(g_zappy.logger_fd, message, strlen(message));
	write(g_zappy.logger_fd, "\n", 1);
}

void		logger_close(void)
{
	close(g_zappy.logger_fd);
}
