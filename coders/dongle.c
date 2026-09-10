/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 11:14:20 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 11:53:43 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_dongles(t_data *data)
{
	int			i;

	data->dongles = malloc(data->params.number_of_coders * sizeof(t_dongle));
	if (!data->dongles)
		return (1);
	i = 0;
	while (i < data->params.number_of_coders)
	{
		data->dongles[i].id = i + 1;
		data->dongles[i].status = STATUS_AVAILABLE;
		data->dongles[i].last_release_time = 0;
		pthread_mutex_init(&data->dongles[i].mutex, NULL);
		pthread_cond_init(&data->dongles[i].cond, NULL);
		i++;
	}
	return (0);
}
