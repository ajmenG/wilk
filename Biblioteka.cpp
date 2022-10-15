#include <bits/stdc++.h>
using namespace std;

constexpr int S= (1<<17);
int64_t n, a, ans;
vector <pair<int,int>> pom; //skalowanie
int seg[270000], tab[100007];
int64_t odp[100007];

int update(int a)
{
    int pom=a+S;
    seg[pom]++;

    while (pom>1)
    {
        pom/=2;
        seg[pom]++;
    }
}

int query(int v, int L, int R, int a, int b)
{
    if (R == b && L == a)
    {
        return seg[v];
    }

    int mid = (a+b)/2;

    if (L>mid)
    {
        return query(2*v+1, L, R, mid+1, b);
    }
    else if (R<=mid)
    {
        return query(2*v, L, R, a, mid);
    }
    else
    {
        return query(2*v, L, mid, a, mid) + query(2*v+1, mid+1, R, mid+1, b);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    {
        for (int i=0; i<n; i++)
        {
            cin >> a;
            pom.push_back({a, i});
        }

        sort(pom.begin(), pom.end());
        int L=1;
        for (int i=0; i<n; i++)
        {
            if(i>0 && pom[i].first>pom[i-1].first)
            {
                L++;
            }
            tab[pom[i].second]=L;
        }
    }

    for (int i=0; i<n; i++)
    {
        update(tab[i]);
        odp[i] = query(1, 0, tab[i]-1, 0, S-1);
    }

    for (int i=0; i<2*S; i++)
    {
        seg[i]=0;
    }

    for (int i=n-1; i>=0; i--)
    {
        update(tab[i]);
        ans += odp[i] * query(1, tab[i]+1, S-1, 0, S-1);
    }

    cout << ans;
return 0;
}
