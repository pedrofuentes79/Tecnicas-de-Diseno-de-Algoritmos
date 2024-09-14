#include <iostream>
#include <string>
using namespace std;


bool eq (string a, string b){
    // caso base
    if (a==b) return true;

    // si es impar, no es valido
    if (a.size() % 2 == 1) return false;

    string a1 = a.substr(0, a.size()/2);
    string a2 = a.substr(a.size()/2, a.size());
    string b1 = b.substr(0, a.size()/2);
    string b2 = b.substr(a.size()/2, a.size());

    return  (eq(a1, b2) && eq(a2, b1)) || (eq(a1, b1) && eq(a2, b2));
}

int main() {
    // speed up the input
    ios::sync_with_stdio(0);
    cin.tie(0);

    string a, b;
    cin >> a >> b;

    if (eq(a, b)) cout << "YES" << endl;
    else cout << "NO" << endl;
}