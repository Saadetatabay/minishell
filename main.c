#include "minishell.h"
int	main(int argc, char	*argv[], char *envp[])
{
	char	*input;
	//unused uyarısı almamk için yaptım
	(void)argc;
	(void)argv;
	(void)envp;

	//sonusuz shell döngüsü
	while (1)
	{
		input = readline("minishell$ ");
		// CTRL-D EOF kontrolü yaptım
		if (!input)
		{
			printf("exit\n");
			break;
		}

		//boş satır değilse historye ekliyroum
		if (*input)
		{
			add_history(input);
			//saadet
			//parse_input(input);
			//ayşe
			//exec_command();
		}
		free(input);
	}
	return (0);
}