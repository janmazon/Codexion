/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:03:11 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 18:25:18 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	request_dongle(t_coder *coder, t_dongle *dongle)
{
	t_request	request;

	pthread_mutex_lock(&dongle->mutex);
	request.coder_id = coder->id;
	if (coder->params->scheduler == FIFO)
		request.priority = get_time();
	if (coder->params->scheduler == EDF)
		request.priority = coder->last_compile_start
			+ coder->params->time_to_burnout;
	heap_insert(&dongle->heap, request);
	while (dongle->heap.requests[0].coder_id != coder->id
		|| dongle->status != STATUS_AVAILABLE || get_time()
		< dongle->last_release_time + coder->params->dongle_cooldown)
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	heap_extract(&dongle->heap);
	dongle->status = STATUS_USING;
	pthread_mutex_unlock(&dongle->mutex);
}

static void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->status = STATUS_AVAILABLE;
	dongle->last_release_time = get_time();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

static void	take_dongles(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		request_dongle(coder, coder->left_dongle);
		print_status(coder, "has taken a dongle");
		request_dongle(coder, coder->right_dongle);
		print_status(coder, "has taken a dongle");
	}
	else
	{
		request_dongle(coder, coder->right_dongle);
		print_status(coder, "has taken a dongle");
		request_dongle(coder, coder->left_dongle);
		print_status(coder, "has taken a dongle");
	}
}

static void	return_dongles(t_coder *coder)
{
	release_dongle(coder->left_dongle);
	release_dongle(coder->right_dongle);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->params->number_of_coders == 1)
	{
		request_dongle(coder, coder->left_dongle);
		print_status(coder, "has taken a dongle\n");
		usleep(coder->params->time_to_burnout * 2000);
		return (NULL);
	}
	if (coder->id % 2 != 0)
		usleep(1000);
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
