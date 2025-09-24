/*
 * lector de carpetas - version simple
 * lee carpeta y muestra contenido en terminal
 * para integrar despues con otros codigos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// estructura para archivos encontrados
typedef struct {
    char nombre[256];
    int es_carpeta;
} elemento_t;

// funcion principal para leer carpeta
void leer_carpeta_actual(void);
void leer_carpeta_especifica(const char* ruta);
void mostrar_elementos(elemento_t elementos[], int total);

int main(int argc, char *argv[]) {
    printf("=== lector de carpetas ===\n\n");
    
    if (argc == 1) {
        // sin argumentos, lee carpeta actual
        printf("leyendo carpeta actual...\n");
        leer_carpeta_actual();
    } else {
        // con argumento, lee carpeta especifica
        printf("leyendo carpeta: %s\n", argv[1]);
        leer_carpeta_especifica(argv[1]);
    }
    
    return 0;
}

void leer_carpeta_actual(void) {
    leer_carpeta_especifica(".");
}

void leer_carpeta_especifica(const char* ruta) {
    DIR *directorio;
    struct dirent *entrada;
    elemento_t elementos[100];
    int total = 0;
    
    directorio = opendir(ruta);
    if (directorio == NULL) {
        printf("error: no se puede abrir la carpeta\n");
        return;
    }
    
    // leer todos los elementos
    while ((entrada = readdir(directorio)) != NULL) {
        // saltar . y ..
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }
        
        strcpy(elementos[total].nombre, entrada->d_name);
        elementos[total].es_carpeta = (entrada->d_type == DT_DIR) ? 1 : 0;
        total++;
        
        if (total >= 100) {
            printf("advertencia: demasiados elementos, mostrando solo 100\n");
            break;
        }
    }
    
    closedir(directorio);
    
    printf("total elementos encontrados: %d\n\n", total);
    mostrar_elementos(elementos, total);
}

void mostrar_elementos(elemento_t elementos[], int total) {
    if (total == 0) {
        printf("carpeta vacia\n");
        return;
    }
    
    printf("contenido:\n");
    printf("----------\n");
    
    // primero mostrar carpetas
    int carpetas = 0;
    for (int i = 0; i < total; i++) {
        if (elementos[i].es_carpeta) {
            printf("[DIR]  %s/\n", elementos[i].nombre);
            carpetas++;
        }
    }
    
    // luego mostrar archivos
    int archivos = 0;
    for (int i = 0; i < total; i++) {
        if (!elementos[i].es_carpeta) {
            printf("[FILE] %s\n", elementos[i].nombre);
            archivos++;
        }
    }
    
    printf("----------\n");
    printf("resumen: %d carpetas, %d archivos\n", carpetas, archivos);
}
