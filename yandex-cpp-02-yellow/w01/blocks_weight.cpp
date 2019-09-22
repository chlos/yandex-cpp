#include <iostream>

using namespace std;

int main() {
    uint64_t N;
    uint64_t R;
    cin >> N >> R;
    //cout << "N = " << N << " ; R = " << R << endl;  // FIXME

    uint64_t sum = 0;
    for (uint64_t i = 0; i < N; ++i) {
        uint64_t W, H, D;
        cin >> W >> H >> D;
        //cout << "W = " << W << " ; H = " << H << "; D = " << D << endl;  // FIXME
        sum += W * H * D * R;
    }
    cout << sum << endl;

    return 0;
}
