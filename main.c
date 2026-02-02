#include "minishell.h"

int	exit_status = 0;
int g_sig_status = 0;

int	main(int argc, char	*argv[], char *envp[])
{
	char	*input;
	t_token	*token_list;
	t_env	*env_list;
	t_cmd	*cmd_list;
	//unused uyarısı almamk için yaptım
	(void)argc;
	(void)argv;
	//(void)envp;
	env_list = NULL;
	init_env(&env_list, envp);

    // // 4. TEST: Bakalım listeye almış mıyız? (Sonra sileceğiz)
    // printf("--- ENV LISTESI ---\n");
    // print_env(env_list);
    // printf("-------------------\n");
	//sonusuz shell döngüsü
	init_signals();

	while (1)
	{
		//readlien ekrana minishell$ yazını basar ve kullanıcıdan girdi bekler
		//kullanıcı yazı yazarken yukarı aşağı ok backspace(silme) kullanabiliyor
		// dönüş değeri kullanıcının girdiği string sonuna newline koymaz
		input = readline("minishell$ ");
		// CTRL-D EOF kontrolü yaptım readline NULL döner
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		// //kullanıcı hiçbir şey girmeden ENTER'A basarsa boş string döner.boş satırı hsitorye gömmüyorum
		//boş satır değilse historye ekliyroum
		if (*input)
		{
			add_history(input);
			//saadet
			token_list = lexer(input);
			// 2. TEST: Parçaları ekrana bas (Görmek için)
            // // printf("--- LEXER CIKTISI ---\n");
            // // print_tokens(token_list);
            // // printf("---------------------\n");

            // 3. Executor gelene kadar listeyi burada free'lemeliyiz
            // Yoksa her komutta RAM şişer.
			expander(&token_list,env_list);
			cmd_list = parse_token(token_list);
			free_token_list(&token_list);
			//print_cmd_list(cmd_list);
			// 4. SONUÇLARI GÖRMEK İÇİN YAZDIR
            // printf("--- EXPANDER SONRASI ---\n");
            // t_token *temp = token_list;
            // while (temp)
            // {
            //     printf("Token: [%s]\n", temp->value);
            //     temp = temp->next;
            // }
            // printf("------------------------\n");
			if(cmd_list != NULL)
			{
				executor(cmd_list, env_list);
				free_cmd_list(&cmd_list);
			}
			//ayşe //kanka sen parse_token(token_list) den ksımı alcaksın print_cmd_list görmek içindi benim kısmı
			//exec_command();
		}
		free(input);
	}
	//free_env_list eklemek lazım
	rl_clear_history();
	return (0);
}
