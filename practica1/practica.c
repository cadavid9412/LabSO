#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutar (int v[],int m,int tamao);
void intercambiar (int *p1,int *p2);
void escribir_vector (int vect[], int tam);


int main(int argc, char const *argv[])
{
     char* palabras = (char*)malloc(2100*sizeof(char)); //reservando espacio memoria para los ingredientes, se supone que cada ingrediente tiene 21 caracteres contando el caracter final
     char* ingredientesPlatos = (char*)malloc(21000*sizeof(char));
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
   int ingredientesPorPlato[20];
   int contador = 0;
   int contador2 = 0;
   int I = 0; // Cantidad total de ingredientes diferentes en la totalidad de los platos 
   char *nullchar;
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
           ingredientesPorPlato[contador] = numingredients;
           printf("Ingredientes por plato: %d\n",ingredientesPorPlato[contador]);
           for (int i = 0; i < numingredients; i++) // un loop en el cual se guardaran cada uno de los ingredientes por cada linea
           {
               word = strtok_r(rest," ",&rest);
               printf("Read word: %s\n", word); 
               strcpy((ingredientesPlatos+(contador2*21)), word);
               strtok((ingredientesPlatos+(contador2*21)),"\n");
               if(i==numingredients-1)//este if sirve para que los ingredientes los cuente una sola vez
               { 
               char *s=word;
                   while(*s != '\n') //si es la ultima posicion que esta definida por \n entonces lo reemplza poro \0
                   {
                        ++s;
                   }
                   *s = '\0';
               }

               int comparisonSomeIsEqual = -1;
               for(int j=0; j<I;j++){
                   if(strcmp((palabras+(j*21)),word) == 0){
                   comparisonSomeIsEqual = 0;
                   break;
                   }
               }
               if(comparisonSomeIsEqual == -1){//toma el primer elemento
                   strcpy((palabras+(I*21)), word);
                   I++;
               }
               contador2++;
           }
           contador++;   
        }
    }
    for (int i = 0; i < 4; i++)
    {
        printf("Quiantity: %d\n",quantities[i]);//imprimo cada una de las palabras de la primera linea
    }
    printf("\n");
    //Imprime todos los ingredientes diferentes
    for(int i=0; i<I;i++){
       printf("ingredient: %s\n",(palabras + (i*21))+0);
    }
    
    printf("\n");
    int PP = quantities[0]; //cantidad de platos el primer numero del archivo de entrada
    int P2 = quantities[1];//cantidad de pedidos de 2 platos
    int P3 = quantities[2];//cantidad de pedidos de 3 platos
    int P4 = quantities[3];//cantidad de pedidos de 4 platos
    
    printf("Ingredientes totales: %d\n",I);
    int NTPP = (2*P2)+(3*P3)+(4*P4); //cantidad total de pedidos
    printf("Pedidos totales: %d\n",NTPP);
    
    printf("La matriz P es:\n");
    int P[I][PP];//Instancia de la matriz de 1 y 0
   
    for (int i = 0; i < I; i++) //se llena la matriz con 1 y 0
    {   int aux = 0;
        printf("\n");
        for (int j = 0; j < PP; j++)
        {   
            int fin = ingredientesPorPlato[j];
            for (int k = 0; k < fin; k++)
            {   
                if(strcmp((palabras+(i*21)),ingredientesPlatos + ((k+aux)*21)) == 0){
                    P[i][j] = 1;  
                    break;
                }
                else{
                    P[i][j] = 0;              
                }
         
            }
            aux = fin + aux;
            
            printf(" %d",P[i][j]); 
        }
        
    }

    printf("\n");
    int AP[NTPP];//Intancia el vector AP
    printf("\n");
    //llenando el vector AP
    printf("Vector AP:");
    for (int i = 0; i < NTPP; i++)
    {
       AP[i] = i;
       printf(",%d",AP[i]);
      
    }
     printf("\n");
 
    //Se llama la funcion permutar 
    //permutar(AP,NTPP,NTPP);

   fclose(fp);// cierra el archivo  
   return EXIT_SUCCESS; 
   
}

void permutar (int v[], int m,int tamao)
{
    int tam = tamao;
    register int i;
    if (m > 1)
    {
        for (int i = 0; i < m; i++)
        {   
            //Se llama la funcion intercambiar y de nuevo permutar para ser recursivo
            intercambiar (&v[i],&v[m]);
            permutar(v,m-1,tam);
            intercambiar (&v[i],&v[m]);
        }
    }
    else
    {   
        //se imprime las permutaciones 
        putchar('\n');
        escribir_vector(v,tam);
       
    }    
}

void intercambiar(int *p1, int *p2)
{
    int aux;
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

void escribir_vector (int vect[],int tam)
{
    static unsigned int numero_de_permutacion = 0;
    register int i;
    if (++numero_de_permutacion % 24 == 0)
    {
        printf("Ha salido");
        putchar('\r');
        putchar('\r');
    }
    printf("permutacion %2u:",numero_de_permutacion);
    for ( int i = 0; i < tam; i++)
    {
        printf("%d",vect[i]);
        printf(",");
  
    }
}