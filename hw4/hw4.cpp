
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void readfile ( string dir, int &c, vector<int>& v, vector<int>& w, int &n );
void writefile ( string dir, int ans, vector<int> arr, int n );
int SA_knapsack ( int c, vector<int> v, vector<int> w, int n, vector<int>& max_arr );
int main() {
    int ans;
    int c = 0;                  // capacity
    vector <int> v;             // value
    vector <int> w;             // weight 
    int n = 0;                  // number of items

    string dir;
    cout << "Please enter the directory: ";
    cin >> dir;

    readfile (dir, c, v, w, n);                // read file from dataset
    vector<int> arr(n, 0);                     // array for storing 0/1
    ans = SA_knapsack (c, v, w, n, arr);
    cout << ans << endl;
    writefile(dir, ans, arr, n);
}

int SA_knapsack ( int c, vector<int> v, vector<int> w, int n, vector<int>& max_arr ) {
    // c : capacity
    // v : value array
    // w : weight array
    // n : number of items
    srand(time(NULL));
    double alpha = 0.99189;
    double T = 19260;                       // initial temperature
    double final_T = 3;                     // final temperature
    int n_iter = 1000;                      // iteration times
    int max_wt = 0;
    int max_val = 0;
    // randomize 0/1 array
    while (1) {
        max_wt = 0;
        max_val = 0;
        for ( int i = 0 ; i < n ; i++ ) {
            int bit = rand() % 2;
            max_arr[i] = bit;
            max_wt += w[i] * max_arr[i];
            max_val += v[i] * max_arr[i];
        }
        if ( max_wt <= c )
            break;
    }
    while ( T > final_T ) {
        for ( int i = 0 ; i < n_iter ; i++ ) {
            int current_wt;
            int current_val;
            int idx1, idx2;
            // randomly choose 2 entries to flip
            while (1) {
                current_wt = max_wt;
                current_val = max_val;
                idx1 = rand() % n;
                idx2 = rand() % n;
                if ( idx1 == idx2 )
                    continue;
                if ( max_arr[idx1] == 1 ) {
                    current_wt -= w[idx1];
                    current_val -= v[idx1];
                } else {
                    current_wt += w[idx1];
                    current_val += v[idx1];
                }
                if ( max_arr[idx2] == 1 ) {
                    current_wt -= w[idx2];
                    current_val -= v[idx2];
                } else {
                    current_wt += w[idx2];
                    current_val += v[idx2];
                }
                // each updated weights need to smaller than capacity
                if ( current_wt <= c )
                    break;
            }
            if ( current_val > max_val ) {
                max_val = current_val;
                max_wt = current_wt;
                max_arr[idx1] = !max_arr[idx1];
                max_arr[idx2] = !max_arr[idx2];
            } else {
                double p = ((double) rand() / (RAND_MAX + 1.0));      // generate probability between [0, 1)
                double e = exp( -(max_val - current_val) / T );
                if ( e > p ) {
                    max_val = current_val;
                    max_wt = current_wt;
                    max_arr[idx1] = !max_arr[idx1];
                    max_arr[idx2] = !max_arr[idx2];
                }
            }
        }
        T = T * alpha;
    }
    return max_val;
}

void readfile ( string dir, int &c, vector<int>& v, vector<int>& w, int &n ) {
    ifstream fileIn;
    fileIn.open("dataset/" + dir + "/c.txt");
    // capacity
    fileIn >> c;
    fileIn.close();

    int tmp;
    fileIn.open("dataset/" + dir + "/p.txt");
    // value
    while ( fileIn >> tmp ) {
        v.push_back(tmp);
    }
    fileIn.close();

    fileIn.open("dataset/" + dir + "/w.txt");
    // weight
    while ( fileIn >> tmp ) {
        w.push_back(tmp);
    }
    // number of items
    n = w.size();
    fileIn.close();
}

void writefile ( string dir, int ans, vector<int> arr, int n ) {
    ofstream file;
    file.open("ans_" + dir + ".txt");
    file << ans << "\n";
    for ( int i = 0 ; i < n ; i++ )
        file << arr[i] << "\n";
    file.close();
}