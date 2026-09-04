#include "RTE_Components.h"
#include CMSIS_device_header      

#include <stdio.h>

// Operaciones 
int  myGCD(const char *set);
void myCombinations(int n, const char *set, char *comb);

//Datos
static const char numbers[] = "10, 60, 48";
static const char setA[]    = "A = {rojo, verde, azul}";

// salidas 
char comb_n1[512]; // n = 1 
char comb_n2[512]; // n = 2
char comb_n3[512]; // n = 3


int main(void){

  // MCD
  int result = myGCD(numbers);              

 
  myCombinations(1, setA, comb_n1);
  myCombinations(2, setA, comb_n2);
  myCombinations(3, setA, comb_n3);


  printf("MCD = %d\n", result);
  printf("n=1: %s\n", comb_n1);
  printf("n=2: %s\n", comb_n2);
  printf("n=3: %s\n", comb_n3);

  while (1);

}

//Parte 1 MCD

// Miramos el residuo hasta que de 0 
static int EuclidesMCD (int a, int b) {
    while (b != 0) {  // si el residuo es 0 se termino 
        int valor = b; // guardamos valor de b 
        b = a % b; // obtenemos el residuo de a/b
        a = valor; // nuevo valor para a 
    }
    return a;
}

int myGCD(const char *set) {
    const char *p = set; // el puntero que va a recorer la cadena 
    int gcd = 0;           // valor para retorno 

    while (*p != '\0') { // leer hasta el final 

        while (*p != '\0' && (*p < '0' || *p > '9')) { // ver si es un numero, para el parseo 
            p++;
        }
        if (*p == '\0') {
            break;
        }
        // realizar el parseo 
        int num = 0;
        while (*p >= '0' && *p <= '9') { // mientras sea un numero 
            num = num * 10 + (*p - '0'); // convertir de ascii a int 
            p++;
        }

        // hacer el MCD y guardarlo en el gcd ( comparamos de 2 en 2 )
        gcd = EuclidesMCD(gcd, num);
    }

    return gcd; // resultado del MCD de los numeros 
}

// Parte 2  Cardinalidad de n en k 

#define Maxima_Cardinalidad   5    // Definimos la Maxima cardinalidad 
#define Maximo_N      3    // Definimos el Maximo valor de n 


static void appendStr(char **destino, const char *origen) { // str de origen y donde es el destino de el 
    char *d = *destino; // recive el destino 
    while (*origen != '\0') { // copiamos todo el origen 
        *d++ = *origen++;
    }
    *destino = d;         // actualiamos puntero de destino 
}

void myCombinations(int n, const char *set, char *comb) {

    static char buffer[128];  // guardamos los nombres ( azul/0rojo/0verde/0 )
    char *punteros[Maxima_Cardinalidad]; // punteros 
    int   k = 0; // cardinalidad 

    if (comb == 0 || set == 0) {
        return;
    }
    comb[0] = '\0'; // preparar el puntero 
    const char *p = set; // empezar donde set empieza 
    char *w = buffer; // puntero para escribir los punteros  
    while (*p != '\0' && *p != '{') { // buscamos el principio ( vaidaciones)
        p++;
    } if (*p != '{') { return; }
    p++;
    while (*p != '\0' && *p != '}' && k < Maxima_Cardinalidad) {

        while (*p == ' ') { // saltar espacios 
            p++;
        }
        punteros[k] = w;    // para ver donde seguir con el ptro puntero o donde empezar 
        while (*p != '\0' && *p != ',' && *p != '}') { // copiar elemento 
            *w++ = *p++;
        }
        while (w > punteros[k] && *(w - 1) == ' ') { // eliminar los espacion en blanco ( si existen )
            w--;
        }
        *w++ = '\0';  // cerrar la cadena ya qu eno hay espacios en blanco 
        k++; 
        if (*p == ',') {
            p++;
        }
    }

    if (n < 1 || n > Maximo_N || n > k) { // vaidaciones de valores de n 
        return;                              
    }

    int   indice[Maximo_N];   // guarda espacio para convinaciones 
    char *salida = comb;  // salida 
    int   primera = 1;  // para la coma 
    int   i, j; // para los ciclos 

    for (i = 0; i < n; i++) { // se crea la primera comvinacion 
        indice[i] = i;                 
     }

    for (;;) {
        if (!primera) {
            appendStr(&salida, ", "); // separar combinacion 
        }
        primera = 0;

        appendStr(&salida, "{"); // empezar con la lave 
        for (i = 0; i < n; i++) {
            if (i > 0) {
                appendStr(&salida, ", "); // separar los nombres adentro de las combinaciones 
            }
            appendStr(&salida, punteros[indice[i]]); // copiar la palabra en la combinacion 
        }
        appendStr(&salida, "}"); // cerrar la combinacion 

        i = n - 1;
        while (i >= 0 && indice[i] == k - n + i) { // miramos el valor maximo de la casilla, si lo alcanzo se cambia el anterior 
            i--;
        }
        if (i < 0) { // si se termino salir 
            break;                           
        }
        indice[i]++; // siguente valor de k [0,2] -> [1,2]
        for (j = i + 1; j < n; j++) { // reiniciamos las de la derecha [0,2] -> [1,0]
            indice[j] = indice[j - 1] + 1; // no repetidos, simepre el de la derecha mayor 
        }
    }

    *salida = '\0';
}
