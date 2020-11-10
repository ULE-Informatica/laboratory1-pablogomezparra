/**
 *  
 * The student needs to compile, test and comment the source code file.
 * 
 * Enumerate those Rules and Recommendation associated that are broken in the previous source code file.
 * FIO40-C Reset strings on fgets() or fgetws() failure
 * ARR32-C. Ensure size arguments for variable length arrays are in a valid range
 * 
 * Enumerate he compilation tools and paramenters (gcc vs g++), -Wall ...
 * gcc -g /Users/pablounileon/Documents/DPS/hola.c -o /Users/pablounileon/Documents/DPS/hola -std=c17 -Wall
 * gcc -g /Users/pablounileon/Documents/DPS/hola.c -o /Users/pablounileon/Documents/DPS/hola -std=c99 -Wall
 * gcc -g /Users/pablounileon/Documents/DPS/hola.c -o /Users/pablounileon/Documents/DPS/hola -ansi -Wall
 * 
 * Enumerate the standard associated  -std=c99, -std=c11
 * Me da los mismos warnings independientemente de la versión de compilador que use
 * Aparece algún cambio con el estándar -ansi, sobre todo comentarios //
 * 
 * There are several variants. You should choose at least two.
 * At the end the source code  should compile without warnings to the variant selected (you can remove/change instructions).
 */

/**
 * Obtengo un error en tiempo de ejecución en la línea 63: EXC_BAD_ACCESS
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char array1[] = "Foo" "bar";
char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };


enum { BUFFER_MAX_SIZE = 1024 };
 
/* Corregido. Había un error de compilación en la variable s1 */
const char* s1 = "foo(HelloWorld)foo";
const char* s2 = "\nHello\nWorld\n";

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
*/
char *get_dirname(char *pathname) {
  printf("Inicio de get_dirname\n");
  /*char *slash; /* Puntero no inicializado */
  char *slash = 0;

  slash = strrchr(pathname, '/'); /* Se escribe en una dirección que puede machacar otra*/
  printf("slash=%s\n",slash);
  if (slash==NULL) {
    pathname[0]='\0';
  }else{
    *slash = '\0'; /* Error en tiempo de ejecución: "zsh: bus error. EXC_BAD_ACCESS" */
  }
  return pathname;
}
 
/* ARR32-C. Ensure size arguments for variable length arrays are in a valid range */
/* El programador supone una lectura de 8 caracteres, pero si excede la lectura de 8 caracteres puede haber problemas */
/* No sé por qué no me genera warnings aunque use la versión c11 o c99. */
void get_y_or_n(void) {  
	char response[8];

	printf("Continue? [y] n: ");  
	gets(response); /* función "deprecated" */

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
    char *ptr_char  = "new string literal";
    int size_array1 = strlen("аналитик");
    int size_array2 = 100;
    
   // char analitic1[size_array1]="аналитик";
   // char analitic2[size_array2]="аналитик";
    char analitic3[100]="аналитик";

    printf("Inicio main...\n");
    puts(get_dirname(__FILE__));

        
    strcpy(key, argv[1]);  
    strcat(key, " = ");  
    strcat(key, argv[2]);


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
    
    strncpy(array3, array5, sizeof(array3));  
    strncpy(array4, array3, strlen(array3));
    
    array5 [0] = 'M';
    ptr_char [0] = 'N';
    
    array3[sizeof(array3)-1]='\0';
    
    
    return 0;
}