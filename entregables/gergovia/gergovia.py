def main(n, arr):
    # TWO POINTERS APPROACH
    i = 0
    j = 0
    res = 0

    while i<n and j<n:
        # AUMENTO i HASTA QUE ENCUENTRE UN BUYER (>0)
        # si es == 0, lo quiero seguir aumentando
        while i<n and arr[i]<=0:
            i += 1
            
        # AUMENTO j HASTA QUE ENCUENTRE UN SELLER (<0)
        # si es == 0, lo quiero seguir aumentando
        while j<n and arr[j]>=0:
            j += 1
        
        # si llegué al final de la lista
        if i==n or j==n:
            return res

        # si el seller puede vender al buyer
        if arr[i] <= -arr[j]:
            arr[j] += arr[i]                # el seller vendió arr[i] botellas
            res += arr[i]*abs(i-j)          # costo de transportar las arr[i] botellas
            arr[i] = 0                      # el buyer ya satisfizo su demanda

        # si al seller le faltan botellas
        else:
            arr[i] += arr[j]                # el seller vendió todas sus botellas
            res += abs(arr[j])*abs(i-j)     # costo de transportar las arr[j] botellas
            arr[j] = 0                      # el buyer ya compró todas las botellas

    return res



if __name__=="__main__":
    # input para no gastar memoria :)
    n = int(input())
    while n!=0:
        nums = input().split()
        arr = [int(num) for num in nums]
        print(main(n, arr))
        n = int(input())