/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:37:57 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:54:49 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int			tkz_is_error(int error)
{
	return (error != TKZ_SUCCESS);
}

const char	*tkz_error_str2(int error)
{
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_NORMAL_ESCAPE)
		return ("contract is terminated for backslash normal escape");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE)
		return ("contract is terminated for backslash dquote escape");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL)
		return ("contract is terminated for dollar symbol");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUATION_MARK_SYMBOL)
		return ("contract is terminated for quation mark symbol");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER)
		return ("contract is terminated for control character");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUOTE_SYMBOL)
		return ("contract is terminated for quote symbol");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DQUOTE_SYMBOL)
		return ("contract is terminated for dquote symbol");
	return ("undefined value");
}

const char	*tkz_error_str(int error)
{
	if (error == TKZ_ERROR)
		return ("unrecognized error.");
	else if (error == TKZ_ERROR_PREFETCH_REQUEST_OVERFLOW)
		return ("prefetch request overflow");
	else if (error == TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN)
		return ("unistd read negative return");
	else if (error == TKZ_ERROR_UNISTD_READ_EOF)
		return ("unistd read eof");
	else if (error == TKZ_ERROR_MALLOC_NULL_RETURN)
		return ("malloc null return");
	else if (error == TKZ_ERROR_INVALID_DOLLAR_SYNTAX)
		return ("invalid dollar syntax");
	else if (error == TKZ_ERROR_UNEXPECTED_EOF_WHILE_QUOTE)
		return ("unexpected EOF while looking for matching `''");
	else if (error == TKZ_ERROR_UNEXPECTED_EOF_WHILE_DQUOTE)
		return ("unexpected EOF while looking for matching `\"'");
	else
		return (tkz_error_str2(error));
	return ("undefined value");
}
