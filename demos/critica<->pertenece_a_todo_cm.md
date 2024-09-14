sea e=vi->vj

d_{G}(v1,vn) < d_{G-e}(v1,vn) <=> e pertenece a todo camino minimo en G entre v1 y vn

IDA: d_{G}(v1,vn) < d_{G-e}(v1,vn) => e pertenece a todo camino minimo en G entre v1 y vn

Absurdo: asumo que hay un camino minimo entre v1 y vn que no contiene a e=vi,vj

Entonces, puedo quitar a e del grafo G y esto no altera la distancia entre v1 y vn, puesto que hay un camino minimo entre v1 y vn que no contiene a esta arista
Es decir, d_{G}(v1,vn) = d_{G-e}(v1,vn), lo que contradice de manera directa nuestra hipotesis


VUELTA: e pertenece a todo camino minimo en G entre v1 y vn => d_{G}(v1,vn) < d_{G-e}(v1,vn) 

Absurdo: d_{G}(v1,vn) >= d_{G-e}(v1,vn)

- vemos inmediatamente que  d_{G}(v1,vn) > d_{G-e}(v1,vn) no tiene sentido alguno, puesto que quitar una arista no puede aumentar el peso de un camino minimo entre dos vertices.

- Veamos el caso en que d_{G}(v1,vn) = d_{G-e}(v1,vn)
Esto significa que el camino minimo entre v1 y vn en G tiene el mismo peso en G-e
Por hipotesis, se que e pertenece a todo CM entre v1 y vn
Luego, sea C un camino minimo entre v1 y vn en G. C es de la pinta v1...vi vj ... vn, ya que todo CM en G tiene a e.
Lo que nos dice esta igualdad es que hay un C' = v1...vn que no usa a vi->vj. Es decir, que yo podria haber construido un camino del mismo peso (minimo) en G llamado C'' que no contenga a vi -> vj. Esto contradice la hipotesis de que e pertenece a todo camino minimo en G entre v1 y vn.


