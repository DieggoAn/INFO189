# trabajo 1 sistope

## Explicacion de la aplicacion 

Esta es una aplicacion en **c++**, que recibe un nombre y un vector de cualquier largo, tambien se puede crear un archivo de texto, escribir sobre este mismo y subir un documento en formato .txt y contar cuantas veces se repite una palabra, para esto debe incluirse al ejecutar el programa el nombre del archivo, el contenido de este, la ruta del archivo de texto y el nombre del nuevo archivo que va a contener el conteo de palabras.
Al ejecutarse esta aplicacion, se desplegara en la consola una lista de comandos la cual le permitira al usuario escoger que operacion quiere realizar en el vector que este proporciono, al escribir el numero que representa la operacion que se quiere realizar, se presiona Enter y el programa ejecutara la funcion correspondiente.
Esta aplicacion se desarrollo en un ambiente Linux, y todas las dependencias de este programa se encuentra en la misma carpeta.

## Comando para compilar

Para compilar en Linux, solo debe abrir una terminal y ubicarse en la carpeta donde se encuentra el programa, luego en la terminal debe escribir ***make*** para compilar, si se quiere modificar el codigo, debe hacer ***make clean*** para eliminar el programa actual, luego hacer ***make*** para crearlo con los nuevos cambios.
Al compilarlo con ***make*** se crea un ejecutable llamado ***myprogram***

## Comando para ejecutar

Para ejecutar el programa primero hay que compilarlo, luego de que se haya compilado este programa se puede ejecutar desde el terminal ubicado en la carpeta que este se encuentra, para ingresar los parametros al programa debe escribir los flags correspondientes :

```
-n <Nombre de usuario en la base de datos>
-v <Vector de numeros enteros>
-f <Nombre del archivo que quiere crear o seleccionar>
-t <Contenido del texto que quiere agregar al archivo seleccionado>
-i <Direccion donde se encuentra el archivo de texto>
-o <Direccion donde se quiere crear el archivo de conteo de palabras y el nombre de este archivo>
```
Para ingresar un vector este debe esta encerrado en comillas " " y cada numero debe ir separado por un punto y coma ;

```
"<Numero entero>;<Numero Entero>"

"1;2;3;4;5;6;7;8;9;10"
```
Una entrada completa para iniciar el programa se ve de esta forma :

```
./myprogram -n Diego -v "1;2;3;4;5;6" -f Test -f "Hello World" -i "Dependencias/lotr.txt" -o "Dependencias/conteo"
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

El nivel de acceso de un usuario refleja la cantidad de funciones a las cual este usuario tiene permisos para utilizar, en el archivo ***menu.txt*** a la derecha de cada funcion estan nombrados los tipos de usuario con acceso a la funcion. Estos son los permisos que tiene cada nivel de usuario.

### Admin
```
0) Salir. 
1) Realizar sumatoria del vector. 
2) Realizar promedio del vector. 
3) Realizar moda del vector. 
4) Contar elementos del vector. 
5) Crear Archivo. 
6) Agregar texto a archivo. 
7) Contar palabras. 
```
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
