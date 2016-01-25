#include <bits/stdc++.h>
using namespace std;

class SegmentTree{
public:
	vector<int> A,st;
	int n;
	
	int left  (int p){ return  p << 1; }
	int right (int p){ return (p << 1) + 1; }

	void build(int p,int L,int R){
		if( L==R )
			st[p] = L;
		else {
			build(left(p), L, (L+R)/2);
			build(right(p),(L+R)/2+1,R);
			int p1=st[left(p)],p2=st[right(p)];
			st[p]=(A[p1] <= A[p2])?  p1:p2;
		}
	}

	int rmq(int p, int L, int R,int i,int j){
		if(i >  R  || j <  L) return -1;
		if(L >= i  && R <= j) return st[p];

		int p1=rmq(left(p),L,(L+R)/2,i,j);
		int p2=rmq(right(p),(L+R)/2+1,R,i,j);
		if(p1==-1) return p2;
		if(p2==-1) return p1;
		return (A[p1] <= A[p2])? p1:p2;
	}
	SegmentTree(){
		st.assign(400005,0);
	}
	void create(){
		n=(int)A.size();
		build(1,0,n-1);
	} 

	int rmq(int i,int j){ return rmq(1,0,n-1,i,j);}
};


//global variables
int tc;
int n,q;
int x,l,r; // x: each element of the vector, l: left index from querie, r: right index from querie.
SegmentTree  st;


void start(int z){
	printf("Case %d:\n",z+1);
	scanf("%d %d",&n,&q);
	st.A.clear();
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		st.A.push_back(x);
	}
	st.create();

	for(int i=0;i<q;i++){
		scanf("%d %d",&l,&r);
		printf("%d\n",st.A[st.rmq(l-1,r-1)]);
	}

}


int main(){
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	scanf("%d",&tc);
	for(int i=0;i<tc;i++) start(i);
	return 0;
}