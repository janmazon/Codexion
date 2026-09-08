/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:50:07 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/07 16:56:45 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int	validate_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		printf("Error: argument must be an integer.\n");
		return (1);
	}
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
		{
			printf("Error: argument must be positive.\n");
			return (1);
		}
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Error: argument must be an integer.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		printf("Error: invalid number of arguments. Expected 8.\n");
		return (1);
	}
}