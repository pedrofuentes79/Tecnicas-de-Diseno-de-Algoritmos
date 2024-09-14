def main(S, n, k):
    maxes = [0] * k+1

    # cantidad de 1s seguidos en el arreglo
    cantidad_unos_seguidos = 0
    en_string_de_unos = False
    for i in range(n):
        if S[i] == 1:
            cantidad_unos_seguidos += 1
            en_string_de_unos = True
        else:
            if en_string_de_unos:
                maxes[0] = max(maxes[0], cantidad_unos_seguidos)
                en_string_de_unos = False
            cantidad_unos_seguidos = 0
            

            
    
    