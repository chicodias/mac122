/* ATENCAO: Compilar com a tag -lm no gcc
 *
 * EP01b
 - MAC0122 - Prof. Paulo Miranda
 * 
 * AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
 * TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
 * DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
 * E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
 * POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
 * SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
 * REPROVAÇÃO DIRETA NA DISCIPLINA.
 *
 * Nome: Francisco Rosa Dias de Miranda
 * NUSP: 4402962
 *
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define LIM 128

struct ImagemRGB{
  int **R;
  int **G;
  int **B;
  int m;
  int n;
};

struct Descritor{
  char filename[512];
  float *hist;
  struct Descritor *prox;
};

typedef struct Descritor * ListaDescritores;

struct Ranking{
  char filename[512];
  float dist;
  struct Ranking *prox;
};

typedef struct Ranking * ListaRanking;

int ** AlocaMatriz (int m, int n);
void LiberaMatriz (int **M, int m);
struct ImagemRGB *AlocaImagemRGB(int m, int n);
void LiberaImagemRGB(struct ImagemRGB *I);
struct ImagemRGB *AbreImagemRGB(char filename[]);
float *HistogramaCores(struct ImagemRGB *I);
float DistanciaHistogramas(float *hist1, float *hist2);
void LiberaDescritores(ListaDescritores L);
ListaRanking InsereNoRanking(ListaRanking R,float d,char filename[]);
void LiberaRanking(ListaRanking L);


int main (){
  
  int a = 0;
  char filename[LIM];
  struct ImagemRGB * img;
  FILE *fp;
  
  struct Descritor *D, *E = NULL;
  ListaDescritores inic;
  struct Ranking * K;
  ListaRanking rank = NULL;
  
  printf ("Digite o nome do arquivo texto: ");
  scanf(" %s",filename);

  fp = fopen(filename,"r");
  printf("Carregando imagens do arquivo. Aguarde...\n");

  while(a != EOF){

    a = fscanf(fp, "%s\n",filename);

    img = AbreImagemRGB(filename);
    
    D = (struct Descritor*) malloc (sizeof (struct Descritor));
    D -> hist = HistogramaCores(img);
    strcpy(D -> filename,filename);
    LiberaImagemRGB(img);
    
    if (E == NULL){ //primeiro elemento da lista ligada
      inic = D;
      E = D;
      continue;
    } 
    E -> prox = D;
    E = D;
  }
  E -> prox = NULL;
  fclose(fp);
  printf("Imagens carregadas com sucesso. ");

  //encontrando o arquivo desejado na lista ligada
 while (1){
    printf("Qual imagem deseja comparar? ");
	scanf(" %s", filename);
	D = inic;
	while (D != NULL){
	  if(strcmp(filename, D-> filename)==0)
            break;
	  D = D->prox;
	}
	if (D == NULL)
	  printf("Arquivo invalido.\n");
	else
	  break;
  }  

 E = inic;
  while (E != NULL){
    rank = InsereNoRanking (rank, DistanciaHistogramas(D->hist,E->hist),
			   E -> filename);
    E = E-> prox;   
  }
  LiberaDescritores(inic);

  
  printf("Imagens similares a %s\n\n",filename);
  a = 0;
  printf("Pos  Arquivo  Dist\n");
  for (K = rank; K != NULL; K = K-> prox)
    printf("%2d  %s %.2f  \n",a++,K->filename,K->dist);

  LiberaRanking(rank);

  printf("\n");
  return 0;
}


int ** AlocaMatriz (int m, int n){
  int **M, i;
  M = (int **)malloc(m*sizeof(int*));
  
  for (i = 0; i <  m; i++)
    M[i] = (int *) malloc (n*sizeof(int));
  
  return M;
}

void LiberaMatriz (int **M, int m){
  int i;
  
  for (i = 0; i < m; i++)
    free (M[i]);

  free (M);
}

struct ImagemRGB *AlocaImagemRGB(int m, int n){
  int i, j;
  struct ImagemRGB * img;
  
  img = (struct ImagemRGB *) malloc(sizeof(struct ImagemRGB));
  
  img -> R = AlocaMatriz(m,n);
  img -> G = AlocaMatriz(m,n);
  img -> B = AlocaMatriz(m,n);
  img -> m = m;
  img -> n = n;
  
  return img;
}

void LiberaImagemRGB(struct ImagemRGB *I){
  LiberaMatriz(I -> R, I-> m);
  LiberaMatriz(I -> G, I-> m);
  LiberaMatriz(I -> B, I-> m);

  free (I);
}

struct ImagemRGB *AbreImagemRGB(char filename[]){
  FILE *fp;
  int i,j;
  struct ImagemRGB * img;
  
  fp = fopen (filename, "r");
  fscanf (fp,"P3 %d %d 255", &i, &j);
  
  img = AlocaImagemRGB(i, j);
    
  for (i=0; i < img -> m; i++)
    for (j=0; j < img -> n; j++)
      fscanf(fp," %d %d %d", &img -> R[i][j], &img -> G[i][j], &img -> B[i][j]);
  
  fclose (fp);
  return img;
}

float *HistogramaCores(struct ImagemRGB *I){
  int i,j;
  float * H, npix = (I -> m * I -> n);
  
  H = (float *) calloc (64, sizeof(float));
 
  for (i= 0; i < I -> m; i++){
    for (j = 0; j < I -> n ; j++){
      I -> R[i][j] /= 64;
      I -> G[i][j] /= 64;
      I -> B[i][j] /= 64;
      H[I -> R[i][j] + 4 * I -> G[i][j] + 16 * I -> B [i][j] ]++;
    }
  }
  for (i = 0; i < 64 ; i++)
    H[i] /= npix;
  
  return H;
}

float DistanciaHistogramas(float *hist1, float *hist2){
  int i;
  float d = 0.0;
  
  for (i= 0; i < 64; i++)
    d += (hist1[i] - hist2[i])*(hist1[i] - hist2[i]);
  
  d = sqrtf(d);
  
  return d;
}

void LiberaDescritores(ListaDescritores L){
  struct Descritor *D;
  
  while(L != NULL){
    D = L;
    free(D->hist);
    L = L -> prox;
    free(D);
  }
}
void LiberaRanking(ListaRanking L){
  ListaRanking M;

  while(L != NULL){
    M = L;
    L = L -> prox;
    free(M);
  }
}

ListaRanking InsereNoRanking(ListaRanking R,float d,char filename[]){
  struct Ranking * new;
  ListaRanking pri = R, ant;

  new = (struct Ranking*) malloc (sizeof (struct Ranking));
  strcpy(new -> filename,filename);
  new -> dist = d;

  if (R == NULL){
    new -> prox = NULL;
    return new;
  }  
  else if (new -> dist <= R->dist){
    new -> prox = R;
    return new;
  }
  else{
  while (R != NULL){
    if (new -> dist < R-> dist)
      break;
    ant = R;  
    R = R -> prox;
  }
  ant -> prox = new;
  new -> prox = R;

  return pri;
  }
}
