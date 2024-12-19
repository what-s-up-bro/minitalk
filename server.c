/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:42:08 by yaait-am          #+#    #+#             */
/*   Updated: 2024/12/19 21:28:27 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char	c;
	static int	numbit;

	(void) context;
	if (sig == SIGUSR1)
		c |= (1 << numbit);
	else if (sig == SIGUSR2)
		c &= ~(1 << numbit);
	numbit++;
	if (numbit == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		numbit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("this the pid : %d\nwaiting for signal...\n", getpid());
	while (1)
		pause();
	return (0);
}
