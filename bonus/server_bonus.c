/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/14 18:57:58 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_server	*server;

void	handle(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (server->bits < 8)
	{
		if (sig == SIGUSR1)
			server->charc |= (1 << (7 - server->bits));
		server->bits++;
	}
	if (server->bits == 8)
	{
		if (server->charc == '\0')
			write(1, "\n", 1);
		else
			write(1, &server->charc, 1);
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_printf("PID DOESNT EXIST\n");
		server->bits = 0;
		server->charc = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t		pid;

	(void)av;
	if (ac != 1)
		return (ft_printf("Error\nUsage: ./server (no args)\n"), 1);
	server = malloc(sizeof(t_server));
	if (!server)
		return (1);
	pid = getpid();
	if (pid == -1)
		return (ft_printf("Error\nUnable to get server's pid.\n"), 1);
	ft_printf("PID: %d\nWaiting for a message...\n\n", pid);
	ft_bzero(server, sizeof(t_server));
	sa.sa_sigaction = handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
