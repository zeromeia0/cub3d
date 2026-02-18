#include "../inc/cub3d.h"

int	nodeComparator(void *node1, void *node2, void *context)
{
	(void)context;
	t_node *n1 = (t_node *)node1;
	t_node *n2 = (t_node *)node2;	
	if (n1->x < n2->x)
		return -1;
	if (n1->x > n2->x)
		return 1;
	if (n1->y < n2->y)
		return -1;
	if (n1->y > n2->y)
		return 1;
	return 0;
}

void	nodeNeighbors(ASNeighborList neighbors, void *currentNode, void *context)
{

	t_gen *gen = (t_gen *)context;
	t_node *node = (t_node *)currentNode;
	int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };	
	for (int i = 0; i < 4; i++)
	{
		int nx = node->x + dirs[i][0];
		int ny = node->y + dirs[i][1];	
		if (ny >= 0 && ny < gen->parse->height && nx >= 0 && nx < gen->parse->width)
	    {
			if (gen->parse->map[ny][nx] != '1')
			{
				t_node neighbor = { nx, ny };
				ASNeighborListAdd(neighbors, &neighbor, 1.0f);
			}
	    }
	}
}

float	pathCostHeuristic(void *a, void *b, void *context)
{
	(void)context;
	t_node *n1 = (t_node *)a;
	t_node *n2 = (t_node *)b;
	return abs(n1->x - n2->x) + abs(n1->y - n2->y);
}

void	update_enemy(t_gen *gen, int i)
{
	t_node start = { (int)gen->enemy[i].x, (int)gen->enemy[i].y };
	t_node goal  = { (int)gen->player->x, (int)gen->player->y };

	ASPathNodeSource source = {0};
	source.nodeSize = sizeof(t_node);
	source.nodeNeighbors = nodeNeighbors;
	source.pathCostHeuristic = pathCostHeuristic;
	source.nodeComparator = nodeComparator;
	source.earlyExit = NULL;
	ASPath path = ASPathCreate(&source, gen, &start, &goal);
	if (path && ASPathGetCount(path) > 0)
	{
		t_node *nextStep;	
		double dx = gen->player->x - gen->enemy[i].x;
		double dy = gen->player->y - gen->enemy[i].y;
		double distance = sqrt(dx*dx + dy*dy);
		if (distance > 0.5 && ASPathGetCount(path) > 1)
			nextStep = ASPathGetNode(path, 1);
		else
	    {
			t_node direct = { (int)gen->player->x, (int)gen->player->y };
			nextStep = &direct;
	    }
		gen->enemy[i].x += (nextStep->x + 0.5 - gen->enemy[i].x) * gen->enemy[i].move_speed;
		gen->enemy[i].y += (nextStep->y + 0.5 - gen->enemy[i].y) * gen->enemy[i].move_speed;
	}
	if (path)
		ASPathDestroy(path);
}