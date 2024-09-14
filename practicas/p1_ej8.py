from numpy import infty

def min_costo(c, i, j):
    # Casos base
    if j >= i or i<0: return infty
    if len(c)==0: return 0
    # Caso recursivo

    if memoria[i][j] == -1:
        # busco el minimo corte
        min_corte = c[-1] # inicializo en el mas costoso posible
        for k in range(i+1, j):
            min_corte = min(min_corte, min_costo(c,i,k) + min_costo(c,k,j))

        # guardo: el valor del corte minimo recursivo + el paso actual, que cuesta la longitud de la tabla= j-i
        memoria[i][j] = min_corte + c[j] - c[i]
    
    return memoria[i][j]


def main():
    # longitud de la tabla
    l = 10
    
    # Cortes
    c = [0, 2, 4, 7, 8, l]
    cn = len(c)
    
    #...
    
    # Inicializo la memoria
    global memoria
    

    



