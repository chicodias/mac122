/* EP01 - MAC0122 - Prof. Paulo Miranda
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
#include <string.h>
#define LIM 128

int** CopiaMatriz(int **M, int m, int n);
void OrdenaVetor (int *vet, int a);

int **AlocaMatriz(int m, int n);
void LiberaMatriz(int** M, int m, int n);
int** AbreImagem (char filename[],int* m, int* n);
void GravaImagem(char filename[], int** M, int m, int n);
void negativo(int** M, int m, int n);
int** corte(int** M, int* m, int* n,int xsup, int ysup, int xinf, int yinf);
void rebatimentoVertical(int** M, int m, int n);
void rebatimentoHorizontal(int** M, int m, int n);
int** rotacao(int **M, int* m, int* n);
void filtroMediana(int** M, int m, int n, int larguraJanela);
void filtroMedia(int** M, int m, int n, int larguraJanela);
void filtroErosao(int** M, int m, int n, int larguraJanela);
void filtroDilatacao(int** M, int m, int n, int larguraJanela);
void limiarizacao(int** M, int m, int n, int k);
void filtroBorda1(int** M, int m, int n, int larguraJanela, int k);
void filtroBorda2(int** M, int m, int n, int larguraJanela, int k);
void filtroBorda3(int** M, int m, int n, int larguraJanela, int k);



int main ()
{
  char filename[LIM], comp[LIM];
  char filename_[LIM]; //string que guarda nome sem ext e grava operacoes
  char opt;
  int i,j,k,m,n, xsup, ysup, xinf, yinf, dif =0, larguraJanela;
  int **M, **N;

  do
    {
      printf("Digite o nome do arquivo: ");
      scanf ("%s", filename);
      strcpy(filename_,filename);
      strcat(filename_,"_");
      strcat(filename,".pgm");
 
      M = AbreImagem(filename, &m, &n);
      
      if (M == NULL)
	printf("Arquivo invalido. ");
    }
  while (M == NULL);
  
  
  printf("c - carga\nt - exibicao na tela\nn - negativo\nr - rotacao\nv - espelhamento vertical\nh - espelhamento horizontal\nx - corte\ne - filtro da erosao\nd - filtro da dilatacao\nm - filtro da mediana\nM - filtro da media\n1 - filtro de bordas 1\n2 - filtro de bordas 2\n3 - filtro de bordas 3\ng - gravacao\nC - comparacao\na - ajuda\ns - sair\n");
  
  while (1)
    {    
    printf("\nDigite um comando: ");
    scanf (" %c", &opt);
    
    //carga
    if (opt == 'c'){
      do
	{
     printf("Digite o nome do arquivo: ");
     scanf ("%s", filename);
     strcpy(filename_,filename);
     strcat(filename_,"_");
     strcat(filename,".pgm");
     
     M = AbreImagem(filename, &m, &n);
     
      if (M == NULL)
	printf("Arquivo invalido. ");
	}
      while (M == NULL);
      
      opt = 'a';
    }
    
    //exibicao
    if (opt == 't'){
      printf("\nExibindo %s\n",filename);
      for (i=0; i < m; i++){
	for (j=0; j < n; j++){
	  printf(" %3d", M[i][j]);
	}
	printf("\n");
      }
    }
    
    //negativo
    else if (opt == 'n'){
      negativo(M, m, n);
      strcat(filename_,"n");
      printf ("Operacao realizada com sucesso.\n");
    }
    
    //rotacao
    else if (opt == 'r'){
      M = rotacao(M, &m, &n);
      strcat(filename_,"r");
      printf ("Operacao realizada com sucesso.\n");
    }
    
    //espelhahorizontal
    else if (opt == 'h'){
      rebatimentoHorizontal(M, m, n);
      strcat(filename_,"h");
      printf ("Operacao realizada com sucesso.\n");
    }

    //espelhavertcal
    else if (opt == 'v'){
      rebatimentoVertical(M, m, n);
      strcat(filename_,"v");
      printf ("Operacao realizada com sucesso.\n");
    }
    
    //corte
    else if (opt == 'x'){
      xsup = ysup = xinf = yinf = 0;
      while(1){
      printf("Informe x superior: ");
      scanf(" %d", &xsup);
      printf("Informe y superior: ");
      scanf(" %d", &ysup);
      printf("Informe x inferior: ");
      scanf(" %d", &xinf);
      printf("Informe y inferior: ");
      scanf(" %d", &yinf);
      if(xsup < 0 || xsup > m || ysup < 0 || ysup > n ||
	 xinf < xsup || xinf > m || yinf < ysup || yinf > n ||
	 xsup == xinf || ysup == yinf)
	printf("Coordenadas invalidas. \n");
      else
	break;
      }
      M = corte(M, &m, &n, xsup, ysup, xinf, yinf);
      strcat(filename_,"x");
      printf ("Operacao realizada com sucesso.\n");
    }
      //erosao
    else if (opt == 'e'){
	while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	  scanf(" %d",&larguraJanela);
	  if (larguraJanela < 3 || larguraJanela > 50)
	    printf("Largura Invalida.\n");
	  else
	    break;
	}
	  filtroErosao(M,m,n,larguraJanela);
	  strcat(filename_,"e"); 
	  printf ("Operacao realizada com sucesso.\n");
    }
      //dilatacao
    else if (opt == 'd'){
	while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	  scanf(" %d",&larguraJanela);
	  if (larguraJanela < 3 || larguraJanela > 50)
	    printf("Largura Invalida.\n");
	  else
	    break;
	}
	  filtroDilatacao(M,m,n,larguraJanela);
	  strcat(filename_,"d"); 
	  printf ("Operacao realizada com sucesso.\n");
    }
      //mediana
    else if (opt == 'm'){
	while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	  scanf(" %d",&larguraJanela);
	  if (larguraJanela < 3 || larguraJanela > 50)
	    printf("Largura Invalida.\n");
	  else
	    break;
	}
	  filtroMediana(M,m,n,larguraJanela);
	  strcat(filename_,"m");
	  printf("Operacao Realizada com sucesso.");
    }
      //media
    else if (opt == 'M'){
	while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	  scanf(" %d",&larguraJanela);
	  if (larguraJanela < 3 || larguraJanela > 50)
	    printf("Largura Invalida.\n");
	  else
	    break;
	}
	  filtroMedia(M,m,n,larguraJanela);
	  strcat(filename_,"M"); 
	  printf("Operacao Realizada com sucesso.");
    }
    //filtro1
    else if (opt == '1'){
      while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	scanf(" %d",&larguraJanela);
	printf("Digite k: ");
	scanf(" %d",&k);
	  if (larguraJanela < 3 || larguraJanela > 50 || k < 0 || k > 255)
	    printf("valores invalidos.\n");
	  else
	    break;
      }
      filtroBorda1(M,m,n,larguraJanela,k);
      strcat(filename_,"1"); 
      printf("Operacao Realizada com sucesso.");
       }
      //filtro2
    else if (opt == '2'){
	while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	scanf(" %d",&larguraJanela);
	printf("Digite k: ");
	scanf(" %d",&k);
	  if (larguraJanela < 3 || larguraJanela > 50 || k < 0 || k > 255)
	    printf("valores invalidos.\n");
	  else
	    break;
     	}
	filtroBorda2(M,m,n,larguraJanela,k);
	  strcat(filename_,"2"); 
	  printf("Operacao Realizada com sucesso.");
    }
    //filtro3
    else if (opt == '3'){
   	while(1){
	printf("Digite a largura de janela (min 3, max 50): ");
	scanf(" %d",&larguraJanela);
	printf("Digite k: ");
	scanf(" %d",&k);
	if (larguraJanela < 3 || larguraJanela > 50 || k < 0 || k > 255)
	  printf("valores invalidos.\n");
	else
	  break;
     	}
	filtroBorda3(M,m,n,larguraJanela,k);
	strcat(filename_,"3"); 
	printf("Operacao Realizada com sucesso.");
    }

      //gravacao
    else if (opt == 'g'){
      strcpy(filename,filename_);
      strcat(filename,".pgm");
      GravaImagem(filename, M, m, n);
    }

    //compara
    else if (opt == 'C'){
      do{
	printf("Digite o nome do arquivo: ");
	scanf ("%s", comp);
	strcat(comp,".pgm");
	
	N = AbreImagem(comp, &m, &n);
	
	if (N == NULL)
	  printf("Arquivo invalido. ");
      }
      while (N == NULL);
      
      for (i=0; i < m; i++)
	for (j=0; j < n; j++)
	  if(N[i][j] != M[i][j]){
	    dif = 1;
	    break;
	  }
      
      if(dif)
	printf("Arquivos diferentes.\n");
      else
	printf("Arquivos iguais.\n");

      dif = 0;    
      LiberaMatriz (N, m, n);
    }

    //ajuda
    else if (opt == 'a'){
      printf("c - carga\nt - exibicao na tela\nn - negativo\nr - rotacao\nv - espelhamento vertical\nh - espelhamento horizontal\nx - corte\ne - filtro da erosao\nd - filtro da dilatacao\nm - filtro da mediana\nM - filtro da media\n1 - filtro de bordas 1\n2 - filtro de bordas 2\n3 - filtro de bordas 3\ng - gravacao\nC - comparacao\na - ajuda\ns - sair\n");
    }

      //sair
    else if (opt == 's')
      break;
    else
      printf("Opcao Invalida. Digite Novamente: ");
  }

  LiberaMatriz(M,m,n);
 return 0;
}

int **AlocaMatriz(int m, int n)
{
  int **M;
  int i;
  
  M = (int **)malloc(m * sizeof(int *));
  for (i=0; i < m; i++)
    M[i] = (int *)malloc(n * sizeof(int));
     
  return M;
}

void LiberaMatriz(int** M, int m, int n)
{
  int i;

  for (i=0; i < m; i++)
    free(M[i]);
  free (M);

}


int** AbreImagem (char filename[], int* m, int* n)
{
  FILE *fp;
  int **M;
  int i, j;

  fp = fopen(filename,"r");
  if (fp == NULL)
    return NULL;

  //lendo as dimensoes da imagem
  fscanf (fp,"P2 %d %d 255", m, n);

  M = AlocaMatriz(*m, *n);
  
  for (i=0; i < *m; i++)
    for (j=0; j < *n; j++)
      fscanf(fp," %d", &M[i][j]);

  printf("%s (%d x %d) carregado com sucesso.\n",filename, *m, *n);

  fclose (fp);
  return M;
}

void GravaImagem(char filename[], int** M, int m, int n)
{
  FILE *fp;
  int i, j;
  fp = fopen (filename,"w");
  fprintf(fp,"P2\n%d %d\n255\n",m,n);

  for (i=0; i < m; i++){
    for (j=0; j < n; j++){
      fprintf(fp," %d", M[i][j]);
    }
      fprintf(fp," \n");
  }

  printf("%s gravado com sucesso.\n",filename);
  fclose (fp);
}

void negativo(int** M, int m, int n)
{
  int i, j;
 for (i=0; i < m; i++)
    for (j=0; j < n; j++)
      M[i][j] = 255 - M[i][j];
}

int** corte(int** M, int* m, int* n,int xsup, int ysup, int xinf, int yinf){
  int **corte;
  int i,j, newm, newn;

  newm = xinf-xsup;
  newn = yinf-ysup;

  corte = AlocaMatriz(newm,newn);

  for (i = 0; i < newm; i++)
    for(j = 0; j < newn; j++)
      corte[i][j] = M[i+xsup][j+ysup];
    

  LiberaMatriz (M, *m, *n);
  *m = newm;
  *n = newn;

  return corte;
}

void rebatimentoHorizontal(int** M, int m, int n){
  int tmp, i, j;

  for (i = 0; i < m ; i++){
    for(j = 0; j < n/2; j++){
      tmp = M[i][j];
      M[i][j] = M[i][(n-1)-j];
      M[i][(n-1)-j] = tmp;
    }
  }
}

void rebatimentoVertical(int** M, int m, int n){
  int tmp, i, j;

  for(j = 0; j < n; j++){
    for (i = 0; i < m/2 ; i++){
      tmp = M[i][j];
      M[i][j] = M[(m-1)-i][j];
      M[(m-1)-i][j] = tmp;
    }
  }
}

int** rotacao(int **M, int* m, int* n){
  int **img;
  int tmp, i, j;

  img = AlocaMatriz(*n, *m);

   for(i=0; i < *n; i++)
     for (j=0; j < *m; j++)
       img[i][j] = M[*m-j-1][i];

   LiberaMatriz (M, *n, *m);
  
  tmp = *m;
  *m = *n;
  *n = tmp;
  
  return img;
}

void filtroMediana(int** M, int m, int n, int larguraJanela){
  int** N; //matriz copia
  int *viz; //vetor da vizinhanca
  int tam = 4* larguraJanela*larguraJanela;
  int a=0; //tamanho do vetor atual
  int md; //valor da mediana
  int i, j, k;

  viz = (int*)malloc(tam*sizeof(int));
  N = CopiaMatriz(M,m,n);

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){      
      a = 0;
      for(k = larguraJanela; k >= 0 ; k-- ){
	
	if (i+k < m){
	  viz[a]= N[i+k][j];
	  a++;
	}
	if (i-k >= 0){
	  viz[a]= N[i-k][j];
	  a++;	
	}
	if (i+k < m && j+k < n){
	  viz[a] = N[i+k][j+k];
	  a++;		
	}
	if(i+k < m && j-k >= 0){ 
	  viz[a] = N[i+k][j-k];
	  a++;		
	}
	if(i-k >= 0 && j-k >= 0){ 
	  viz[a] = N[i-k][j-k];
	  a++;	
	}
	if(i-k >= 0 && j+k < n){ 
	  viz[a] = N[i-k][j+k];
	  a++;	
	}
	 if(j+k < n){
	   viz[a] = N[i][j+k];
	   a++;	
	 }
	 if(j-k >= 0){
	   viz[a]=N[i][j-k];
	   a++;	
	 }
      } 
      OrdenaVetor (viz, a);
      if (a%2)
	md = viz[a/2];
      else
	md = viz[(a+1)/2];
      
      M[i][j] = md;
    }
  }

  LiberaMatriz(N,m,n);
  free(viz);
}

void filtroMedia(int** M, int m, int n, int larguraJanela){
  int** N; //matriz copia
  int *viz; //vetor da vizinhanca
  int tam = 4* larguraJanela*larguraJanela;
  int a=0; //tamanho do vetor atual
  int soma; //valor da soma da media
  int i, j, k, l;

  viz = (int*)malloc(tam*sizeof(int));
  N = CopiaMatriz(M,m,n);

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){      
      a = 0;
      for(k = larguraJanela; k >= 0 ; k-- ){

	if (i+k < m){
	  viz[a]= N[i+k][j];
	  a++;
	}
	if (i-k >= 0){
	  viz[a]= N[i-k][j];
	  a++;	
	}
	if (i+k < m && j+k < n){
	  viz[a] = N[i+k][j+k];
	  a++;		
	}
	if(i+k < m && j-k >= 0){ 
	  viz[a] = N[i+k][j-k];
	  a++;		
	}
	 if(i-k >= 0 && j-k >= 0){ 
	   viz[a] = N[i-k][j-k];
	   a++;	
	 }
	if(i-k >= 0 && j+k < n){ 
	  viz[a] = N[i-k][j+k];
	  a++;	
	}
        if(j+k < n){
	  viz[a] = N[i][j+k];
	  a++;	
	}
        if(j-k >= 0){
	  viz[a]=N[i][j-k];
	  a++;	
	}
	
      } 
      for(l=0;l<=a;l++)
	soma+=viz[l];
      soma/=a;
      M[i][j] = soma;
    }
  }
  
  LiberaMatriz(N,m,n);
  free(viz);
}

void filtroErosao(int** M, int m, int n, int larguraJanela){
  int** N; //matriz copia
  int *viz; //vetor da vizinhanca
  int tam = 4* larguraJanela*larguraJanela;
  int a=0; //tamanho do vetor atual
  int min; //valor minimo
  int i, j, k, l;
  
  viz = (int*)malloc(tam*sizeof(int));
  N = CopiaMatriz(M,m,n);

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){      
      a = 0;
      
      for(k = larguraJanela; k >= 0 ; k-- ){
	
	if (i+k < m){
	  viz[a]= N[i+k][j];
	  a++;
	}
	if (i-k >= 0){
	  viz[a]= N[i-k][j];
	  a++;	
	}
	if (i+k < m && j+k < n){
	  viz[a] = N[i+k][j+k];
	  a++;		
	}
	if(i+k < m && j-k >= 0){ 
	  viz[a] = N[i+k][j-k];
	  a++;		
	}
	if(i-k >= 0 && j-k >= 0){ 
	  viz[a] = N[i-k][j-k];
	  a++;	
	}
	if(i-k >= 0 && j+k < n){ 
	  viz[a] = N[i-k][j+k];
	  a++;	
	}
        if(j+k < n){
	  viz[a] = N[i][j+k];
	  a++;	
	}
        if(j-k >= 0){
	  viz[a]=N[i][j-k];
	  a++;	
	}
	
      } 
      OrdenaVetor(viz,a);
      M[i][j] = viz[0];
    }
  }
  
  LiberaMatriz(N,m,n);
  free(viz);
}

void filtroDilatacao(int** M, int m, int n, int larguraJanela){
  int** N; //matriz copia
  int *viz; //vetor da vizinhanca
  int tam = 4* larguraJanela*larguraJanela;
  int a=0; //tamanho do vetor atual
  int i, j, k;
  
  viz = (int*)malloc(tam*sizeof(int));
  N = CopiaMatriz(M,m,n);
  
  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){      
      a = 0;
      
      for(k = larguraJanela; k >= 0 ; k-- ){
	
	if (i+k < m){
	  viz[a]= N[i+k][j];
	  a++;	
	}
	if (i-k >= 0){
	  viz[a]= N[i-k][j];
	  a++;	
	}
	if (i+k < m && j+k < n){
	  viz[a] = N[i+k][j+k];
	  a++;		
	}
	if(i+k < m && j-k >= 0){ 
	  viz[a] = N[i+k][j-k];
	  a++;		
	}
	if(i-k >= 0 && j-k >= 0){ 
	  viz[a] = N[i-k][j-k];
	  a++;	
	}
	if(i-k >= 0 && j+k < n){ 
	  viz[a] = N[i-k][j+k];
	  a++;	
	}
        if(j+k < n){
	  viz[a] = N[i][j+k];
	  a++;	
	}
        if(j-k >= 0){
	  viz[a]=N[i][j-k];
	  a++;	
	}
	
      } 
      OrdenaVetor(viz,a);
      M[i][j] = viz[a-1];
    }
  }
  
  LiberaMatriz(N,m,n);
  free(viz);
}

void limiarizacao(int** M, int m, int n, int k){
  int i, j;
  
  for (i = 0; i < m; i++){
    for (j = 0; j < n; j++){
      if (M[i][j] >= k)
	M[i][j] = 255;
      else
	M[i][j] = 0;
    }
  }
}

void filtroBorda1(int** M, int m, int n, int larguraJanela, int k){
  int **N,**O;
  int i, j;
  
  N = CopiaMatriz(M,m,n);
  O = CopiaMatriz(M,m,n);

  filtroDilatacao(N,m,n,larguraJanela);
  filtroErosao(O,m,n,larguraJanela);

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      M[i][j] = N[i][j]-O[i][j];

  limiarizacao(M, m,  n, k);

  LiberaMatriz(N, m, n);
  LiberaMatriz(O, m, n);

}

void filtroBorda2(int** M, int m, int n, int larguraJanela, int k){
  int **O;
  int i, j;

  O = CopiaMatriz(M,m,n);
  filtroErosao(O,m,n,larguraJanela);

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      M[i][j]-=O[i][j];

  limiarizacao(M, m,  n, k);
  LiberaMatriz(O, m, n);
}

void filtroBorda3(int** M, int m, int n, int larguraJanela, int k){
  int **N;
  int i, j;

  N = CopiaMatriz(M,m,n);
  filtroDilatacao(N,m,n,larguraJanela);

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      M[i][j]=N[i][j]-M[i][j];

  limiarizacao(M,m,n,k);
  LiberaMatriz(N, m, n);
}

int** CopiaMatriz(int **M, int m, int n){
  int **N, i, j;
  N =  AlocaMatriz(m,n);
  for(i = 0; i < m; i++)
    for(j = 0; j < n; j++)
      N[i][j] = M[i][j];
    
  return N;
}

void OrdenaVetor (int *vet, int n){
  int i,j,k,tmp;
  //implementacao de algoritmo por selecao simples
    for(i = n-1; i > 0; i--){
      k = 0;
      for(j = 1; j <= i; j++){
	if(vet[j] > vet[k])
	  k = j;
      }
      tmp = vet[i];
      vet[i] = vet[k];
      vet[k] = tmp;
    }
  }
