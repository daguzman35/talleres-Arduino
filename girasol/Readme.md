# Girasol mecánico

Con Arduino, dos fotoceldas, dos resistencias y un motor de pasos, se crea sistema que gira hacia el lugar más iluminado, como lo haría un girasol mecánico.

Consiste de los siguientes pasos para el sistema de lectura de luz con fotoceldas, en orden:
* lectura_serial_una_fotocelda
* comparador_fotoceldas
* comparador_fotoceldas_con_puerto_serial

Aparte, preparar para mover un motor de pasos:
* stepper_28byj48_oneRevolution

Por último, se unen para hacer:
* girasol_mecanico

Consejo: usar fotoceldas idénticas y resistencias idénticas facilita la calibración del sistema.

Diseñado y probado en julio de 2021. 

David Guzmán. Bogotá, Colombia.

## Videos

Se muestra el funcionamiento por etapas del sistema en los siguientes videos.

- lectura_serial_una_fotocelda: https://youtu.be/u2LACJjgBOI
- comparador_fotoceldas_con_puerto_serial: https://youtu.be/jsJxvF_rZl0
- girasol en protoboard: https://youtu.be/xXiOrHjCTdw
- girasol terminado: https://youtu.be/9cwLkvv2tMU
