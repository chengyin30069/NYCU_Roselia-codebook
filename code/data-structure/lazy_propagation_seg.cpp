struct lazy_propagation{
	// 0-based, [l, r], tg[0]->add, tg[1]->set
	ll seg[N * 4], tg[2][N*4];
	void assign (bool op, ll val, int idx){
		if (op == 0){
			if (tg[1][idx])	tg[1][idx] += val;
			else			tg[0][idx] += val;
		}
		else	seg[idx] = 0, tg[0][idx] = 0, tg[1][idx] = val;
	}
	ll sum (int idx, int len){
		if (tg[1][idx])	return tg[1][idx] * len;
		return tg[0][idx] * len + seg[idx];
	}
	void pull (int idx, int len){
		seg[idx] = sum(2*idx, (len+1)/2) + sum(2*idx+1, len/2);
	}
	void push (int idx){
		if (!tg[0][idx] && !tg[1][idx])	return ;
		if (tg[0][idx]){
			assign(0, tg[0][idx], 2*idx);
			assign(0, tg[0][idx], 2*idx+1);
			tg[0][idx] = 0;
		}
		else{
			assign(1, tg[1][idx], 2*idx);
			assign(1, tg[1][idx], 2*idx+1);
			tg[1][idx] = 0;
		}
	}
	void update (bool op, ll val, int gl, int gr, int l, int r, int idx){
		if (r < l || gr < l || r < gl)	return ;
		if (gl <= l && r <= gr){
			assign(op, val, idx);
			return ;
		}

		int mid = (l + r) / 2;
		push(idx);
		update(op, val, gl, gr, l, mid, 2*idx);
		update(op, val, gl, gr, mid+1, r, 2*idx+1);
		pull(idx, r-l+1);
	}
	ll query (int gl, int gr, int l, int r, int idx){
		if (r < l || gr < l || r < gl)	return 0;
		if (gl <= l && r <= gr)	return sum(idx, r-l+1);

		push(idx), pull(idx, r-l+1);
		int mid = (l + r) / 2;
		return query(gl, gr, l, mid, 2*idx) + query(gl, gr, mid+1, r, 2*idx+1);
	}
}bm;