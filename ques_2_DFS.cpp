#include <bits/stdc++.h>

using namespace std;

map< pair<int, int>, int> visited;
map< pair<int, int>, pair<int, int> > parent;

void DFS(pair<int, int> cur, pair<int, int> goal)
{
	visited[cur] = 1;
	if(cur == goal)
	{
		return;
	}
	if(cur.first < 4 && visited[make_pair(4, cur.second)] == 0)
	{
		DFS(make_pair(4, cur.second), goal);
		parent[make_pair(4, cur.second)] = cur;
	}
	if(cur.second < 3 && visited[make_pair(cur.first, 3)] == 0)
	{
		DFS(make_pair(cur.first, 3), goal);
		parent[make_pair(cur.first, 3)] = cur;
	}
	if(cur.first > 0 && visited[make_pair(0, cur.second)] == 0)
	{
		DFS(make_pair(0, cur.second), goal);
		parent[make_pair(0, cur.second)] = cur;
	}
	if(cur.second > 0 && visited[make_pair(cur.first, 0)] == 0)
	{
		DFS(make_pair(cur.first, 0), goal);
		parent[make_pair(cur.first, 0)] = cur;
	}
	if(cur.second > 0 && cur.first + cur.second >= 4 && visited[make_pair(4, cur.second - (4-cur.first))] == 0)
	{
		DFS(make_pair(4, cur.second - (4-cur.first)), goal);
		parent[make_pair(4, cur.second - (4-cur.first))] = cur;
	}
	if(cur.first > 0 && cur.first + cur.second >= 3 && visited[make_pair(cur.first - (3-cur.second), 3)] == 0)
	{
		DFS(make_pair(cur.first - (3-cur.second), 3), goal);
		parent[make_pair(cur.first - (3-cur.second), 3)] = cur;
	}
	if(cur.second > 0 && cur.first + cur.second <= 4 && visited[make_pair(cur.first+cur.second, 0)] == 0)
	{
		DFS(make_pair(cur.first+cur.second, 0), goal);
		parent[make_pair(cur.first+cur.second, 0)] = cur;
	}
	if(cur.first > 0 && cur.first + cur.second <= 3 && visited[make_pair(0, cur.first+cur.second)] == 0)
	{
		DFS(make_pair(0, cur.first+cur.second), goal);
		parent[make_pair(0, cur.first+cur.second)] = cur;
	}
	
}

void DFS_init(pair<int, int> start, pair<int, int> goal)
{
	parent[start] = start;
	DFS(start, goal);
	if(visited[goal])
	{
		cout << "In reverse order : \n";
		while(goal != start)
		{
			cout << goal.first << "," << goal.second << endl;
			goal = parent[goal];
		}
	}
	else
		cout << "No solution exists!\n";
}

int main()
{
	DFS_init(make_pair(0,0), make_pair(2,0));
}

// OUTPUT:
// In reverse order : 
// 2,0
// 0,2
// 4,2
// 3,3
// 3,0
// 0,3
// 4,3
// 4,0
