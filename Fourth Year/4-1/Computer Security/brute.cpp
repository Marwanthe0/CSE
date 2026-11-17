#include <bits/stdc++.h>
using namespace std;

// Brute force: try all possible new edges, for each compute worst-case reachability
int main(){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<pair<int,int>> edges(n-1);
        set<pair<int,int>> edge_set;
        vector<vector<int>> adj(n+1);
        for(int i=0;i<n-1;i++){
            int u,v; cin >> u >> v;
            edges[i]={u,v};
            edge_set.insert({u,v});
            edge_set.insert({v,u});
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        int best = 0;
        // Try all possible new edges
        for(int a=1;a<=n;a++){
            for(int b=a+1;b<=n;b++){
                if(edge_set.count({a,b})) continue; // already connected
                
                // Add edge (a,b), then try removing each of the n edges
                int worst = n; // worst case reachable from 1
                for(int r=0;r<n-1;r++){
                    // Remove edge r, add edge (a,b)
                    // BFS from 1
                    vector<vector<int>> g(n+1);
                    for(int i=0;i<n-1;i++){
                        if(i==r) continue;
                        g[edges[i].first].push_back(edges[i].second);
                        g[edges[i].second].push_back(edges[i].first);
                    }
                    g[a].push_back(b);
                    g[b].push_back(a);
                    
                    vector<bool> vis(n+1, false);
                    queue<int> q;
                    q.push(1);
                    vis[1]=true;
                    int cnt=1;
                    while(!q.empty()){
                        int u=q.front(); q.pop();
                        for(int v:g[u]){
                            if(!vis[v]){
                                vis[v]=true;
                                cnt++;
                                q.push(v);
                            }
                        }
                    }
                    worst = min(worst, cnt);
                }
                // Also try removing the new edge itself
                {
                    // just the original tree
                    vector<bool> vis(n+1,false);
                    queue<int> q;
                    q.push(1); vis[1]=true; int cnt=1;
                    while(!q.empty()){
                        int u=q.front();q.pop();
                        for(int v:adj[u]) if(!vis[v]){vis[v]=true;cnt++;q.push(v);}
                    }
                    worst = min(worst, cnt);
                }
                best = max(best, worst);
            }
        }
        cout << best << endl;
    }
}
