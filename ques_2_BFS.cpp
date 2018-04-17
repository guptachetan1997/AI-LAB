#include <bits/stdc++.h>

using namespace std;

void BFS(pair<int, int> start, pair<int, int> goal)
{
	queue< pair<int, int> > q;
	q.push(start);
	map< pair<int, int>, int> visited;
	map< pair<int, int>, pair<int, int> > parent;
	visited[start] = 1;
	parent[start] = start;
	pair<int, int> cur;
	while(!q.empty())
	{
		cur = q.front();
		visited[cur] = 1;
		q.pop();
		if(cur == goal)
		{
			cout << "In reverse order : \n";
			while(cur != start)
			{
				cout << cur.first << "," << cur.second << endl;
				cur = parent[cur];
			}
			return;
		}
		if(cur.first < 4 && visited[make_pair(4, cur.second)] == 0)
		{
			q.push(make_pair(4, cur.second));
			parent[make_pair(4, cur.second)] = cur;
		}
		if(cur.second < 3 && visited[make_pair(cur.first, 3)] == 0)
		{
			q.push(make_pair(cur.first, 3));
			parent[make_pair(cur.first, 3)] = cur;
		}
		if(cur.first > 0 && visited[make_pair(0, cur.second)] == 0)
		{
			q.push(make_pair(0, cur.second));
			parent[make_pair(0, cur.second)] = cur;
		}
		if(cur.second > 0 && visited[make_pair(cur.first, 0)] == 0)
		{
			q.push(make_pair(cur.first, 0));
			parent[make_pair(cur.first, 0)] = cur;
		}
		if(cur.second > 0 && cur.first + cur.second >= 4 && visited[make_pair(4, cur.second - (4-cur.first))] == 0)
		{
			q.push(make_pair(4, cur.second - (4-cur.first)));
			parent[make_pair(4, cur.second - (4-cur.first))] = cur;
		}
		if(cur.first > 0 && cur.first + cur.second >= 3 && visited[make_pair(cur.first - (3-cur.second), 3)] == 0)
		{
			q.push(make_pair(cur.first - (3-cur.second), 3));
			parent[make_pair(cur.first - (3-cur.second), 3)] = cur;
		}
		if(cur.second > 0 && cur.first + cur.second <= 4 && visited[make_pair(cur.first+cur.second, 0)] == 0)
		{
			q.push(make_pair(cur.first+cur.second, 0));
			parent[make_pair(cur.first+cur.second, 0)] = cur;
		}
		if(cur.first > 0 && cur.first + cur.second <= 3 && visited[make_pair(0, cur.first+cur.second)] == 0)
		{
			q.push(make_pair(0, cur.first+cur.second));
			parent[make_pair(0, cur.first+cur.second)] = cur;
		}
	}
}

int main()
{
	BFS(make_pair(0,0), make_pair(2,0));
}

// OUTPUT:
// In reverse order : 
// 2,0
// 2,3
// 4,1
// 0,1
// 1,0
// 1,3
// 4,0
