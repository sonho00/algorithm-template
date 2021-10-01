vector<int> dfsn(n, -1);
    vector<vector<pair<int, int>>> bcc;
    function<int(int, int)> dfs = [&](int now, int before)->int
    {
        static int dcnt = 0;
        static stack<pair<int, int>> stk;
        int result = dfsn[now] = dcnt++;
        for (int nxt: g[now])
        {
            if (nxt == before) continue;
            if (dfsn[now] > dfsn[nxt]) stk.push({now, nxt});
            if (dfsn[nxt] != -1) result = min(result, dfsn[nxt]);
            else
            {
                int tmp = dfs(nxt, now);
                result = min(result, tmp);
                if (tmp >= dfsn[now])
                {
                    vector<pair<int,int>> nbcc;
                    while(!stk.empty() && stk.top() != make_pair(now, nxt))
                    {
                        nbcc.push_back(stk.top()); stk.pop();
                    }
                    nbcc.push_back(stk.top());
                    stk.pop();
                    bcc.push_back(nbcc);
                }
            }
        }
        return result;
    };
    for (int i=0; i<n;++i)
        if (dfsn[i] == -1) dfs(i, i);
