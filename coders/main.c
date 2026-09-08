/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:50:07 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/08 16:58:05 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_parameters	parameters;

	if (argc != 9)
	{
		printf("Error: invalid number of arguments. Expected 8.\n");
		return (1);
	}
	if (validate_args(argv) == 1)
		return (1);
	parse_parameters(&parameters, argv);
	if (check_parameters(&parameters) == 1)
		return (1);
	return (0);
}
