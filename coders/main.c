/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:50:07 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 12:12:43 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_data(t_data *data, char **argv)
{
	parse_params(&data->params, argv);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (check_params(&data->params) == 1)
		return (1);
	if (init_dongles(data) == 1)
		return (1);
	if (init_coders(data) == 1)
	{
		free(data->dongles);
		return (1);
	}
	data->params.start_time = get_time();
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
	return (0);
}
