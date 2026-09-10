/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 11:14:11 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 11:21:17 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_coders(t_data *data)
{
	int		i;

	data->coders = malloc(data->params.number_of_coders * sizeof(t_coder));
	if (!data->coders)
		return (1);
	i = 0;
	while (i < data->params.number_of_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].status = STATUS_WAITING;
		data->coders[i].params = &data->params;
		data->coders[i].left_dongle = &data->dongles[i];
		data->coders[i].right_dongle = &data->dongles[(i + 1)
			% data->params.number_of_coders];
		data->coders[i].compile_counter = 0;
		data->coders[i].last_compile_start = 0;
		data->coders[i].print_mutex = &data->print_mutex;
		pthread_mutex_init(&data->coders[i].mutex, NULL);
		i++;
	}
	return (0);
}
