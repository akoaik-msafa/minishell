/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:22:28 by msafa             #+#    #+#             */
/*   Updated: 2025/10/01 05:27:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	here_doc(char *delimiter, t_data *data, int expand_flag)
{
	char	*temp_file;
	int		fd_write;
	int		fd_read;
	char	*line;
	int		tty_fd;
	int		saved_stdin;
	char	*temp_line;

	temp_file = "/tmp/heredoc_tmp";
	tty_fd = -1;
	saved_stdin = -1;
	// If stdin is redirected, use /dev/tty for readline
	if (!isatty(STDIN_FILENO))
	{
		tty_fd = open("/dev/tty", O_RDONLY);
		if (tty_fd != -1)
		{
			saved_stdin = dup(STDIN_FILENO);
			dup2(tty_fd, STDIN_FILENO);
			close(tty_fd);
		}
	}
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
	// Restore original stdin if we changed it
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
		int expand_flag;

	if (!ast || ast->redir_type != t_re_heredoc || !ast->filename)
		return ;
	// Use pre-created heredoc_fd if available (from pipe context)
	if (ast->heredoc_fd != -1)
		fd = ast->heredoc_fd;
	else
	{
		printf("\n=== HEREDOC EXPAND FLAG CONVERSION ===\n");
		printf("AST node filename: '%s'\n", ast->filename);
		printf("AST node expand_flags: ");
		if (ast->expand_flags)
		{
			printf("allocated\n");
			printf("  char expand_flags[0] = %d\n", ast->expand_flags[0]);
			expand_flag = ast->expand_flags[0]; // char -> int conversion
			printf("  Converting to int expand_flag = %d\n", expand_flag);
			printf("  Source: This came from the delimiter token's expand_flag\n");
		}
		else
		{
			printf("NULL\n");
			expand_flag = 1;
			printf("  Using default int expand_flag = %d\n", expand_flag);
			printf("  Source: Default fallback (should not happen for heredoc)\n");
		}
		printf("  Result: Heredoc content will%s be expanded\n",
			expand_flag ? "" : " NOT");
		printf("=====================================\n");
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
