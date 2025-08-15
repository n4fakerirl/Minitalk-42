/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/15 09:30:07 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	cleaning(int sig)
{
	(void)sig;
	// free(server);
	exit(0);
}

void	handle(int sig, siginfo_t *info, void *ucontext)
{
	static int bits = 0;
	static char c = 0;
	
	(void)info;
	(void)ucontext;
	if (bits < 8)
	{
		if (sig == SIGUSR1)
			c |= (1 << (7 - bits));
		bits++;
	}
	if (bits == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bits = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t		pid;

	(void)av;
	if (ac != 1)
		return (ft_printf("Error\nUsage: ./server (no args)\n"), 1);
	// server = malloc(sizeof(t_server));
	// if (!server)
	// 	return (1);
	pid = getpid();
	if (pid == -1)
		return (ft_printf("Error\nUnable to get server's pid.\n"), 1);
	ft_printf("PID: %d\nWaiting for a message...\n\n", pid);
	//ft_bzero(server, sizeof(t_server));
	sa.sa_sigaction = handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		signal(SIGINT, cleaning);
		pause();
	}
}
