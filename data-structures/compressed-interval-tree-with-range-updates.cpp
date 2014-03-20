/*
ID: sean.we1
PROB: lazy
LANG: c++
*/
#include<iostream>
#include<vector>
#include<fstream>
#include<cassert>
#include<string>
#include<queue>
#include<stack>
#include<utility>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define f(i,a,b) for(int (i)=(a);(i)<(b);++(i))

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > event;
int n,k;
int gi[100005];
int xi[100005];
int yi[100005];
set<event> evs;

class maxtree
{
	bool stale;
	int modifier,lo,hi,split;
	int mval;
	maxtree* lh;
	maxtree* rh;
	public:
	maxtree(int l,int h)
	{
		stale=false;
		lo=l;
		hi=h;
		split=(l+h)/2;
		modifier=0;
		mval=0;
		lh=NULL;
		rh=NULL;
	}

	void print()
	{
		cerr<<"from "<<lo<<" to "<<hi<<endl;
		cerr<<"MVAL: "<<maxval()<<endl;
		cerr<<"LCHILD: ";
		if(lh!=NULL) (*lh).print();
		cerr<<"END LCHILD, RCHILD: ";
		if(rh!=NULL) (*rh).print();
		cerr<<"END RCHILD\n";
	}
	int maxval()
	{
		if(stale)
		{
			if(lh==NULL && rh==NULL) mval=modifier;
			else if(lh==NULL) mval=modifier+max(0,(*rh).maxval());
			else if(rh==NULL) mval=modifier+max(0,(*lh).maxval());
			else mval=modifier+max((*lh).maxval(),(*rh).maxval());
			stale=false;
		}
		return mval;
	}

	void modify(int change,int l,int h)
	{
		//cerr<<"MOD "<<change<<" from "<<l<<" TO "<<h<<" IN "<<lo<<"-"<<hi<<endl;
		if(l<lo) l=lo;
		if(h>hi) h=hi;
		if(l==h) return;
		stale=true;
		if(l==lo)
		{
			if(h==hi)
			{
				modifier+=change;
			}
			else if(h<=split)
			{
				if(lh==NULL)
				{
					lh=new maxtree(lo,split);
				}
				(*lh).modify(change,l,h);
			}
			else
			{
				modifier+=change;
				if(rh==NULL)
				{
					rh=new maxtree(split,hi);
				}
				(*rh).modify(-change,h,hi);
				
			}
		}
		else if(h==hi)
		{
			if(l>=split)
			{
				if(rh==NULL)
				{
					rh=new maxtree(split,hi);
				}
				(*rh).modify(change,l,h);
			}
			else
			{
				modifier+=change;
				if(lh==NULL) lh=new maxtree(lo,split);
				(*lh).modify(-change,lo,l);
			}
		}
		else
		{
			if(l>=split)
			{
				if(rh==NULL) rh=new maxtree(split,hi);
				(*rh).modify(change,l,h);
			}
			else if(h<=split)
			{
				if(lh==NULL) lh=new maxtree(lo,split);
				(*lh).modify(change,l,h);
			}
			else
			{
				if(lh==NULL) lh=new maxtree(lo,split);
				if(rh==NULL) rh=new maxtree(split,hi);
				(*rh).modify(change,split,h);
				(*lh).modify(change,l,split);
			}
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	ifstream fin("lazy.in");
	ofstream fout("lazy.out");
	fin>>n>>k;
	f(i,0,n)
	{
		fin>>gi[i]>>xi[i]>>yi[i];
		int tmp=xi[i];
		xi[i]=yi[i]-xi[i];
		yi[i]=yi[i]+tmp;
		evs.insert(mp(xi[i]-k,mp(1,i)));
		evs.insert(mp(xi[i]+k+1,mp(-1,i)));
	}
	int best=0;
	maxtree world(-2700005,2700005);
	event now;
	int circle;
	for(set<event>::iterator it=evs.begin();it!=evs.end();++it)
	{
		//world.print();
		now=(*it);
		circle=now.y.y;
	//	cerr<<now.y.x*gi[circle]<<' '<<yi[circle]-k<<' '<<yi[circle]+k+1<<endl<<world.maxval()<<endl;
		world.modify(now.y.x*gi[circle],yi[circle]-k,yi[circle]+k+1);
		best=max(best,world.maxval());
	}
	fout<<best<<endl;
	fin.close();
	fout.close();
	return 0;
}
