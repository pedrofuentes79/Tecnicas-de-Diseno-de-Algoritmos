#include<vector>
#include<iostream>
#include<cmath>

using namespace std;

int solve(vector<int>& arr, int n){
    int i = 0;
    int j = 0;
    int work = 0;

    // inicializo i y j en los primer buyer y seller, respectivamente

    


    while (i<n && j<n){

        // ACTUALIZO i, j PARA QUE SEAN BUYER Y SELLER, RESPECTIVAMENTE
        while (i<n && arr[i]<=0){
            i++;
        }
        while (j<n && arr[j]>=0){
                j++;
        }


        // caso 0: llegué al final de la lista
        if (i==n || j==n){
            return work;
        }

        // caso 1: el seller puede vender al buyer
        if (arr[i] <= -arr[j]){
            arr[j] += arr[i];                       // le "resto" las botellas que vendió
            work += abs(arr[i]) * abs(i-j);         // añado el costo del viaje * cant botellas
            arr[i] = 0;                            // el buyer compro todo lo que queria
        }

        // caso 2: el seller no tiene suficientes botellas
        else {
            arr[i] += arr[j];                       // le "resto" las botellas que compro al buyer
            work += abs(arr[j]* (i-j));             // añado el costo del viaje * cant botellas
            arr[j] = 0;                             // el seller se queda con 0 botellas
        }
    }
    return work;
}


int main() {
    // speed up input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> res;

    while (n != 0) {
        vector<int> arr;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            arr.push_back(x);
        }
        int answer_i = solve(arr, n);
        res.push_back(answer_i);
        cin >> n;
    }

    for (int i = 0; i < res.size(); i++){
        cout << res[i] << endl;
    }
}