#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *vectorpermu(int *AP,int N,int *total,int PP,int P2,int I, int P3,int P4,int OP3, int OP4,int P[I][PP],FILE* output);
void intercambiar (int *p1,int *p2);
int B(int N, int c);
void reverse (int * AP,int N);
void escribir_vector (int * AP,int N, int* total);

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
   FILE* output = fopen("output.txt","wt");//crea el archivo de salida 
   fprintf(output,"Este es el archivo donde encontraras la solucion de la practica\n\n");
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
    int OP3 = 2*P2;
    int OP4 = 2*P2+3*P3;

    printf("Ingredientes totales: %d\n",I);
    int NTPP = (2*P2)+(3*P3)+(4*P4); //cantidad total de pedidos
    printf("Pedidos totales: %d\n",NTPP);
    
    printf("La matriz P es:\n");
    fprintf(output,"La matriz de los platos:\n\n");
    int P[I][PP];//Instancia de la matriz de 1 y 0
   
    for (int i = 0; i < I; i++) //se llena la matriz con 1 y 0
    {   int aux = 0;
        printf("\n");
        fprintf(output,"\n");
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
            fprintf(output," %d",P[i][j]);
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
 
    printf("\n");
    

     //Se llama la funcion que permutara el vector AP 
    int total =0;
    //int vSolucion[] = {0,2,1,3,5,4,6,7,8};
    int *vSolucion = vectorpermu(AP,NTPP,&total,PP,P2,I,P3,P4,OP3,OP4,P,output);
    //Total de permutaciones realizadas
    printf("Total: %d permutaciones \n",total);

    printf("\n");
    fprintf(output,"\n");
    //Inicializo las variables para guardar los ingredientes diferentes de cada pedido
    char* pedido0 = (char*)malloc(21000*sizeof(char));
    char* pedido1= (char*)malloc(21000*sizeof(char));
    char* pedido2 = (char*)malloc(21000*sizeof(char));
    printf("El pedido 0 contiene:");
    fprintf(output,"El pedido 0 contiene:");
    for (int i = 0; i < I; i++)
    {
       for (int j = 0; j < 2*P2; j++)
       {          
           if (P[i][vSolucion[j]]==1)
           {    
               strcpy((pedido0+(i*21)),(palabras+(i*21))); 
               printf(" %s",(pedido0+(i*21)));
               fprintf(output," %s",(pedido0+(i*21)));
               printf(",");
               fprintf(output,",");
               break;
           }
           
       }
       
    }
    printf("\n");
    printf("El pedido 1 contiene:");
    fprintf(output,"\n");
    fprintf(output,"El pedido 1 contiene:");
    for (int i = 0; i < I; i++)
    {
       for (int j = 0; j < 3*P3; j++)
       {          
           if (P[i][vSolucion[OP3+j]]==1)
           {    
               strcpy((pedido1+(i*21)),(palabras+(i*21))); 
               printf(" %s",(pedido1+(i*21)));
               printf(",");
               fprintf(output," %s",(pedido1+(i*21)));
               fprintf(output,",");
               break;
           }
           
       }
       
    }
    printf("\n");
    printf("El pedido 2 contiene:");
    fprintf(output,"\n");
    fprintf(output,"El pedido 2 contiene:");
    for (int i = 0; i < I; i++)
    {
       for (int j = 0; j < 4*P4; j++)
       {          
           if (P[i][vSolucion[OP4+j]]==1)
           {    
               strcpy((pedido2+(i*21)),(palabras+(i*21))); 
               printf(" %s",(pedido2+(i*21)));
               printf(",");
               fprintf(output," %s",(pedido2+(i*21)));
               fprintf(output,",");
               break;
           }
           
       }
       
    }
    printf("\n");

   fclose(fp);// cierra el archivo  
   return EXIT_SUCCESS; 
   
}

int *vectorpermu(int *AP,int N,int *total,int PP,int P2,int I, int P3,int P4,int OP3, int OP4,int P[I][PP], FILE* output)
{   
    int *vSolucion=malloc(N*sizeof(int));
    int comparador = 0;
    int i;
    int c[N];
    for (i= N; i>1; i--)
    {
        c[i]=1;
    }
    i=2;
    //escribir_vector(AP,N,total);
    do
    {
        if (c[i]<i)
        {   
            intercambiar(&AP[i],&AP[c[i]]);
            reverse(AP,i-1);
            //escribir_vector(AP,N,total);
           
            c[i] ++;
            i = 2;
        }
        else
        {
            c[i]=1;
            i++;
        }
        int maximoIngredientes=0;
        for (int j = 0; j < P2; j++)
        {
            for (int k = 0; k < I; k++)
            {
                if (P[k][AP[2*j]] || P[k][AP[2*j+1]])
                {
                    maximoIngredientes++;
                } 
            }
        }
        for (int j = 0; j < P3; j++)
        {
            for (int k = 0; k < I; k++)
            {
                if (P[k][AP[OP3+3*j]] || P[k][AP[OP3+3*j+1]]  || P[k][AP[OP3+3*j+2]])
                {
                    maximoIngredientes++;
                }
                
            }     
        }
        for (int j = 0; j < P4; j++)
        {
            for (int k = 0; k < I; k++)
            {
                if (P[k][AP[OP4+4*j]] || P[k][AP[OP4+4*j+1]]|| P[k][AP[OP4+4*j+2]] || P[k][AP[OP4+4*j+3]])
                {
                     maximoIngredientes++;
                }
                
            }
            
        }
        if (comparador < maximoIngredientes && maximoIngredientes!=28)
        {   
            comparador = maximoIngredientes;
           for (int j = 0; j < N; j++)
           {
               vSolucion[j]=AP[j];
           }
           

        }
        
       
    } while (i<=N);
    fprintf(output,"\n\n");
    printf("Este es el vector de solucion:");
    fprintf(output,"Este es el vector de solucion:");
     for (int j = 0; j < N; j++)
     {
         printf(" %d",vSolucion[j]);
         fprintf(output," %d",vSolucion[j]);
     }
     printf("\n");
     fprintf(output,"\n\n");
     fprintf(output,"La cantidad de ingredientes diferentes totales son: %d\n",comparador);
     printf("La cantidad de ingredientes diferentes totales son: %d\n",comparador);
     return vSolucion;
}
void intercambiar(int *p1, int *p2)
{
    int aux;
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

int B(int N, int c){
    return ( (N % 2) != 0 ? 1 :c);
}
void reverse (int *AP,int N){
    int i =1;
    while (i<(N+1-i))
    {
        intercambiar(&AP[i],&AP[N+1-i]);
        i++;
    }
    
}
void escribir_vector (int* AP,int N, int* total)
{
 int i;
printf("vector");
 for ( i = N; i > 0; i--)
 {
     
     printf(" %d",AP[i]);
 }
 printf("\n");
 (*total)++;
}