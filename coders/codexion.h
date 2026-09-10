/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:14:38 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 12:00:42 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_coder_status
{
	STATUS_COMPILING,
	STATUS_DEBUGGING,
	STATUS_REFACTORING,
	STATUS_WAITING,
	STATUS_BURNED,
}	t_coder_status;

typedef enum e_dongle_status
{
	STATUS_AVAILABLE,
	STATUS_USING,
	STATUS_COOLDOWN,
}	t_dongle_status;

typedef enum e_scheduler
{
	FIFO,
	EDF,
}	t_scheduler;

typedef struct s_params
{
	int			number_of_coders;
	long		time_to_burnout;
	long		time_to_compile;
	long		time_to_debug;
	long		time_to_refactor;
	int			number_of_compiles_required;
	long		dongle_cooldown;
	long		start_time;
	t_scheduler	scheduler;
}	t_params;

typedef struct s_dongle
{
	int				id;
	t_dongle_status	status;
	long			last_release_time;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	t_coder_status	status;
	t_params		*params;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	int				compile_counter;
	long			last_compile_start;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*print_mutex;
}	t_coder;

typedef struct s_data
{
	t_params		params;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_mutex_t	print_mutex;
}	t_data;

int		validate_args(char **argv);
int		parse_params(t_params *params, char **argv);
int		check_params(t_params *params);
int		init_dongles(t_data *data);
int		init_coders(t_data *data);
long	get_time(void);
void	do_compiling(t_coder *coder);
void	do_debugging(t_coder *coder);
void	do_refactoring(t_coder *coder);
void	*coder_routine(void *arg);

#endif