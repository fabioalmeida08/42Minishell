/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:47:12 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/22 18:25:53 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_PAREN_OPEN,
	TK_PAREN_CLOSE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_REDIR_HEREDOC,
	TK_UNKNOWN
}	t_token_type;

typedef struct s_redirect
{
	t_token_type	type;
	char			*file;
	char			*content;
}	t_redirect;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;// lado esquerdo do pipe ou NULL se comando simples
	struct s_ast	*right;// lado direito do pipe ou NULL se comando simples
	// Apenas se type == CMD_NODE
	char			**args;// comando + argumentos
	t_redirect		*in;// redirecionamento de entrada
	t_redirect		*out;// redirecionamento de saída
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;	
}	t_env;

typedef struct s_shell	t_shell;
typedef struct s_builtin
{
	char	*name;
	void	(*func)(char **cmd, t_shell *sh);
}	t_builtin;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char		**envp;
	t_env		*env_list;
	int			exit_status;
	t_builtin	*g_builtins;
	t_token		*head_tokens;
	t_ast		*head_ast;
}	t_shell;

//MINISHELL(MAIN)
void	interactive_mode(t_shell *sh);
void	non_interactive_mode(void);

//LEXER/TOKEN
t_token	*ft_tokenize(const char *str, t_shell *sh);
t_token	*ft_strtok(const char *str, t_shell *sh);
void	lexer_syntax_error(t_token *token, t_shell *sh);
t_token	*create_token(t_token_type type, char *value);
void	add_token_back(t_token **head, t_token *new_token);
void	ft_free_tokens(t_token *tokens);
char	*extract_word(const char **str);
t_token	*handle_operator(const char **str);
bool	check_quotes(const char *str);

//SIGNAL
void	handle_sigint(int sig);
void	setup_interactive_parent_signals(void);
void	setup_child_signals(void);

//INIT_ENV
void	init_env(char **envp, t_shell *shell_vars);
void	free_env_list(t_env *env_list);
char	**env_to_envp(t_env *env);
void	free_envp(char **envp);
t_env	*get_env_node(t_env *env_list, char *key);
char	*get_env_value(t_env *env_list, char *key);
int		add_env_var(t_env **env_list, char *key, char *value);
int		update_env_var(t_env *env_list, char *key, char *value);
int		remove_env_var(t_env **env_list, char *key);

//SIMPLE EXECVE
void	execve_cmd(char **input, t_shell *sh);

//BUILTIN
void	init_builtin(t_shell *sh);
int		is_builtin(char **cmd, t_shell *sh);
void	exec_builtin(char **cmd, t_shell *sh);
void	builtin_pwd(char **cmd, t_shell *sh);
void	builtin_env(char **cmd, t_shell *sh);
void	builtin_export(char **cmd, t_shell *sh);
void	builtin_unset(char **cmd, t_shell *sh);

//PARSER
t_ast	*create_node(t_node_type type);
void	brake_list_until(t_token *list, t_token *until);
void	paren_depth_counter(int *depth, t_token *current);
t_token	*find_last_logical_node(t_token *tokens);
t_ast	*parser_logical(t_token *tokens);
t_token	*find_last_node(t_token *tokens, t_token_type to_find);
t_ast	*parser_pipe(t_token *tokens);
t_ast	*parser_cmd(t_token *tokens);
t_ast	*simple_cmd(t_token *tokens);
t_token	*complex_cmd(t_token *tokens, int *depth);

//DEBUG
void	print_ast(t_ast *node, int depth);
void	print_tokens(t_token *tokens);
#endif
