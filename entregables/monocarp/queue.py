
def main(n,s,t):
    res_s = []
    res_t = []
    k = 0
    ab = []
    ba = []

    for i in range(n):
        if s[i] == "a" and t[i] == "b":
            if(ab == []):
                ab.append(i+1)
            else:
                res_s.append(ab[0])
                ab.pop(0)
                res_t.append(i+1)
                k += 1
        elif s[i] == "b" and t[i] == "a":
            if(ba == []):
                ba.append(i+1)
            else:
                res_s.append(ba[0])
                ba.pop(0)
                res_t.append(i+1)
                k += 1

    while not ab==[] and not ba==[]:
        swap = ab[0]+1
        ab.pop(0)
        res_s.append(swap)
        res_t.append(swap)
        res_s.append(swap)
        res_t.append(ba[0])
        ba.pop(0)
        k += 2
    
    if(ab==[] and ba==[]):
        return k, res_t, res_s
    else:
        return -1, [], []
    
if __name__ == "__main__":
    n = int(input())
    s = input()
    t = input()
    k, res_s, res_t = main(n,s,t)
    if(k == -1):
        print(-1)
    else:
        print(k)
        for i in range(k):
            print(res_s[i], res_t[i])
