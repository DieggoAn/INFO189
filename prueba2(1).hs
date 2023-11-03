{-# LANGUAGE NoImplicitPrelude #-}
module Prueba2 where
-- PRUEBA 2 INFO188
-- 24 de Octubre 2023
-- Tiempo: 90mins
-- Entrega: Subir archivo <nombre-apellido>.hs a la tarea 'prueba 2' de SiveducMD
--
-- ***************************************************************************************
-- INSTRUCCIONES:
--      - Toda funcion debe ir con contrato y una explicacion breve y clara de lo que hace.
--      - Puede escribir funciones auxiliares para ayudar a organizar su codigo
-- ***************************************************************************************
--
import Prelude hiding ((<*>),pure) 
-- 1) Grafo
--   Se tiene el siguiente tipo de dato 'Grafo' que vamos a usar.
data Grafo a = G [(a,[a])] deriving (Show, Eq)
--   donde cada elemento (tupla) de la lista es un nodo con su identificador (a) y su lista de nodos adyacentes ([a]).
--   ejemplo: miGrafo = G [(1,[2,3]),(2,[1]),(3,[1,2,4])]
--
--   a) (1.5 pts) Instancie Grafo a Functor y use esa nueva funcionalidad para hacer la 
--                funcion 'shiftUp' que recibe un Grafo y convierte cada identificador a su sucesor.
--

instance Functor Grafo where
fmap f (G grafo) = G [(f x, map f xs) | (x, xs) <- grafo]

shiftUp :: Grafo Integer -> Grafo Integer
shiftUp = Prelude.fmap (+1)




--   b) (1.5 pts) Instancie Grafo a Aplicativo, y use esa nueva funcionalidad para hacer 
--                la funcion 'superConexion' donde se aplica un grafo de funciones a un grafo 
--                de datos, resultando en muchas mas conexiones por nodo. 
--
--instance Applicative Grafo where
--    pure x = Vec (x,x)
--    Vec (f,g) <*> Vec (x,y) = Vec (f x, g y)
    

    

--   c) (1.5 pts) Instancie Grafo a Monada, proponga un diseno que le haga sentido 
--                y que permita hacer 'modificaciones' a un grafo al hacer "Grafo >>= f". 
--                Trate de elaborar algo interesante.
--

--
-- 2) (1.5 pts) En Python, implemente el operador aplicativo para listas con el mismo 
--              comportamiento que tiene en Haskell. El aplicativo puede ser una funcion 
--              como "aplicativo(lista_funcs, lista_datos)". La respuesta debe estar 
--              en un archivo python aparte con un codigo "main" ejemplicifando su uso.
    