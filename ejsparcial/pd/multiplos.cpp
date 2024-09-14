#include <iostream>
#include <vector>

using namespace std;

int main(vector<int>& V, int n){
    vector<int> b = vector<int>(n, -1);
    b[0] = 1;

    for (int i=1; i < V.size(); i++){
        int max_value = 0;
        
        int j = 0;

        while (j<i){
            if (V[i] % V[j] == 0){
                // si el indice j es multiplo, busco si es el que me dio "mas rendimiento" en b
                max_value = max(max_value, b[j]);
            }
        }

        if (max_value > 0) {
            b[i] = 1 + max_value;
        }
        else{
            b[i] = b[i-1];
        }
    }

}