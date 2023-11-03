#!/bin/bash

# cambiar a la carpeta donde se ubican los makefiles
cd makefiles/

# Build the first program in the background
make -f Makefile_prog

# Build the second program in the background
make -f Makefile_invertedIndex

# Build the third program in the background
make -f Makefile_wordCounter

# Build the forth program in the background
make -f Makefile_llamarBuscador

# Wait for all background jobs to finish
wait

# You can add more makefile commands as needed
