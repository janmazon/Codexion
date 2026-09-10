/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:50:07 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 18:58:24 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_data(t_data *data, char **argv)
{
	parse_params(&data->params, argv);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->stop_flag = 0;
	pthread_mutex_init(&data->stop_mutex, NULL);
	if (check_params(&data->params) == 1)
		return (1);
	if (init_dongles(data) == 1)
		return (1);
	data->params.start_time = get_time();
	if (init_coders(data) == 1)
	{
		free(data->dongles);
		return (1);
	}
	return (0);
}

static void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.number_of_coders)
	{
		pthread_mutex_destroy(&data->coders[i].mutex);
		pthread_mutex_destroy(&data->dongles[i].mutex);
		pthread_cond_destroy(&data->dongles[i].cond);
		free(data->dongles[i].heap.requests);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->dongles);
	free(data->coders);
}

static void	join_simulation(t_data *data, pthread_t monitor, pthread_t *threads)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->params.number_of_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}

static int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	pthread_t	*threads;
	int			i;

	threads = malloc(data->params.number_of_coders * sizeof(pthread_t));
	if (!threads)
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		free(threads);
		return (1);
	}
	i = 0;
	while (i < data->params.number_of_coders)
	{
		if (pthread_create(&threads[i], NULL, coder_routine,
				&data->coders[i]) != 0)
		{
			free(threads);
			return (1);
		}
		i++;
	}
	join_simulation(data, monitor, threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 9)
	{
		printf("Error: invalid number of arguments. Expected 8.\n");
		return (1);
	}
	if (validate_args(argv) == 1)
		return (1);
	if (init_data(&data, argv) == 1)
		return (1);
	start_simulation(&data);
	clean_data(&data);
	return (0);
}
