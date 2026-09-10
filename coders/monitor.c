/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:42:55 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 13:54:41 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_burnout(t_data *data, int i)
{
	long	time;

	pthread_mutex_lock(&data->coders[i].mutex);
	if (data->coders[i].compile_counter
		>= data->params.number_of_compiles_required)
	{
		pthread_mutex_unlock(&data->coders[i].mutex);
		return (2);
	}
	if (get_time() - data->coders[i].last_compile_start
		>= data->params.time_to_burnout)
	{
		pthread_mutex_lock(&data->print_mutex);
		time = get_time() - data->params.start_time;
		printf("%ld %d burned out\n", time, data->coders[i].id);
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_flag = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->coders[i].mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->coders[i].mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		finished;
	int		status;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		finished = 0;
		while (i < data->params.number_of_coders)
		{
			status = check_burnout(data, i);
			if (status == 1)
				return (NULL);
			if (status == 2)
				finished++;
			i++;
		}
		if (finished == data->params.number_of_coders)
			return (NULL);
	}
	return (NULL);
}
