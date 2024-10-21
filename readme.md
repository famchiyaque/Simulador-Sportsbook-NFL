# Proyecto: Apuesta/Parlay Maker para Futból Americano
Este programa es un simulador de aplicaciones para apostar que 
te deja depositar dinero y elegir tus apuestas y/o crear un parlay
de varias apuestas para ganar aún más.

## Descripción del avance 1
(Esto fue totalment por aparte del primer avance)
Qué es un domingo viendo la NFL sin una apuesta?! Este proyecto require de un archivo que contiene los guesses de puntajes del usuario, es decir los 5 valores númericos que el usuario cree que van a ser puntajes finales de todos los partidos de football americano de la semana, y también uno que contiene los puntajes finales reales de los partidos de esa semana. El programa evalúa si al menos 3 de los 5 guesses por el usuario sí fueron puntajes finales reales, para determinar si el usuario ganó o no.

## Descripción del avance 2
1. Este programa lee las líneas de apuestas disponibles de un archivo dadas por "Las Vegas" para
    la semana de futból, y las guarda en un vector.
2. Luego utiliza otro vector para guardar las apuestas que va creando el usuario.
3. Utiliza una lista ligada para crear el parlay del usuario, que sirve para permitir
    acciones de undo, que es normalment donde sirven las lista ligadas en la vida real,
    como en un editor de texto, que guarda las acciones que haces para ofrecer un shortcut
    que pueda eliminar tu ultima accion. Bueno para eso iba con mi idea del parlay.
4. Luego el usuario puede salir del creador de apuestas/parlay, y se usa otro vector para
    cargar los resultados de los jugadores de otro archivo.
5. Las apuestas y apuestas del parlay del usuario se comparan con este vector de resultados
    para determinar si fueron éxitosos o no.
6. Regresa un balance final después de las apuestas al usuario.

## Instrucciones para compilar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`g++ main.cpp` 

## Instrucciones para ejecutar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`./a.exe`, o como se llame el archivo generado a partir del comando anterior 

## Descripción de las entradas del avance de proyecto
Este programa requiere de 2 archivos. Ambos vienen del sportsbook provider. Uno contiene 
las apuestas y odds que tienen disponibles como oferta para los usuarios de su app, con
el siguiente formato:
    Player_Name | Player_Line | Over_Odds | Under_Odds

Y el otro archivo contiene los resultados de estas ofertas, con un solo integer que 
representa el desempeño real del jugador:
    44 (por ejemplo, aquí representaría 44 yardas)

Es importante notar que el programa espera que los resultados del segundo archivo vienen
en el mismo orden, según la apuesta, de las líneas en el primer archivo.

## Descripción de las salidas del avance de proyecto
Hay mucha salida para que sea interactiva la experiencia, que después de cada acción del 
usuario, hay un mensaje que describe los cálculos/registros que se hicieron a partir del 
input.
Al final, regresa el balance final del usuario, que es el depósito inicial del usuario menos
la cantidad que apostó, más las ganancias de sus apuestas.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes
#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.
(Esto viene del avance 1, que otra vez no tiene que ver con este programa)
Para este programa, el método de ordenamiento elegido es el merge sort, debido a que entre selection sort, insertion sort, y merge sort, es el más rápido de los 3 en promedio, y en su peor caso (caso que más le puede costar al algoritmo en términos de tiempo). Tiene un tiempo de complejidad fijo de O(n log(n)) siempre, solo al costo de ocupar doble el espacio de memoria que los otros 2, que, para este proyecto, no es un problema. Los otros dos tienen como promedio un tiempo de complejidad de O(n^2), que para este caso podría funcionar como el dataset es pequeño pero para las buenas prácticas, utilizaremos el método más rapido.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.
(Nuevo análisis de esctructuras de datos en este programa)
Aquí hago uso de la estructura más sencilla para guardar datos que es el vector, e inicializo 3 al inicio
del programa, cada uno que servirá de otra cosa:
    vector<string> bet_lines = {""}; n = cantidad de apuestas disponibles
        - push_back() para guardar las apuestas dadas en el primer archivo: O(1) en promedio
        - accedimiento de cada elemento para una lectura completa para la interfaz al usuario: O(n) (pero es necesario)
    vector<Bet> user_bets; n = cantidad de apuestas creadas por el usuario
        - utiliza push_back(Bet) de los bets creados: O(1) en promedio
        - accedimiento para hacer cálculos finales a cada elemento: O(n)
    vector<int> bet_results = {0}; n = cantidad de resultados de las apuestas
        - push_back() durante lectura O(1)
        - accedimiento directo para comparar resultados con apuestas O(1)

    Parlay parlay = Parlay(); **Una lista ligada**
        - inicialización: O(1)
        - undoBet(): O(1)
        - addBet(): O(1)
        - gradeParlay(): O(n) n = cantidad de apuestas en el parlay

Yo creo que cumplo con esta competencia porque en **ningún lugar en mi programa, si fueras a hacer más grandes los archivos o si un usuario creara mil apuestas y/o un parlay de 10,000 apuestas, existiría un proceso/algoritmo que tenga una complejidad de tiempo peor a O(n)**. 
De hecho cuando iba a programar la parte de evaluar las apuestas, iba a hacer un for loop añadido que
correría por cada apuesta, sacar el nombre del jugador, y iterar por todo el archivo hasta encontrar 
la línea correspondiente, pero eso sería muy tardado a gran escala. Por eso creé el vector de 
resultados, que itera por el archivo de resultados solamente una vez, y luego las apuestas pueden
acceder a las resultados por su index con O(1).

### SICT0302: Toma decisiones
#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
(Del avance 1)
Ya que los vectores están ordenados, el programa itera por los valores del vector de guesses del usuario, y para cada valor utiliza el método de búsqueda binaria en el vector de los puntajes finales reales para ver si el guess del usuario fue correcto y determinar el score total del usuario. Necesita 3/5 mínimo para ganar.
Igual que antes, este método de búsqueda es para optimizar el programa en términos del tiempo. La búsqueda secuencial normal tiene un a complejidad de tiempo de O(n) (n siendo el número de elementos del vector), mientras que la búsqueda binaria tiene una complejidad de tiempo de O(log(n)).

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.
Lo que buscaba era una manera de proporcionar la opción de 'undo' en la creación del parlay, igual como
los casos en la vida real que usan listas ligadas. La lista ligada en este programa, o parlay, es una lista
de tipo stack, porque la última apuesta que entra, es la que se elimina al llamar en 'undoBet' función.
Last In First Out. El 'undoBet' es como un 'pop', donde el pop saca el último element en agregarse.
El problema con las listas es la iteración/búsqueda de elementos, pero en este caso la
búsqueda no era necesaria, y la iteración solamente se ocupa al terminar las apuestas y para 
evaluar cada apuesta del parlay y ver que cada una salió bien para que el usuario pueda ganar. En ese caso,
la iteración de O(n) es necesario.

### SICT0303: Implementa acciones científicas
#### Implementa mecanismos para consultar información de las estructras correctos.
El accedimiento a las esctructuras de datos en este programa, que son vectores y una lista ligada, siempre
son optimizadas. La iteración de la lista ligada tiene O(n), y es necesario al evaluarse. Luego durante esa 
evaluación, el vector de resultados proporciona la información para evaluar cada apuesta y siempre se le 
accede con un index y por lo tanto O(1).

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.
Utilizando ifstream, se leen los archivos línea por línea y las carga en vectores para que el programa más adelante pueda acceder a la información de forma inmediata con un index O(1).