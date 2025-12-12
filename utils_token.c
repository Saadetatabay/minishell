# include "minishell.h"
// TEST İÇİN: Tokenları ekrana basar
void    print_tokens(t_token *token)
{
    int i = 0;
    while (token)
    {
        printf("Token %d: [%s] (Type: %d)\n", i, token->value, token->type);
        token = token->next;
        i++;
    }
}

// TEMİZLİK İÇİN: Token listesini free'ler (Leak olmaması için şart)
void    free_token_list(t_token **token)
{
    t_token *curr;
    t_token *next;

    if (!token || !*token)
        return;
    curr = *token;
    while (curr)
    {
        next = curr->next;
        free(curr->value); // İçindeki stringi (content) free'le
        free(curr);        // Vagonun kendisini free'le
        curr = next;
    }
    *token = NULL;
}