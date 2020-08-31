#include <stdio.h>
#include <string.h>

#define TODO_OK 0
#define ERROR_ARG 1
#define ERROR_ARCH 2

#define ARG_BIN 1
#define ARG_TXT 2
#define ARG_TIPO_TXT 3

#define TAM_LINEA 501
#define TAM_DESCR 51

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct
{
    int codigo;
    char descripcion[TAM_DESCR];
    int cantidad;
    float precioUnitario;
    Fecha fechaPreUni;
}Producto;

///Clase_2020-05-12_txt_a_bin nombre_bin nombre_txt [f|v]
int main(int argc, char* argv[])
{
    FILE* productosABin = fopen(argv[ARG_BIN],"rb"); //abro archivo bin

    if(!productosABin)
    {
        puts("ERROR ABRIENDO ARCHIVO bin.");
        return ERROR_ARCH;
    }

    FILE* productosATxt = fopen(argv[ARG_TXT],"wb"); //Abro archivo txt

    if(!productosATxt)
    {
        puts("ERROR ABRIENDO ARCHIVO txt.");
        return ERROR_ARCH;
    }

    Producto prod;
    char formato[51];
    char tipoTxt = argv[ARG_TIPO_TXT][0];

    strcpy(formato, tipoTxt == 'v' ? "%d|%s|%d|%.2f|%d/%d/%d\n" : "%03d%50s%03d%08.2f%02d%02d%04d\n");

    fread(&prod, sizeof(Producto), 1, productosABin);
    while(!feof(productosABin))
          {
              fprintf(productosATxt, formato, prod.codigo, prod.descripcion, prod.cantidad, prod.precioUnitario, prod.fechaPreUni.dia, prod.fechaPreUni.mes, prod.fechaPreUni.anio); //En vez de imprimir pantalla, imprime el archivo.
              fread(&prod, sizeof(Producto), 1, productosABin);
          }

    fclose(productosABin);
    fclose(productosATxt);

    puts("Conversion exitosa.");

    return TODO_OK;
}
