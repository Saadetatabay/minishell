#include "minishell.h"

int	g_exit_status = 0;
int	g_sig_status = 0;

static void	process_input(char *input, t_env *env_list)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	if (!*input)
		return ;
	add_history(input);
	token_list = lexer(input);
	expander(&token_list, env_list);
	cmd_list = parse_token(token_list);
	free_token_list(&token_list);
	if (cmd_list != NULL)
	{
		executor(cmd_list, env_list);
		free_cmd_list(&cmd_list);
	}
}

static int	read_and_process(t_env *env_list)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	process_input(input, env_list);
	free(input);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = NULL;
	init_env(&env_list, envp);
	init_signals();
	while (read_and_process(env_list));
	rl_clear_history();
	return (0);
}