#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s, t;
    vector<int> ab, ba;
    cin >> s >> t;

    int count_a = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'a' || t[i] == 'a') {
            count_a++;
        }

        if (s[i] != t[i]){
            if (s[i] == 'a') {
                ab.push_back(i);
            } 
            else {
                ba.push_back(i);
            }
        }
    }

    //?????
    if (count_a % 2 != 0) {
        cout << -1 << endl;
        return 0;
    }

    int res = 0;
    res = (ab.size()/2 + ba.size()/2);
    // caso ab impar
    if (ab.size() % 2 != 0) {
        res += 2;
    }
    cout << res << endl;

    int i=0, j=0;
    int l1=ab.size(), l2=ba.size();

    while (i < l1-1) {
        cout << ab[i]+1 << " " << ab[i+1]+1 << endl;
        i += 2;
    }

    while (j < l2-1) {
        cout << ba[j]+1 << " " << ba[j+1]+1 << endl;
        j += 2;
    }

    if (i == l1-1){
        cout << ab[i]+1 << " " << ab[i]+1 << endl;
        cout << ab[i]+1 << " " << ba[j]+1 << endl;
    }
    return 0;
}