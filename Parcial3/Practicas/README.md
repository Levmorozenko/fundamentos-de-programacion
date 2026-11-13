# Xmake

Las practicas del parcial 3 `./Parcial3/Practicas` se compilan con [xmake](https://xmake.io/) debido al deseo de agregar la dependencia [faker-cxx](https://github.com/cieslarmichal/faker-cxx). Todos los demas comandos asumen que esté en esta directoria, es decir, `/Parcial3/Practicas`.

## Quick-start

### Windows

1) Compilar proyecto al menos una vez:
  ```pwsh
  git clone https://github.com/Levmorozenko/fundamentos-de-programacion
  cd .\Practicas\Parcial3
  xmake
  ```

2) Correr practicas a traves de:
  - Donde x es el numero de la practica:
  - Archivos compilados: 
    ```pwsh 
    cd .\build\windows\x64\release
    .\x.cpp
    ```
  - `xmake run`: 
    ```pwsh 
    xmake run x
    ```
  *Nota: algunas practicas dependen de archivos generados por otros.*


## Clang compatibility
Por determinado, clang no detecta las bibliotecas que pertenecen a xmake. Para arreglar eso se debe crear `compile_commands.json` a traves de:
```xmake project -k compile_commands```
