/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: mapa.h                                    *
* Descrição: Abre o arquivo de mapa e pega o mapa de *
* chão e o mapa de relevo. Desenha o mapa em suas    *
* diferentes camadas.                                *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponível sob licensa GPL.     *
******************************************************/

enum {
	arvore=0, mercado, parede_limpa, pizzaria, comercial, semaforo,
	parede_suja, embaixada, banca, hospital, saco_de_areia_vertical
	};

typedef struct _relevo{
/* Lógico */
	int x, y; /* Posição X e Y relativa ao cenário */
	int tipo; /* Tipo de relevo, para as outras funções saberem*/
	int solidez; /* 0 é fantasma, 1 é solido.*/
	int vida; /* Tipo um life */
	unsigned char explosao; /* tipo de imagem para explosao */

/* Estrutura de Dados */
	struct _relevo *prox; /* Lista encadeada*/

/* Imagem */
	SDL_Surface *img; /* Imagem com sprites */
	int largura, altura; /* Altura e Largura de cada sprite. */

/* Colisão */
	int  ix, iy; /* Ponto Superior esquerdo da fronteira de colisão */
	int fx,fy; /* Ponto Superior direito da fronteira de colisão */
} Relevo;


typedef struct _mapa {
/* Lógico */
	int x,y; /* Localização do mapa */
	int mapa[10][10];

/* Tijolos de imagem */
	SDL_Surface *img; /* Imagem com sprites */
	int largura, altura; /* Altura e Largura de cada sprite. */
}Mapa;

/* Proximos mapas. O norte tambem indica o primeiro mapa do jogo*/
char proximo_norte[255];
char proximo_leste[255];
char proximo_sul[255];
char proximo_oeste[255];

/* Lista encadeada */
Relevo *r_raiz;


/*
NOVO_RELEVO
Aloca um espaço na memória com um relevo e devolve sua localização através de um ponteiro.
tipo: tipo de relevo (árvore, prédio...).
x,y: posição no mapa.
*/
Relevo* novo_relevo(int tipo, int x , int y){
	/* Aloca o espaço para colocar o relevo*/
	Relevo *rlv = calloc( 1, sizeof( Relevo ) );

	/* Se não alocou, não tem memória. Cai fora.*/
	if(!rlv){ printf("Memória insuficiênte."); exit(1); }
	
	/* Põe algumas informações básicas da estrutura */
	rlv->prox = NULL;
	rlv->x = x; rlv->y = y;

	/* Trata cada tipo de relevo */
	switch(tipo){
		case arvore:{
			rlv->img = img_arvore;
			rlv->tipo = arvore;
			rlv->solidez = 1;
			rlv->vida = 2;
			rlv->ix = 11;
			rlv->iy = 22;
			rlv->fx = 22;
			rlv->fy = 31;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_simples;
			break;
		}
		case mercado:{
			rlv->img = img_mercado;
			rlv->tipo = mercado;
			rlv->solidez = 1;
			rlv->vida = 5;
			rlv->ix = 0;
			rlv->iy = 64;
			rlv->fx = 64;
			rlv->fy = 96;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_parede;
			break;
		}
		case parede_limpa:{
			rlv->img = img_parede_limpa;
			rlv->tipo = parede_limpa;
			rlv->solidez = 1;
			rlv->vida = 2;
			rlv->ix = 0;
			rlv->iy = 21;
			rlv->fx = 32;
			rlv->fy = 32;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_tijolos;
			break;
		}
		case parede_suja:{
			rlv->img = img_parede_suja;
			rlv->tipo = parede_suja;
			rlv->solidez = 1;
			rlv->vida = 2;
			rlv->ix = 0;
			rlv->iy = 21;
			rlv->fx = 32;
			rlv->fy = 32;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_tijolos;
			break;
		}
		case pizzaria:{
			rlv->img = img_pizzaria;
			rlv->tipo = pizzaria;
			rlv->solidez = 1;
			rlv->vida = 3;
			rlv->ix = 0;
			rlv->iy = 32;
			rlv->fx = 64;
			rlv->fy = 64;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_parede;
			break;
		}
		case comercial:{
			rlv->img = img_comercial;
			rlv->tipo = comercial;
			rlv->solidez = 1;
			rlv->vida = 5;
			rlv->ix = 0;
			rlv->iy = 64;
			rlv->fx = 64;
			rlv->fy = 96;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_parede;
			break;
		}
		case embaixada:{
			rlv->img = img_embaixada;
			rlv->tipo = embaixada;
			rlv->solidez = 1;
			rlv->vida = 5;
			rlv->ix = 0;
			rlv->iy = 64;
			rlv->fx = 64;
			rlv->fy = 96;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_parede;
			break;
		}
		case semaforo:{
			rlv->img = img_semaforo;
			rlv->tipo = semaforo;
			rlv->solidez = 0;
			rlv->vida = 1;
			rlv->ix = 12;
			rlv->iy = 24;
			rlv->fx = 21;
			rlv->fy = 30;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_simples;
			break;
		}
		case banca:{
			rlv->img = img_banca;
			rlv->tipo = banca;
			rlv->solidez = 1;
			rlv->vida = 2;
			rlv->ix = 0;
			rlv->iy = 22;
			rlv->fx = 32;
			rlv->fy = 32;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_simples;
			break;
		}
		case hospital:{
			rlv->img = img_hospital;
			rlv->tipo = hospital;
			rlv->solidez = 1;
			rlv->vida = 5;
			rlv->ix = 0;
			rlv->iy = 64;
			rlv->fx = 64;
			rlv->fy = 96;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_parede;
			break;
		}
		case saco_de_areia_vertical:{
			rlv->img = img_saco_de_areia_vertical;
			rlv->tipo = saco_de_areia_vertical;
			rlv->solidez = 1;
			rlv->vida = 1;
			rlv->ix = 1;
			rlv->iy = 3;
			rlv->fx = 28;
			rlv->fy = 30;
			rlv->largura = rlv->img->w;
			rlv->altura = rlv->img->h;
			rlv->explosao = explosao_fogo;
			break;
		}				
	}
	return rlv;
}

/*
NOVO_CHAO
Recebe um caminho de arquivo, posições x e y e retorna uma Chao.
nome_arquivo: Arquivo onde está o mapa.
x,y: posição do chão em relação à janela.
*/
Mapa novo_mapa(char *nome_arquivo,int x, int y){
	int i,j,novo_x,novo_y,tipo,nova_direcao;
	char preString[255];
	Mapa tmp;
	FILE *arquivo;
	Relevo *agulha;

	/* Cria um mapa e põe seus primeiros valores.*/
	tmp.x = x;
	tmp.y = y;
	tmp.largura = 32;
	tmp.altura = 32;
	tmp.img = img_mapa;

	/* Abre o exemplo.mapa para leitura */
	arquivo=fopen(nome_arquivo,"r");

	printf("abrindo %s ... ", nome_arquivo);

	/* Tratamento de erro */
	if (!arquivo){
		printf ("Erro\n");
		for(i=0;i<10;i++)
		for(j=0;j<10;j++){
			tmp.mapa[i][j]=0;
		}
		exit(1);
		return tmp;
	}

	/* Ler dados de chão */
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf( arquivo, "%d", &(tmp.mapa[i][j]) );
		}
	}	
	
	/* Le a posicao da antena */
	fscanf(arquivo,"%d %d", &pre_antena.x, &pre_antena.y);
	
	/* Le a posicao inicial do jogador */
	fscanf(arquivo, "%d %d", &pre_jogador.x, &pre_jogador.y);

	/* Ler agora o relevo, le o numero de elementos do relevo */
	fscanf( arquivo, "%d", &i);
		

	/* Para cada elemento, ele lê a localização dele e cria um relevo */
	for(j=0;j<i;j++){
		fscanf( arquivo,"%d %d %d",&tipo,&novo_x,&novo_y );

		if( r_raiz==NULL ){
			r_raiz = novo_relevo(tipo,
			32*novo_x,32*novo_y);
			agulha = r_raiz;
		} else {
			agulha->prox = 	novo_relevo(tipo,
			32*novo_x,32*novo_y);
			agulha = agulha->prox;
		}
	}
		
	/* Agora lê a lista de inimigos.*/
	fscanf( arquivo, "%d", &n_inimigos_da_fase);	
	for(j=0;j<n_inimigos_da_fase;j++){
		fscanf( arquivo,"%d %d %d %d", &tipo, &novo_x, &novo_y, &nova_direcao);
		inimigos[j].tipo = tipo;
		inimigos[j].x = novo_x;
		inimigos[j].y = novo_y;
		inimigos[j].direcao = nova_direcao;
	}
	
	/* Le as setas que seram colocadas depois que a fase acabar*/
	fscanf( arquivo, "%d", &n_setas_da_fase);	
	for(j=0;j<n_setas_da_fase;j++){
		fscanf( arquivo,"%d %d %d %d",&tipo,&novo_x,&novo_y, &nova_direcao);
		setas[j].tipo = tipo;
		setas[j].x = novo_x;
		setas[j].y = novo_y;
		setas[j].direcao = nova_direcao;
	}
		
	/* Le as proximas fases */
	fscanf( arquivo, "%d", &i);	
	for(j=0;j<i;j++){
		fscanf(arquivo, "%d", &nova_direcao);		
		switch (nova_direcao){
			case 0:{
				fscanf(arquivo, "%s", proximo_norte);	
				break;
				}
			case 1:{
				fscanf(arquivo, "%s", proximo_leste);				
				break;
				}
			case 2:{
				fscanf(arquivo, "%s", proximo_sul);				
				break;
				}
			case 3:{
				fscanf(arquivo, "%s", proximo_oeste);					
				break;
				}
		}		
	}
	
	indice_inimigos = 0;
	n_inimigos_mortos = 0;
	printf("ok\n");
	
	fclose(arquivo);

	
	return tmp;
}


/*
DESENHA_CHAO
Recebe um Chao e o desenha.
ch: Chao a ser desenhado.
*/
void desenha_mapa_chao(Mapa *mp){
	int i,j;
	SDL_Rect fonte,dest;

	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fonte.x = (mp->mapa[i][j]%10) * mp->largura;
			fonte.y = ((int)(mp->mapa[i][j]/10)) * mp->altura;
			fonte.w = mp->largura;
			fonte.h = mp->altura;

			dest.x= xoff + j*mp->largura;
			dest.y= yoff + i*mp->altura;
			dest.w= mp->largura;
			dest.h= mp->altura;
			SDL_BlitSurface(mp->img, &fonte, tela, &dest);
		}
	}
}

void desenha_relevo(Relevo *r){
	SDL_Rect fonte,dest;

	fonte.x = 0;
	fonte.y = 0;
	fonte.w = r->img->w;
	fonte.h = r->img->h;

	dest.x= xoff + r->x;
	dest.y= yoff + r->y;
	dest.w= r->img->w;
	dest.h= r->img->h;
	SDL_BlitSurface(r->img, &fonte, tela, &dest);

	//r = r->prox;
}


/*
PINTA_LISTA
pinta a lista na tela.
*/
void pinta_lista(Mapa *mp){
	SDL_Rect fonte,dest;
	Relevo *r = r_raiz;

	while(r!=NULL){
		fonte.x = 0;
		fonte.y = 0;
		fonte.w = r->img->w;
		fonte.h = r->img->h;

		dest.x= r->x;
		dest.y= r->y;
		dest.w= r->img->w;
		dest.h= r->img->h;
		SDL_BlitSurface(r->img, &fonte, tela, &dest);

		r = r->prox;
	}
}

/*
TIRA_DA_LISTA_RELEVO
Recebe um Relevo r e retira ele da lista encadeada de relevos
*/
void tira_da_lista_relevo(Relevo *r){
	Relevo *p, *aux;
	if(r_raiz == NULL) return;
	if(r_raiz == r){
		Relevo *aux = r_raiz;
		r_raiz = r_raiz->prox;
		free(aux);
		return;
	}
	p = r_raiz;
	while(p!=NULL){
		aux = p;
		p = p->prox;
		if(p == r){
			aux->prox = p->prox;
			free(p);	    
			return;
		}
    }
}

/*
DESTROI_LISTA_RELEVO
r: raiz da lista a ser destruida;
*/
void destroi_lista_relevo(Relevo *r){
	Relevo *agulha1 = r, *agulha2 = r;

	/* Percorre a lista e sai destruindo */
	while(agulha1!=NULL){
		agulha2 = agulha1;
		agulha1=agulha1->prox;
		free(agulha2);
	}
	r_raiz = NULL;

	/* Diz que destruiu */
	printf("Memoria dos relevos liberada.\n");
}

/*
LEVOU_TIRO_RELEVO
Recebe uma unidade que levou um tiro, diminui o life dela e eventualmente a destroi. Essa funcao nao deveria estar aqui mas esta porque precisa conhecer as unidades.
*/
void levou_tiro_relevo(Relevo *r){
	if(--r->vida==0) tira_da_lista_relevo(r);
}
