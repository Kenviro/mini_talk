/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:49:10 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/21 11:23:56 by ktintim-         ###   ########.fr       */
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

void	handle_signal(int sig)
{
	static unsigned char	current_char;
	static int				bit_count;

	if (sig == SIGUSR1)
	{
		current_char <<= 1;
	}
	else if (sig == SIGUSR2)
	{
		current_char = (current_char << 1) | 1;
	}
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		current_char = 0;
		bit_count = 0;
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, \
			&sa, NULL) == -1)
	{
		perror("Erreur lors de la configuration des signaux");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	int	pid;

	pid = get_pid();
	setup_signal_handlers();
	while (1)
	{
		pause();
	}
	return (0);
}
