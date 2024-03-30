
def main():
    # get input
    test_cases = int(input())
    for i in range(test_cases):
        players = []
        for j in range(10):
            players.append(input().split(" "))

        # sort players by attack, defense and earlier lexicographical order
        sorted_players = radix(players)

        # get the sorted version of this, meaning the top 5 players, get them in sorted order, as well as the other
        bestAttackers = sorted(sorted_players[:5], key=lambda x: x[0])
        bestDefenders = sorted(sorted_players[5:], key=lambda x: x[0])
        
        
        # print the answer
        print("Case #{}:".format(i+1))
        output_attackers = '('
        for i in range(len(bestAttackers)):
            output_attackers += bestAttackers[i][0] + ', ' if i != len(bestAttackers)-1 else bestAttackers[i][0]
        print(output_attackers + ')')
        
        output_defenders = '('
        for i in range(len(bestDefenders)):
            output_defenders += bestDefenders[i][0] + ', ' if i != len(bestDefenders)-1 else bestDefenders[i][0]
        print(output_defenders + ')')
        
def radix(players):
    # sort by attack
    players = sorted(players, key=lambda x: x[0])
    players = sorted(players, key=lambda x: x[2])
    players = sorted(players, key=lambda x: x[1], reverse=True)
    return players

if __name__=='__main__':
    main()

