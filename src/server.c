/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:10:21 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/15 12:21:33 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_server	*g_server;

void	cleaning(int sig)
{
	(void)sig;
	free(g_server);
	exit(0);
}

void	still_instr(void)
{
	g_server->buffer[g_server->i++] = g_server->c;
	if (g_server->i >= 9999)
	{
		g_server->buffer[g_server->i] = '\0';
		write(1, g_server->buffer, g_server->i);
		g_server->i = 0;
		ft_memset(g_server->buffer, 0, sizeof(g_server->buffer));
	}
}

void	handle(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_server->bits < 8)
	{
		if (sig == SIGUSR1)
			g_server->c |= (1 << (7 - g_server->bits));
		g_server->bits++;
	}
	if (g_server->bits == 8)
	{
		if (g_server->c == '\0')
		{
			g_server->buffer[g_server->i] = '\0';
			write(1, g_server->buffer, g_server->i);
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
			g_server->i = 0;
			ft_memset(g_server->buffer, 0, sizeof(g_server->buffer));
		}
		else
			still_instr();
		g_server->bits = 0;
		g_server->c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	init_server(void)
{
	g_server->bits = 0;
	g_server->c = 0;
	g_server->i = 0;
	ft_memset(g_server->buffer, 0, sizeof(g_server->buffer));
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				pid;

	(void)av;
	if (ac != 1)
		return (ft_printf("Error\nUsage: ./g_server (no args)\n"), 1);
	pid = getpid();
	if (pid == -1)
		return (ft_printf("Error\nUnable to get g_server's pid.\n"), 1);
	g_server = malloc(sizeof(t_server));
	if (!g_server)
		return (0);
	init_server();
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
