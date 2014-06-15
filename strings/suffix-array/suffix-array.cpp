#include<bits/stdc++.h>

using namespace std;

typedef pair< pair<int,int>,int> piii;

struct SuffixArray
{
	vector<vector<int> > prefix_table;
	vector<int> suffix_array;

	//O(N log^2 N)
	SuffixArray(const string& s)
	{
		int n=s.length();
		vector<int> p0;
		vector<int> lcp;
		for(int i=0;i<n;++i)
		{
			p0.push_back(int(s[i]));
		}
		prefix_table.push_back(p0);
		int level=1;
		for(int range=1;range<n;++level,range<<=1)
		{
			vector<piii> sortv;
			for(int i=0;i<n;++i)
			{
				sortv.push_back(make_pair(make_pair(prefix_table[level-1][i],
								(i+range<n)?prefix_table[level-1][i+range]:-257),i));
			}
			sort(sortv.begin(),sortv.end());
		
			vector<int> pnext(n);
			for(int i=0;i<n;++i)
			{
				pnext[sortv[i].second]=i;
				if(i!=0 && sortv[i].first==sortv[i-1].first)
				{
					pnext[sortv[i].second]=pnext[sortv[i-1].second];
				}
			}
			prefix_table.push_back(pnext);
		}
		suffix_array=vector<int>(n);
		for(int i=0;i<n;++i)
		{
			suffix_array[prefix_table[level-1][i]]=i;
		}
	}
};

int main()
{
	string tmp;
	cin>>tmp;
	SuffixArray foo(tmp);
	for(int i=0;i<foo.suffix_array.size();++i)
	{
		cout<<foo.suffix_array[i]<<" ";
	}
	cout<<endl;
	return 0;
}
