/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/15 11:57:28 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_server	*server;

void	cleaning(int sig)
{
	(void)sig;
	free(server);
	exit(0);
}

void	still_instr(void)
{
	server->buffer[server->i++] = server->c;
	if (server->i >= 9999)
	{
		server->buffer[server->i] = '\0';
		write(1, server->buffer, server->i);
		server->i = 0;
		ft_memset(server->buffer, 0, sizeof(server->buffer));
	}
}

void	handle(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (server->bits < 8)
	{
		if (sig == SIGUSR1)
			server->c |= (1 << (7 - server->bits));
		server->bits++;
	}
	if (server->bits == 8)
	{
		if (server->c == '\0')
		{
			server->buffer[server->i] = '\0';
			write(1, server->buffer, server->i);
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
			server->i = 0;
			ft_memset(server->buffer, 0, sizeof(server->buffer));
		}
		else
			still_instr();
		server->bits = 0;
		server->c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				pid;

	(void)av;
	if (ac != 1)
		return (ft_printf("Error\nUsage: ./server (no args)\n"), 1);
	pid = getpid();
	if (pid == -1)
		return (ft_printf("Error\nUnable to get server's pid.\n"), 1);
	server = malloc(sizeof(t_server));
	if (!server)
		return (0);
	ft_bzero(server, 0);
	ft_printf("PID: %d\nWaiting for a message...\n\n", pid);
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
