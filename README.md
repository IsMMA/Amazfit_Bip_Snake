# Amazfit_Bip_Snake
 Juego del Snake para el reloj Amazfit Bip en el firmware Amazfit OS. Escrito en C.
 
 Atención utiliza este tutorial para editar el programa.
 
1. Instalar SDK de ARM: gcc-arm-none-eabi-8-2019-q3-update-win32-sha2.exe
2. Descomprimir todas las carpetas en la misma raíz (libbip.zip, ResPack.zip, template_app_en.zip <-- Esta añadirla a una carpeta que se llame igual osea template)
3. Quedarán entonces libbip, ResPack y template.
4. Ir a Template y editar el Bat con notepad ++ o cualquier editor de texto.
5. Buscar la ruta  @SET BASE_PATH=d:\Dev\AmazfitBip_FW\soft\Patch\GNUArmEmbeddedGCC
y editarla por la que corresponde. (es la ruta donde se ejecuta el compilador instalado de ARM embedded)
En mi caso es:
C:\Program Files (x86)\GNU Tools ARM Embedded\8 2019-q3-update

Y Se queda asi: 

@SET BASE_PATH=C:\Program Files (x86)\GNU Tools ARM Embedded\8 2019-q3-update

6. Ahora ya se puede editar el fichero .c y .h 
7. Para compilar el código solo hay que pulsar en build.bat.
8. Si todo va bien se generaran muchos achivos, el ejecutable importante para el reloj es .elf

9. Llevamos el .elf a la carpeta ResPack
10. Dentro de la carpeta ResPack añadimos un RES original (de los que se flashean al actualizar el reloj) este 
RES nos sirve de base para añadir el elf generado (no se el máximo de memoria que se puede utilizar por eso cuidado)

11. Abrir cmd ir a la carpeta de ResPack y ejecutar de esta forma:
ResPack -a <nombre_RES_que_se_genera> <nombre_RES_original> <archivos_que_se_añaden>

En mi caso es: 

ResPack -a Res_Move.res Res_Original.res HelloWorld.elf 

*SOLO AÑADIR EL ELF, desconozco si se pueden añadir imágenes.

*ATENCIÓN PONER LA LIBRERIA EN LA MISMA CARPETA DONDE ESTAN LAS DEMAS CARPETAS DE LAS APPS

******************************************************************************

Por falta de tiempo no puedo continuar con el desarrollo en unos días. 

Problemas detectados:

	- Hay lagg al cambiar de posición la serpiete.
	- La serpiente no gira correctamente.
	- No funciona la función aleatorio de C en el compilador.
	- Los recursos que utiliza la serpiente (el .) ocupa demasiados pixeles y se tapa al subir o bajar por la pantalla, desconozco si se puede añadir otro recurso (otro .png) con un punto que realmente ocupe un solo pixel.
	- La serpiente no come ni crece aún.
	- La serpiente no muere con las paredes ni al chocarse con su propio cuerpo.
	- Adjunto el RES para probar el funcionamiento.
 
