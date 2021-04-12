#include "builtins.h"

int main(int argc, char **argv, char **env)
{
	t_shell shell_vars;
	(void) argc;
	shell_vars.env = env_to_list(env);

	char *args[2];
	args[0] = "K=EKELKRL";
	args[1] = NULL;
	unset_builtin(&shell_vars.env, &argv[1]);
	unset_builtin(&shell_vars.env, &args[0]);
	puts("<---------------------------------------------------->");

	env_builtin(shell_vars.env);
	puts("<---------------------------------------------------->");

	pwd_builtin();
	puts("<---------------------------------------------------->");

	export_builtin(&shell_vars.env, NULL);
	puts("<---------------------------------------------------->");

	export_builtin(&shell_vars.env, &argv[1]);
	puts("<---------------------------------------------------->");

	export_builtin(&shell_vars.env, NULL);
	puts("<---------------------------------------------------->");

	env_builtin(shell_vars.env);
	puts("<---------------------------------------------------->");

	unset_builtin(&shell_vars.env, &argv[1]);
	puts("<---------------------------------------------------->");

	export_builtin(&shell_vars.env, NULL);
	puts("<---------------------------------------------------->");
	export_builtin(&shell_vars.env, &argv[1]);
	export_builtin(&shell_vars.env, NULL);
	puts("<---------------------------------------------------->");
	unset_builtin(&shell_vars.env, &argv[1]);
	export_builtin(&shell_vars.env, NULL);

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
