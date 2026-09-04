# Lab 3 - Programacion en C

Universidad Galileo - Microprocesadores
Luis Cordova - 23012122

Implementacion de `myGCD` (maximo comun divisor a partir de una cadena) y
`myCombinations` (combinaciones de n elementos de un conjunto de k), para
ARM Cortex-M4 generico (device ARMCM4) con CMSIS-Toolbox y AC6.

## Como compilarlo

1. Abrir la carpeta en VS Code con el Keil Studio Pack (extension CMSIS Solution).
2. Contexto activo: `Lab3_LuisCordova_23012122.Debug+ARMCM4`.
3. Command Palette (`Ctrl+Shift+P`) -> **CMSIS: Build**.
   La primera vez tarda: vcpkg descarga el toolchain y csolution genera la carpeta `RTE/`.
4. Depurar con **F5**, configuracion **mdc** (modelo Arm FVP MPS2_Cortex_M4).
   No se necesita hardware.

## Salida esperada

En el Debug Console:

```
MCD = 12
n=1: {rojo}, {verde}, {azul}
n=2: {rojo, verde}, {rojo, azul}, {verde, azul}
n=3: {rojo, verde, azul}
```

## Si falla el depurador

Error: *"This Arm Debugger version is not supported... (6.9.0 or later)"*

La extension no encuentra el `armdbg` del entorno vcpkg. Se arregla agregando a
`.vscode/settings.json` la ruta al ejecutable, por ejemplo:

```json
"arm-debugger.debuggerPath": "C:\\Users\\<usuario>\\.vcpkg\\artifacts\\<id>\\debuggers.arm.armdbg\\6.10.1\\bin\\armdbg.exe"
```

Ese archivo no se sube al repo porque la ruta cambia en cada maquina.
