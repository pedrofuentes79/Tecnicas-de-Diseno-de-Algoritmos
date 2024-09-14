def espejo(A, low, high):
    if low > high:
        return -1
    
    mid = (high-low) // 2 + low
    if A[mid] < mid:
        return espejo(A, mid+1, high)
    elif A[mid] > mid:
        return espejo(A, low, mid-1)
    else:
        return mid
    

a = [-14, -1, 2]
print(espejo(a,0,len(a)))