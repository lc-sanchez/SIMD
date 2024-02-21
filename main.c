#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "lectorBmp.h"
#include "filtros.h"



extern int asmPrint
(char * msg, int lenght);

int asm_Print(char * msg){
  return asmPrint(msg,strlen(msg));
}
/******************************************************************************/


int main (int argc, char* argv[]) {
	asm_Print("Organización del Computador 2.\nTrabajo Práctico Nro. 2\nPrograma para procesamiento de imágenes BMP.\n");
	int resolucion = 1080;
	BMPDATA bmpData;
	BMPDATA bmpData2;
	BMPDATA bmpData3;
	BMPDATA bmpData4;
	int i;

	/*printf("Ejecutando con parametros: ");
	for (i=1 ; i<argc; i++){
		printf("%s ", argv[i]);
	}*/


	clock_t start, end;
	// comienza a medir el tiempo
	start = clock();

	//Funcion blanco y negro---------------------------------------------------------------------	
	if (loadBmpFile ("lena.bmp", &bmpData) != 0) {

		printf ("Error al leer el archivo %s\n\n", "lena.bmp");
		return 1;
	}

	blancoYNegro (&bmpData);
	
	if (saveBmpFile ("lenaEnGrises.bmp", &bmpData) != 0)
		asm_Print("Error al grabar el archivo!");
	
 
	//Funcion aclarar---------------------------------------------------------------------
	if (loadBmpFile ("lena.bmp", &bmpData) != 0) {

		printf ("Error al leer el archivo %s\n\n", "lena.bmp");
		return 1;
	}
	
	aclarar(&bmpData,50);

	if (saveBmpFile ("lenaAclarada.bmp", &bmpData) != 0)
		asm_Print("Error al grabar el archivo!");
	

	//Negativo---------------------------------------------------------------------
	if(loadBmpFile("lena.bmp",&bmpData)!= 0){
		printf ("Error al leer el archivo %s\n\n", "lena.bmp");
		return 1;
	}

	negativo(&bmpData);

	if (saveBmpFile ("lenaNegativo.bmp", &bmpData) != 0)
		asm_Print("Error al grabar el archivo!");

	//Median Filter------------------------------------------------------------------
	if (loadBmpFile ("lena_corrupted.bmp", &bmpData) != 0) {

		printf ("Error al leer el archivo %s\n\n", "lena_corrupted.bmp");
		return 1;
	}
	

	medianFilter(&bmpData);


	if (saveBmpFile ("lenaMedianFilter.bmp", &bmpData) != 0)
		asm_Print("Error al grabar el archivo!");

	//Blend------------------------------------------------------------------------------------
	if (loadBmpFile("imagen_1.bmp",&bmpData2)!=0)
		printf("Error al leer el archivo %s\n\n","imagen_1.bmp");

	if (loadBmpFile("imagen_2.bmp",&bmpData3)!=0)
		printf("Error al leer el archivo %s\n\n","imagen_2.bmp");



	blend(&bmpData2,&bmpData3);

	if (saveBmpFile ("Imagen1_2Blended.bmp", &bmpData2) != 0)
		asm_Print("Error al grabar el archivo!");


	//Blend_asm------------------------------------------------------------------------------------
	if (loadBmpFile("imagen_1.bmp",&bmpData2)!=0)
		printf("Error al leer el archivo %s\n\n","imagen_1.bmp");

	if (loadBmpFile("imagen_2.bmp",&bmpData3)!=0)
		printf("Error al leer el archivo %s\n\n","imagen_2.bmp");


	blendASM(&bmpData2,&bmpData3);


	if (saveBmpFile ("Imagen1_2BlendedASM.bmp", &bmpData3) != 0)
		asm_Print("Error al grabar el archivo!");	

	







	end = clock();
	FILE *out = fopen("results.csv", "a");  
	int tiempo = end-start;
	fprintf(out, "%d %s %d", resolucion, " tiempo: ", tiempo );
  	fclose(out); 


	// imprime tiempo
	
	printf("\nTiempo de proceso: %ld ticks.\n\n", end-start);



	// libera memoria
	limpiarBmpData(&bmpData);
	return 0;
}
