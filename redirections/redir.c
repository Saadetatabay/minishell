/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayonal <ayonal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:35 by ayonal            #+#    #+#             */
/*   Updated: 2026/02/14 15:26:35 by ayonal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void direct_and_close(int *fd) {
  if (*fd != -1) {
    dup2(*fd, 1);
    close(*fd);
  }
}

int heredoc_utils(t_redir *tmp) {
  int fd;

  fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1)
    return (-1);
  fill_heredoc(tmp->file, &fd);
  close(fd);
  fd = open(".heredoc_tmp", O_RDONLY);
  if (fd == -1) {
    unlink(".heredoc_tmp");
    return (-1);
  }
  dup2(fd, 0);
  close(fd);
  unlink(".heredoc_tmp");
  return (0);
}

void handle_utils(t_redir *tmp, int *fd) {
  if (tmp->type == REDIR_OUT) {
    *fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    direct_and_close(fd);
  } else if (tmp->type == REDIR_APPEND) {
    *fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    direct_and_close(fd);
  } else if (tmp->type == REDIR_IN) {
    *fd = open(tmp->file, O_RDONLY);
    if (*fd != -1) {
      dup2(*fd, 0);
      close(*fd);
    } else
      return;
  } else if (tmp->type == REDIR_HEREDOC)
    *fd = heredoc_utils(tmp);
}

void fill_heredoc(char *stop, int *fd) {
  char *line;
  int saved_stdin;
  int tty_fd;

  saved_stdin = dup(STDIN_FILENO);
  tty_fd = open("/dev/tty", O_RDONLY);
  if (tty_fd != -1) {
    dup2(tty_fd, STDIN_FILENO);
    close(tty_fd);
  }
  while (1) {
    line = readline("> ");
    if (line == NULL)
      break;
    if (ft_strncmp(line, stop, ft_strlen(line) + 1) == 0) {
      free(line);
      break;
    }
    write(*fd, line, ft_strlen(line));
    write(*fd, "\n", 1);
    free(line);
  }
  dup2(saved_stdin, STDIN_FILENO);
  close(saved_stdin);
}

int handle_redirections(t_cmd *cmd) {
  t_redir *tmp;
  int fd;
  int saved_stdin;

  saved_stdin = dup(STDIN_FILENO);
  tmp = cmd->redirections;
  while (tmp != NULL) {
    fd = -1;
    if (tmp->type == REDIR_HEREDOC)
      dup2(saved_stdin, STDIN_FILENO);
    handle_utils(tmp, &fd);
    if (fd == -1) {
      close(saved_stdin);
      perror("minishell");
      return (1);
    }
    tmp = tmp->next;
  }
  close(saved_stdin);
  return (0);
}
