#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <latch>
#include <mutex>
using namespace std;
mutex cout_mutex;
void sync_print(const string& text) {
    lock_guard<mutex> lock(cout_mutex);
    cout << text << endl;
}
const int nt = 5;
const int A = 8;
const int B = 5;
const int C = 9;
const int D = 4;
const int E = 6;
const int Fcount = 5;
const int G = 5;
const int H = 6;
const int Icount = 7;
const int J = 4;
void f(const string& label, int idx) {
    this_thread::sleep_for(chrono::milliseconds(50));
    sync_print("From the set " + label + " action performed " + to_string(idx) + ".");
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sync_print("Calculation started");
    latch latch_a(A), latch_b(B), latch_c(C), latch_d(D), latch_e(E),
        latch_f(Fcount), latch_g(G), latch_h(H), latch_i(Icount), latch_j(J);
    using Task = pair<string, int>;
    vector<vector<Task>> work(nt);
    int ai = 1;
    for (int t = 0; t < nt; ++t) {
        int take = A / nt + (t < (A % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "a", ai++ });
    }
    int bi = 1;
    for (int t = 0; t < nt; ++t) {
        int take = B / nt + (t < (B % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "b", bi++ });
    }
    int ci = 1;
    for (int t = 0; t < nt; ++t) {
        int take = C / nt + (t < (C % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "c", ci++ });
    }
    int di = 1;
    for (int t = 0; t < nt; ++t) {
        int take = D / nt + (t < (D % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "d", di++ });
    }
    int ei = 1;
    for (int t = 0; t < nt; ++t) {
        int take = E / nt + (t < (E % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "e", ei++ });
    }
    int fi = 1;
    for (int t = 0; t < nt; ++t) {
        int take = Fcount / nt + (t < (Fcount % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "f", fi++ });
    }
    int gi = 1;
    for (int t = 0; t < nt; ++t) {
        int take = G / nt + (t < (G % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "g", gi++ });
    }
    int hi = 1;
    for (int t = 0; t < nt; ++t) {
        int take = H / nt + (t < (H % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "h", hi++ });
    }
    int ii = 1;
    for (int t = 0; t < nt; ++t) {
        int take = Icount / nt + (t < (Icount % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "i", ii++ });
    }
    int ji = 1;
    for (int t = 0; t < nt; ++t) {
        int take = J / nt + (t < (J % nt) ? 1 : 0);
        for (int k = 0; k < take; ++k) work[t].push_back({ "j", ji++ });
    }
    auto worker = [&](int tid, const vector<Task>& tasks) {
        for (auto [label, idx] : tasks) {
            if (label == "d") {
                latch_a.wait();
                latch_c.wait();
            }
            else if (label == "e" || label == "f") {
                latch_b.wait();
            }
            else if (label == "g") {
                latch_c.wait();
            }
            else if (label == "h") {
                latch_d.wait();
                latch_e.wait();
                latch_g.wait();
            }
            else if (label == "i") {
                latch_f.wait();
            }
            else if (label == "j") {
                latch_h.wait();
                latch_i.wait();
            }
            f(label, idx);
            if (label == "a") latch_a.count_down();
            else if (label == "b") latch_b.count_down();
            else if (label == "c") latch_c.count_down();
            else if (label == "d") latch_d.count_down();
            else if (label == "e") latch_e.count_down();
            else if (label == "f") latch_f.count_down();
            else if (label == "g") latch_g.count_down();
            else if (label == "h") latch_h.count_down();
            else if (label == "i") latch_i.count_down();
            else if (label == "j") latch_j.count_down();
        }
        };
    vector<thread> threads;
    for (int t = 0; t < nt; ++t)
        threads.emplace_back(worker, t, work[t]);
    for (auto& th : threads)
        if (th.joinable()) th.join();
    sync_print("Calculation complete");
    return 0;
}
