#pragma once

#include "pathfinding.h"

Node* nodemap = Pathfinding::CreateNodeMap();

Node* start = &nodemap[0];
Node* end = &nodemap[32*18];

vector<Node*> result = Pathfinding::A_Star(nodemap, start, end);

