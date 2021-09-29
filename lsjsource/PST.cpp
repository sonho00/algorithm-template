template<typename T> struct PST
{
    #define L 0
    #define R 2'000'000'200

    struct vertex{int l, r; T val;};
    vector<vertex> pst;
    int make_tree(int nx)
    {
        if (nx == -1)
        {
            pst.push_back({-1, -1, T()});//
            return (int)(pst.size()) - 1;
        }
        else
        {
            pst.push_back(pst[nx]);
            return (int)(pst.size()) - 1;
        }
    }
    void update(int nx, int idx, T df, int ns = L, int ne = R)
    {
        if (ns == ne)
        {
            pst[nx].val = pst[nx].val + df;//
            return;
        }
        int mid = (ns + ne) >> 1;
        if (idx <= mid) update(pst[nx].l = make_tree(pst[nx].l), idx, df, ns, mid);
        else update(pst[nx].r = make_tree(pst[nx].r), idx, df, mid + 1, ne);
        pst[nx].val = T();//
        if (pst[nx].l != -1) pst[nx].val = pst[nx].val + pst[pst[nx].l].val;//
        if (pst[nx].r != -1) pst[nx].val = pst[nx].val + pst[pst[nx].r].val;//
    }
    T get_sum(int nx, int qs, int qe, int ns = L, int ne = R)
    {
        if (nx == -1) return T();//
        if (ne < qs || qe < ns) return T(); //
        if (qs <= ns && ne <= qe) return pst[nx].val;
        int mid = (ns + ne) >> 1;
        return get_sum(pst[nx].l, qs, qe, ns, mid) + get_sum(pst[nx].r, qs, qe, mid + 1, ne);//
    }
};
