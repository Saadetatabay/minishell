#include "minishell.h"

t_cmd	*parse_token(t_token *token_list)
{
    t_token *current_token;
    t_cmd   *head;
    t_cmd   *current;
    t_cmd   *new_cmd;

	if (!token_list)
		return NULL;
    current_token = token_list;
    head = new_cmd_node();
    if (!head)
		return NULL;
	current = head;
    while (current_token)
    {
        //eğer pipe gördüysek linked list ile bağlayacağız yeni bir kutu açıp oradaki komutları da koyuyorz
        if (current_token->type == PIPE)
        {
            new_cmd = new_cmd_node(); // pıpe sonrarsında yer alanları bağladım yani 
            if (!new_cmd)
                return NULL;
            current->next = new_cmd;
            current = new_cmd;
        }
        //joinstrarr ile arga ekleyeceğiz
        else if (current_token->type == WORD)
        {
            // la mesela argümana ekledim
            current->args = join_str_array(current->args, current_token->value);
            if (!current->args)
                return NULL; // buraya sonradn temizleme için kod gelecek    
        }
        else
        {
            if (!add_redirect(current_token, current))
                return NULL;
            current_token = current_token->next; // neext valuesı doyaadı biz onu hallettik zaten
        }
        current_token = current_token->next;
    }
	return (head);
}