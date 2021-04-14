#include "handler/handler.h"

int main(int argc, char **argv, char **env)
{
	// handler init
	t_keyval *env_list;

	env_list = handler_init(env);

	char *unset_args[2];

	unset_args[0] = "PATH";
	unset_args[1] = NULL;
	(void) argc;
	char  *arg[3];

	unset_builtin(&env_list, unset_args);
	arg[0] = ft_strdup("ls");
	arg[1] = ft_strdup("-la");
	arg[2] = NULL;
	env_builtin(env_list);
	exec(arg, env_list);

//	char *args[2];
//	args[0] = "K=EKELKRL";
//	args[1] = NULL;
//	unset_builtin(&shell_vars.env, &argv[1]);
//	unset_builtin(&shell_vars.env, &args[0]);
//	puts("<---------------------------------------------------->");
//
//	env_builtin(shell_vars.env);
//	puts("<---------------------------------------------------->");
//
//	pwd_builtin();
//	puts("<---------------------------------------------------->");
//
//	export_builtin(&shell_vars.env, NULL);
//	puts("<---------------------------------------------------->");
//
//	export_builtin(&shell_vars.env, &argv[1]);
//	puts("<---------------------------------------------------->");
//
//	export_builtin(&shell_vars.env, NULL);
//	puts("<---------------------------------------------------->");
//
//	env_builtin(shell_vars.env);
//	puts("<---------------------------------------------------->");
//
//	unset_builtin(&shell_vars.env, &argv[1]);
//	puts("<---------------------------------------------------->");
//
//	export_builtin(&shell_vars.env, NULL);
//	puts("<---------------------------------------------------->");
//	export_builtin(&shell_vars.env, &argv[1]);
//	export_builtin(&shell_vars.env, NULL);
//	puts("<---------------------------------------------------->");
//	unset_builtin(&shell_vars.env, &argv[1]);
//	export_builtin(&shell_vars.env, NULL);

//	char *args[2];
//	args[0] = "../";
//	args[1] = NULL;
//	cd_builtin(&shell_vars.env, args);
//	pwd_builtin();
//
//	args[0] = "-";
//	cd_builtin(&shell_vars.env, args);
//	pwd_builtin();
//
//	args[0] = "/";
//	cd_builtin(&shell_vars.env, args);
//	pwd_builtin();
//
//	args[0] = "~";
//	cd_builtin(&shell_vars.env, args);
//	pwd_builtin();
//	env_builtin(shell_vars.env);


//	env_builtin(shell_vars.env);
	//	puts("<---------------------------------------------------->");
//	while (*env != NULL)
//	{
//		printf("%s\n", *env++);
//	}
//	printf("%s", strerror(errno));

//	t_keyval *tmp = shell_vars.env;
//	t_keyval *tmp_next;
//
//	while (tmp != NULL)
//	{
//		tmp_next = tmp->next;
//		env_free_one(tmp);
//		tmp = tmp_next;
//	}
	return (0);
}
