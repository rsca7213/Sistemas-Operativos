# Proyecto de Sistemas Operativos

* **Makefile:** Escribir un makefile (Linux) el cual construya todos los programas necesarios para resolver
los problemas que se exponen a continuación.
* **UCP:** Escribir una versión propia del programa para copiar archivos de Unix, cp.
Denominar esta nueva versión ucp. La sintaxis para ucp es la siguiente:
**ucp bufsize file1 file2**
En donde bufsize es un entero que determina el tamaño del buffer para la lectura de la data
desde file1 y la escritura de la data en file2. El programa deberá aceptar valores para bufsize
dentro del rango 1 a 16384. Utilizar timeprog de la pregunta anterior para probar ucp
copiando un archivo grande (640K o mayor). Los valores de prueba para bufsize deberán ser: 1,
32, 8192 y 16384. ¿Cuáles son los resultados? 
* **Timeprog:** Escribir un programa denominado timeprog. Este programa recibirá como parámetros un
programa (prog) y sus argumentos, para determinar cuánto tiempo demora la ejecución de
dicho programa (prog). La sintaxis para timeprog es la siguiente:
**timeprog <prog><[arg1, arg2, ..., arg9]>**
Los parámetros son opcionales y dependerán del programa prog a ser ejecutado por timeprog.
La salida de timeprog deberá ser el número de segundos requeridos durante la ejecución de
prog. 
* **Messenger:** Escribir un programa en donde un padre crea dos procesos hijos, C1 y C2 y crea un pipe para
que C1 se comunique con C2. Programar C1 para que reciba una señal SIGALRM cada 2
segundos. Cada vez que C1 reciba una señal SIGALRM envía el mensaje recibido a C2, el cual lo
imprime por pantalla al recibirlo. C1 deberá terminar una vez que haya recibido 10 señales
SIGALRM y enviado 10 mensajes a C2. El proceso C2 deberá terminar una vez que haya
recibido todos los mensajes y los haya impreso por pantalla. Terminar el proceso padre una
vez que ambos hijos hayan terminado. 
* **Fib. Secuencial:** Realizar dos (2) versiones para el cálculo de “Sucesión de Fibonacci”. La primera versión es
secuencial la cuál deberá sumar un millón de números de FIBONACCI y generar de forma
aleatoria entre 0 y 19 y a ese número le calculamos su FIBONACCI, generar ese millón de
números hacer la suma e imprimirlo por pantalla (usar las siguientes librerías: stdio.h, math.h,
stdlib.h y time.h).
* **Fib. Multi:**  La segunda versión deberá ser en paralelo utilizando “HILOS” e imprimirlo
por pantalla, el objetivo de este ejercicio es observar cual versión correr más rápido (usar
función “pthread”). 