/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:50:07 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 14:00:31 by jcamarer         ###   ########.fr       */
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

/* static int start_simulation(t_data *data)
{
	int			i;
	pthread_t	*threads;
	pthread_t	monitor_thread;

	threads = malloc(data->params.number_of_coders * sizeof(pthread_t));
	if (!threads)
		return (1);
	i = 0;
	while (i < data->params.number_of_coders)
	{
		pthread_create(&threads[i], NULL, coder_routine, &data->coders[i]);
		i++;
	}
	
	// Creamos el hilo del vigilante, pasándole t_data entero
	pthread_create(&monitor_thread, NULL, monitor_routine, data);

	// Esperamos al vigilante
	pthread_join(monitor_thread, NULL);
	
	i = 0;
	while (i < data->params.number_of_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
} */

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
/* 	if (start_simulation(&data) == 1)
		return (1); */
	return (0);
}
