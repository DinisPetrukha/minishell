/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:44:56 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 13:04:50 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>

# define NL 0
# define JOB 1
# define CMD 2
# define REDIR 3
# define NAME 4
# define TOKEN 5
# define PATH_MAX 1024
# define BUFFERSIZE 42

# define SYN_ERROR1 "bash: unexpected EOF while looking for matching"
# define SYN_ERROR2 "bash: syntax error near unexpected token '"
# define SYN_ERROR3 "bash: syntax error near unexpected token '"

typedef struct s_tree
{
	int				id;
	int				fid;
	int				pipefd[2];
	char			*content;
	int				pipe_flag;
	int				redir_type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_herelist
{
	int					fd;
	char				*content;
	char				*str;
	struct s_herelist	*next;
}	t_herelist;

typedef struct s_lexer
{
	int			report;
	int			start;
	int			end;
	int			in_quote;
	int			in_redir;
	int			willexpand;
	int			pipe_flag;
	int			child;
	int			sflag;
	int			status;
	char		**env;
	t_tree		*tree;
	t_herelist	*herelist;
}	t_lexer;

typedef enum e_signals
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE
}	t_signals;

int		pipe_in_str(char *str, int *i);
//E_REFORKED.C
t_tree	*left_cmd(t_tree *tree);
void	popfirst(t_herelist **head, t_lexer *lexer);
t_tree	*find_cmd(t_tree *tree);
char	*hereexpander(char *new, t_lexer *lexer, int dolexpand, int i);
void	printlist(t_herelist *head);

int		findheredir(char *str);
int		new_node(t_herelist **head, char *content, char *str, int fd);
void	changelast_node(t_herelist **head, int newfd);
void	free_nodes(t_herelist **head);

char	*set_command(char *str);
char	**join_tokens(t_tree *tree, int n_tokens);
int		pipecount(t_tree *tree);
int		openinfile(t_tree *tree, t_lexer *lexer, t_herelist *herelist);
int		openoutfile(t_tree *tree);
int		openfiles(t_tree *tree, t_tree *cmd, t_lexer *lexer);
int		closeclean(int fd, int force);
int		error_return(char *str, int exit_status);
int		setfds(t_tree *tree, t_tree *cmd, int prevpipe, t_lexer *lexer);
void	closeall_fd(t_tree *cmd);
void	waiter(t_tree *cmd, t_lexer *lexer);
int		executive(t_tree *tree, t_tree *reset, t_lexer *lexer, int retpipe);
int		find_nid(t_tree *tree, int id);

//HEREDOC
int		pre_heredoc(char *str, int i);
int		init_heredoc(t_herelist **head, char *str, t_lexer *lexer, int i);
int		ft_heredoc(char *eof, t_lexer *lexer, t_herelist **head);
int		read_heredoc(int piper[2], char *eof, t_lexer *lexer,
			t_herelist **head);
void	heredoc_childprocess(int piper[2], char *eof, t_lexer *lexer);

//P_BIGIS.C
int		str_extracall(char *str, char **untied, t_lexer *lexer, int i);
int		isjob(char *str);
char	*iscmd(char *str, t_lexer *lexer);
int		quote_skipper(char *str);
int		str_skipper(char *str);
char	*str_untier(char *str, t_lexer *lexer, int i, int j);
char	*quote_untier(char *str, t_lexer *lexer, int i);
int		space_skipper(char *str);

//P_DOLLAR.C
int		dollar_join(char *str, char **ret, t_lexer *lexer, int i);
int		ft_islnu(int c);
int		addtostr(char **ret, char **from);
char	**matcpy(char **mat);
char	*ft_getenv(char **envir, char *str);
char	*weak_quote(char *str, t_lexer *lexer, int i);
char	*stro_quote(char *str);

//P_ENVIR.C
char	*ret_free(char **str, char **mat);
char	**set_pather(char **mat);
char	*check_env(char **cmd);
char	*cmd_path(char *cmd, char **pather, int i);
char	*check_dir(char *cmd);

//P_NODES.C
char	*expanddollar(char *new, t_lexer *lexer, int i, int inquote);
int		anulsflag(t_lexer *lexer);
int		tree_init(t_tree **tree, t_lexer *lexer, char *str);
char	*emptyclean(char *str, t_lexer *lexer, int i);

//P_PARSER.c
void	parser(t_tree *node, t_lexer *lexer, int cmd_found);
void	add_right(t_tree *tree, t_lexer *lexer, char *str, int id);
int		add_left(t_tree *tree, t_lexer *lexer, char *str, int id);

//P_STRINGS.c
int		charnstr(char *s, int c);
int		onlyspacestr(char *str);
int		onlyspacestr(char *str);
int		quotealternate(int nbr, int compare);
void	dolquotehandle(char *str);
int		str_skipper(char *str);

//P_TREE_INIT.c
int		ifexist(char *str, int i);
int		tree_init(t_tree **tree, t_lexer *lexer, char *str);

//P_REDIR.C
int		ft_islnudsq(int c);
int		ft_islnudsqi(int c);
int		set_redir(char *str, t_lexer *lexer, int i, int inquote);
char	*isredir(char *str, t_lexer *lexer, int hereactive);

//P_REMAIN.C
void	strnotstr(char *dst, char *src, int start, int end);
int		emptystring(char *str);
char	*remain(char *str, t_lexer *lexer);
char	*remain_calc(char *str, t_lexer *lexer, int j);

//MAIN.C
void	tree_reader(t_tree *tree, int n);

//BUILTINS
void	pipeignore(int fd);
void	builtins(t_tree *reset, char **mat, t_lexer *lexer, int pipenbr);
int		b_echo(char **mat);
int		b_pwd(void);

// CD
int		b_cd(char **mat, int tofree, t_lexer *lexer);

// EXPORT
int		exports_loop(char	**mat, t_lexer *lexer);
int		export(char *key_value, char ***envp);
int		append_env(char *key_value, char ***envp);
void	unset_env(char *key, char ***envp);

// EXPORT_UTILS
int		is_in_env(char *key, char **envp);
int		is_valid_key_value(char *arg, char **token);

// UNSET
int		unset_loop(char **mat, t_lexer *lexer);
int		unset(char *key_value, char ***envp);

// SIGACTION
void	get_status(int sts);

//CHECKSINTAX UTILS
int		checksyntax(char *str, int i, int number);
int		syntaxpipe(char *str, int before_pipe, char **syntax);
int		sr(char *str, char symbol, char **token);
int		syntaxquotes(char *str, char quote, int *i);
char	*symbols_ret(char *str);

// CHECKSYNTAX
int		print_syntaxerror(char *str_error, char *token, int dir);

void	b_exit(char **mat, t_lexer *lexer, t_tree *reset);
void	bubble_sort(char **mat);

void	closenodefds(t_tree *tree);
void	closeall_fd(t_tree *tree);
int		closeclean(int fd, int force);
int		setfds(t_tree *tree, t_tree *cmd, int prevpipe, t_lexer *lexer);
int		verify_inout(t_tree *cmd, int infile, int outfile, int fdstatus);

// E_ERROR_RETURN
void	exit_exec(t_tree *reset, t_tree *tree, t_lexer *lexer, char **full);
int		error_return(char *str, int exit_status);
void	directexit(char *str, int status);
void	checkreport(t_tree *tree, t_lexer *lexer, char *line, int force);
int		free_return(t_tree *reset, t_lexer *lexer, char **full, int value);

void	free_nodes(t_herelist **head);
void	totalfree(t_tree *reset, t_lexer *lexer, char **full);
void	free_mat(char **mat);
void	tree_free(t_tree *tree);
int		free_and_error(char ***envp, char *error);

void	onlyredir(t_tree *tree, t_lexer *lexer);
int		ft_isspace(int c);

//	SIGNAL
void	handle_sigint(int sig, siginfo_t *info, void *context);
void	handle_heredoc(int sig, siginfo_t *info, void *context);
void	sig_ignore(struct sigaction *sa, int signal);
void	setup_signal_handlers(t_signals sig);
void	signal_main(struct sigaction sa);
void	signal_child(struct sigaction sa);
void	signal_heredoc(struct sigaction sa);

// ENVIR UTILS
void	increment_shlvl(char **envp);
char	**ft_enviroment(char **envp);
char	*ft_getenv(char **envir, char *str);

// READLOOP
void	checkreport(t_tree *tree, t_lexer *lexer, char *line, int force);
void	tree_sorter(t_tree *tree, t_lexer *lexer, char *line,
			t_herelist *herelist);
void	shell_machine(char *line, t_herelist *herelist, t_lexer *lexer);
char	*input_line(t_lexer *lexer);
void	read_loop(t_lexer *lexer, t_herelist *herelist);
char	*get_cur_directory(t_lexer *lexer, int dollar);

//REFORKED UTILS
int		pipecount(t_tree *tree);
t_tree	*find_cmd(t_tree *tree);
t_tree	*left_cmd(t_tree *tree);

// P_QUOTES
int		quote_skipper(char *str);
int		find_samequote(char *str, int i);
char	*quote_untier(char *str, t_lexer *lexer, int i);

//P_NODES_UTILS
char	*isname(char *str, t_lexer *lexer);
char	*dollar_sign(char *str, t_lexer *lexer);
int		cleandollar(char *new, int *i);
void	skip_question(int *i, char *new);
int		skip_lnu(char *str, int i);

int		error_heredoc(t_herelist **head, char *redir, char *str, int level);
int		s_sts(int new_status);
int		s_here(int new_status);

#endif
