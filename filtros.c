#include "filtros.h"
#include <stdio.h>
#include <stdlib.h>

// intel simd
#if defined(__SSE2__)
#include <emmintrin.h>
#endif

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

FILTRO SEPIA = { 
	.393, .760, .189,
	.349, .686, .168,
	.272, .534, .131
};
extern unsigned char multiplyBlend(unsigned char valorColor1,unsigned char valorColor2);
extern void xmmBlend(char * datos1, char * datos2, int cantPixels);
/******************************************************************************/

void filtro (BMPDATA *bmpData, FILTRO filtro) {

	for (int i=0; i<cantPixels(bmpData); i++) {

		unsigned char r = bmpData->red[i];
		unsigned char g = bmpData->green[i];
		unsigned char b = bmpData->blue[i];
		bmpData->red[i]   = min (r * filtro.RR + g * filtro.RG + b * filtro.RB, 255);
		bmpData->green[i] = min (r * filtro.GR + g * filtro.GG + b * filtro.GB, 255);
		bmpData->blue[i]  = min (r * filtro.BR + g * filtro.BG + b * filtro.BB, 255);
	}
}

/******************************************************************************/

void blancoYNegro (BMPDATA *bmpData) {
	
	for (int i=0; i<cantPixels(bmpData); i++) {
	
		unsigned char y = bmpData->red[i] * 0.11448f + bmpData->green[i] * 0.58661f + bmpData->blue[i] * 0.29891f;
		bmpData->red[i]   = y;
		bmpData->green[i] = y;
		bmpData->blue[i]  = y;
	}	
}

/*******************************************************************************/
void medianFilter(BMPDATA *bmpData){
	//param nDeNxN
	int N= bmpData->infoHeader.biWidth;
	int M= bmpData->infoHeader.biHeight;
		
	//int sizeWindow= nDeNxN*nDeNxN;
	int sizeWindow=9;
	int mitadWindow= (int)(sizeWindow/2);

	//Movemos a traves de la imagen	
	for(int m=1; m< M-1;m++){
		for(int n=1;n<N-1;n++){
			//Elegimos elementos de las ventanas
			int k=0;
			unsigned char RWindow[sizeWindow];
			unsigned char GWindow[sizeWindow];
			unsigned char BWindow[sizeWindow];
			
			for(int j=m-1; j< m+2; j++){
				for(int i=n-1; i< n+2; i++){
					RWindow[k]=bmpData->red[(j*N)+i];
					GWindow[k]=bmpData->green[(j*N)+i];
					BWindow[k]=bmpData->blue[(j*N)+i];
					k++;
				}
			}
			//ORDENO Y REEMPLAZO LOS ROJOS
			for(int j=0;j < sizeWindow;j++){
				//Encontrar posicion del minimo elemento
				int min= j;
				for(int l=j+1; l<sizeWindow;l++){
					if(RWindow[l]<RWindow[min]){
						min=l;	
					}
				}
				//SWAP ROJO
				const unsigned char Rtemp= RWindow[j];
				RWindow[j]=RWindow[min];
				RWindow[min]=Rtemp;
			}
			bmpData->red[(m-1)*N+(n-1)]= RWindow[4];

			//ORDENO LOS VERDES
			for(int j=0;j < mitadWindow+1;j++){
				//Encontrar posicion del minimo elemento
				int min=j;
				for(int l=j+1; l<sizeWindow;l++){
					if(GWindow[l]<GWindow[min]){
						min=l;
					}
				}
				//SWAP VERDE
				const unsigned char Gtemp=GWindow[j];
				GWindow[j]=GWindow[min];
				GWindow[min]=Gtemp;
			}
			bmpData->green[(m-1)*N+(n-1)]= GWindow[4];

			//ORDENO LOS AZULES
			for(int j=0;j < mitadWindow+1;j++){
				//Encontrar posicion del minimo elemento
				int min=j;
				for(int l=j+1; l<sizeWindow;l++){
					if(BWindow[l]<BWindow[min]){
						min=l;
					}
				}
				//SAWP AZUL
				const unsigned char Btemp=BWindow[j];
				BWindow[j]=BWindow[min];
				BWindow[min]=Btemp;

			}
			bmpData->blue[(m-1)*N+(n-1)]=BWindow[4];
			}
			
		}
	
	
}

/*******************************************************************************/
void aclarar(BMPDATA *bmpData, long brillo){
	//Para que se respete el rango -255 a 255
	//Si el valor es menor a 0 se oscurece la imagen, caso contrario, se aclara
	brillo= max(0,min(255,brillo));

	
	for (int i=0; i<cantPixels(bmpData);i++){
		unsigned char r= bmpData->red[i];
		unsigned char g = bmpData->green[i];
		unsigned char b = bmpData->blue[i];
		bmpData->red[i]   = max(0,min(r+brillo,255));  //max y min para ir verificando los rangos
		bmpData->green[i] = max(0,min(g+brillo,255));
		bmpData->blue[i]  = max(0,min(b+brillo,255));
	}
}
/*******************************************************************************/
void negativo(BMPDATA *bmpData){
	//Consta en invertir los colores
	for(int i=0;i<cantPixels(bmpData);i++){
		bmpData->red[i]=min(bmpData->red[i]*(-1),255); //Para mantener rango de valores
		bmpData->green[i]=min(bmpData->green[i]*(-1),255);
		bmpData->blue[i]=min(bmpData->blue[i]*(-1),255);
	}
}

/************************************************************************************************/
void blend(BMPDATA *bmpData, BMPDATA *bmpData2) {
	//Se presupone que ambas imagenes son del mismo tamaño
	int numeroPixeles1=cantPixels(bmpData);
	int numeroPixeles2=cantPixels(bmpData2);
	if(numeroPixeles1!=numeroPixeles2){
		printf("Las imagenes son de distinto tamaño!\n");
	}
	else{
		for (int i=0; i<cantPixels(bmpData); i++) { //Blending images

			bmpData->red[i]=multiplyBlend(bmpData->red[i],bmpData2->red[i]);
			bmpData->green[i]=multiplyBlend(bmpData->green[i],bmpData2->green[i]);
			bmpData->blue[i]=multiplyBlend(bmpData->blue[i],bmpData2->blue[i]);
		}
	}
}
/******************************************************************************/
/******************************************************************************/
void blendASM(BMPDATA *bmpData, BMPDATA *bmpData2) {
	//Se presupone que ambas imagenes son del mismo tamaño
	int numeroPixeles1=cantPixels(bmpData);
	int numeroPixeles2=cantPixels(bmpData2);
	if(numeroPixeles1!=numeroPixeles2){
		printf("Las imagenes son de distinto tamaño!\n");
	}
	else{
		
		unsigned char * RWindowImagen1= malloc(numeroPixeles1 * sizeof(int)); //asigna determinados bytes de tamaño de almacenamiento no inicializado.
		unsigned char * GWindowImagen1= malloc(numeroPixeles1 * sizeof(int));
		unsigned char * BWindowImagen1= malloc(numeroPixeles1 * sizeof(int));

		unsigned char * RWindowImagen2= malloc(numeroPixeles1 * sizeof(int));
		unsigned char * GWindowImagen2= malloc(numeroPixeles1 * sizeof(int));
		unsigned char * BWindowImagen2= malloc(numeroPixeles1 * sizeof(int));

		//unsigned char * Divisor = malloc(numeroPixeles1);

		for(int i=0; i<numeroPixeles1;i++){ //Filling up each color windows
			RWindowImagen1[i]=bmpData->red[i];
			GWindowImagen1[i]=bmpData->green[i];
			BWindowImagen1[i]=bmpData->blue[i];

			RWindowImagen2[i]=bmpData2->red[i];
			GWindowImagen2[i]=bmpData2->green[i];
			BWindowImagen2[i]=bmpData2->blue[i];

			
		}
		xmmBlend(RWindowImagen1,RWindowImagen2,numeroPixeles1);
		bmpData2->red=RWindowImagen1;

		xmmBlend(GWindowImagen1,GWindowImagen2,numeroPixeles1);
		bmpData2->green=GWindowImagen1;
		
		xmmBlend(BWindowImagen1,BWindowImagen2,numeroPixeles1);
		bmpData2->blue=BWindowImagen1;
	}
}
/******************************************************************************/

unsigned char mediana (unsigned char *histo, int imediana) {

	int k, aux=0;
	for (k=0; k<255 && aux<=imediana; k++)
		aux += histo[k];

	return k;
}

/******************************************************************************/

int cantPixels(BMPDATA *bmpData) {

	return bmpData->infoHeader.biWidth * bmpData->infoHeader.biHeight;
}

/******************************************************************************/



















