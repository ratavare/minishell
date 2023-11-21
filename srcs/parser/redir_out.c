/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:39 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:16:44 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*redir_out(void)
{
	t_ast	*new_node;
	t_list	*backup;

	backup = get()->tokens_tmp;
	new_node = redir_out_case1();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = redir_out_case2();
	if (new_node)
		return (new_node);
	return (NULL);
}

// ">>" [file]

t_ast	*redir_out_case1(void)
{
	t_ast	*new_node;

	if (!get()->tokens_tmp || !get()->tokens_tmp->next)
		return (NULL);
	if (get()->tokens_tmp->type != AST_OUT || \
		get()->tokens_tmp->next->type != AST_OUT)
		return (NULL);
	get()->tokens_tmp = get()->tokens_tmp->next->next;
	if (!get()->tokens_tmp)
		return (NULL);
	new_node = ast_new_node(AST_RDO_AP);
	new_node->content = ft_strdup(get()->tokens_tmp->content);
	get()->tokens_tmp = get()->tokens_tmp->next;
	return (new_node);
}

// ">" [file]

t_ast	*redir_out_case2(void)
{
	t_ast	*new_node;

	if (!get()->tokens_tmp)
		return (NULL);
	if (get()->tokens_tmp->type != AST_OUT)
		return (NULL);
	get()->tokens_tmp = get()->tokens_tmp->next;
	if ((!get()->tokens_tmp) || (!get()->tokens_tmp->type) == 0)
		return (NULL);
	new_node = ast_new_node(AST_RDO_TR);
	new_node->content = ft_strdup(get()->tokens_tmp->content);
	get()->tokens_tmp = get()->tokens_tmp->next;
	return (new_node);
}
