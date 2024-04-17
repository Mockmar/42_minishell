
#include "../incl/minishell.h"

static void	easy_init(t_tok *token)
{
	token->quote = NULL;
	token->limiter = NULL;
	token->heredoc = NULL;
	token->cmd = NULL;
	token->path = NULL;
	token->type_input = 0;
	token->fd_hdoc = 0;
	token->fd_input = 0;
	token->f_input = NULL;
	token->type_output = 0;
	token->fd_output = 1;
	token->file_output = NULL;
	token->error = 0;
}

int	init_token(t_tok *token, t_env *envlst)
{
	int		flag;
	char	*str;

	flag = 0;
	while (token)
	{
		str = NULL;
		easy_init(token);
		if (envlst)
			str = ft_getenv(envlst, "PATH");
		token->multi_path = ft_split(str, ':');
		if (str)
			free(str);
		if (token->multi_path)
			flag = 1;
		token = token->next;
	}
	return (flag);
}
