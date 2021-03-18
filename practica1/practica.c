#include <stdio.h>

int main(int argc, char const *argv[])
{
   if (argc < 2)
   {
       /* code */
       printf("hola");
   }
   FILE* fp = fopen(argv[1],"r");//Abre el archivo
   if (!fp)
   {
       printf("Error opening the file %s\n",argv[1]); //error al abrir el archivo
   }
   char line[1024];//buffer donde se almacenaran las lineas
   int linecount = 0;
   int termscount = 0;
   int quantities[4];
   int numingredients = 0; 
   while (fgets(line,1024,fp)) // coja el archivo y guardemelo linea por linea en el buffer
   {
       char * word; 
       char *rest = line;
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
               printf(Read word: %\n, word); 
           }
           
       }
    }
    for (int i = 0; i < 4; i++)
    {
        printf("Quiantity: %d\n",quantities[i]);//imprimo cada una de las palabras de la primera linea
    }
    

   fclose(fp);// cierra el archivo   
   
}

