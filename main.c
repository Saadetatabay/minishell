#include "minishell.h"

int	main(int argc, char	*argv[], char *envp[])
{
	char	*input;
	t_token	*token_list;
	//unused uyarısı almamk için yaptım
	(void)argc;
	(void)argv;
	(void)envp;
	//sonusuz shell döngüsü
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
		//kullanıcı hiçbir şey girmeden ENTER'A basarsa boş string döner.boş satırı hsitorye gömmüyorum
		//boş satır değilse historye ekliyroum
		if (*input)
		{
			add_history(input);
			//saadet
			token_list = lexer(input);
			// 2. TEST: Parçaları ekrana bas (Görmek için)
            printf("--- LEXER CIKTISI ---\n");
            print_tokens(token_list);
            printf("---------------------\n");

            // 3. Executor gelene kadar listeyi burada free'lemeliyiz
            // Yoksa her komutta RAM şişer.
            free_token_list(&token_list);
			//parse_input(input);
			//ayşe
			//exec_command();
		}
		free(input);
	}
	return (0);
}
