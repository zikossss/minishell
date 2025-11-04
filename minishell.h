/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajabir <zajabir@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:59:26 by zajabir           #+#    #+#             */
/*   Updated: 2025/08/15 23:28:37 by zajabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_mini
{
	char	**envirenement;
	char	**env;
	char	**exportenv;
	char	**commands;
	char	**path;
	char	**tokens;
	char	**pipecommand;
	char	*linefromread;
	char	*oldpwd;
	char	*newpwd;
	char	*heredocdelimiter;
	int		**pipefd;
	char	**files;
	char	*file;
	int		cn_flag;
	int		compos;
	int		expand;
	int		xpipe;
	int		pid;
	int		okay;
	int		fd;
	int		infd;
	int		is_pwd;
	int		infile;
	int		outfile;
	int		heredoc;
	int		isbuiltin;
	int		stat;
	int		inflag;
	int		outflag;
	int		heredocfd;
	int		start;
	int		v;
	int		isambiguous;
}			t_mini;

# define OLDPWD "OLDPWD="
# define PWD "PWD="
# define DEC "declare -x "

extern int	g_var_for_signal;

/////////////////// builts-in ///////////////////

/////////////////// cd utils ///////////////////
int			check_to_many_args(t_mini *ls);
int			ft_dir_form(char *s, int c);
int			cwd_error(t_mini *ls, char *cwd);

/////////////////// cd ///////////////////
int			check_error(t_mini *ls, int *index);
int			parce_cd_arg(t_mini *ls, int index);
int			get_new_pwd(t_mini *ls);
void		cd(t_mini *ls, int *index);

/////////////////// echo utils ///////////////////
void		ft_putstr_fd1(char *s, int fd);
int			count_pending(char *str);

/////////////////// echo ///////////////////
int			is_new_line(char **line, int *i);
void		print_fd(t_mini *ls);
int			count_non_redirections(t_mini *ls);
char		**parce_line(t_mini *ls);
void		echo(t_mini *ls, int *i);

/////////////////// env utils ///////////////////
int			ft_strcount(char **arr);
void		print_env(t_mini *ls);
int			find_equal1(char *str);

/////////////////// env ///////////////////
void		sort_env(char **env);
void		ch_env(char ***env, t_mini *ls);
char		**copy_env(t_mini *ls, char **env);
void		vars_only(char **var, int i);
void		env(t_mini *ls);

/////////////////// export utils3 ///////////////////
char		**new_env(char *line, t_mini *ls);
int			countquote(char *line);

/////////////////// export utils2 ///////////////////
int			ft_str_count(t_mini *ls);
int			find_equal(char *str);
int			there_is_quotes(char *s);
int			there_is_quotes_ex(char *s);
int			is_valide_var(char *s);

/////////////////// export utils1 ///////////////////
int			calculate_size(char *s);
void		copy_and_quote(char *s, char *p);
char		*ft_strdup1(char *s);
int			replace_env(t_mini *ls, char *line);
char		**add_new_env(t_mini *ls, char *line);

/////////////////// export ///////////////////
void		parce_new_line(char *line, char *new_line, int i, int j);
char		*parse_line(char *line);
void		addvalid_arg(t_mini *ls, int index);
void		print_export(t_mini *ls, int index);
void		export(t_mini *ls, int *index);

/////////////////// pwd ///////////////////
void		pwd(t_mini *ls);

/////////////////// unset //////////////////
void		update_env(t_mini *ls);
void		unset(t_mini *ls, int *index);

/////////////////// exit ///////////////////
int			check_n_arg_r(t_mini *ls, int j);
int			check_arguments(t_mini *ls);
void		free_befor_exit(t_mini *ls);
void		my_exit(t_mini *ls);

/////////////////// builts-in ///////////////////

/////////////////// helper function6 ///////////////////
int			ft_isnumber(int c);
char		*ft_itoa(int n);
long int	ft_atoi(char *nptr);

/////////////////// helper function5 ///////////////////
void		ft_free(char ***arr);
char		*ft_joinofvar(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_isalnum(int c);
void		ft_strnncpy(char *dst, char *src, unsigned int n);

/////////////////// helper function4 ///////////////////
char		*ft_strdup(char *s);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strcpy(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_join_var_exp(char *s1, char *s2);

/////////////////// helper function3 ///////////////////
int			cowntswords(char *s, char c);
char		**ft_split(char *s, char c);

/////////////////// helper function2 ///////////////////
char		**ft_splitpath(char *s, char c, char *commandname);

/////////////////// helper function1 ///////////////////
int			isclose(t_mini *ls);
int			thereispipe(t_mini *ls);
void		ft_putstr_fd(char *s, int fd);
int			isbuiltin(char *arg);
void		dobuiltin(t_mini *ls, int *index);

/////////////////// helper function ///////////////////
int			checkquoteclosed(char *line, int *i, char c);
int			ft_strchar(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_ln(char *s, char c, int j);

/////////////////// signals ///////////////////
void		handler(int signum);
void		recievesignals(void);
void		handler1(int signum);
void		heredoc_signal(void);
void		reset_sihandler(void);

/////////////////// redirections ///////////////////
int			dostdout(char *filename, t_mini *ls);
int			doappend(char *filename, t_mini *ls);
int			dostdin(char *filename, t_mini *ls);
int			checkwhichtodo(int x, t_mini *ls, int i);
int			isredirection(t_mini *ls, int i);

/////////////////// variable expantion3 ///////////////////
void		treat_it_with_dquote(t_mini *ls, int *i, int *j, char **commands);
void		resplit_tokens(t_mini *ls, char **commands);
void		update_it(char **commands, int i, char *varname, char *editedptr);
char		*update_var(t_mini *ls, int j, int i, char **commands);

/////////////////// variable expantion2 ///////////////////
char		*create_substr_dq(char **line, int x, int *j, int i);
int			is_validchar(char c);
char		**join_and_split(t_mini *ls, char **commands);
int			check_only_quotes(char *str);
char		*create_substr(char *line, char *substr, int *j);

/////////////////// variable expantion1 ///////////////////
char		*takevalue(t_mini *ls, char *varname, int n);
char		*findvar(t_mini *ls, char *nameofvar);
char		*getvarname(t_mini *ls, char *line, int j);
char		*replace_it(char *line, int *j, char *varvalue, char *nameofvar);
char		*replacevar(t_mini *ls, char *line, int *j);

/////////////////// variable expantion ///////////////////
void		treatdquotesvar(t_mini *ls, int *i, int *j, char **commands);
void		treat_normal(t_mini *ls, int *i, int *j, char **commands);
void		treatnormalvar(t_mini *ls, int *i, int *j, char **commands);
void		no_treat(t_mini *ls, char **command, int i, int *j);
void		variablexpantion(t_mini *ls, char **commands);

/////////////////// command execution utils1 ///////////////////
void		dupfor_pipe(t_mini *ls);
void		dupfor(t_mini *ls);
void		closepipefds(t_mini *ls);
void		builtin_execute_child(t_mini *ls, int *i);
void		protect_malloc(t_mini *ls, void *str);

/////////////////// command execution utils ///////////////////
char		*my_getenv(t_mini *ls, char *var);
int			check_pd_cf(t_mini *ls, int i);
int			isaccesiblecommand(t_mini *ls, int i);
void		execute_child(t_mini *ls, int i);

/////////////////// command execution ///////////////////
void		addonetoclose(t_mini *ls, int x);
int			thecorrectfd(t_mini *ls);
int			fork_built_ins(t_mini *ls, int *i);
int			aboutbuiltin(t_mini *ls, int *i);
void		commandexec(t_mini *ls);

/////////////////// execution utils ///////////////////
int			pipecount(t_mini *ls);
int			countpointers(t_mini *ls, int *n);
char		**getcommand(t_mini *ls, int *f);
int			dopipe(t_mini *ls);
int			emptystring_error(t_mini *ls);

/////////////////// execution ///////////////////
void		initff(t_mini *ls);
int			ft_fork(t_mini *ls, int i);
void		ft_freepipe(t_mini *ls);
void		update_exitstat(t_mini *ls);
void		execution(t_mini *ls);

/////////////////// heredoc_utils2 ///////////////////
int			toexpand(t_mini *ls);
int			protect_syscall(int fd);
int			count_herdoc(char **tokens);

/////////////////// heredoc_utils1 ///////////////////
int			heredoc_handler(t_mini *ls, char *line, char *delimiter);
int			aretheyoption(t_mini *ls);
int			size_to_alloc(char *str);
char		*correct_heredoc(t_mini *ls, char *limiter);

/////////////////// heredoc ///////////////////
int			run_herdoc(t_mini *ls, char *line, char *cor_limetter);
int			fileforheredoc(t_mini *ls);
int			doheredoc(t_mini *ls);
int			begin_herdoc(t_mini *ls, int x, int i);
int			itsheredoc(t_mini *ls);

/////////////////// parsing ///////////////////
int			amoperator(t_mini *ls, char *token, char *nexttoken);
int			parseline(t_mini *ls);

/////////////////// utilsofsplittotokens2 ///////////////////
int			normal_word_alloc(int len, char **string, int *i, char *f);
int			insidequotesalloc(char *f, int *j, char **string, int *i);
int			alloc_and_copy_for_operator(char **string, int *i, char *f, int *j);
void		count_operator(char *f, int *j, int *count);
int			ftfree(int i, void ***string);

/////////////////// utilsofsplittotokens1 ///////////////////
void		skippinside(char *s, char c, int *i);
void		countoperator(char *s, int *j);
void		ftskipxcount(char *s, char c, int *i, int *j);
void		no_operator_skip(char *s, int *i);
int			cowntword(char *s);

/////////////////// splittotokens ///////////////////
int			operatoralloc(char *f, int *j, char **string, int *i);
int			wordalloc(char *f, int *j, char **string, int *i);
char		**str(char *f, char **string, int i, int x);
char		**ft_tokens(t_mini *ls, char *f);

/////////////////// begin work ///////////////////
void		child_clean_up(t_mini *ls);
int			check_stat(t_mini *ls, int i);
int			execute_command(t_mini *ls, int i);
void		isfrompath(t_mini *ls, int i);
void		begin_work(t_mini *ls);

/////////////////// main utils 2 ///////////////////
void		clean_up(t_mini *ls, int i, void ***arr);
void		init_intigires(t_mini *ls);
void		init_struct(t_mini *ls);

/////////////////// main utils 1 ///////////////////
void		ft_str_error(t_mini *ls, char *str, char *arg);
char		*getinput(char *str);
int			ft_isspaces(char *line);
void		reinit(t_mini *ls);
void		run_program(t_mini *ls, char **envp);

/////////////////// main ///////////////////

#endif