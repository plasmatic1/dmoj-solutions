// Генадзь Караткевіч
void Solve() {
    int t[3] = {0, 1, 1}, resp = 1;
    while (resp) {
        t[resp - 1]++;
        resp = Theory(t[0], t[1], t[2]);
    }
}