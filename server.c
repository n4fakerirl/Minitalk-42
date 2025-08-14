/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/14 17:12:40 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		server->bits = 0;
		server->charc = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	server = malloc(sizeof(t_server));
	if (!server)
		return (1);
	ft_bzero(server, 0);
	sa.sa_sigaction = handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
}
