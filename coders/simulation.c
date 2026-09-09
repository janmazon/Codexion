/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:03:11 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/09 17:45:53 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_compiling(t_coder *coder)
{
	long	time;

	time = get_time() - coder->params->start_time;
	pthread_mutex_lock(coder->print_mutex);
	printf("%ld %d is compiling\n", time, coder->id);
	pthread_mutex_unlock(coder->print_mutex);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_counter += 1;
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->mutex);
	usleep(coder->params->time_to_compile * 1000);
}

static void	do_debugging(t_coder *coder)
{
	long	time;

	time = get_time() - coder->params->start_time;
	pthread_mutex_lock(coder->print_mutex);
	printf("%ld %d is debugging\n", time, coder->id);
	pthread_mutex_unlock(coder->print_mutex);
	usleep(coder->params->time_to_debug * 1000);
}

static void	do_refactoring(t_coder *coder)
{
	long	time;

	time = get_time() - coder->params->start_time;
	pthread_mutex_lock(coder->print_mutex);
	printf("%ld %d is refactoring\n", time, coder->id);
	pthread_mutex_unlock(coder->print_mutex);
	usleep(coder->params->time_to_refactor * 1000);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compile_counter < coder->params->number_of_compiles_required)
	{
		//take_dongles(coder);
		do_compiling(coder);
		//release_dongles(coder);
		do_debugging(coder);
		do_refactoring(coder);
	}
	return (NULL);
}
