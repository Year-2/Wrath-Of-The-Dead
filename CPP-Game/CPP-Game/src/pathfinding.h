#pragma once
#pragma once
#include <vector>
#include <algorithm>
#include <math.h>

#include "vector2d.h"

using std::vector;
using std::max;
using std::min;
using std::sort;
#define MAP_HEIGHT 18
#define MAP_WIDTH 32

struct Node {
	bool obstacle = false;
	bool visited = false;
	float g, h, f;
	Vector2D<int> position;
	vector<Node*> neighbours;
	Node* parent;
};

class Pathfinding {
public:
	static float Distance(Node* current, Node* destination) {
		int xDist = max(current->position.x, destination->position.x) - min(current->position.x, destination->position.x);
		int yDist = max(current->position.y, destination->position.y) - min(current->position.y, destination->position.y);
		return static_cast<float>(sqrt((xDist * xDist) + (yDist * yDist)));
	}

	/// <summary>
	///		Create array of nodes.
	/// </summary>
	/// <returns>
	///		Array of nodes.
	/// </returns>
	/// 
	/// change this to make obstacles from tile map?
	static Node* CreateNodeMap() {
		Node* nodes = new Node[MAP_WIDTH * MAP_HEIGHT];
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				nodes[y * MAP_WIDTH + x].obstacle = false;
				nodes[y * MAP_WIDTH + x].visited = false;
				nodes[y * MAP_WIDTH + x].position = { x, y };
				nodes[y * MAP_WIDTH + x].parent = nullptr;
			}
		}

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				if (y > 0)
					nodes[y * MAP_WIDTH + x].neighbours.push_back(&nodes[(y - 1) * MAP_WIDTH + (x)]);
				if (y < MAP_HEIGHT - 1)
					nodes[y * MAP_WIDTH + x].neighbours.push_back(&nodes[(y + 1) * MAP_WIDTH + (x)]);
				if (x > 0)
					nodes[y * MAP_WIDTH + x].neighbours.push_back(&nodes[(y)*MAP_WIDTH + (x - 1)]);
				if (x < MAP_WIDTH - 1)
					nodes[y * MAP_WIDTH + x].neighbours.push_back(&nodes[(y)*MAP_WIDTH + (x + 1)]);
			}
		}
		return nodes;
	}

	//	TODO: Remove the double empty() while loop test???
	//	TODO: Pass a pointer to the return?????
	//	Maybe not need nodes param.
	//	nodes, arr of nodes
	static vector<Node> A_Star(Node* nodes, Node* startNode, Node* endNode) {

		vector<Node> path;

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				nodes[y * MAP_WIDTH + x].g = FLT_MAX;
				nodes[y * MAP_WIDTH + x].h = FLT_MAX;
				nodes[y * MAP_WIDTH + x].f = FLT_MAX;
				nodes[y * MAP_WIDTH + x].visited = false;
				nodes[y * MAP_WIDTH + x].parent = nullptr;
			}
		}

		Node* currentNode = startNode;
		startNode->g = 0;
		startNode->h = Distance(startNode, endNode);
		startNode->f = currentNode->g + currentNode->h;

		vector<Node*> nodesToTest;
		nodesToTest.push_back(startNode);

		while (!nodesToTest.empty()) {

			sort(begin(nodesToTest), end(nodesToTest), [](Node* lhs, Node* rhs) {
				return lhs->f < rhs->f;
				});

			while (!nodesToTest.empty() && nodesToTest.front()->visited)
				nodesToTest.erase(begin(nodesToTest));

			if (nodesToTest.empty())
				break;

			currentNode = nodesToTest.front();
			currentNode->visited = true;

			for (Node* nodeNeighbour : currentNode->neighbours) {
				if (!nodeNeighbour->visited && !nodeNeighbour->obstacle)
					nodesToTest.push_back(nodeNeighbour);

				float gPossibleLowerGoal = currentNode->g + Distance(currentNode, nodeNeighbour);

				if (gPossibleLowerGoal < nodeNeighbour->g) {
					nodeNeighbour->parent = currentNode;
					nodeNeighbour->g = gPossibleLowerGoal;
					nodeNeighbour->h = nodeNeighbour->g + Distance(currentNode, endNode);
					nodeNeighbour->f = nodeNeighbour->g + nodeNeighbour->h;
				}
			}
		}
		Node* pathNode = endNode;
		while (pathNode->parent != nullptr) {
			path.insert(begin(path), *pathNode);
			pathNode = pathNode->parent;
		}
		path.insert(begin(path), *pathNode);

		return path;
	}
};

