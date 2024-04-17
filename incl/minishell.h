#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>

extern int	g_sig[2];

typedef struct s_token
{
	char			*content;
	char			*quote;
	char			**cmd;
	char			*path;
	char			*heredoc;
	int				fd_hdoc;
	char			**multi_path;
	int				type_input;
	int				fd_input;
	char			*f_input;
	int				type_output;
	int				fd_output;
	char			*file_output;
	char			*limiter;
	int				error;
	struct s_token	*next;
}	t_tok;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/*main*/
void	sigint( int code );
/*token-izer*/
t_tok	*token_izer(char *str, char *str_desac);
char	*cp_cmd(char *str, char *quote, int *i);
t_tok	*reorganize_token(t_tok *lst_tok);
void	insert_token(t_tok *lst_tok, t_tok *new);
/*tok_lst*/
int		tok_lstadd_back(t_tok **alst, t_tok *new);
t_tok	*tok_lstlast(t_tok *lst);
t_tok	*tok_lstnew(char *content);
int		tok_lstsize(t_tok *lst);
void	tok_lstclear(t_tok *lst);
/*lexer*/
char	*quote_secur(char *str);
char	*suppr_quote(char *str);
/*ft_split_cmd*/
char	**ft_split_cmd(char const *s);
/*dollars*/
char	*import_varsenv(t_env *envlst, char *str, int i);
/*launch_minishell*/
int		launch_minish(t_env *envlst);
void	exit_free(t_tok *token, t_env *envlst, int mode);
/*parsing*/
t_tok	*parsing(char *str, t_env *envlst);
int		token_split_and_varenv(t_tok *token, t_env *envlst);
void	trim_path_et_cmd(t_tok *token);
/*syntax_check.c*/
int		syntax_check(char *str);
/*init_token*/
int		init_token(t_tok *token, t_env *envlst);
/*big_free*/
int		free_env(t_env *envlst);
t_tok	*free_token(t_tok *token, t_tok *ret);
void	free_tab(char **tab);
/*bin_path*/
int		path_cmd(t_tok *token);
int		cmd_is_path(char *str, char *quote);
char	*find_path(char **multi_path, char *cmd);
/*exec_cmd*/
void	multi_cmd(t_tok *token, t_env *envlst);
int		multi_cmd_2(int *fd, int fdin);
/*gestion_error*/
int		path_is_dir(char *str);
int		gestion_error(t_tok *token, t_env *envlst);
int		path_error(char *str, int error);
int		path_error_2(t_tok *tok);
/*heredoc*/
int		heredoc(char *limiter);
void	reset_signals(void);
void	reset_signals_2(void);
/*trim_cmd*/
int		len_tab(char **cmd);
char	**alloc_tab(char **tab, char **cmd);
char	**trim_cmd(char **cmd);
char	*trim_str(char *cmd);
/*bultins*/
int		manage_bultins(t_tok *token, t_env *envlst, int mode);
int		solo_token_bultins(t_tok *token, t_env *envlst, int mode);
/*manage_execute*/
int		manage_exec(t_tok *token, t_env *envlst);
/*my_exit*/
int		my_exit(t_tok *token, t_env *envlst, int mode);
/*my_echo*/
int		my_echo(t_tok *token);
/*env_lst*/
int		env_lstadd_back(t_env **alst, t_env *new);
t_env	*env_lstlast(t_env *lst);
t_env	*env_lstnew(char *name);
int		env_lstsize(t_env *lst);
void	env_lstclear(t_env *lst);
/*env*/
char	*recup_name(char *env_line);
t_env	*lst_env(char **env);
int		set_value(t_env *envlist);
char	*ft_getenv(t_env *envlst, char *name);
char	**env_lst_to_tab(t_env *envlist);
/*my_env*/
int		my_env(t_tok *token, t_env *envlst);
/*my_cd*/
int		my_cd(t_tok *token, t_env *envliste	);
/*my_export2*/
int		valid_identifier(char *str);
/*my_export*/
int		my_export(t_tok *token, t_env *envlst);
/*my_pwd*/
int		my_pwd(void);
/*my_unset*/
int		my_unset(t_tok *token, t_env *envlst);
/*redir1*/
int		redir_in(t_tok *tok, int i);
void	redir(t_tok *tok);
/*redir2*/
int		skipped_ws(char *content, int i);
int		redir_out(t_tok *tok, int i);
int		clear_content_1(char *content, int i, char *quote);
char	*clear_content(char *content, char *quote, t_tok *tok);
/*rm_quote*/
void	rm_pair(t_tok *tok, int i, char quote_t);
void	rm_quotes(t_tok *tok);
char	*file_name(t_tok *tok, int i, char *str);
/*shell_print*/
int		print_msg(int fd, char *s1, char *s2, char *s3);
void	print_tab(char **tab);
/*execution*/
int		executing(t_tok *token, t_env *envlst);
int		pipex(t_tok *token, t_env *envlst);
int		redir_input(int fdin, t_tok *token);
int		redir_output(int fdout, t_tok *token);
int		exec(t_tok *token, t_env *envlst, int fd[2], int fd_in);
int		builtins(char *str);
void	piping(int fd[2], int fd_in);
t_env	*error_env(void);
/*chev_err*/
int		chev_err(char *str);

#endif
