#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char* palabras = (char*)malloc(2100*sizeof(char)); //reservando espacio memoria para los ingredientes, se supone que cada ingrediente tiene 21 caracteres contando el caracter final

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
    int numOfDifferentIngredients = 0;
    char *nullchar = '\0';

    while (fgets(line,1024,fp)) // coja el archivo y guardemelo linea por linea en el buffer
    {
        char * word; 
        char *rest = line; //contiene linea leida

        if (linecount == 0){
            while(word = strtok_r(rest," ",&rest)){
                quantities[termscount] = atoi(word); //en el array quantities se guarda los nuemeros de la primera linea que son los terminos de los platos
                termscount++;
                printf("Word: %s\n",word);
            } //me parte la linea cuando encuentra un caracter espacio y lo guarda en word
            linecount++;
       }else{
           word = strtok_r(rest," ",&rest); // guarda la primera palabra de la linea que es le numero de ingredientes
           numingredients = atoi(word); //convierte el string en un numero
           for (int i = 0; i < numingredients; i++) // un loop en el cual se guardaran cada uno de los ingredientes por cada linea
           {
               word = strtok_r(rest," ",&rest);
               if(i==numingredients-1)
               {//este if sirve para que los ingredientes los cuente una sola vez
                   char *s=word;
                   while(*s != '\n') //si es la ultima posicion que esta definida por \n entonces lo reemplza poro \0
                   {
                       ++s;
                   }
                   *s = '\0';
               }

               int comparisonSomeIsEqual = -1;
               for(int j=0; j<numOfDifferentIngredients;j++){
                   if(strcmp((palabras+(j*21)),word) == 0){
                   comparisonSomeIsEqual = 0;
                   break;
                   }
               }
               if(comparisonSomeIsEqual == -1){//toma el primer elemento
                   strcpy((palabras+(numOfDifferentIngredients*21)), word);
                   numOfDifferentIngredients++;
               }

           }
           
       }
    }
    
   fclose(fp);// cierra el archivo   
   
   for(int i=0;i<4;i++){
       printf("%d\n", quantities[i]);
   }

   for(int i=0; i<numOfDifferentIngredients;i++){
       printf("ingredient: %s\n",(palabras + (i*21))+0);
   }
   return EXIT_SUCCESS;
}

