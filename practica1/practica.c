#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
   if (argc < 2)
   {
       fprintf(stderr,"hay un error con la ruta del archivo\n");
       return EXIT_FAILURE;
   }

   FILE* fp = fopen(argv[1],"r");//Abre el archivo
   
   if (!fp)
   {
       printf("Error opening the file %s\n",argv[1]); //error al abrir el archivo
       return EXIT_FAILURE;
   }
   char line[1024];//buffer donde se almacenaran las lineas
   int linecount = 0;
   int termscount = 0;
   int quantities[4];
   int numingredients = 0; 
   int I = 10; // Cantidad total de ingredientes diferentes en la totalidad de los platos por el momento lo dejo asi porque no se como sacarlo 
   while (fgets(line,1024,fp)) // coja el archivo y guardemelo linea por linea en el buffer
   {
       char * word; 
       char *rest = line;
       if (linecount == 0){
            /*while(word = strtok_r(rest," ",&rest)){
                quantities[termscount] = atoi(word); //en el array quantities se guarda los nuemeros de la primera linea que son los terminos de los platos
                termscount++;
                printf("Word: %s\n",word);
            } //me parte la linea cuando encuentra un caracter espacio y lo guarda en word
            linecount++;*/
       }else{
           word = strtok_r(rest," ",&rest); // guarda la primera palabra de la linea que es le numero de ingredientes
           numingredients = atoi(word); //convierte el string en un numero
           for (int i = 0; i < numingredients; i++) // un loop en el cual se guardaran cada uno de los ingredientes por cada linea
           {
               word = strtok_r(rest," ",&rest);
               printf("Read word: %s\n", word); 

           }
           
       }
    }
    for (int i = 0; i < 4; i++)
    {
        printf("Quiantity: %d\n",quantities[i]);//imprimo cada una de las palabras de la primera linea
    }
    
    int PP = quantities[0]; //cantidad de pedidos el primer numero del archivo de entrada
    int P2 = quantities[1];//cantidad de pedidos de 2 platos
    int P3 = quantities[2];//cantidad de pedidos de 3 platos
    int P4 = quantities[3];//cantidad de pedidos de 4 platos

    int NTPP = (2*P2)+(3*P3)+(4*P4); //cantidad total de pedidos
    printf("Pedidos totales: %d\n",NTPP);

    int P[PP][I]; // Matriz de relacion entre platos y ingredientes 
    for (int i = 0; i < I; i++){
        for (int j = 0; j < PP; j++){ 
            /*en este loop se guardara un 1 cuando se encuentra un ingrediente*/ 
        }
    }
    
   fclose(fp);// cierra el archivo   
   
}

