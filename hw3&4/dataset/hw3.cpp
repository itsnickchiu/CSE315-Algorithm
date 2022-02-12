
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void readfile ( string dir, int &c, vector<int>& v, vector<int>& w, int &n );
void writefile ( string dir, int ans, int arr[], int n );
int knapsack ( int c, vector<int> v, vector<int> w, int n, int arr[] );
int main() {
    int ans;
    int c = 0;                  // capacity
    vector <int> v;             // value
    vector <int> w;             // weight 
    int n = 0;                  // number of items

    string dir;
    cout << "Please enter the directory: ";
    cin >> dir;

    readfile (dir, c, v, w, n);      // read file from dataset
    int arr[n];                      // array for storing 0/1
    ans = knapsack (c, v, w, n, arr);
    cout << ans << endl;
    for ( int i = 0 ; i < n ; i++ ) {
        cout << arr[i] << endl;
    }
    writefile(dir, ans, arr, n);
}

int knapsack ( int c, vector<int> v, vector<int> w, int n, int arr[] ) {
    vector <vector <int> > dp( n+1, vector<int> (c+1) );
    for ( int i = 0 ; i <= n ; i++ ) {
        for ( int j = 0 ; j <= c ; j++ ) {
            if ( i == 0 || j == 0 ) {
                dp[i][j] = 0;
            } else if ( j < w[i-1] ) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max( v[i-1] + dp[i-1][j-w[i-1]], dp[i-1][j] );
            }
        }
    }
    int res = dp[n][c];
    int wt = c;
    for ( int i = n ; i > 0 ; i-- ) {
        if ( res == dp[i-1][wt] ) {
            arr[i-1] = 0;
            continue;
        }
        else {
            arr[i-1] = 1;
            res = res - v[i-1];
            wt = wt - w[i-1];
        }
    } 
    return dp[n][c];
}

void readfile ( string dir, int &c, vector<int>& v, vector<int>& w, int &n ) {
    ifstream fileIn;
    fileIn.open("../dataset/" + dir + "/c.txt");
    // capacity
    fileIn >> c;
    fileIn.close();

    int tmp;
    fileIn.open("../dataset/" + dir + "/p.txt");
    // value
    while ( fileIn >> tmp ) {
        v.push_back(tmp);
    }
    fileIn.close();

    fileIn.open("../dataset/" + dir + "/w.txt");
    // weight
    while ( fileIn >> tmp ) {
        w.push_back(tmp);
    }
    // number of items
    n = w.size();
    fileIn.close();
}

void writefile ( string dir, int ans, int arr[], int n ) {
    ofstream file;
    file.open("ans_" + dir + ".txt");
    file << ans << "\n";
    for ( int i = 0 ; i < n ; i++ )
        file << arr[i] << "\n";
    file.close();
}