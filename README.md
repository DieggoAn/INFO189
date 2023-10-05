# trabajo 1 sistope

## Explicacion de la aplicacion 

Esta es una aplicacion en **c++**, que recibe un nombre y un vector de cualquier largo, tambien se puede crear un archivo de texto y escribir sobre este mismo, para esto debe incluirse al ejecutar el programa el nombre del archivo y el contenido de este. 
Al ejecutarse esta aplicacion, se desplegara en la consola una lista de comandos la cual le permitira al usuario escoger que operacion quiere realizar en el vector que este proporciono, al escribir el numero que representa la operacion que se quiere realizar, se presiona Enter y el programa ejecutara la funcion correspondiente.
Esta aplicacion se desarrollo en un ambiente Linux, y todas las dependencias de este programa se encuentra en la misma carpeta.

## Comando para compilar

Para compilar en Linux, abrir una terminal y ubicarse en la carpeta donde se encuentra el programa, luego en la terminal debe ejecutar los siguientes comandos 

```
make
make -f Makefile_wordCounter

```
 Despues de ejecutar los comandos ***make*** y ***make -f Makefile_wordCounter*** se crearan los ejecutables, ***myprogram*** y ***wordCounter***

## Comando para ejecutar

Para ejecutar el programa primero hay que compilarlo, luego de que se haya compilado este programa se puede ejecutar desde el terminal ubicado en la carpeta que este se encuentra, para ingresar los parametros al programa debe escribir los flags correspondientes :

```
-n <Nombre de usuario en la base de datos>
-v <Vector de numeros enteros>
-f <Nombre del archivo que quiere crear o seleccionar>
-t <Contenido del texto que quiere agregar al archivo seleccionado>
```
Para ingresar un vector este debe esta encerrado en comillas " " y cada numero debe ir separado por un punto y coma ;

```
"<Numero entero>;<Numero Entero>"

"1;2;3;4;5;6;7;8;9;10"
```
Una entrada completa para iniciar el programa se ve de esta forma :

```
./myprogram -n Diego -v "1;2;3;4;5;6" -f Test -f "Hello World"
```

## Explicacion base de datos

La base de datos de usuarios se creo en un archivo ***db.txt***, el formato de esta base de datos es **< Nombre de usuario >** **< Punto separador >** **< Nivel de acceso >** y cada usuario distinto esta separado por una coma **","**, por ejemplo los datos de un usuario se verian asi : 
```
Diego.2
```
 Donde **Diego** es el nombre de usuario y **2** es su nivel de acceso

La base de datos de menu se creo en un archivo ***menu.txt***, el formato de esta base de datos es :
```
< Numero identificador de la funcion> < Nombre de la funcion >
```
y cada funcion esta separada por un "\n", por ejemplo los datos de una funcion se verian asi: 
```
0) Salir 
```
Donde **0** es el Numero identificador de la funcion y **Salir** es el nombre de la funcion.

### Nivel de acceso

El nivel de acceso de un usuario refleja la cantidad de funciones a las cual este usuario tiene permisos para utilizar, en el archivo ***menu.txt*** a la izquierda de cada funcion hay un numero, este numero representa el nivel de acceso minimo que debe tener un usuario para poder usar esta funcion.

Por ejemplo el usuario **Diego** tiene un nivel de acceso **2**, por lo tanto el solo puede acceder a estas funciones :

```
0) Salir 
1) Realizar sumatoria del vector. 
2) Realizar promedio del vector. 
```