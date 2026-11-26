# Xmake

Las tareas del parcial 3 se compilan con [xmake](https://xmake.io/) debido al deseo de agregar la dependencia [faker-cxx](https://github.com/cieslarmichal/faker-cxx). Todos los demas comandos asumen que esté en la directoria con `xmake.lua`, es decir: `/Parcial3/Practicas` o `/Proyecto/v3`.

## Ejemplo de uso (Windows):

1) Compilar proyecto al menos una vez:
    ```pwsh
    git clone https://github.com/Levmorozenko/fundamentos-de-programacion
    cd .\Practicas\Parcial3
    xmake
    ```

2) Instalar faker-cxx:
    ```pwsh
    xrepo install faker-cxx
    ```
    *Se me olvido cual comando era.*
  
3) Correr practicas a traves de:
    - **Recomendado:** `xmake run x`, lea `xmake.lua` para mas informacion sobre cada proyecto. 
    - En caso de desear utilizar archivos compilados directamente, se pueden encontrar en la carpeta `build` generada por xmake. Ejemplo: 
    ```pwsh 
    cd .\build\windows\x64\release
    .\x.exe
    ```

## Clang compatibility
Por determinado, clang no detecta las bibliotecas que pertenecen a xmake. Para arreglar eso se debe crear `compile_commands.json` a traves de:
```xmake project -k compile_commands```

Ademas, para activar compilacion con clang, use `xmake f --toolchain=clang -c`
