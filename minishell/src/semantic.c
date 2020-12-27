/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:19 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/27 22:34:25 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "semantic.h"
#include <stdlib.h>
#include <stdio.h>

void	free_super_program(t_program *pr)
{
	void	*ptr;

	ptr = pr->arguments;
	while (ptr && *pr->arguments)
	{
		free(*pr->arguments);
		pr->arguments += 1;
	}
	if (ptr)
		free(ptr);
	if (pr->redirect_filename[0])
		free(pr->redirect_filename[0]);
	if (pr->redirect_filename[1])
		free(pr->redirect_filename[1]);
}

void	free_super_programs(t_super *sp)
{
	int		i;
	void	*ptr;

	i = 0;
	while (i < sp->count)
	{
		free_super_program(&sp->programs[i]);
		i += 1;
	}
	sp->count = 0;
}

void	free_super(t_super **psp)
{
	if (*psp)
	{
		if ((*psp)->tkz)
			tkz_free(&(*psp)->tkz);
		if ((*psp)->count)
			free_super_programs(*psp);
		if ((*psp)->programs)
			free((*psp)->programs);
		free(*psp);
		*psp = 0;
	}
}

t_super	*init_super(void)
{
	t_super	*super;

	super = malloc(sizeof(t_super));
	if (super)
	{
		super->cap = 16;
		super->programs = malloc(sizeof(t_program) * super->cap);
		if (super->programs)
		{
			super->count = 0;
			super->tkz = tkz_init();
			super->tkz_error = TKZ_SUCCESS;
			super->current_token = 0;
			if (!super->tkz)
				free_super(&super);
		}
		else
			free_super(&super);
	}
	return (super);
}

void	init_super_program(t_program *pr)
{
	pr->arguments = 0;
	pr->redirect_filename[0] = 0;
	pr->redirect_filename[1] = 0;
	pr->flags = 0;
	pr->fd[0] = 0;
	pr->fd[1] = 1;
}

int		is_super_error(int error)
{
	return (error != SUP_SUCCESS);
}

typedef const char t_cchar;

t_cchar	*super_error_str(int error)
{
	if (error == SUP_ERROR)
		return ("unrecognized error");
	else if (error == SUP_ERROR_NO_ARGUMENTS)
		return ("no arguments");
	else if (error == SUP_ERROR_MALLOC_NULL_RETURN)
		return ("malloc null return");
	else if (error == SUP_ERROR_INVALID_REDIRECTION_SYNTAX)
		return ("invalid redirection syntax");
	else if (error == SUP_ERROR_MISSING_REDIRECTION_FILE)
		return ("missing redirection file");
	else if (error == SUP_ERROR_INVALID_REDIRECTION_FILE)
		return ("invalid redirection file");
	else if (error == SUP_ERROR_UNRECOGNIZED_REDIRECTION)
		return ("unrecognized redirection");
	else if (error == SUP_ERROR_INVALID_EXEC_SEPARATION)
		return ("invalid exec separation");
	else if (error == SUP_ERROR_INVALID_PIPE_SYNTAX)
		return ("invalid pipe syntax");
	else
		return (tkz_error_str(error));
}

int		is_token_redirect(t_token *tkn)
{
	int		ret;

	ret = 0;
	if (tkn->len == 1 && (tkn->mem[0] == '>' || tkn->mem[0] == '<'))
		ret = 1;
	else if (tkn->len == 2 && (tkn->mem[0] == '>' && tkn->mem[1] == '>'))
		ret = 1;
	return (ret);
}

int		is_token_pipe(t_token *tkn)
{
	return (tkn->len == 1 && tkn->mem[0] == '|');
}

int		is_token_argument(t_token *tkn)
{
	return (tkn->len > 0 && !is_token_redirect(tkn) && !is_token_pipe(tkn));
}

t_token	*get_current_token(t_super *sp)
{
	t_token	*tkn;

	tkn = 0;
	if (sp->current_token >= 0 && sp->current_token < sp->tkz->tkn_count)
		tkn = &sp->tkz->tkn[sp->current_token];
	return (tkn);
}

t_token	*get_offseted_token(t_super *sp, int offset)
{
	int		token_start;
	t_token	*tkn;

	token_start = sp->current_token;
	sp->current_token += offset;
	tkn = get_current_token(sp);
	sp->current_token = token_start;
	return (tkn);
}

void	increment_token_pointer(t_super *sp)
{
	if (sp->current_token < sp->tkz->tkn_count)
		sp->current_token += 1;
}

void	move_token_pointer(t_super *sp, int offset)
{
	sp->current_token += offset;
}

int		count_super_program_arguments(t_super *sp)
{
	int		count;
	t_token	*tkn;

	count = 0;
	while ((tkn = get_current_token(sp)))
	{
		if (is_token_argument(tkn))
			count += 1;
		else
			break ;
		increment_token_pointer(sp);
	}
	move_token_pointer(sp, -count);
	return (count);
}

void	sp_memcpy(void *l, void *r, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)l)[i] = ((unsigned char *)r)[i];
		i += 1;
	}
}

int		copy_token_string(t_token *tkn, char **pstr)
{
	if (*pstr)
		free(*pstr);
	(*pstr) = malloc(tkn->len + 1);
	if (!(*pstr))
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	sp_memcpy((*pstr), tkn->mem, tkn->len);
	(*pstr)[tkn->len] = '\0';
	return (SUP_SUCCESS);
}

int		token_compare(t_token *tkn, const char *str, int len)
{
	int		i;

	if (tkn->len != len)
		return (0);
	i = 0;
	while (i < len && i < tkn->len && tkn->mem[i] == str[i])
		i += 1;
	return (i >= len);
}

int		make_super_program_arguments(t_super *sp, t_program *pr)
{
	int		count;
	int		error;
	t_token	*tkn;
	int		i;

	count = count_super_program_arguments(sp);
	if (!count)
		return (SUP_ERROR_NO_ARGUMENTS);
	pr->arguments = malloc(sizeof(char *) * (count + 1));
	if (!pr->arguments)
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	error = SUP_SUCCESS;
	i = 0;
	while (!is_super_error(error) && i < count)
	{
		tkn = get_offseted_token(sp, i);
		pr->arguments[i] = 0;
		error = copy_token_string(tkn, &pr->arguments[i]);
		i += 1;
	}
	pr->arguments[i] = 0;
	move_token_pointer(sp, count);
	return (error);
}

int		recognize_program_redirection(t_program *pr, t_token *rd, t_token *fn)
{
	int		error;

	if (token_compare(rd, "<", 1))
	{
		pr->flags |= SUP_REDIRECTION_IN_FLAG;
		error = copy_token_string(fn, &pr->redirect_filename[0]);
	}
	else if (token_compare(rd, ">", 1))
	{
		pr->flags |= SUP_REDIRECTION_OUT_FLAG;
		pr->flags &= ~SUP_REDIRECTION_OUT_APPEND_FLAG;
		error = copy_token_string(fn, &pr->redirect_filename[1]);
	}
	else if (token_compare(rd, ">>", 2))
	{
		pr->flags |= SUP_REDIRECTION_OUT_APPEND_FLAG;
		pr->flags &= ~SUP_REDIRECTION_OUT_FLAG;
		error = copy_token_string(fn, &pr->redirect_filename[1]);
	}
	else
		error = SUP_ERROR_UNRECOGNIZED_REDIRECTION;
	return (error);
}

int		make_super_program(t_super *sp, t_program *pr, int *remains)
{
	int		error;
	t_token	*tkn;
	t_token	*tkn_n;

	init_super_program(pr);
	error = make_super_program_arguments(sp, pr);
	while ((tkn = get_current_token(sp)) && !is_super_error(error) &&
		!is_token_pipe(tkn))
	{
		if (!is_token_redirect(tkn))
			return (SUP_ERROR_INVALID_REDIRECTION_SYNTAX);
		increment_token_pointer(sp);
		tkn_n = get_current_token(sp);
		if (!tkn_n)
			return (SUP_ERROR_MISSING_REDIRECTION_FILE);
		if (!is_token_argument(tkn_n))
			return (SUP_ERROR_INVALID_REDIRECTION_FILE);
		increment_token_pointer(sp);
		error = recognize_program_redirection(pr, tkn, tkn_n);
	}
	if (!is_super_error(error) && tkn && is_token_pipe(tkn))
		pr->flags |= SUP_REDIRECTION_PIPE_FLAG;
	*remains = !!tkn;
	return (error);
}

int		expand_super_programs_array(t_super *sp)
{
	int		new_cap;
	void	*new_ptr;

	new_cap = sp->cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	new_ptr = malloc(sizeof(t_program) * new_cap);
	if (!new_ptr)
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	if (sp->programs)
	{
		sp_memcpy(new_ptr, sp->programs, sizeof(t_program) * sp->count);
		free(sp->programs);
	}
	sp->programs = new_ptr;
	sp->cap = new_cap;
	return (SUP_SUCCESS);
}

int		rechange_error(t_super *sp, int remains, int error)
{
	if (error == SUP_ERROR_NO_ARGUMENTS && (remains || sp->count > 0))
		error = SUP_ERROR_INVALID_PIPE_SYNTAX;
	else
		error = SUP_SUCCESS;
	return (error);
}

void	delete_last_program(t_super *sp)
{
	if (sp->count - 1 >= 0)
	{
		free_super_program(&sp->programs[sp->count - 1]);
		sp->count -= 1;
	}
}

int		make_super(t_super *sp)
{
	int		error;
	int		remains;
	t_token	*tkn;

	free_super_programs(sp);
	sp->current_token = 0;
	error = tkz_make(sp->tkz);
	sp->tkz_error = error;
	//tkz_print_lite(sp->tkz);
	if (tkz_is_error(error) && !(error == TKZ_ERROR_UNISTD_READ_EOF &&
			sp->tkz->tkn_count != 0))
		return (error);
	if (is_super_error((error = make_super_program(sp, &sp->programs[sp->count++], &remains))))
		delete_last_program(sp);
	while (!is_super_error(error) && remains)
	{
		tkn = get_current_token(sp);
		if (!is_token_pipe(tkn))
			return (SUP_ERROR_INVALID_EXEC_SEPARATION);
		increment_token_pointer(sp);
		if (sp->count >= sp->cap)
			error = expand_super_programs_array(sp);
		if (!is_super_error(error))
			error = make_super_program(sp, &sp->programs[sp->count++], &remains);
	}
	error = rechange_error(sp, remains, error);
	return (error);
}

void	print_super(t_super *sp)
{
	int		i;
	int		j;

	i = 0;
	while (i < sp->count)
	{
		printf("program[%d]\n", i);
		printf(" - args:");
		j = 0;
		while (sp->programs[i].arguments && sp->programs[i].arguments[j])
		{
			printf(" %s", sp->programs[i].arguments[j]);
			j += 1;
		}
		printf("\n - redirect[0]: %s\n - redirect[1]: %s\n",
			sp->programs[i].redirect_filename[0], sp->programs[i].redirect_filename[1]);
		printf(" - flags:");
		if (sp->programs[i].flags & SUP_REDIRECTION_IN_FLAG)
			printf(" IN");
		if (sp->programs[i].flags & SUP_REDIRECTION_OUT_FLAG)
			printf(" OUT");
		if (sp->programs[i].flags & SUP_REDIRECTION_OUT_APPEND_FLAG)
			printf(" OUT_APPEND");
		if (sp->programs[i].flags & SUP_REDIRECTION_PIPE_FLAG)
			printf(" PIPE");
		printf("\n");
		i += 1;
	}
}
