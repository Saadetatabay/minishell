#include "minishell.h"
#include <stdio.h>

void    direct_and_close(int *fd)
{
    if(*fd != -1)
        {
            dup2(*fd, 1);
            close(*fd);
        }
}

int    heredoc_utils(t_redir *tmp)
{
    int fd;

    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (-1);
    fill_heredoc(tmp->file, &fd);
    close(fd);
    fd = open(".heredoc_tmp",O_RDONLY);
    if (fd == -1)
    {
        unlink(".heredoc_tmp");
        return(-1);
    }
    dup2(fd, 0);
    close(fd);
    unlink(".heredoc_tmp");
    return (fd);
}

void     handle_utils(t_redir *tmp, int* fd)
{
    if(tmp->type == REDIRECT_OUT)
    {
        *fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        direct_and_close(fd);    
    }
    else if (tmp->type == APPEND)
    {
        *fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        direct_and_close(fd);
    }
    else if (tmp->type == REDIRECT_IN)
    {
        *fd = open(tmp->file, O_RDONLY);
        if (*fd != -1)
        {
            dup2(*fd, 0);
            close(*fd);
        }
    }
    else if(tmp->type == HEREDOC)
        *fd = heredoc_utils(tmp);
}

void    fill_heredoc(char *stop, int *fd)
{
    char *line;
    while(1)
    {
        line = readline("> ");
        if(line == NULL)
            break;
        if(ft_strncmp(line, stop, ft_strlen(line) + 1) == 0)
        {
            free(line);
            break;
        }
        write(*fd, line, ft_strlen(line));
        write(*fd, "\n", 1);
        free(line);
    }
}

int     handle_redirections(t_cmd *cmd)
{
    t_redir     *tmp;
    int         fd;

    tmp = cmd->redirections;
    while (tmp != NULL)
    {
        fd = -1;
        handle_utils(tmp, &fd);
        if(fd == -1)
        {
            perror("minishell");
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}