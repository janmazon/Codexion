/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:03:11 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 13:45:32 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	take_dongles(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		pthread_mutex_lock(&coder->left_dongle->mutex);
		print_status(coder, "has taken a dongle");
		pthread_mutex_lock(&coder->right_dongle->mutex);
		print_status(coder, "has taken a dongle");
	}
	else
	{
		pthread_mutex_lock(&coder->right_dongle->mutex);
		print_status(coder, "has taken a dongle");
		pthread_mutex_lock(&coder->left_dongle->mutex);
		print_status(coder, "has taken a dongle");
	}
}

static void	return_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compile_counter < coder->params->number_of_compiles_required
		&& check_stop(coder) == 0)
	{
		take_dongles(coder);
		do_compiling(coder);
		return_dongles(coder);
		do_debugging(coder);
		do_refactoring(coder);
	}
	return (NULL);
}
