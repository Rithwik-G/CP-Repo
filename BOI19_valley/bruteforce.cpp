#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second
#define all(x) x.begin(),x.end()
#define _ ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void setIO(string s) {
   freopen((s + ".in").c_str(), "r", stdin);
   freopen((s + ".out").c_str(), "w", stdout);
}

const int mxn=1e5+5;
vector<pair<int,int>> adj[mxn];
pair<int,int> edgeid[mxn];
bool isshop[mxn]={false};
ll depth[mxn]={0},length[mxn]={0};
ll magic[mxn]={(ll)1e18};
ll jumping[20][mxn],jumpingans[20][mxn];
int st[mxn],en[mxn];
int parent[mxn];
int timer=0;

ll query(int top,int node){
   int x=node;
   int pathlength=depth[node]-depth[top];
   ll ans=magic[node];
   for(int i=0;i<20;i++){
       if(pathlength & (1<<i)){
           ans=min(ans,jumpingans[i][node]);
           node=jumping[i][node];
       }
   }
   return ans+length[x];
}

void dfs(int v,int p){
   st[v]=timer;
   timer++;
   parent[v]=p;
   for(auto u:adj[v]){
       if(u.f==p) continue;
       depth[u.f]=depth[v]+1;
       //cout<<v<<' '<<u.f<<' '<<u.s<<'\n';
       length[u.f]=length[v]+u.s;
       dfs(u.f,v);
   }
   en[v]=timer;
   timer++;
}

void dfs2(int v,int p){
   if(isshop[v]) magic[v]=length[v];
   else magic[v]=(ll)1e18;
   for(auto u:adj[v]){
       if(u.f==p) continue;
       dfs2(u.f,v);
       magic[v]=min(magic[v],magic[u.f]);
   }
}

int main() {_
   //setIO("wayne");
   int n,s,q,e;
   cin>>n>>s>>q>>e;
   for(int i=1;i<=n-1;i++){
       int a,b,w;
       cin>>a>>b>>w;
       adj[a].push_back({b,w});
       adj[b].push_back({a,w});
       edgeid[i]={a,b};
   }
   for(int i=0;i<s;i++){
       int x;
       cin>>x;
       isshop[x]=true;
   }
   dfs(e,0);
   dfs2(e,0);
   for(int i=1;i<=n;i++){
       magic[i]-=2*length[i];
   }
   for(int i=1;i<=n;i++){
       jumping[0][i]=parent[i];
       jumpingans[0][i]=magic[parent[i]];
   }
   for(int i=1;i<20;i++){
       for(int j=1;j<=n;j++){
           jumping[i][j]=jumping[i-1][jumping[i-1][j]];
           jumpingans[i][j]=min(jumpingans[i-1][j],jumpingans[i-1][jumping[i-1][j]]);
       }
   }
   for(int i=0;i<q;i++){
       int edge,node;
       cin>>edge>>node;
       int top=(depth[edgeid[edge].f]>depth[edgeid[edge].s]?edgeid[edge].f:edgeid[edge].s);
       if(st[top]<=st[node] and en[node]<=en[top]){
           if(query(top,node)<=(ll)1e14) cout<<query(top,node)<<'\n';
           else cout<<"oo"<<'\n';
       }
       else{
           cout<<"escaped"<<'\n';
       }
   }
   return 0;
}