/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:44:27 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/08 16:48:02 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	validate_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		printf("Error: invalid values. Must be an integer.\n");
		return (1);
	}
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
		{
			printf("Error: invalid values. Must be positive.\n");
			return (1);
		}
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Error: invalid values. Must be an integer.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_args(char **argv)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (validate_number(argv[i]) == 1)
			return (1);
		i++;
	}
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
	{
		printf("Error: invalid values. Must be 'fifo' or 'edf'.\n");
		return (1);
	}
	return (0);
}

int	parse_parameters(t_parameters *parameters, char **argv)
{
	parameters->number_of_coders = atoi(argv[1]);
	parameters->time_to_burnout = atoi(argv[2]);
	parameters->time_to_compile = atoi(argv[3]);
	parameters->time_to_debug = atoi(argv[4]);
	parameters->time_to_refactor = atoi(argv[5]);
	parameters->number_of_compiles_required = atoi(argv[6]);
	parameters->dongle_cooldown = atoi(argv[7]);
	parameters->scheduler = strcmp(argv[8], "edf") == 0;
	return (0);
}

int	check_parameters(t_parameters *parameters)
{
	if (parameters->number_of_coders <= 0
		|| parameters->time_to_burnout <= 0
		|| parameters->time_to_compile <= 0
		|| parameters->time_to_debug <= 0
		|| parameters->time_to_refactor <= 0
		|| parameters->number_of_compiles_required <= 0)
	{
		printf("Error: invalid values. Must be greater than 0.\n");
		return (1);
	}
	if (parameters->dongle_cooldown < 0)
	{
		printf("Error: invalid values. Must be positive.\n");
		return (1);
	}
	return (0);
}
