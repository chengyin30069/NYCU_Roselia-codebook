typedef complex<double> cp;

const double pi = acos(-1);
const int NN = 131072;

struct FastFourierTransform {
    /*
            Iterative Fast Fourier Transform
            How this works? Look at this
            0th recursion 0(000)   1(001)   2(010)   3(011)   4(100)   5(101)   6(110)   7(111)
            1th recursion 0(000)   2(010)   4(100)   6(110) | 1(011)   3(011)   5(101)   7(111)
            2th recursion 0(000)   4(100) | 2(010)   6(110) | 1(011)   5(101) | 3(011)   7(111)
            3th recursion 0(000) | 4(100) | 2(010) | 6(110) | 1(011) | 5(101) | 3(011) | 7(111)
            All the bits are reversed => We can save the reverse of the numbers in an array!
    */
    int n, rev[NN];
    cp omega[NN], iomega[NN];
    void init(int n_) {
        n = n_;
        for (int i = 0; i < n_; i++) {
            // Calculate the nth roots of unity
            omega[i] = cp(cos(2 * pi * i / n_), sin(2 * pi * i / n_));
            iomega[i] = conj(omega[i]);
        }
        int k = __lg(n_);
        for (int i = 0; i < n_; i++) {
            int t = 0;
            for (int j = 0; j < k; j++) {
                if (i & (1 << j)) t |= (1 << (k - j - 1));
            }
            rev[i] = t;
        }
    }

    void transform(vector<cp> &a, cp *xomega) {
        for (int i = 0; i < n; i++)
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int len = 2; len <= n; len <<= 1) {
            int mid = len >> 1;
            int r = n / len;
            for (int j = 0; j < n; j += len)
                for (int i = 0; i < mid; i++) {
                    cp tmp = xomega[r * i] * a[j + mid + i];
                    a[j + mid + i] = a[j + i] - tmp;
                    a[j + i] = a[j + i] + tmp;
                }
        }
    }

    void fft(vector<cp> &a) { transform(a, omega); }
    void ifft(vector<cp> &a) {
        transform(a, iomega);
        for (int i = 0; i < n; i++) a[i] /= n;
    }
} FFT;

const int MAXN = 262144;
// (must be 2^k)
// 262144, 524288, 1048576, 2097152, 4194304
// before any usage, run pre_fft() first
typedef long double ld;
typedef complex<ld> cplx;  // real() ,imag()
const ld PI = acosl(-1);
const cplx I(0, 1);
cplx omega[MAXN + 1];
void pre_fft() {
    for (int i = 0; i <= MAXN; i++) {
        omega[i] = exp(i * 2 * PI / MAXN * I);
    }
}
// n must be 2^k
void fft(int n, cplx a[], bool inv = false) {
    int basic = MAXN / n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        for (int i = 0; i < mh; i++) {
            cplx w = omega[inv ? MAXN - (i * theta % MAXN) : i * theta % MAXN];
            for (int j = i; j < n; j += m) {
                int k = j + mh;
                cplx x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
        theta = (theta * 2) % MAXN;
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }
    if (inv) {
        for (i = 0; i < n; i++) a[i] /= n;
    }
}
cplx arr[MAXN + 1];
inline void mul(int _n, long long a[], int _m, long long b[], long long ans[]) {
    int n = 1, sum = _n + _m - 1;
    while (n < sum) n <<= 1;
    for (int i = 0; i < n; i++) {
        double x = (i < _n ? a[i] : 0), y = (i < _m ? b[i] : 0);
        arr[i] = complex<double>(x + y, x - y);
    }
    fft(n, arr);
    for (int i = 0; i < n; i++) arr[i] = arr[i] * arr[i];
    fft(n, arr, true);
    for (int i = 0; i < sum; i++) ans[i] = (long long int)(arr[i].real() / 4 + 0.5);
}

long long a[MAXN];
long long b[MAXN];
long long ans[MAXN];
int a_length;
int b_length;