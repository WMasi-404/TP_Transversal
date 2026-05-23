La Propuesta 1 (lista de transiciones) es la más directa ya que modelar δ como una lista de ternas (q, a, destino) es casi una traducción literal de la definición formal. Su debilidad es el acceso lineal, que se vuelve costoso en autómatas grandes.

La Propuesta 2 (indexado por estado) introduce una mejora estructural significativa: cada estado "sabe" sus propias transiciones. Esto convierte al autómata en un "grafo"  y hace que la simulación de una cadena sea muy natural: buscás el estado, recorrés su lista, avanzás. Funciona bien tanto para AFD como AFND sin cambiar la estructura.

La Propuesta 3 (matriz dispersa) apunta a la eficiencia. Al convertir estados y símbolos en índices enteros, la consulta δ(q, a) puede hacerse en O(1). El costo es que se pierde legibilidad y se requiere una capa de numeración previa. Es más apropiada para AFDs donde el alfabeto y los estados son conocidos de antemano.

La Propuesta 4 (delta funcional) es conceptualmente la más cercana a la matemática: cada entrada del array representa una aplicación concreta de δ. Esto la hace muy fácil de razonar formalmente .

La Propuesta 5 (estados compuestos) no es realmente una representación general del autómata, sino una estructura auxiliar pensada exclusivamente para el proceso de construcción por subconjuntos de AFND -> AFD. No sirve como punto de partida ya que depende de las propuestas anterirores para representar el AFND.

==>

Según lo que pudimos analizar entre los tres integrantes del grupo,
en conjunto hemos decidido optar por la segunda propuesta de las 
estructuras para representar a los autómatas, nuestras razones van
de la mano con el tipo de estructura que utiliza la propuesta, la
reutilización del código de nuestras operaciones de ast, y demás
ventajas en los testeos de la propuesta con respecto a las demás,

-Reutilización de código
-Misma estructura para AFD y AFND cambia solo la cardinalidad de los
destinos pero el modelo para los dos es el mismo
-Tiene una simulación bastante parecida: busca el estado, recorre
 las transiciones, y avanza con las funciones de lista ya implementadas
  en el ast

las demás propuestas se quedan estancadas en la poca viabilidad con
respecto a las estructuras de datos utilizadas y la poca
eficiencia en sus modelos...