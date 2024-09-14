def main(n, s, t):
    if len(s) != n or len(t) != n:
        print(-1)
        return None

    ab = []
    ba = []

    for i in range(n):
        if s[i] == "a" and t[i] == "b":
            ab.append(i + 1)  # +1 because 1-indexed
        elif s[i] == "b" and t[i] == "a":
            ba.append(i + 1)

    # Calculate the sum of lengths
    k = len(ab) + len(ba)

    # If the sum is odd, it's impossible to make necessary swaps
    if k % 2 != 0:
        print(-1)
    else:
        # If both are even
        if len(ab) % 2 == 0:
            cant_swaps = k // 2
            print(cant_swaps)
            swaps = ab + ba
            for i in range(0, len(swaps), 2):
                print(swaps[i], swaps[i + 1])

        # If both are odd
        else:
            cant_swaps = k // 2 + 1
            print(cant_swaps)
            # primer swap, "consigo mismo"
            print(ab[0], ab[0])
            print(ba[0], ba[0])
            swaps = ab[1:] + ba[1:]
            for i in range(0, cant_swaps - 2, 2):
                print(ab[i], ba[i])


if __name__ == "__main__":
    n = int(input())
    s = input()
    t = input()
    main(n,s,t)
