# trabajo 1 sistope

## Explicacion de la aplicacion 

Esta es una aplicacion en **c++**, que recibe un nombre y un vector de cualquier largo, tambien se puede crear un archivo de texto y escribir sobre este mismo, para esto debe incluirse al ejecutar el programa el nombre del archivo y el contenido de este. 
Al ejecutarse esta aplicacion, se desplegara en la consola una lista de comandos la cual le permitira al usuario escoger que operacion quiere realizar en el vector que este proporciono, al escribir el numero que representa la operacion que se quiere realizar, se presiona Enter y el programa ejecutara la funcion correspondiente.
Esta aplicacion se desarrollo en un ambiente Linux, y todas las dependencias de este programa se encuentra en la misma carpeta.

## Comando para compilar

Para compilar en linux, abrir una terminal y ubicarse en la carpeta donde se encuentran los archivos makeAll.sh y cleanAll.sh, luego en la terminal ejecutar los siguientes comandos

```
chmod +x makeAll.sh
chmod +x cleanAll.sh

```
Para compilar el programa, debe ejecutar el programa ***makeAll.sh***. Para borrar los ejecutables creados, ejecutar el programa ***cleanAll.sh***.

## Comando para ejecutar

Para ejecutar el programa primero hay que compilarlo, luego de que se haya compilado este programa se puede ejecutar desde el terminal ubicado en la carpeta que este se encuentra, para ingresar los parametros al programa debe escribir los flags correspondientes :

```
-n <Nombre de usuario en la base de datos>
-v <Vector de numeros enteros>
-f <Nombre del archivo que quiere crear o seleccionar>
-t <Contenido del texto que quiere agregar al archivo seleccionado>
-i <Direccion del libro al cual le quiere contar las palabras>
-o <Direccion donde se quiere guardar el conteo de palabras>
```
Para ingresar un vector este debe esta encerrado en comillas " " y cada numero debe ir separado por un punto y coma ;

```
"<Numero entero>;<Numero Entero>"

"1;2;3;4;5;6;7;8;9;10"
```
Una entrada completa para iniciar el programa se ve de esta forma :

```
./myprogram -n Diego -v "1;2;3;4;5;6" -f Test -f "Hello World" -i Dependencias/lotr.txt -o Dependencias/conteo.txt
```

## Explicacion base de datos

La base de datos de usuarios se creo en un archivo ***db.txt***, el formato de esta base de datos es **< Nombre de usuario >** **< Punto separador >** **< Nivel de acceso >** y cada usuario distinto esta separado por una coma **","**, por ejemplo los datos de un usuario se verian asi : 
```
Diego.admin
```
 Donde **Diego** es el nombre de usuario y **admin** es su nivel de acceso

La base de datos de menu se creo en un archivo ***menu.txt***, el formato de esta base de datos es :
```
< Numero identificador de la funcion> < Nombre de la funcion > <Tipo de usuario que puede usar la funcion>
```
y cada funcion esta separada por un "\n", por ejemplo los datos de una funcion se verian asi: 
```
0) Salir <admin,userGeneral,userRookie>
```
Donde **0** es el Numero identificador de la funcion, **Salir** es el nombre de la funcion y los usuarios que pueden usar esta funcion son **admin,userGeneral,userRookie**

## Nivel de acceso

El nivel de acceso de un usuario refleja la cantidad de funciones a las cual este usuario tiene permisos para utilizar, en el archivo ***menu.txt*** a la derecha de cada funcion estan nombrados los tipos de usuario con acceso a la funcion. Estos son los permisos que tiene cada nivel de usuario:

### userGeneral
```
0) Salir. 
1) Realizar sumatoria del vector. 
2) Realizar promedio del vector. 
3) Realizar moda del vector. 
4) Contar elementos del vector. 
```

### userRookie
```
0) Salir. 
1) Realizar sumatoria del vector. 
4) Contar elementos del vector. 
```