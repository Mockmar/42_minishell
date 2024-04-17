
#include "../incl/minishell.h"

void	reset_std(int tpin, int tpout)
{
	dup2(tpin, STDIN_FILENO);
	dup2(tpout, STDOUT_FILENO);
	close(tpin);
	close(tpout);
}

void	save_std(int *tpin, int *tpout)
{
	*tpin = dup(STDIN_FILENO);
	*tpout = dup(STDOUT_FILENO);
}

int	executing(t_tok *token, t_env *envlst)
{
	int	tpin;
	int	tpout;
	int	last_pid;
	int	status;

	last_pid = 0;
	status = 0;
	save_std(&tpin, &tpout);
	last_pid = pipex(token, envlst);
	reset_std(tpin, tpout);
	if (last_pid == -1)
		return (-1);
	if (last_pid > 0)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			g_sig[1] = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sig[1] = WTERMSIG(status) + 128;
	}
	while (wait(&status) != -1)
		continue ;
	return (0);
}
