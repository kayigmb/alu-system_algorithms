#include "graphs.h"

/**
 * edge_exists - checks if an edge already exists
 * @src: source vertex
 * @dst: destination vertex
 * Return: 1 if exists, 0 otherwise
 */
static int edge_exists(vertex_t *src, vertex_t *dst)
{
	edge_t *curr;

	for (curr = src->edges; curr; curr = curr->next)
	{
		if (curr->dest == dst)
			return (1);
	}
	return (0);
}

/**
 * insert_edge_sorted - insert edge in sorted order
 * @src: source vertex
 * @dst: destination vertex
 * Return: 1 on success, 0 on failure
 */
static int insert_edge_sorted(vertex_t *src, vertex_t *dst)
{
	edge_t *new, *curr;

	new = calloc(1, sizeof(*new));
	if (!new)
		return (0);

	new->dest = dst;

	if (!src->edges || dst->index < src->edges->dest->index)
	{
		new->next = src->edges;
		src->edges = new;
		src->nb_edges++;
		return (1);
	}

	curr = src->edges;
	while (curr->next && curr->next->dest->index < dst->index)
		curr = curr->next;

	new->next = curr->next;
	curr->next = new;
	src->nb_edges++;

	return (1);
}

/**
 * link_vertex - safely link src to dst
 * @src: source vertex
 * @dst: destination vertex
 * Return: 1 on success, 0 on failure
 */
static int link_vertex(vertex_t *src, vertex_t *dst)
{
	if (!src || !dst)
		return (0);

	if (edge_exists(src, dst))
		return (0);

	return (insert_edge_sorted(src, dst));
}

/**
 * rollback_edge - remove src -> dst edge
 * @src: source vertex
 * @dst: destination vertex
 */
static void rollback_edge(vertex_t *src, vertex_t *dst)
{
	edge_t *curr, *tmp;

	curr = src->edges;
	if (curr && curr->dest == dst)
	{
		src->edges = curr->next;
		free(curr);
		src->nb_edges--;
		return;
	}

	while (curr && curr->next)
	{
		if (curr->next->dest == dst)
		{
			tmp = curr->next;
			curr->next = tmp->next;
			free(tmp);
			src->nb_edges--;
			return;
		}
		curr = curr->next;
	}
}

/**
 * graph_add_edge - adds an edge between two vertices
 * @graph: pointer to graph
 * @src: source vertex name
 * @dst: destination vertex name
 * @type: UNIDIRECTIONAL or BIDIRECTIONAL
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph,
		   const char *src,
		   const char *dst,
		   edge_type_t type)
{
	vertex_t *src_v, *dst_v;

	if (!graph || !src || !dst || !*src || !*dst)
		return (0);

	if (type != UNIDIRECTIONAL && type != BIDIRECTIONAL)
		return (0);

	src_v = graph->vertices;
	dst_v = graph->vertices;

	while (src_v && strcmp(src_v->content, src))
		src_v = src_v->next;

	while (dst_v && strcmp(dst_v->content, dst))
		dst_v = dst_v->next;

	if (!src_v || !dst_v)
		return (0);

	if (!link_vertex(src_v, dst_v))
		return (0);

	if (type == BIDIRECTIONAL && !link_vertex(dst_v, src_v))
	{
		rollback_edge(src_v, dst_v);
		return (0);
	}

	return (1);
}
