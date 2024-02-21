# Trabajo practico 2: “SIMD”

## Introducción
La idea del trabajo es probar imágenes a distintos tamaños, para los dos algoritmos de Blend así se puede observar la diferencia en velocidad de usar SIMD vs no usarlo a distintas resoluciones.
Las pruebas deben ser guardadas en el csv para graficarlos.

Acá se agrega el [link](https://drive.google.com/file/d/1XnVqyaPgg4OyjGkm5yfF598EKcJjGvqi/view?usp=sharing) a la consigna del trabajo.

## Resumen
Se implementarón 4 métodos para el tratamiento de imágenes en formato _".bmp"_, los cuales son:
1. **Aclarar:** recibe una imagen y aclara su tonaldiad en base a un parámetros numérico.
2. **Median filter:** una función que permite eliminar el "ruido/distorsión" de una imagen. El método recibe la imagen con interferencia, la recoge y corrige la distorsión original.
3. **Blend (sin operaciones multimedia):** recibe dos imágenes de igual tamaño y mediante el uso de código Assembler sin utilizar operaciones multimedia, da como resultado la combinación de ambas imágenes.
4. **Blend (utlizando operaciones multimedia):** recibe dos imágenes de igual tamaño y mediante el uso de código Assembler utilizando las operaciones multimedia correspondientes, da como resultado la combinación de ambas imagenes.

Adicionalmente, se incluyó un método adicional: Filtro negativo.

Finalmente, se mostrará en el [informe](https://drive.google.com/file/d/1SZGa9NghD9NF18Syh--4vRb1qNTIMFph/view?usp=sharing) una comparación entre los tiempos de ejecución del método "blend" para combinar las imágenes
utilizando operaciones multimedia y sin utilizar operaciones multimedia, mediante el uso del lenguaje Assmebler.

_Cabe aclarar que se eliminó de este repositorio las imagenes de resoluciones 6000x6309_. 
Acá se agrega el [repositorio](https://gitlab.com/NahuelSauma/orgaii-tp2-grupo-3) original en el cual se trabajó durante el periodo de desarrollo.
