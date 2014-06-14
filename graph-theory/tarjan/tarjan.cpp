#include<bits/stdc++.h>

#define INF 1000000000
#define y second
#define x first

using namespace std;

//O(N+M) SCC algorithm. returns a list of components 
vector< vector<int> > tarjan(vector<vector<int> >& adj)
{
	vector< vector<int> > ans;
	int n = adj.size();
	int low[n];
	int ind[n];
	int par[n];
	int at;
	for(int i=0;i<n;++i)
	{
		ind[i]=-1;
		low[i]=INF;
	}
	for(int i=0;i<adj.size();++i)
	{
		if(ind[i]==-1)
		{
			vector<pair<int,vector<int>::iterator > > stack;
			stack.push_back(make_pair(i,adj[i].begin()));
			int at=0;
			ind[i]=0;
			low[i]=0;
			while(stack.size()>0)
			{
				int vert = stack[at].x;
				if(stack[at].y==adj[vert].end())
				{
					if(low[vert]==at)
					{
						vector<int> comp;
						while(at<stack.size())
						{
							ind[stack.back().x]=-2;
							comp.push_back(stack.back().x);
							stack.pop_back();
						}
						ans.push_back(comp);
					}
					else
					{
						low[par[vert]]=min(low[par[vert]],low[vert]);
					}
					at=par[vert];
					continue;
				}
				int nxt = *(stack[at].y);
				++stack[at].y;
				if(ind[nxt]==-1)
				{
					stack.push_back(make_pair(nxt,adj[nxt].begin()));
					par[nxt]=at;
					ind[nxt]=stack.size()-1;
					low[nxt]=ind[nxt];
					at=stack.size()-1;
				}
				else if(ind[nxt]!=-2)
				{
					low[vert]=min(low[vert],low[nxt]);
				}
			}
		}
	}
	return ans;
}

int main()
{
	int n,m;
	cin>>n>>m;
	vector<vector<int> > verts(n);
	for(int i = 0; i < m; ++i)
	{
		int a,b;
		cin>>a>>b;
		verts[a].push_back(b);
	}
	vector<vector<int> > ans = tarjan(verts);
	for(int i = 0; i < ans.size(); ++i)
	{
		for(int j=0;j< ans[i].size(); ++j)
		{
			cout<<ans[i][j]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
