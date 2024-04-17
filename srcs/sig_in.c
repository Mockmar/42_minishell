
#include "../incl/minishell.h"

void	reset_signals_2(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
