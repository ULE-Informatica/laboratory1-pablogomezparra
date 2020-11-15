/**
 * Pablo Gómez de la Parra García. 13-nov-2020. Practica 3. Programación Segura.
 * The student needs to compile, test and comment the source code file.
 * 
 * Enumerate those Rules and Recommendation associated that are broken in the previous source code file.
 * FIO40-C Reset strings on fgets() or fgetws() failure
 * ARR32-C. Ensure size arguments for variable length arrays are in a valid range
 * STR30-C. Do not attempt to modify string literals
 * STR31-C. Guarantee that storage for strings has sufficient space for character data and the null terminator
 * STR32-C. Do not pass a non-null-terminated character
 * STR38-C. Do not confue narrow and wide character sring and functions
 * STR07-C. Use the bounds-checking interfaces for string manipulation
 * STR01-C. Adopt and implement a consistent plan for manaing strings
 * STR11-C. Do not specify the bound of a character array initialized with a string literal
 * MSC34-C. Do not use deprecated or obsoloescent functions
 * 
 * Enumerate he compilation tools and paramenters (gcc vs g++), -Wall ...
 * gcc -g /Users/pablounileon/Documents/DPS/As3.c -o /Users/pablounileon/Documents/DPS/As3 -std=c17 -Wall
 * gcc -g /Users/pablounileon/Documents/DPS/As3.c -o /Users/pablounileon/Documents/DPS/As3 -std=c99 -Wall
 * gcc -g /Users/pablounileon/Documents/DPS/As3.c -o /Users/pablounileon/Documents/DPS/As3 -ansi -Wall
 * clang -g /Users/pablounileon/Documents/DPS/As3.c -o /Users/pablounileon/Documents/DPS/As3 
 * 
 * 
 * Enumerate the standard associated  -std=c99, -std=c11
 * Me da los mismos warnings independientemente de la versión de compilador que use
 * Aparece algún cambio con el estándar -ansi, sobre todo comentarios con '//'
 * 
 * There are several variants. You should choose at least two.
 * At the end the source code  should compile without warnings to the variant selected (you can remove/change instructions).
 * Se incluye el códgio corregido para que compile sin warnings. Se ha utilizado el siguiente comando:
 * > gcc -g /Users/pablounileon/Documents/DPS/As4.c -o /Users/pablounileon/Documents/DPS/As4 -Wall -std=c99
 * 
 * Se ha compilado sobre un MacOS Catalina 10.15.7 y con una versión de gcc:
 * pablounileon@iMac-de-Pablo ~ % gcc --version
 *  Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
 *  Apple clang version 11.0.0 (clang-1100.0.33.16)
 *  Target: x86_64-apple-darwin19.6.0
 *  Thread model: posix
 *  InstalledDir: /Library/Developer/CommandLineTools/usr/bin
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char array1[] = "Foo" "bar";
char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };


enum { BUFFER_MAX_SIZE = 1024 };
 
/* Corregido. Había un error de compilación en la variable s1. Entiendo que el formato con salto LF o CRLF es 
para que de problemas en la lectua de gets vs. scanf */
const char* s1 = "foo(HelloWorld)foo";
const char* s2 = "\nHello\nWorld\n";

/* No se llama desde ningún sitio */
void gets_example_func(void) {
  char buf[BUFFER_MAX_SIZE];
  /*FIO40-C. Reset strings on fgets() or fgetws() failure*/
  if (fgets(buf, sizeof(buf), stdin) == NULL) {
        /*return 1; Codigo eliminado. No puede devolver un valor una función VOID*/
      *buf='\0';
  }
  buf[strlen(buf) - 1] = '\0';
}

/**
 * Origen del fuente corregido:
 * https://opensource.apple.com/source/distcc/distcc-2503/distcc_dist/src/filename.c
 * Esta función me continua dando un error que no entiendo... 
 * Comentado con profesor y enviado correo.
*/
char *get_dirname(char *pathname) {
  printf("Inicio de get_dirname\n");
  /*char *slash;  Puntero no inicializado */
  char *slash = 0;

  slash = strrchr(pathname, '/'); /* Se escribe en una dirección que puede machacar otra si el puntero no está inicializado */
  printf("slash=%s\n",slash);
  if (slash==NULL) {
    pathname[0]='\0';
  }else{
    *slash = '\0'; /* Error en tiempo de ejecución: "zsh: bus error. EXC_BAD_ACCESS" */
                   /* También me da error en el compilador onlinegdb.com */
  }
  return pathname;
}
 
/* ARR32-C. Ensure size arguments for variable length arrays are in a valid range */
/* STR31-C */
/* El programador supone una lectura de 8 caracteres, pero si excede la lectura de 8 caracteres puede haber problemas */
/* No sé por qué no me genera warnings aunque use la versión c11 o c99. */
void get_y_or_n(void) {  
	char response[8];

	printf("Continue? [y] n: ");  
    /* función "deprecated" */
	/* gets(response);  */
    scanf("%s",response);
	if (response[0] == 'n') 
		exit(0);  

	return;
}

 
int main(int argc, char *argv[])
{
    char key[24];
    char response[8];
    char array3[16];
    char array4[16];
    char array5 []  = "01234567890123456";
    /* char *ptr_char  = "new string literal"; Comentada porque no se usa al comentarla en la parte del main porque da error en ejecución */
    /* int size_array1 = strlen("аналитик"); */
    /* int size_array2 = 100; */
    
    
    /* char analitic1[size_array1]="аналитик"; */
    /* char analitic2[100]="аналитик"; */
    /* char analitic3[100]="аналитик"; */
    
    printf("Inicio main...\n");
    
    /* puts(get_dirname(__FILE__)); */

    /* Accede a posiciones que no están inicializadas sin comprobar previamente la cantidad de argumentos recibida */
    /* Se que la solución no es la más elegante, pero hace 20 años que no programo :-) */
    if (argc == 1){
        printf("Se ha recibido un parametro.\n");
    }else if(argc == 2){
        printf("Se han recibido dos parametros.\n");
        strcpy(key, argv[1]);
    }else if(argc == 2){
        printf("Se han recibido tres parametros.\n");
        strcpy(key, argv[2]);
    }
    /* No se puede acceder a un elemento de un array sin saber si realmente existe */
    /* strcpy(key, argv[1]) */
    /* Mal uso de array de cracteres asignándole un string */
    strcat(key, " = ");  
    /* strcat(key, argv[2]); */

    /** 
     * Solo lee 8 caracteres de entrada: "sizeof(response)". Si el usuario introduce más caracteres se quedan 
     * encolados y los lee automáticamente la próxima vez que lea la entrada, en este caso
     * la funcion get_y_or_n. Si la entrada es muy larga puede corromper la lectura de la
     * funcion get_y_or_n porque supone un tamaño máximo de 8.
     */
     printf("Lectura desde consola:");
    fgets(response,sizeof(response),stdin);

    get_y_or_n();

    printf ("%s",array1);
    printf ("\n");
    printf ("%s",array2);
    printf ("\n");
 
    puts (s1);
    printf ("\n");
    puts (s2);
    printf ("\n");
    
    /**
     * Utiliza tamaños y longitudes de arrays sin comprobar. Hay riesgo de machacar la pila.
     * Además mezcla sizeof (cantidad de caracteres antes del nulo) con strlen (cantidad de 
     * memoria que utiliza la variable) y no tienen por qué ser iguales.
     * Además strlen requiere que haya \0 para obtener la longitud real. En este caso array3
     * no tiene porque acaber en \0.
    */
    strncpy(array3, array5, sizeof(array3));
    array3[sizeof(array3)-1]='\0';
    strncpy(array4, array3, strlen(array3));
    

    array5 [0] = 'M';
    
    /**
     * No se puede modificar un string literal porque está en el segmento de datos de
     * solo lectura.
     * Si se descomenta da error de ejecución.
     */
    /* ptr_char [0] = 'N'; */
    
    /*Esto debería ir más arriba para asegurar que strlen lee correctamente el tamaño */
    array3[sizeof(array3)-1]='\0';
    
    
    return 0;
}
