/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:03:11 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 12:10:41 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	take_one_dongle(t_coder	*coder, t_dongle *dongle)
{
	long	time;

	pthread_mutex_lock(&dongle->mutex);
	time = get_time() - coder->params->start_time;
	pthread_mutex_lock(coder->print_mutex);
	printf("%ld %d has taken a dongle\n", time, coder->id);
	pthread_mutex_unlock(coder->print_mutex);
}

static void	take_dongles(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		take_one_dongle(coder, coder->left_dongle);
		take_one_dongle(coder, coder->right_dongle);
	}
	else
	{
		take_one_dongle(coder, coder->right_dongle);
		take_one_dongle(coder, coder->left_dongle);
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
	while (coder->compile_counter < coder->params->number_of_compiles_required)
	{
		take_dongles(coder);
		do_compiling(coder);
		return_dongles(coder);
		do_debugging(coder);
		do_refactoring(coder);
	}
	return (NULL);
}
