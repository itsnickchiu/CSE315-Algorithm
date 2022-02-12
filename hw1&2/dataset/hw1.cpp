
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int knapsack ( int n, int w[], int v[], int c, int i, int arr[] );
void copyArr(int arr[], int arrDest[], int n);

int main() {
    
    string dir;
    cout << "Please enter the directory: ";
    cin >> dir;

    /* --------------------------- read dataset ---------------------------- */
    ifstream fileIn;
    fileIn.open("../dataset/" + dir + "/c.txt");
    int c;     // capacity
    fileIn >> c;
    fileIn.close();

    fileIn.open("../dataset/" + dir + "/p.txt");
    int n = 0; // number of items
    int tmp;
    while ( fileIn >> tmp ) {
        n++;
    }
    fileIn.close();

    fileIn.open("../dataset/" + dir + "/p.txt");
    int v[n];  // value
    int i = 0;
    while ( fileIn >> v[i] ) {
        i++;
    }
    fileIn.close();

    fileIn.open("../dataset/" + dir + "/w.txt");
    int w[n];  // weight
    i = 0;
    while ( fileIn >> w[i] ) {
        i++;
    }
    fileIn.close();

    /* ----------------------------- solution ------------------------------ */

    int arr[n];  // array for indicating 0/1
    memset(arr, 0, sizeof(arr));
    int ans = knapsack ( n, w, v, c, 0, arr );

    // print the answer
    cout << ans << endl;
    // condition for item taken or not 
    for ( int i = 0 ; i < n ; i++ )
        cout << arr[i] << endl;

    // write output to text file
    ofstream file;
    file.open("ans_" + dir + ".txt");
    file << ans << "\n";
    for ( int i = 0 ; i < n ; i++ )
        file << arr[i] << "\n";
    file.close();
    
}

int knapsack ( int n, int w[], int v[], int c, int i, int arr[] ) {
    // base case
    if ( i == n || c <= 0 ) {
        return 0;
    }
    // weight heavier than capacity
    if ( w[i] > c ) {
        arr[i] = 0;
        return knapsack ( n, w, v, c, i+1, arr );
    }
    else {
        int vin = v[i] + knapsack ( n, w, v, c-w[i], i+1, arr ); // include value
        int arrWith[n];                                          // replicate of array indicating 0/1, in order to avoid overwritting
        copyArr(arr, arrWith, n);
        int vex = knapsack ( n, w, v, c, i+1, arr );             // exclude value
        if ( vin > vex ) {               // take 
            copyArr(arrWith, arr, n);
            arr[i] = 1;
            return vin;
        }
        else {                           // not take
            arr[i] = 0;
            return vex;
        }
    }
}

void copyArr(int arr[], int arrDest[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        arrDest[i] = arr[i];
    }
}
