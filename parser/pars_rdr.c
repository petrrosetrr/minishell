
#include "../includes/minishell.h"

static int	pars_rdr_out(t_param *param, t_rdr *rdr_out, int *i)
{
	(*i)++;
	while (rdr_out->next)
		rdr_out = rdr_out->next;
	if (rdr_out->f_name)
	{
		rdr_out->next = init_rdr();
		rdr_out = rdr_out->next;
	}
	rdr_out->type = R_REWRITE;
	if (param->com[*i] && param->com[*i] == '>' && ++(*i))
		rdr_out->type = R_APPEND;
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|< ", param->com[*i]))
	{
		if (!rdr_out->f_name)
			rdr_out->f_name = ft_calloc(2, sizeof(char));
		if (param->com[*i] == '\'')
			pars_quo_one(param, &rdr_out->f_name, i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &rdr_out->f_name, i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &rdr_out->f_name, i);
		else if (param->com[*i] == '$')
			pars_env(param, &rdr_out->f_name, i);
		else
		{
			join_symbol(&(rdr_out->f_name), param->com[*i]);
			(*i)++;
		}
	}
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
		(*i)++;
	return (0); // FIXME если пустая строка, удалять RDR ?
}

static int	pars_rdr_in(t_param *param, t_rdr *rdr_in, int *i)
{
	(*i)++;
	while (rdr_in->next)
		rdr_in = rdr_in->next;
	if (rdr_in->f_name)
	{
		rdr_in->next = init_rdr();
		rdr_in = rdr_in->next;
	}
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|< ", param->com[*i]))
	{
		if (!rdr_in->f_name)
			rdr_in->f_name = ft_calloc(2, sizeof(char));
		if (param->com[*i] == '\'')
			pars_quo_one(param, &rdr_in->f_name, i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &rdr_in->f_name, i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &rdr_in->f_name, i);
		else if (param->com[*i] == '$')
			pars_env(param, &rdr_in->f_name, i);
		else
		{
			join_symbol(&(rdr_in->f_name), param->com[*i]);
			(*i)++;
		}
	}
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
		(*i)++;
	return (0);
}

int			pars_rdr(t_param *param, t_rdr **rdr_out, t_rdr **rdr_in, int *i)
{
	t_rdr *temp;

	while (param->com[*i] && !ft_rhr(";|", param->com[*i]))
	{
		if (param->com[*i] == '>')
		{
			if (!*rdr_out)
				*rdr_out = init_rdr();
			pars_rdr_out(param, *rdr_out, i);
		}
		else if (param->com[*i] == '<')
		{
			if (!*rdr_in)
				*rdr_in = init_rdr();
			pars_rdr_in(param, *rdr_in, i);
		}
		if (*rdr_out)
		{
			temp = *rdr_out;
			while ((*rdr_out)->next)
				*rdr_out = (*rdr_out)->next;
			if (temp == *rdr_out && !((*rdr_out)->f_name))
				temp = NULL;
			if (!((*rdr_out)->f_name))
				free(*rdr_out);
			*rdr_out = temp;
		}
		if (*rdr_in)
		{
			temp = *rdr_in;
			while ((*rdr_in)->next)
				*rdr_in = (*rdr_in)->next;
			if (temp == *rdr_in && !((*rdr_in)->f_name))
				temp = NULL;
			if (!((*rdr_in)->f_name))
				free(*rdr_in);
			*rdr_in = temp;
		}
	}
	return (0);
}
