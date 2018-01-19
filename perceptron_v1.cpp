#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef WINDOWS
	#define limpia_pantalla system("cls");
#else
	#define limpia_pantalla system("clear");
#endif

static float umbral = 0.3;
static float tasaAprendizaje = 0.1;
int training[4][4] = {{1, 0, 0, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
float pesos[3] = {0, 0, 0};
bool done = false;

bool entrenar(){
	float suma, correccion, z[3];
	int resultado, qDef;
	int error = 0;
	bool success = false;
	
	limpia_pantalla
	while(true){
		printf("1.Por defecto\n2.Tus resultados\nAND por defecto!\n");
		scanf("%d", &qDef);
		if(qDef == 2){
			limpia_pantalla
			printf("AND por defecto!\nResultado para 0 y 0:");
			scanf("%d", &training[0][3]);
			printf("Resultado para 0 y 1:");
			scanf("%d", &training[1][3]);
			printf("Resultado para 1 y 0:");
			scanf("%d", &training[2][3]);
			printf("Resultado para 1 y 1:");
			scanf("%d", &training[3][3]);
			break;
		}else if(qDef != 1){
			limpia_pantalla
			printf("Opción no valida!\n");
		}
	}
	
	while(!success){
		int errorCont = 0;
		
		printf("----\n");
		for(int indice1 = 0; indice1 <= 3; indice1++){
			for(int indice2 = 0; indice2 <= 2; indice2++){
				z[indice2] = training[indice1][indice2] * pesos[indice2];
			}
			suma = z[0] + z[1] + z[2];
			if(suma < umbral){
				resultado = 0;
			}else {
				resultado = 1;
			}
			error = training[indice1][3] - resultado;
			if(error != 0) errorCont++;
			correccion = tasaAprendizaje * error;
			pesos[0] += training[indice1][0] * correccion;
			pesos[1] += training[indice1][1] * correccion;
			pesos[2] += training[indice1][2] * correccion;
			printf("Pesos: i0 - %f i1 - %f i2 - %f\n", pesos[0], pesos[1], pesos[2]);
		}
		
		if(errorCont == 0) success = true;
	}
	getc(stdin);getc(stdin);
	return success;
}

bool pregunta(){
	int v1 = 0; 
	int v2 = 0;
	int resultado;
	float preResultado, x0, x1, x2;

	limpia_pantalla
	printf ("Primer valor: ");
	scanf("%d", &v1);
	printf ("Segundo valor: ");
	scanf("%d", &v2);
	
	x0 = 1 * pesos[0];
	x1 = v1 * pesos[1];
	x2 = v2 * pesos[2];
	
	preResultado = x0 + x1 + x2;
	
	if(preResultado < umbral){
		resultado = 0;
	}else {
		resultado = 1;
	}
	
	printf("---------\nEl resultado es: %u\n", resultado);
	getc(stdin);getc(stdin);
}

int main(){
	int opMenu;
	while(!done){
		limpia_pantalla
		printf("Menu:\n1.Entrenar\n2.Preguntar\n3.Salir\n");
		scanf("%d", &opMenu);
		
		switch(opMenu){
			case 1: entrenar();
			break;
			case 2: pregunta();
			break;
			case 3: done = true;
			break;
			default: printf("Opción no valida!\n");
		}
	}
	return 0;
}
