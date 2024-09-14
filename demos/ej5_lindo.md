# Determinar aristas críticas en G para v1 y vn dados

1. Encontrar distancias desde v1 en G 
2. Encontrar distancias desde vn en G^t
3. Armar el subgrafo P de caminos mínimos en G de v1 a vn
4. Identificar las aristas puente en P

---

## Demostraciones
Uso la definición de e arista crítica si d_{G}(v1,vn) < d_{G-e}(v1,vn)

e es puente en P <=> d_{G}(v1,vn) < d_{G-e}(v1,vn)

---

### Subdemo:
Para ver esto, observo que:
d_{G}(v1,vn) < d_{G-e}(v1,vn) <=> e pertenece a todo camino mínimo en G entre v1 y vn

#### Demostración:

**Ida**: d_{G}(v1,vn) < d_{G-e}(v1,vn) => e pertenece a todo camino mínimo en G entre v1 y vn

**Prueba por el absurdo**: Asumo que hay un camino mínimo entre v1 y vn que no contiene a e=vi,vj

Entonces, puedo quitar a e del grafo G y esto no altera la distancia entre v1 y vn, puesto que hay un camino mínimo entre v1 y vn que no contiene a esta arista. Es decir, d_{G}(v1,vn) = d_{G-e}(v1,vn), lo que contradice de manera directa nuestra hipótesis.

**Vuelta**: e pertenece a todo camino mínimo en G entre v1 y vn => d_{G}(v1,vn) < d_{G-e}(v1,vn) 

**Prueba por el absurdo**: d_{G}(v1,vn) >= d_{G-e}(v1,vn)

- Vemos inmediatamente que d_{G}(v1,vn) > d_{G-e}(v1,vn) no tiene sentido alguno, puesto que quitar una arista no puede aumentar el peso de un camino mínimo entre dos vértices.

- Veamos el caso en que d_{G}(v1,vn) = d_{G-e}(v1,vn). Esto significa que el camino mínimo entre v1 y vn en G tiene el mismo peso en G-e. Por hipótesis, sé que e pertenece a todo camino mínimo entre v1 y vn. Luego, sea C un camino mínimo entre v1 y vn en G. C es de la forma v1...vi vj ... vn, ya que todo camino mínimo en G tiene a e. Lo que nos dice esta igualdad es que hay un C' = v1...vn que no usa a vi->vj. Es decir, que yo podría haber construido un camino del mismo peso (mínimo) en G llamado C'' que no contenga a vi -> vj. Esto contradice la hipótesis de que e pertenece a todo camino mínimo en G entre v1 y vn.

---

Luego, demostrar que e es puente en P <=> d_{G}(v1,vn) < d_{G-e}(v1,vn) es equivalente a demostrar:
e es puente en P <=> e pertenece a todos los caminos mínimos de v1 a vn en G.

**Ida**
Quiero ver que si e es puente en $P => e$ pertenece a todos los caminos mínimos de v1 a vn en G.

**Prueba por el absurdo**: Asumo que e NO pertenece a todos los caminos mínimos de v1 a vn en G.

Es decir, hay un camino mínimo C que no utiliza a vi->vj para llegar de v1 a vn.

Por hipótesis, que e sea puente en P significa que su remoción aumenta las componentes conexas en P. Es decir, necesito esta arista para llegar desde v1 a vn (por definición de subgrafo de caminos mínimos de v1 a vn en G).

Luego, observemos C, que no utiliza vi->vj para llegar de v1 a vn. Como C es camino mínimo de v1 a vn, pertenece a P, el subgrafo de caminos mínimos en G de v1 a vn. Luego, hay un camino en P que no utiliza la arista vi->vj. Esto contradice lo que dedujimos recién de la hipótesis, que al remover esta arista no se puede llegar de v1 a vn en P. Entonces, llego a un absurdo.

**Vuelta**
Quiero ver que e=vi->vj está en todos los caminos mínimos de v1 a vn en G => e es puente en P, el subgrafo de caminos mínimos de v1 a vn en G.

**Prueba por el absurdo**: Asumo que e no es una arista puente en P. 
Luego, la remoción de e en P no afecta la cantidad de componentes conexas, es decir, que el grafo sigue siendo conexo (era conexo de antes porque sé que existe un camino mínimo de v1 a vn, si no existiese la demostración es trivial).
Que siga siendo conexo quiere decir que puedo llegar desde un vértice hasta otro, tomamos v1 y vn.

Es decir, hay un camino en P desde v1 a vn que no utiliza e=vi->vj

(Aclaración: e pertenece a P puesto que e pertenece a todos los caminos mínimos de v1 a vn en G por hipótesis)

Luego, como todos los caminos de v1 a vn en P son caminos mínimos (por definición de subgrafo de caminos mínimos), implica que si puedo llegar desde v1 a vn en P sin utilizar una arista, es porque esa arista no pertenece a todos los caminos mínimos de v1 a vn en G.

Entonces, llego a un absurdo! Si puedo llegar desde v1 a vn sin utilizar vi-> vj es porque vi->vj no pertenece a todos los caminos mínimos en G, lo que contradice mi hipótesis.