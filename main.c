#include "minishell.h"

int	exit_status = 0;
int g_sig_status = 0;

int	main(int argc, char	*argv[], char *envp[])
{
	char	*input;
	t_token	*token_list;
	t_env	*env_list;
	t_cmd	*cmd_list;

	(void)argc;
	(void)argv;
	env_list = NULL;
	init_env(&env_list, envp);
	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			token_list = lexer(input);
			expander(&token_list,env_list);
			cmd_list = parse_token(token_list);
			free_token_list(&token_list);
			if(cmd_list != NULL)
			{
				executor(cmd_list, env_list);
				free_cmd_list(&cmd_list);
			}
		}
		free(input);
	}
	rl_clear_history();
	return (0);
}
