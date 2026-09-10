/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 11:58:49 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 12:00:45 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	do_compiling(t_coder *coder)
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

void	do_debugging(t_coder *coder)
{
	long	time;

	time = get_time() - coder->params->start_time;
	pthread_mutex_lock(coder->print_mutex);
	printf("%ld %d is debugging\n", time, coder->id);
	pthread_mutex_unlock(coder->print_mutex);
	usleep(coder->params->time_to_debug * 1000);
}

void	do_refactoring(t_coder *coder)
{
	long	time;

	time = get_time() - coder->params->start_time;
	pthread_mutex_lock(coder->print_mutex);
	printf("%ld %d is refactoring\n", time, coder->id);
	pthread_mutex_unlock(coder->print_mutex);
	usleep(coder->params->time_to_refactor * 1000);
}
