#include <bits/stdc++.h>

using namespace std;

class BoardState
{

public:
	int board[3][3];
	int value;
	void set(int state[3][3])
	{
		for(int i=0 ; i<3 ; i++)
			for(int j=0 ; j<3 ; j++)
				board[i][j] = state[i][j];
	}
	void display()
	{
		for(int i=0 ; i<3 ; i++)
		{
			for(int j=0 ; j<3 ; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
	int evaluate_state(BoardState goal)
	{
		// sum of differences between goal and current state tiles in terms of moves.
		pair<int, int> movesMap[9];
		for(int i=0 ; i<3 ; i++)
		{
			for(int j=0 ; j<3 ; j++)
			{
				movesMap[goal.board[i][j]] = make_pair(i,j);
			}
		}

		int value=0;
		for(int i=0 ; i<3 ; i++)
		{
			for(int j=0 ; j<3 ; j++)
			{
				value += (fabs(i-movesMap[board[i][j]].first) +  fabs(j-movesMap[board[i][j]].second));
			}
		}
		return -value;
	}
	bool isGoal(BoardState goal)
	{
		for(int i=0 ; i<3 ; i++)
		{
			for(int j=0 ; j<3 ; j++)
			{
				if(board[i][j] != goal.board[i][j])
					return false;
			}
		}
		return true;
	}
};

bool isSafe(int x, int y)
{
	if(x >= 0 && x<=2 && y>=0 && y<=2)
		return true;
	else
		return false;
}

vector<BoardState> genChildren(BoardState state)
{
	vector<BoardState> children;
	int x0,y0;
	for(int i=0 ; i<3 ; i++)
		for(int j=0 ; j<3 ; j++)
			if(state.board[i][j] == 0)
			{
				x0 = i;
				y0 = j;
				break;
			}
	BoardState temp;
	if(isSafe(x0-1, y0))
	{
		temp = state;
		swap(temp.board[x0][y0], temp.board[x0-1][y0]);
		children.push_back(temp);
	}
	if(isSafe(x0+1, y0))
	{
		temp = state;
		swap(temp.board[x0][y0], temp.board[x0+1][y0]);
		children.push_back(temp);
	}
	if(isSafe(x0, y0-1))
	{
		temp = state;
		swap(temp.board[x0][y0], temp.board[x0][y0-1]);
		children.push_back(temp);
	}
	if(isSafe(x0, y0+1))
	{
		temp = state;
		swap(temp.board[x0][y0], temp.board[x0][y0+1]);
		children.push_back(temp);
	}
	return children;
}

class compPair
{
	public:
	bool operator()(const pair<BoardState, int>& a, const pair<BoardState, int>& b)
	{
		return a.second<b.second;
	}
};

class comp
{
	public:
	bool operator()(const BoardState& a, const BoardState& b)
	{
		string as="",bs="";
		for(int i=0 ; i<3 ; i++)
			for(int j=0 ; j<3 ; j++)
			{
				as.push_back(a.board[i][j] - '0');
				bs.push_back(b.board[i][j] - '0');
			}
		return as < bs;
	}
};

void AStar(BoardState start, BoardState goal)
{
	priority_queue < pair<BoardState, int>, vector< pair<BoardState, int> >, compPair > pq;
	pq.push(make_pair(start, start.evaluate_state(goal)));
	pair<BoardState, int> cur;
	map<BoardState, int, comp> visited;
	map<BoardState, BoardState, comp> parent;
	visited[start] = 1;
	parent[start] = start;
	while(!pq.empty())
	{
		cur = pq.top();
		pq.pop();
		if(cur.first.isGoal(goal))
		{
			BoardState c = cur.first;
			cout << "Goal\n";
			cout << "In reverse order : \n";
			while(!c.isGoal(start))
			{
				c.display();
				cout << endl;
				c = parent[c];
			}
			c.display();
			cout << endl;
			return;
		}
		vector<BoardState> children = genChildren(cur.first);
		for(int i=0 ; i<children.size() ; i++)
		{
			if(visited[children[i]] == 0)
			{
				pq.push(make_pair(children[i], children[i].evaluate_state(goal)+visited[cur.first]+1));
				parent[children[i]] = cur.first;
				visited[children[i]] = visited[cur.first]+1;
			}
		}

	}

}

int main()
{
	int start[3][3] = {1,2,3,8,5,6,4,7,0};
	int goal[3][3] = {1,2,3,4,5,6,7,8,0};
	BoardState startS, goalS;
	startS.set(start);
	goalS.set(goal);
	AStar(startS, goalS);
}

// OUTPUT
// Goal
// In reverse order : 
// 1 2 3 
// 4 5 6 
// 7 8 0 

// 1 2 3 
// 4 5 6 
// 7 0 8 

// 1 2 3 
// 4 0 6 
// 7 5 8 

// 1 2 3 
// 4 6 0 
// 7 5 8 

// 1 2 3 
// 4 6 8 
// 7 5 0 

// 1 2 3 
// 4 6 8 
// 7 0 5 

// 1 2 3 
// 4 6 8 
// 0 7 5 

// 1 2 3 
// 0 6 8 
// 4 7 5 

// 1 2 3 
// 6 0 8 
// 4 7 5 

// 1 2 3 
// 6 8 0 
// 4 7 5 

// 1 2 3 
// 6 8 5 
// 4 7 0 

// 1 2 3 
// 6 8 5 
// 4 0 7 

// 1 2 3 
// 6 0 5 
// 4 8 7 

// 1 2 3 
// 6 5 0 
// 4 8 7 

// 1 2 3 
// 6 5 7 
// 4 8 0 

// 1 2 3 
// 6 5 7 
// 4 0 8 

// 1 2 3 
// 6 0 7 
// 4 5 8 

// 1 2 3 
// 0 6 7 
// 4 5 8 

// 1 2 3 
// 4 6 7 
// 0 5 8 

// 1 2 3 
// 4 6 7 
// 5 0 8 

// 1 2 3 
// 4 6 7 
// 5 8 0 

// 1 2 3 
// 4 6 0 
// 5 8 7 

// 1 2 3 
// 4 0 6 
// 5 8 7 

// 1 2 3 
// 4 8 6 
// 5 0 7 

// 1 2 3 
// 4 8 6 
// 0 5 7 

// 1 2 3 
// 0 8 6 
// 4 5 7 

// 1 2 3 
// 8 0 6 
// 4 5 7 

// 1 2 3 
// 8 5 6 
// 4 0 7 

// 1 2 3 
// 8 5 6 
// 4 7 0 