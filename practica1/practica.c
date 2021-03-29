#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutar (int v[],int m);
void intercambiar (int *p1,int *p2);
void escribir_vector (int vect[], int m);


int main(int argc, char const *argv[])
{
   if (argc < 2)
   {
       fprintf(stderr,"hay un error con  la ruta del archivo\n");
       return EXIT_FAILURE;
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
   int I = 10; // Cantidad total de ingredientes diferentes en la totalidad de los platos por el momento lo dejo asi porque no se como sacarlo 
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
    int AP[NTPP];
    
    //llenando el vector AP
    printf("Vector AP:");
    for (int i = 0; i < NTPP; i++)
    {
       AP[i] = i;
      
    }
    for (int i = 0; i < NTPP; i++)
    {
        printf("%d",AP[i]);
    }
    
    printf("\n");
    
    //Se llama la funcion permutar 
    permutar(AP,NTPP);

   fclose(fp);// cierra el archivo   
   
}

void intercambiar(int *p1, int *p2)
{
    int aux;
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

void permutar (int v[], int m)
{
    register int i;
    if (m > 1)
    {
        for (int i = 0; i < m; i++)
        {   
            //Se llama la funcion intercambiar y se y de nuevo permutar para ser recursivo
            intercambiar (&v[i],&v[m]);
            permutar(v,m-1);
            intercambiar (&v[i],&v[m]);
        }
    }
    else
    {   
        //se imprime las permutaciones 
        escribir_vector(v,m);

    }    
}

void escribir_vector (int vect[],int m)
{
    static unsigned int numero_de_permutacion = 0;

    if (++numero_de_permutacion % 24 == 0)
    {
        printf("Ha salido");
        putchar('\r');
        putchar('\r');
    }
    printf("permutacion %2u:",numero_de_permutacion);
    for ( int i = 0; i < m; i++)
    {
        printf("%d",vect[i]);
        putchar('\n');
    }
}