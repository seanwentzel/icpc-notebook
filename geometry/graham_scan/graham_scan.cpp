#include<bits/stdc++.h>

#define x first
#define y second
#define EPS 1e-9

using namespace std;

typedef pair<double,double> pt;

double d2(pt a, pt b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

double ccw(pt a, pt b, pt c)
{
	return (b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x);
}

//excluding points interior to sides of conv hull
//O(n log n)
vector<pt> conv_hull(vector<pt> inp)
{
	vector<pt> ans;
	int n=inp.size();
	if(n==1)
	{
		ans.push_back(inp[0]);
		return ans;
	}
	else if(n==0)
	{
		return ans;
	}
	int best=0;
	for(int i=1;i<n;++i)
	{
		if(inp[i]<inp[best])
			best=i;
	}
	vector< pair<pt,pt> > sortage;
	for(int i=0;i<n;++i)
	{
		if(i==best) continue;
		sortage.push_back(make_pair(
					make_pair(atan2(inp[i].y-inp[best].y,inp[i].x-inp[best].x),
						d2(inp[i],inp[best])),inp[i]));
	}
	sort(sortage.begin(),sortage.end());
	ans.push_back(inp[best]);
	ans.push_back(sortage.begin()->y);
	vector<pair<pt,pt> >::iterator it=sortage.begin();
	++it;
	for(;it!=sortage.end();++it)
	{
		pt at = it -> y;
		while(ans.size()>=2 && ccw(ans[ans.size()-2],ans[ans.size()-1],at)<0+EPS)
			ans.pop_back();
		ans.push_back(at);
	}
	return ans;
}

int main()
{
	int N;
	cin>>N;
	vector<pt> inp;
	for(int i=0;i<N;++i)
	{
		double x,y;
		cin>>x>>y;
		inp.push_back(make_pair(x,y));
	}
	vector<pt> ans=conv_hull(inp);
	for(int i=0;i<ans.size();++i)
	{
		cout<< ans[i].x<<' '<<ans[i].y<<endl;
	}
	return 0;
}
