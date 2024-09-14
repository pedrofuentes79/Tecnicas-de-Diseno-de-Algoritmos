def top_down(M, i, j, mem):
    n = len(M) # filas
    m = len(M[0]) # columnas

    if mem is None:
        mem = [[-1] * n for _ in range(m)]
    
    if mem[i][j] == -1:
        # caso borde abajo
        if i == n-1 and j<m-1:
            mem[i][j] = M[i][j] + top_down(M, i, j+1, mem)
        # caso borde derecha
        if j == m-1 and i<n-1:
            mem[i][j] = M[i][j] + top_down(M, i+1, j, mem)
        # caso normal
        if i<n-1 and j<m-1:
            mem[i][j] = M[i][j] + min(top_down(M, i+1, j, mem), top_down(M, i, j+1, mem))
        
    return mem[i][j]


def bottom_up(M):
    n = len(M) # filas
    m = len(M[0]) # columnas
    mem = [[-1] * n for _ in range(m)]  

    # lleno esq inf der
    mem[m-1][n-1] = M[m-1][n-1]

    # lleno borde der
    i = n-2
    while i>=0:
        mem[i][m-1] = mem[i+1][m-1] + M[i+1][m-1]
        i-=1

    # lleno borde inf
    j = m-2
    while i>=0:
        mem[n-1][j] = mem[n-1][j+1] + M[n-1][j+1]
        j-=1

    # lleno el resto
    for i in range(n-2, 0, -1):
        for j in range(m-2, 0, -1):
            mem[i][j] = min(mem[i+1][j], mem[i][j+1])

    return mem

def reconstruir(M):
    costos = bottom_up(M)
    camino = [(0,0)]
    n = len(M) # filas
    m = len(M[0]) # columnas

    i,j=0
    # itero desde el principio buscando el costo más barato, "deshanciendo" hasta llegar al final

    # hasta que lleguen ambos a n-1 y m-1
    while i!=n-1 and j!=m-1:
        
        #casos borde
        if i == n-1:
            j+=1
        elif j == m-1:
            i+=1
        else:
            # caso "normal"
            if costos[i+1][j] > costos[i][j+1]:
                i+=1
            else:
                j+=1
        camino.append((i,j))
    
    return camino