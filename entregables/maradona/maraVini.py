def bt(players, team, index, max_attack, max_defense, min_name):


    # team has 5 attackers: put rest of players in defense and compute max values
    if len(team) == 5: 
        # put rest of players in defense
        remaining_players_defense = [p for p in players if p not in team]
        # get current attack and defense sum
        current_attack = sum(player[1] for player in team)
        current_defense = sum(player[2] for player in remaining_players_defense)
        current_names = sorted(player[0] for player in team)

        # si cumple las condiciones, actualizo        
        if (current_attack > max_attack[0] or
            (current_attack == max_attack[0] and current_defense > max_defense[0]) or
            (current_attack == max_attack[0] and current_defense == max_defense[0] and current_names < min_name[0])):
            max_attack[0] = current_attack
            max_defense[0] = current_defense
            min_name[0] = current_names
            max_attack[1] = team[:]
        return
    
    # if we have selected 10 players, end bt
    if index == len(players):
        return


    # backtrack
    team.append(players[index])
    bt(players, team, index + 1, max_attack, max_defense, min_name)
    team.pop()
    bt(players, team, index + 1, max_attack, max_defense, min_name)

def main():
    T = int(input())
    res = []
    for case in range(T):
        players = []
        for j in range(10):
            player_input = input().split()
            players.append((player_input[0], int(player_input[1]), int(player_input[2]), j))
        
        max_attack = [0, []]
        max_defense = [0]


        bt(players, [], 0, max_attack, max_defense, [None])

        max_attack_indices = [player[3] for player in max_attack[1]]
        max_attack[1] = [player[0] for player in max_attack[1]]
        defense_team = []
        
        for player in players:
            if player[3] not in max_attack_indices:
                defense_team.append(player[0])
        res.append("Case " + str(case+1) + ":")
        res.append("(" + ", ".join(sorted(max_attack[1])) + ")")
        res.append("(" + ", ".join(sorted(defense_team)) + ")")  
    print("\n".join(res))


if __name__ == "__main__":
    main()