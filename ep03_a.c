/* EP03a - MAC0122 - Prof. Paulo Miranda
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

struct Vertice{
  float x;
  float y;
  struct Vertice *prox;
};

typedef struct Vertice* Poligono;


struct Vertice * CriaVertice(float x, float y){
  Poligono P;

  P = (Poligono) malloc (sizeof(struct Vertice));
  P -> x = x;
  P -> y = y;

  return P;
}

void LiberaPoligono(Poligono P){
  Poligono Q = P;
  int num = 0, v = NumeroDeVertices(P);

  while (num < v){
    Q = P->prox;
    free(P);
    P = Q;
    num++;
  }
}

int NumeroDeVertices(Poligono P){
  Poligono Q = P->prox;
  int num;

  for(num = 1; Q != P; num++)
    Q = Q->prox;

  return num;
}

Poligono PoligonoPorPontoMedio(Poligono P){
  Poligono Q, M=NULL, N, Pri;
  float x, y;

  if(NumeroDeVertices(P) < 3)
    return NULL;

  Q = P;

  do{
    x = ((Q->x) + (Q->prox->x))/2;
    y = ((Q->y) + (Q->prox->y))/2;
    Q = Q -> prox;

    if (M == NULL){
      M = CriaVertice(x, y);
      M -> prox = M;
      Pri = M;
    }
    else {
      N = CriaVertice(x, y);
      M -> prox = N;
      N -> prox = Pri;
      M = N;
    }
  }
  while (Q != P);
  return M;
  }

void DrawLine(int **M, int m, int n, int x1, int y1, int x2, int y2, int val){
  float x,y,dx,dy;
  int xi,yi;

  dx = (x2-x1);
  dy = (y2-y1);

  if(fabs(dx) > fabs(dy)){
    dy = dy/(fabs(dx));
    dx = dx/(fabs(dx));
  }
  else{
    dx = dx/(fabs(dy));
    dy = dy/(fabs(dy));
  }

  x = (float)x1;
  y = (float)y1;

  xi = x1;
  yi = y1;

  while(xi != x2 || yi != y2){

    if(yi >= 0 && yi < m && xi >= 0 && xi < n)
      M[yi][xi] = val;

    x += dx;
    y += dy;
    xi = (int)(x + 0.5);
    yi = (int)(y + 0.5);
  }

  if(y2 >= 0 && y2 < m && x2 >= 0 && x2 < n)
    M[y2][x2] = val;
}

void DrawPoligono(Poligono P, int **M){
 Poligono Q;

 for(Q = P->prox; Q != P; Q = Q->prox)
    DrawLine(M, 480, 640, Q->x, Q->y, Q->prox->x, Q->prox->y, 1);
 DrawLine(M, 480, 640, Q->x, Q->y, Q->prox->x, Q->prox->y, 1);
}

int main (){
  int i, j, r;
  int **M, m = 640, n = 480;
  float x, y;
  FILE *fp;
  Poligono P=NULL, Q, H, Pri, lixo;

  fp = fopen ("entrada.txt","r");

  while (1){
    i = fscanf (fp, " %f %f ", &x, &y);

    if (i == EOF)
      break;

    if(P == NULL){
      P = CriaVertice(x, y);
      P->prox = P;
      Pri = P;
    }

    else{
      Q = CriaVertice(x, y);

      P -> prox = Q;
      Q -> prox = Pri;
      P = Q;
    }
  }
  printf("Vertices: %d \n",NumeroDeVertices(P));

  fclose(fp);

  M = (int **)calloc (n,sizeof(int *));
  for (i = 0; i < n ; i++)
    M[i] = (int *) calloc(m,sizeof(int));

  printf("Digite R: ");
  scanf(" %d", &r);

  H = P;
  for (i = 0; i < r && H != NULL; i++){
    Q = H;
    H = PoligonoPorPontoMedio(H);
    DrawPoligono(H, M);
    if (i > 0)
      LiberaPoligono(Q);
  }

  DrawPoligono(P, M);
  fp = fopen ("poligono.pgm","w");

  fprintf(fp, "P2\n%d %d\n%d\n", m, n, 1);
  for (i = 0; i < n; i++)
    for (j = 0 ; j < m; j++)
      fprintf(fp,"%d\n",M[i][j]);

  printf("Poligono gravado com sucesso.\n");
  LiberaPoligono (P);
  for (i = 0 ; i<n;i++)
    free (M[i]);

  free (M);
  fclose(fp);
  return 0;

}
