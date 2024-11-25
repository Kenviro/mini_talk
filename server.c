/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:49:10 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/25 10:46:49 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

int	get_pid(void)
{
	int	pid;

	pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	return (pid);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static sig_atomic_t		current_char = 0;
	static sig_atomic_t		bit_count = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		current_char <<= 1;
	else if (sig == SIGUSR2)
		current_char = (current_char << 1) | 1;
	bit_count++;
	if (bit_count == 8)
	{
		good_malloc(current_char, &client_pid);
		current_char = 0;
		bit_count = 0;
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_RESTART | SA_SIGINFO | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
			sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("Erreur lors de la configuration des signaux");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	get_pid();
	setup_signal_handlers();
	while (1)
	{
		pause();
	}
	return (0);
}
