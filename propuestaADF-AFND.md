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