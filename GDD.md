# 'JuegoZombis'

## Resumen
- **Género**: Twin Stick Shooter
- **Modos**: Un jugador / Arcade
- **Plataformas**: Pc - Teclado y ratón
- **Lenguaje de programación**: C++
- **Público objetivo:** Mayores de 13

## 1.- Descripción

JuegoZombis es un juego del genero Twin-Stick Shooter para un jugador en el que este tendrá que sobrevivir oleadas de zombis que se volverán más difíciles cada vez que el jugador logre matar a todos los zombis de la oleada actual. El jugador obtendrá puntos por cada zombi que mate y hay una probabilidad que aparezca un powerUp cada vez que muere un zombi. La partida terminará cuando el jugador es derrotado por los zombis y se le mostrará la puntuación total que ha obtenido y su mejor record. El jugador podra guardar la partida desde el menu de pausa y podra continuarla más tarde, pero si el jugador pierde, la partida guardada se borrará.

El juego usa una perspectiva top-down que permite ver todo el area de juego y se podrán distinguir todos los elementos de la partida facilmente. 

El área de juego es un mapa cuadrado que tendra en cada extremo una zona donde pueden aparecer los zombis y el jugador no tendrá aceso a esas zonas, en el interior del mapa se encontrarán obstaculos que impiden el movimiento a traves de ellos asi que el jugador y los zombis tendran que evitarlos.

Los zombis corren hacia el jugador y, si se acercan lo suficiente a él, le harán daño hasta el punto de matarlo. El número de zombis y la vida de estos aumentará por cada oleada que pase hasta que los zombis logren matar al jugador.

Producido usando nuestro querido Motor Ola. Para más información consultar su repositorio.

### 1.1.- Versiones del documento
- Versión 0.1 15/02/2022
    Los apartados incluidos en este documento han sido extraídos de las primeras reuniones del equipo, y por lo tanto no ha habido tiempo para especificarlos en mucho detalle, quedando cualquier aspecto sujeto a posibles cambios.
- Versión 0.2 22/02/2022
    Precisión del contenido y arreglos; presentación al profesor.
- Versión 0.3 02/03/2022
    Mejorado el GDD.

## 2.- Menús e interfaz
### 2.1.- Menú de inicio
El menú de inicio del juego consistirá en una pantalla donde se observarán los siguientes botones:

- **Jugar:** empieza una nueva partida.
- **Cargar Partida:** Carga la partida guardada anteriormente por el jugador, si no hay ninguna partida guardada se iniciará una nueva.
- **Créditos:** muestra los créditos del juego.
- **Ajustes:** muestra la pantalla de opciones, que de momento solo permite ajustar el sonido.
- **Salir:** cierra el juego.

![Menu](https://github.com/GDV-Proyectos3/JuegoZombis/blob/main/imagenes/Menu.png)

### 2.2.- Interfaz durante el *gameplay*
El HUD en pantalla estará compuesto por los siguientes elementos:

- **Vida:** muestra la vida restante del jugador. 
- **Puntuación:** indica los puntos obtenidos hasta el momento.
- **Número de oleada:** presenta el número de oleadas superadas hasta el momento.
- **Contador de muertes:** indica el número de enemigos derrotados.

### 2.3.- Menú de pausa
Este menú se podra acceder al pulsar la tecla "Escape" del teclado y tendra los siguientes botones:

- **Continuar:** se sale del menú de pausa y se continua la partida.
- **Guardar Partida:** se guarda la partida y se regresa al menú principal.
- **Ajustes:** se muestra la pantalla de opciones donde se podrá ajustar el sonido del juego.
- **Salir:** se regresa al menú principal sin guardar la partida.

![Pausa](https://github.com/GDV-Proyectos3/JuegoZombis/blob/main/imagenes/MenuPausa.png)

### 2.4.- Fin de la partida
Aqui se mostrará la puntuacion que ha obtenido el jugador en la partida y la puntuacion record del momento. Abajo hay un boton para regresar al menú principal.

![FinPartida](https://github.com/GDV-Proyectos3/JuegoZombis/blob/main/imagenes/FinPartida.png)

### 2.5.- Diagrama de flujo de pantallas

![FlujoMenus](https://github.com/GDV-Proyectos3/JuegoZombis/blob/main/imagenes/FlujoPantallas.png)

## 3.- Jugabilidad
La jugabilidad nos permitirá movernos en las 8 direcciones, disparando mientras tanto a cualquier otra dirección y las balas serán infinitas. Los zombis que matemos tendrán la posiblilidad de dejar caer power-ups que recogeremos al pasar por encima y estos tendrán efectos únicos.

### 3.1.- Mecánicas
- **Click izquierdo:** disparo de un proyectil en la dirección a la que apunte el ratón.
- **WASD:** se utilizará para moverse, podrán combinarse para conseguir las 8 direcciones.
- **Escape:** habilita el menú de pausa.

### 3.2.- Flujo de juego

![FlujoJuego](https://github.com/GDV-Proyectos3/JuegoZombis/blob/main/imagenes/FlujoJuego.png)

### 3.2.- Dinámicas

#### 3.2.1.- Objetivo principal
El objetivo consiste en sobrevivir el mayor número de oleadas posible y obtener la mejor puntuacion para batir el record anterior.

#### 3.2.2. Ganar
El jugador no podrá ganar, ya que todas las partidas acaban con la muerte del jugador.  
Solo es posible superar la puntuación máxima obtenida en partidas anteriores.

## 4.-Contenido
### 4.1.- Enemigos
Los zombis tendran diferentes modelos pero seguirán siendo el mismo tipo de enemigo que perseguira al jugador hasta que logre matarle o que le elimine este, cuando muere cada zombi hay una posibilidad de que suelten un powerUp que tendrá que recoger el jugador para conseguir un efecto especial que le otorgará una ventaja.  
Cuando el jugador elimina a todos los zombis de la oleada actual, este tendrá unos segundos de descanso hasta que empieze la siguiente oleada en la que aparecerán un número mayor de zombis que en la anterior ronda y estos tendrán más vida. 

### 4.2.- Escenarios

El juego posee un único escenario, que consiste en una "habitación" de 4 paredes con un suelo sobre el cual se desarrolla la acción en 2D.  
En este entorno se sitúan un número de obstáculos de forma aleatoria cada vez que se inicia el juego, que son obstáculos físicos para el jugador y sus enemigos.

### 4.3.- Potenciadores

- Potenciador de daño:      aumenta el daño de los proyectiles del jugador
- Potenciador de disparo:   aumenta la cadencia de tiro del jugador, lo cual permitirá que dispare balas mucho más rapido de lo normal
- Potenciador de salud:     permite curar algo de salud al jugador
- Puntos extra:             otorga una considerable cantidad de puntos de bonificación
   
## 5.Referencias
´´´
* Call of Duty Dead Ops Arcade
* Boxhead zombies
´´´
