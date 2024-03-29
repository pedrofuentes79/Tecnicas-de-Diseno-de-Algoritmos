
def main():
    # get input
    test_cases = int(input())
    for i in range(test_cases):
        players = []
        for j in range(10):
            players.append(input().split(" "))

        global bestAttackers, bestDefenders, bestAttackSum, bestDefenseSum, attackers, defenders
        bestAttackSum = 0
        bestDefenseSum = 0
        bestAttackers = []
        bestDefenders = []
        attackers = []
        defenders = []
        
        backtrack(players, attackers, defenders, 0, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders)

        # sort the answer
        bestAttackers.sort()
        bestDefenders.sort()

        # print the answer
        print("Case #{}:".format(i+1))
        print(bestAttackers)
        print(bestDefenders)


def backtrack(players, attackers, defenders, index, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders):

    attackSum, defenseSum = 0, 0
    for player in attackers:
        attackSum += int(player[1])

    for player in defenders:
        defenseSum += int(player[2])
    
    # caso base: ya se recorrieron todos los jugadores
    if index == len(players):
        if attackSum > bestAttackSum or (attackSum == bestAttackSum and defenseSum > bestDefenseSum):
            # reemplazo
            print("Reemplazo")
            bestAttackSum = attackSum
            bestDefenseSum = defenseSum
            bestAttackers = [player[0] for player in attackers]
            bestDefenders = [player[0] for player in defenders]
            print(bestAttackers, bestAttackSum)
            print(bestDefenders, bestDefenseSum)

        elif (attackSum == bestAttackSum and defenseSum == bestDefenseSum):
            # reemplazar solamente cuando los nombres de los jugadores sean menores
            # hacer una copia de los nombres de los jugadores, ordenarla y comparar
            attackersCopy = sorted(attackers, key=lambda x: x[0])
            bestAttackersCopy = sorted(bestAttackers, key=lambda x: x[0])
            attackersCopy = [player[0] for player in attackersCopy]
            bestAttackersCopy = [player[0] for player in bestAttackersCopy]

            if attackersCopy < bestAttackersCopy:
                bestAttackSum = attackSum
                bestDefenseSum = defenseSum
                bestAttackers = attackersCopy
                bestDefenders = [player[0] for player in defenders]
        else:
            # no hay cambios
            pass
        return

    # caso recursivo
    if len(attackers) < 5:
        attackers.append(players[index])
        backtrack(players, attackers, defenders, index+1, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders)
        attackers.pop()
    else:
        # agrego los jugadores que no están en attackers en defenders
        defenders.append(players[index])
        backtrack(players, attackers, defenders, index+1, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders)
        defenders.pop()
    



if __name__ == "__main__":
    main()