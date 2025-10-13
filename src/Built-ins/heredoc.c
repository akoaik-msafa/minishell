/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:22:28 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 16:31:20 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	read_heredoc_lines(char *delimiter, t_data *data, int expand_flag,
		int fd_write)
{
	char	*line;
	char	*temp_line;

	while (1)
	{
		temp_line = readline("heredoc> ");
		if (!temp_line)
			break ;
		line = my_strdup(temp_line, data->n_head);
		free(temp_line);
		if ((delimiter && ft_strcmp(line, delimiter) == 0) || (!delimiter
				&& line[0] == '\0'))
			break ;
		if (expand_flag)
			line = expand_variable(line, data);
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
	}
	return (0);
}

static int	setup_stdin_for_heredoc(int *saved_stdin)
{
	int	tty_fd;

	*saved_stdin = -1;
	if (!isatty(STDIN_FILENO))
	{
		tty_fd = open("/dev/tty", O_RDONLY);
		if (tty_fd != -1)
		{
			*saved_stdin = dup(STDIN_FILENO);
			dup2(tty_fd, STDIN_FILENO);
			close(tty_fd);
		}
	}
	return (0);
}

static int	open_heredoc_file(char *temp_file, int saved_stdin)
{
	int	fd_write;

	fd_write = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_write == -1)
	{
		if (saved_stdin != -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		return (-1);
	}
	return (fd_write);
}

int	here_doc(char *delimiter, t_data *data, int expand_flag)
{
	char	*temp_file;
	int		fd_write;
	int		fd_read;
	int		saved_stdin;

	temp_file = "/tmp/heredoc_tmp";
	setup_stdin_for_heredoc(&saved_stdin);
	fd_write = open_heredoc_file(temp_file, saved_stdin);
	if (fd_write == -1)
		return (-1);
	read_heredoc_lines(delimiter, data, expand_flag, fd_write);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	close(fd_write);
	fd_read = open(temp_file, O_RDONLY);
	if (fd_read == -1)
		return (-1);
	unlink(temp_file);
	return (fd_read);
}

void	handle_heredoc_redirection(tree_node *ast, t_data *data)
{
	int	fd;
	int	saved_fd;
	int	expand_flag;

	if (!ast || ast->redir_type != t_re_heredoc || !ast->filename)
		return ;
	if (ast->heredoc_fd != -1)
		fd = ast->heredoc_fd;
	else
	{
		expand_flag = 1;
		if (ast->expansion)
			expand_flag = ast->expansion[0];
		fd = here_doc(ast->filename, data, expand_flag);
	}
	if (fd != -1)
	{
		saved_fd = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (ast->left)
			execute_ast(ast->left, data);
		dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
	}
}
