
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

class Item {
    public:
        int value;
        int weight;
        int index;
};

int knapsack ( int n, int c, Item item[], int arr[] );
bool cmp ( Item a, Item b );
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

    fileIn.open("../dataset/" + dir + "/w.txt");
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

    /* ------------------------------ solution ------------------------------- */

    // initialize
    Item item[n];
    for ( int i = 0 ; i < n ; i++ ) {
        item[i].value = v[i];
        item[i].weight = w[i];
        item[i].index = i;
    }
    int arr[n]; // array for indicating 0/1
    memset(arr, 0, sizeof(arr));

    int ans = knapsack ( n, c, item, arr );
    cout << ans << endl;
    for ( int i = 0 ; i < n ; i++ ) {
        cout << arr[i] << endl;
    }

    // write output to text file
    ofstream file;
    file.open("ans_" + dir + ".txt");
    file << ans << "\n";
    for ( int i = 0 ; i < n ; i++ )
        file << arr[i] << "\n";
    file.close();
}

int knapsack ( int n, int c, Item item[], int arr[] ) {
    sort( item, item + n, cmp ); // sort in descending order by value per weight
    int maxVal = 0;
    // take until cannot afford
    for ( int i = 0 ; i < n ; i++ ) {
        if ( c - item[i].weight >= 0 ) {
            c -= item[i].weight;
            maxVal += item[i].value;
            arr[item[i].index] = 1;
        }
    }
    return maxVal;
}

bool cmp ( Item a, Item b ) {
    double r1 = (double)a.value / (double)a.weight;
    double r2 = (double)b.value / (double)b.weight;
    return r1 > r2;
}