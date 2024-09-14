Determinar aristas criticas en $G$ para $v_1$ y $v_n$ dados.

1) encontrar distancias desde $v_1$ en $G$
2) encontrar distancias desde $v_n$ en $G^t$
3) Armar el subgrafo $P$ de caminos mínimos en $G$ de $v_1$ a $v_n$.
4) Identifico las aristas puente en $P$


# Demostraciones. 
Uso la def de $e$ arista crítica si $d_{G}(v_1,v_n) < d_{G-e}(v_1,v_n)$

$e$ es puente en $P \iff d_{G}(v_1,v_n) < d_{G-e}(v_1,v_n)$
---
## subdemo
Para ver esto, observo que:
$d_{G}(v_1,v_n) < d_{G-e}(v_1,v_n) \iff e$ pertenece a todo camino mínimo en $G$ entre $v_1$ y $v_n$

Demostración:

IDA: $d_{G}(v_1,v_n) < d_{G-e}(v_1,v_n) \implies e$ pertenece a todo camino mínimo en $G$ entre $v_1$ y $v_n$

Absurdo: asumo que hay un camino mínimo entre $v_1$ y $v_n$ que no contiene a $e=v_i,v_j$

Entonces, puedo quitar a $e$ del grafo $G$ y esto no altera la distancia entre $v_1$ y $v_n$, puesto que hay un camino mínimo entre $v_1$ y $v_n$ que no contiene a esta arista
Es decir, $d_{G}(v_1,v_n) = d_{G-e}(v_1,v_n)$, lo que contradice de manera directa nuestra hipótesis


VUELTA: $e$ pertenece a todo camino mínimo en $G$ entre $v_1$ y $v_n \implies d_{G}(v_1,v_n) < d_{G-e}(v_1,v_n)$

Absurdo: $d_{G}(v_1,v_n) \geq d_{G-e}(v_1,v_n)$

- vemos inmediatamente que  $d_{G}(v_1,v_n) > d_{G-e}(v_1,v_n)$ no tiene sentido alguno, puesto que quitar una arista no puede aumentar el peso de un camino mínimo entre dos vértices.

- Veamos el caso en que $d_{G}(v_1,v_n) = d_{G-e}(v_1,v_n)$
Esto significa que el camino mínimo entre $v_1$ y $v_n$ en $G$ tiene el mismo peso en $G-e$
Por hipótesis, sé que $e$ pertenece a todo $CM$ entre $v_1$ y $v_n$
Luego, sea $C$ un camino mínimo entre $v_1$ y $v_n$ en $G$. $C$ es de la pinta $v_1\ldots v_i\ v_j\ldots v_n$, ya que todo $CM$ en $G$ tiene a $e$.
Lo que nos dice esta igualdad es que hay un $C' = v_1\ldots v_n$ que no usa a $v_i\to v_j$. Es decir, que yo podría haber construido un camino del mismo peso (mínimo) en $G$ llamado $C''$ que no contenga a $v_i \to v_j$. Esto contradice la hipótesis de que $e$ pertenece a todo camino mínimo en $G$ entre $v_1$ y $v_n$.
-----
Volviendo a la demostracion original...

Luego, demostrar que $e$ es puente en $P \iff d_{G}(v_1,v_n) < d_{G-e}(v_1,v_n)$ es equivalente a demostrar:
$e$ es puente en $P \iff e$ pertenece a todos los caminos mínimos de $v_1$ a $v_n$ en $G$.

IDA
quiero ver que si $e$ es puente en $P \implies e$ pertenece a todos los caminos mínimos de $v_1$ a $v_n$ en $G$.

Demuestro por absurdo: asumo que $e$ NO pertenece a todos los caminos mínimos de $v_1$ a $v_n$ en $G$.

Es decir, hay un $CM$ $C$ que no utiliza a $v_i\to v_j$ para llegar de $v_1$ a $v_n$.

Por hipótesis, que $e$ sea puente en $P$ significa que su remoción aumenta las componentes conexas en $P$. Es decir, necesito esta arista para llegar desde $v_1$ a $v_n$. (por def de subgrafo de caminos mínimos de $v_1$ a $v_n$ en $G$)


Luego, observemos $C$, que no utiliza $v_i\to v_j$ para llegar de $v_1$ a $v_n$. Como $C$ es camino mínimo de $v_1$ a $v_n$, pertenece a $P$, el subgrafo de caminos mínimos en $G$ de $v_1$ a $v_n$. Luego, hay un camino en $P$ que no utiliza la arista $v_i\to v_j$. Esto contradice lo que dedujimos recién de la hipótesis, que al remover esta arista no se puede llegar de $v_1$ a $v_n$ en $P$. Entonces, llego a un absurdo


VUELTA
quiero ver que $e=v_i\to v_j$ está en todos los caminos mínimos de $v_1$ a $v_n$ en $G \implies e$ es puente en $P$, el subgrafo de caminos mínimos de $v_1$ a $v_n$ en $G$.

Veamos esto por absurdo. Asumo que $e$ no es una arista puente en $P$. 
Luego, la remoción de $e$ en $P$ no afecta la cantidad de componentes conexas, es decir que el grafo sigue siendo conexo (era conexo de antes porque sé que existe un camino mínimo de $v_1$ a $v_n$, si no existiese la demostración es trivial)
Que siga siendo conexo quiere decir que puedo llegar desde un vértice hasta otro, tomamos $v_1$ y $v_n$

Es decir, hay un camino en $P$ desde $v_1$ a $v_n$ que no utiliza $e=v_i\to v_j$

(aclaración: $e$ pertenece a $P$ puesto que $e$ pertenece a todos los caminos mínimos de $v_1$ a $v_n$ en $G$ por hipótesis)

Luego, como todos los caminos de $v_1$ a $v_n$  en $P$ son caminos mínimos (por def de subgrafo de caminos mínimos), implica que si puedo llegar desde $v_1$ a $v_n$ en $P$ sin utilizar una arista, es porque esa arista no pertenece a todos los caminos mínimos de $v_1$ a $v_n$ en $G$.

Entonces, llego a un absurdo! Si puedo llegar desde $v_1$ a $v_n$ sin utilizar $v_i\