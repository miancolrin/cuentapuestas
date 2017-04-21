/*###################
#   CUENTAPUESTAS   #
#####################
Como corredor de apuestas sé lo importante que es llevar un registro de todos
los movimientos que se hacen: cantidades apostadas, beneficio, bank...
Por eso he creado este pequeño programa, para poder llevar la cuenta sin
ningún problema, ya que nos calcula el beneficio y nos actualiza el bank
automáticamente.
Debemos tener el fichero del registro en el mismo directorio que el fichero
ejecutable de este programa, si no no seremos capaces de abrirlo. El fichero
del registro se puede copiar, mover, compartir...
NO OLVIDAR PONERLE LA EXTENSIÓN .DAT AL FICHERO
También se puede utilizar la extensión .bin, pero la extensión .dat es más óptima.
Manejar este software con responsabilidad.
El juego puede producir ludopatía.
No soy responsable de un mal uso de este software.
Todas las mejoras y sugerencias son bien recibidas.
##############################
#   Creado por @miancolrin   #
##############################
Verisión 0.0.1 22 abril 2017
VERISÓN UNIX compatible con Mac y Linux

NOTA: En algunas ocasiones el registro (fichero .dat) no se guarda en la ruta donde
se encuentra el ejecutable, sino en el directorio $HOME
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

struct datosFecha{
	int dia;
	int mes;
	int anno;
};

struct datosRegistro{
	struct datosFecha fecha;
	float ganado;
	float apostado;
	float beneficio;
	float bank;
};

void nuevoRegistro(char nombreNuevoRegistro[]);
float anteriorBank(char nombreRegistro[]);
void nuevaEntrada(char nombreRegistro[]);
void eliminarEntrada(char nombreRegistro[]);
int cuantasEntradas(char nombreRegistro[]);
void exportarRegistro(char nombreRegistro[]);
void visualizarRegistro(char nombreRegistro[]);

int main(){
	
	//Idioma español
	setlocale(LC_ALL, "Spanish");
	
	int abrirONuevo;
	char nombreRegistro[30];
	char nombreNuevoRegistro[30];
	int registrado = FALSE;
	
	do{
		printf("¿Desea abrir o crear un registro?");
		printf("\n1. Abrir registro");
		printf("\n2. Crear registro");
		printf("\n\nOpción: ");
		fflush(stdin);
		scanf("%d", &abrirONuevo);
	}while(abrirONuevo != 1 && abrirONuevo != 2);
	
	if(abrirONuevo == 1){
		system("clear");
		printf("Introduzca el nombre del registro: "); fflush(stdin);
		scanf("%s", &nombreRegistro);
		
	}
	else if(abrirONuevo == 2){
		system("clear");
		printf("Introduce el nombre del nuevo registro");
		printf("\nNo olvide incluir la extensión .dat al nombre del archivo");
		printf("\n\nNombre: "); fflush(stdin);
		scanf("%s", &nombreNuevoRegistro);
		nuevoRegistro(nombreNuevoRegistro);
		registrado = TRUE;
		system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
	}
	
	if(registrado == TRUE){
		strcpy(nombreRegistro, nombreNuevoRegistro);
	}
	
	char opc;
	
	do{
		
		do{
			system("clear");
			printf("===================MENÚ===================");
			printf("\n1. Ver registro");
			printf("\n2. Añadir entrada al registro");
			printf("\n3. Borrar la última entrada del registro");
			printf("\n4. Exportar registro");
			printf("\n\n0. SALIR");
			printf("\n\nOpción: ");
		
			opc = getchar();
		
		}while(opc != '1' && opc != '2' && opc != '3' && opc != '4' && opc != '0'); //Cierra do-while opc
		
		switch(opc){
			
			case '1':{
				system("clear");
				visualizarRegistro(nombreRegistro);
				system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
				break;
			}
			case '2':{
				system("clear");
				nuevaEntrada(nombreRegistro);
				system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
				break;
			}
			case '3':{
				system("clear");
				eliminarEntrada(nombreRegistro);
				system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
				break;
			}
			case '4':{
				system("clear");
				exportarRegistro(nombreRegistro);
				system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
				break;
			}
			
			
		} //Cierra switch
		
		
	}while(opc != '0'); //Cierra do-while principal
	
	system("clear");
	printf("Muchas gracias por utilizar este software.");
	printf("\n\nRecuerde: las apuestas pueden producir ludopatía");
	printf("\n\n\nCreado por @miancolrin en marzo de 2017");
	
	printf("\n\n\n");
	
	system( "read -n 1 -s -p \"Presione cualquier tecla para cerrar...\"" );
	
}

void visualizarRegistro(char nombreRegistro[]){
	
	struct datosRegistro registro;
	
	FILE *f;
	f = fopen(nombreRegistro, "rb");
	
	fread(&registro, sizeof(registro), 1, f);
	while(!feof(f)){
		printf("Fecha: ");
		printf("%d", registro.fecha.dia); printf("/");
		printf("%d", registro.fecha.mes); printf("/");
		printf("%d", registro.fecha.anno);
		printf("\nGanancias: %f", registro.ganado);
		printf("\nCantidad apostada: %f", registro.apostado);
		printf("\nBeneficio: %f", registro.beneficio);
		printf("\nBank: %f\n\n", registro.bank);
		
		fread(&registro, sizeof(registro), 1, f);
	}	
	
}

void exportarRegistro(char nombreRegistro[]){
	
	struct datosRegistro registro;
	
	FILE *f;
	FILE *exp;
	
	f = fopen(nombreRegistro, "rb");
	exp = fopen("registroExport.txt", "w");
	
	fputs("Exportado de ", exp);
	fputs(nombreRegistro, exp);
	fputs("\n\n", exp);
	
	fread(&registro, sizeof(registro), 1, f);
	while(!feof(f)){
		fputs("Fecha: ", exp);
		fprintf(exp, "%d", registro.fecha.dia); fputs("/", exp);
		fprintf(exp, "%d", registro.fecha.mes); fputs("/", exp);
		fprintf(exp, "%d", registro.fecha.anno);
		
		fputs("\n\n", exp);
		
		fputs("Ganancias: ", exp);
		fprintf(exp, "%f", registro.ganado);
		fputs("\n", exp);
		
		fputs("Cantidad apostada: ", exp);
		fprintf(exp, "%f", registro.apostado);
		fputs("\n", exp);
		
		fputs("Beneficio: ", exp);
		fprintf(exp, "%f", registro.beneficio);
		fputs("\n", exp);
		
		fputs("Bank: ", exp);
		fprintf(exp, "%f", registro.bank);
		fputs("\n", exp);
		
		fputs("\n\n\n", exp);
		
		fread(&registro, sizeof(registro), 1, f);
	}
	
	fclose(exp);
	fclose(f);
	
	system("clear");
	
	printf("Registro exportado con éxito\n\n");
	
}

void eliminarEntrada(char nombreRegistro[]){
	
	struct datosRegistro registro;
	int totalEntradas, entradaFinal;
	int contador = 0;
	
	totalEntradas = cuantasEntradas(nombreRegistro);	
	
	entradaFinal = totalEntradas - 1;
	
	FILE *f;
	FILE *fAUX;
	
	f = fopen(nombreRegistro, "rb");
	fAUX = fopen("auxiliar.dat", "wb");
	
	if(fAUX == NULL){
		printf("Error al intentar borrar");
		fclose(f); fclose(fAUX); return;
	}
	
	fread(&registro, sizeof(registro), 1, f);
	while(!feof(f)){
		if (contador == entradaFinal){
			break;
		}
		fwrite(&registro, sizeof(registro), 1, fAUX);
		fread(&registro, sizeof(registro), 1, f);
		contador ++;
	}
	
	fclose(fAUX);
	fclose(f);
	
	f = fopen(nombreRegistro, "wb");
	fAUX = fopen("auxiliar.dat", "rb");
	
	fread(&registro, sizeof(registro), 1, fAUX);
	while(!feof(fAUX)){
		fwrite(&registro, sizeof(registro), 1, f);
		fread(&registro, sizeof(registro), 1, fAUX);
	}
	
	fclose(f);
	fclose(fAUX);
	
	remove("auxiliar.dat");
	
	printf("Registro eliminado con éxito\n\n");
	
	return;
	
}

int cuantasEntradas(char nombreRegistro[]){
	
	struct datosRegistro registro;
	int contadorOrg = 0;
	
	FILE *f;
	f = fopen(nombreRegistro, "rb");
	
	fread(&registro, sizeof(registro), 1, f);
	while(!feof(f)){
		contadorOrg = contadorOrg + 1;
		fread(&registro, sizeof(registro), 1, f);
	}
	
	fclose(f);
	
	return contadorOrg;
	
}

void nuevaEntrada(char nombreRegistro[]){
	
	struct datosRegistro registro;
	float bankAntiguo;
	
	//La cantidad del Bank anterior
	bankAntiguo = anteriorBank(nombreRegistro);
	
	FILE *f;
	f = fopen(nombreRegistro, "ab");	
	
	if(f == NULL){
		printf("Error al abrir el registro.");
		printf("\n\nPor favor, compruebe el nombre del fichero que ha introducido.");
		printf("\nRecuerde que hay que añadir .dat al final del nombre del registro.");
		printf("\n\nPara que el programa vuelva a funcionar, por favor, reinicie el programa");
		system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
	}
	
	printf("Introduzca día: "); scanf("%d", &registro.fecha.dia);
	printf("\n\nIntroduzca mes: "); scanf("%d", &registro.fecha.mes);
	printf("\n\nIntroduzca año: "); scanf("%d", &registro.fecha.anno);
	
	printf("\n\n\nIntroduzca ganancias: "); scanf("%f", &registro.ganado);
	printf("\n\nIntroduzca cantidad apostada: "); scanf("%f", &registro.apostado);
	
	registro.beneficio = registro.ganado - registro.apostado;
	
	printf("\n\n\nBeneficio: %f", registro.beneficio);
	
	registro.bank = bankAntiguo + registro.beneficio;
	
	printf("\n\n\nBank: %f\n\n", registro.bank);
	
	fwrite(&registro, sizeof(registro), 1, f);
	
	system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
	
	fclose(f);
	
	system("clear");
	
	printf("Registro guardado con éxito\n\n");
	
}

float anteriorBank(char nombreRegistro[]){
	
	FILE *f;
	f = fopen(nombreRegistro, "rb");
	
	struct datosRegistro registro;
	
	float FbankAnterior = 0;
	
	fread(&registro, sizeof(registro), 1, f);
	while(!feof(f)){
		FbankAnterior = registro.bank;
		fread(&registro, sizeof(registro), 1, f);
	}
	
	fclose(f);
	
	return FbankAnterior;
	
}

void nuevoRegistro(char nombreNuevoRegistro[]){
	
	system("clear");
	
	FILE *f;
	f = fopen(nombreNuevoRegistro, "wb");
	
	struct datosRegistro registro;
	
	if(f == NULL){
		printf("Error al crear el registro");
		fclose(f); return;
	}
	
	printf("Introduce día: "); scanf("%d", &registro.fecha.dia);
	printf("\n\nIntroduce mes: "); scanf("%d", &registro.fecha.mes);
	printf("\n\nIntroduce año: "); scanf("%d", &registro.fecha.anno);
	
	printf("\n\n\nIntroduce ganancias: "); scanf("%f", &registro.ganado);
	printf("\n\nIntroduce cantidad jugada: "); scanf("%f", &registro.apostado);
	registro.beneficio = registro.ganado - registro.apostado;
	
	registro.bank = registro.beneficio;
	
	printf("\n\n\nBeneficio: %f\n\n", registro.beneficio);
	
	system( "read -n 1 -s -p \"Presione una tecla para continuar...\"" );
	
	fwrite(&registro, sizeof(registro), 1, f);
	
	fclose(f);
	
	system("clear");
	
	printf("Registro guardado con éxito\n\n");
	
}
