#include "minishell.h"

void    handle_sigint(int sig)
{
    (void)sig;
    g_sig_status = 130;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    init_signals(void)
{
    signal(SIGINT, &handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
