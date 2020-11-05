/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: unidade.h                                 *
* Descricao: Arquivo com a definicao de unidade      *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponivel sob licensa GPL.     *
******************************************************/

enum estados { perseguir=0, entrar_em_campo, bate_e_gira};

typedef struct _Unidade {
/* Logico */
	int x,y; /* Localizacao no cenerio */
	char direcao; /* Direcao do movimento da unidade */
	char velocidade; /* Velocidade da unidade*/
	int tipo; /* O tipo de unidade. Para as outras funcoes saberem */
	unsigned char ligado; /* ligado==0 indica que estao parado */
	unsigned int temperatura; /* Delay para proximo tiro */
	unsigned char explosao; /* tipo de imagem para explosao */
	unsigned char solidez; /* tipo de imagem para explosao */
	unsigned char inteligente; /* 1 se tem IA */
	char estado; /* Estado do comportamento */
	unsigned char n_tiros; /* numero de tiros que ja deu */
	unsigned char delay_tiros; /* Espaco de tempo entre os tiros */
	unsigned char max_tiros; /* numero de tiros que pode dar */
	unsigned char vida; /* Tipo um life */

/* Sprite */
	SDL_Surface *img; /* Imagem com sprites */
	unsigned char n_quadros; /* Numero de quadros da animacao.(Linhas) */
	unsigned char quadro; /* Quadro atual */
	unsigned char n_modos; /* Numero de modos da animacao.Ex: Norte, Sul. (Colunas)*/
	unsigned char modo; /* Modo atual */
	unsigned char rapidez; /* Velocidade da animacao */
	unsigned char largura, altura; /* Altura e Largura de cada sprite. */

/* Colisao */
	int  ix, iy; /* Ponto Superior esquerdo da fronteira de colisao */
	int fx,fy; /* Ponto Superior direito da fronteira de colisao */

/* Estrutura de Dados */
	struct _Unidade	*prox; /* Lista encadeada */
	struct _Unidade	*dono; /* Um tiro pode ter um dono */
}Unidade;

/* Uma estrutura com um ponteiro para Unidade e para um Relevo. Ele diz em quem voce colidiu. */
typedef struct _Resposta {
	Unidade *u; /* Unidade em que colidiu */
	Relevo *r; /* Relevo em que colidiu */
} Resposta;

/* Aponta para a cauda da lista */
Unidade *u_fim=NULL;
Unidade *u_raiz=NULL;

/* Unidades do jogo */
Unidade *jogador;
Unidade *antena1;


/*
SENO e COSSENO
Uma pequena trapaça. Olha o angulo e dá o seno e cosseno de de cabeça. O(1).

ParÃƒÂ¢metros:
direcao: a direcao do tanque.
*/
int seno(int direcao){
	return direcao%2==0?direcao-1:0;
}

int cosseno(int direcao){
	return direcao%2?2-direcao:0;
}


/*
LIGA
DESLIGA
Setar o ligado para 0 ou 1. SÃƒÂ³ para ficar mais elegante.

u: unidade em questÃƒÂ£o.
*/
void liga(Unidade *u){
	u->ligado = 1;
}

void desliga(Unidade *u){
	u->ligado = 0;
}

/*
MOSTRA_LISTA
Mostra no terminal o conteÃƒÂºdo da lista encadeada.
*/
void mostra_lista_unidade(Unidade *raiz){
	Unidade *p = raiz;
	printf("U");
	while(p!=NULL){
		if(u_raiz==p){
			printf("->{%d,%d}", p->x, p->y);
		}else{
			if(u_fim==p){
				printf("->(%d,%d)", p->x, p->y);
			} else {
				printf("->[%d,%d]", p->x, p->y);
			}
		}
		p = p->prox;
	}
	printf("-|\n");
}

/*
TIRA DA LISTA
Retira u da lista e libera a posiÃ§Ã£o de memÃ³ria.
u: unidade a ser retirada da lista encadeada.
*/
void tira_da_lista_unidade(Unidade *u){
	Unidade *p, *aux;
	if(u_raiz == NULL) return;
	if(u_raiz == u){
		Unidade *aux = u_raiz;
		u_raiz = u_raiz->prox;
		free(aux);
		return;
	}
	p = u_raiz;
	while(p!=NULL){
		aux = p;
		p = p->prox;
		if(p == u){
			aux->prox = p->prox;
			free(p);
			if(aux->prox == NULL) u_fim = aux;
			return;
		}
	}
}

/*
DESTROI_LISTA_UNIDADE
u: raiz da lista a ser destruida;
*/
void destroi_lista_unidade(Unidade *u){
	Unidade *agulha1 = u, *agulha2 = u;

	/* Percorre a lista e sai destruindo */
	while(agulha1!=NULL){
		agulha2 = agulha1;
		agulha1=agulha1->prox;
		free(agulha2);
	}
	
	u_raiz = NULL;
	u_fim = u_raiz;

	/* Diz que destruiu */
	printf("Memoria das unidades liberada.\n");
}

Unidade* nova_unidade_a_partir_de_preunidade(Pre_unidade *pu){
	/* Aloca o espaco para colocar o Unidade*/
	Unidade *uni = calloc(1,sizeof(Unidade) );

	/* Se nao alocou, não tem memória. Cai fora.*/
	if(!uni){ printf("Memória insuficiente."); exit(1); }

	/* Poe algumas informacoes basicas da estrutura */
	uni->prox = NULL;

	/* Constroi a lista encadeada */
	if(u_fim==NULL){
		u_raiz = uni;
		u_fim = uni;
	} else {
		u_fim->prox = uni;
		u_fim = uni;
		u_fim->prox = NULL;
	}
	
	switch(pu->tipo){	
		case perseguidor:{
			uni->img = img_inimigo;
			uni->tipo = pu->tipo;
			uni->estado = entrar_em_campo;
			uni->ligado = 1;
			uni->solidez = 1;
			uni->inteligente = 1;
			uni->vida = VIDA_TANQUE_INIMIGO;
			uni->x = pu->x;
			uni->y = pu->y;			
			uni->n_tiros = 0;
			uni->temperatura = 0;			
			uni->max_tiros = 2;	
			uni->delay_tiros = 30;	
			uni->n_quadros = 5;
			uni->quadro = 0;
			uni->n_modos = 4;
			uni->modo = 0;
			uni->direcao = pu->direcao;
			uni->velocidade = 1;		
			uni->rapidez = 1;		
			uni->largura = 40;
			uni->altura = 40;
			uni->explosao = explosao_fogo;		
			uni->ix = 0;
			uni->iy = 10;		
			uni->fx = 40;
			uni->fy = 35;
			return uni;
		}
		
		case seta_vermelha:{
			uni->explosao = explosao_simples;
			uni->img = img_setas_vermelhas;
			uni->tipo = seta_vermelha;
			uni->ligado = 0;
			uni->solidez = 1;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = pu->x;
			uni->y = pu->y;	
			uni->n_quadros = 7;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 23;
			uni->altura = 23;
			uni->direcao = pu->direcao;
			uni->ix = 8;
			uni->iy = 4;
			uni->fx = 13;
			uni->fy = 9;
			return uni;
		}
		
		case seta_verde:{
			uni->explosao = explosao_simples;
			uni->img = img_setas_verdes;
			uni->tipo = seta_verde;
			uni->ligado = 0;
			uni->solidez = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = pu->x;
			uni->y = pu->y;	
			uni->n_quadros = 7;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 23;
			uni->altura = 23;
			uni->direcao = pu->direcao;
			uni->ix = 8;
			uni->iy = 4;
			uni->fx = 13;
			uni->fy = 9;
			return uni;
		}
	}
	
}

/*
NOVA_UNIDADE
Recebe um tipo de unidade, o xy e pronto.

Parametros:
tipo: tipo de unidade. x,y: posicao relativa ao cenario. 
dono: dono do tiro
*/

Unidade* nova_unidade(int tipo, int x, int y, Unidade *dono){
	/* Aloca o espaco para colocar o Unidade*/
	Unidade *uni = calloc(1,sizeof(Unidade) );

	/* Se nao alocou, não tem memória. Cai fora.*/
	if(!uni){ printf("Memória insuficiente."); exit(1); }

	/* Poe algumas informacoes basicas da estrutura */
	uni->prox = NULL;
	/* Posicao x e y*/
	uni->x = x; uni->y = y;

	/* Constroi a lista encadeada */
	if(u_fim==NULL){
		u_raiz = uni;
		u_fim = uni;
	} else {
		u_fim->prox = uni;
		u_fim = uni;
		u_fim->prox = NULL;
	}

	/* Para cada tipo de unidade, um tratamento diferente */
	switch(tipo){
	    case tanque:{
			uni->img = img_tanque;
			uni->tipo = tanque;
			uni->ligado = 0;
			uni->delay_tiros = 30;
			uni->solidez = 1;
			uni->inteligente = 0;
			uni->vida = VIDA_TANQUE_JOGADOR;
			uni->x = x;
			uni->y = y;
			uni->n_tiros = 0;
			uni->max_tiros = N_BALAS_DO_JOGADOR;		
			uni->n_quadros = 5;
			uni->quadro = 0;
			uni->n_modos = 4;
			uni->modo = 0;
			uni->direcao = leste;
			uni->velocidade = 2;
			uni->rapidez = 1;
			uni->largura = 40;
			uni->altura = 40;
			uni->explosao = explosao_fogo;
			
			uni->ix = 0;
			uni->iy = 10;		
			uni->fx = 40;
			uni->fy = 35;	
			return uni;
	    }
	    
	    case perseguidor:{
			uni->img = img_inimigo;
			uni->tipo = perseguidor;
			uni->estado = entrar_em_campo;
			uni->ligado = 1;
			uni->solidez = 1;
			uni->inteligente = 1;
			uni->vida = VIDA_TANQUE_INIMIGO;
			uni->x = x;
			uni->y = y;			
			uni->n_tiros = 0;
			uni->temperatura = 0;			
			uni->max_tiros = 2;	
			uni->delay_tiros = 30;	
			uni->n_quadros = 5;
			uni->quadro = 0;
			uni->n_modos = 4;
			uni->modo = 0;
			uni->direcao = aleatorio(norte,oeste);
			uni->velocidade = 1;		
			uni->rapidez = 1;		
			uni->largura = 40;
			uni->altura = 40;
			uni->explosao = explosao_fogo;
			
			uni->ix = 0;
			uni->iy = 10;		
			uni->fx = 40;
			uni->fy = 35;
			return uni;
		}	
	
	    case antena:{
			uni->img = img_antena;
			uni->tipo = antena;
			uni->ligado = 1;
			uni->solidez = 1;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x;
			uni->y = y;
			uni->n_tiros = 0;
			uni->max_tiros = 0;
			uni->n_quadros = 20;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;		
			uni->velocidade = 0;
			uni->rapidez = 1;		
			uni->largura = 32;
			uni->altura = 32;
			uni->explosao = explosao_fogo;
			
			uni->ix = 9;
			uni->iy = 17;		
			uni->fx = 26;
			uni->fy = 32;
			return uni;
	    }
	    case tiro_canhao:{
			uni->img = img_tiro_canhao;
			uni->tipo = tiro_canhao;
			uni->ligado = 0;
			uni->solidez = 1;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->dono = dono;
			uni->x = x;
			uni->y = y;
			uni->n_tiros = 0;
			uni->max_tiros = 0;
			uni->n_quadros = 0;
			uni->quadro = 0;
			uni->n_modos = 4;
			uni->modo = 0;
			uni->direcao = dono->direcao;
			uni->velocidade = 3;
			uni->rapidez = 1;
			uni->largura = 5;
			uni->altura = 10;
			uni->explosao = explosao_simples;
			
			uni->ix = 1;
			uni->iy = 3;
			uni->fx = 4;
			uni->fy = 6;
			
			return uni;
	    }
	    case explosao_simples:{
			uni->explosao = explosao_simples;
			uni->img = img_explosao_simples;
			uni->tipo = explosao_simples;
			uni->solidez = 0;
			uni->ligado = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x-5;
			uni->y = y-5;
			uni->n_quadros = 7;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 10;
			uni->altura = 10;
			uni->ix = 0;
			uni->iy = 0;
			uni->fx = 0;
			uni->fy = 0;
			return uni;
	    }

	    case explosao_tijolos:{
			uni->img = img_explosao_tijolos;
			uni->tipo = explosao_tijolos;
			uni->ligado = 0;
			uni->solidez = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x-17;
			uni->y = y-12;
			uni->n_quadros = 15;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 32;
			uni->altura = 20;
			uni->ix = 0;
			uni->iy = 0;
			uni->fx = 0;
			uni->fy = 0;
			return uni;
		}

		case explosao_parede:{
			uni->explosao = explosao_simples;
			uni->img = img_explosao_parede;
			uni->tipo = explosao_parede;
			uni->ligado = 0;
			uni->solidez = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x-17;
			uni->y = y-12;
			uni->n_quadros = 15;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 28;
			uni->altura = 20;
			uni->ix = 0;
			uni->iy = 0;
			uni->fx = 0;
			uni->fy = 0;
			return uni;
		}
		case explosao_fogo:{
			uni->explosao = explosao_simples;
			uni->img = img_explosao_fogo;
			uni->tipo = explosao_fogo;
			uni->ligado = 0;
			uni->solidez = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x-17;
			uni->y = y-12;
			uni->n_quadros = 20;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 32;
			uni->altura = 32;
			uni->ix = 0;
			uni->iy = 0;
			uni->fx = 0;
			uni->fy = 0;
			return uni;
		}
		case explosao_areia:{
			uni->explosao = explosao_simples;
			uni->img = img_explosao_areia;
			uni->tipo = explosao_areia;
			uni->ligado = 0;
			uni->solidez = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x-17;
			uni->y = y-12;
			uni->n_quadros = 5;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 29;
			uni->altura = 32;
			uni->ix = 0;
			uni->iy = 0;
			uni->fx = 0;
			uni->fy = 0;
			return uni;
		}		
		case seta_vermelha:{
			uni->explosao = explosao_simples;
			uni->img = img_setas_vermelhas;
			uni->tipo = seta_vermelha;
			uni->ligado = 0;
			uni->solidez = 1;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x;
			uni->y = y;
			uni->n_quadros = 7;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 23;
			uni->altura = 23;
			uni->ix = 8;
			uni->iy = 4;
			uni->fx = 13;
			uni->fy = 9;
			return uni;
		}
		case seta_verde:{
			uni->explosao = explosao_simples;
			uni->img = img_setas_verdes;
			uni->tipo = seta_verde;
			uni->ligado = 0;
			uni->solidez = 0;
			uni->inteligente = 0;
			uni->vida = 1;
			uni->x = x;
			uni->y = y;
			uni->n_quadros = 7;
			uni->quadro = 0;
			uni->n_modos = 1;
			uni->modo = 0;
			uni->rapidez = 1;
			uni->largura = 23;
			uni->altura = 23;
			uni->ix = 8;
			uni->iy = 4;
			uni->fx = 13;
			uni->fy = 9;
			return uni;
		}
	}
	
}

/* Inicializa um novo inimigo */
void novo_inimigo(){
	if(indice_inimigos<n_inimigos_da_fase){
		nova_unidade_a_partir_de_preunidade(&inimigos[indice_inimigos]);
		indice_inimigos++;
	}
}

/* COLOCA_SETAS
Poe as setas quando a fase termina 
*/
void coloca_setas(){
	int i;
	for(i=0;i<n_setas_da_fase;i++){
		nova_unidade_a_partir_de_preunidade(&setas[i]);
	}
	
}

/* Inicializa novo jogador (quando jogador morre) */
void novo_jogador(){
	n_vidas_perdidas++;
	/* Verifica se ja deu gameover */
	if(n_vidas_perdidas<n_vidas){
		jogador->x = pre_jogador.x;
		jogador->y = pre_jogador.y;
		jogador->vida = VIDA_TANQUE_JOGADOR;		
	}else{
		fim = 1;
	}
}

/*
ATIRA
Unidade u atira.
*/
void atira(Unidade *u){
	//return;
	/* Algumas constantes ficaram aqui para nao poluir ainda mais a 
	estrutura Unidade. Sao os offsets do tiro. */
	if((u->n_tiros < u->max_tiros)&&(u->temperatura==0)){
		if(u->direcao==norte)
			nova_unidade(tiro_canhao, u->x+17, u->y-3, u);
		if(u->direcao==leste)
			nova_unidade(tiro_canhao, u->x+45, u->y+11, u);
		if(u->direcao==sul)
			nova_unidade(tiro_canhao, u->x+17, u->y+38, u);
		if(u->direcao==oeste)
			nova_unidade(tiro_canhao, u->x-10, u->y+11, u);
		u->n_tiros++;
		u->temperatura=calor_tiro_simples;
	}
}


/*
DESENHA UNIDADE
Recebe uma unidade u e faz o que tem que fazer. :D

Parametros:
u: uma unidade
*/
void desenha_unidade(Unidade *u){
	SDL_Rect fonte, destino;

	/* Verifica se existe uma imagem na unidade */
	if(u->img){
		fonte.x = (u->largura)*(u->direcao);
		fonte.y=(u->altura)*(u->quadro);
		fonte.w = u->largura;
		fonte.h = u->altura;

		destino.x = xoff+ u->x;
		destino.y = yoff+ u->y;
		destino.w = u->largura;
		destino.h = u->altura;
		SDL_BlitSurface( u->img, &fonte, tela, &destino );
	}else{
		printf("\n[ERRO] Parametro Nulo, em funcao desenha_unidade\n");
		exit(1);
	}	
}

/*
LEVOU_TIRO_UNIDADE
Tratamento de tiro levado por unidade
*/
void levou_tiro_unidade(Unidade *u){
	int i;	
	
	switch(u->tipo){
		case perseguidor:{
			/* Explode */
			if(--u->vida==0){			
				for(i=0;i<5;i++){
				nova_unidade(u->explosao,
					u->x+20+aleatorio(-10,10),
					u->y+20+aleatorio(-10,10), NULL);
			}
			tira_da_lista_unidade(u);
			
			/* Chama outro tanque */
			novo_inimigo();
			
			/* Conta como inimigo destruido */
			n_inimigos_mortos++;		
			
			/* Pontua */
			pontos += PONTOS_TANQUE_INIMIGO;			
			
			/* Fim da fase? */
			if (n_inimigos_mortos == n_inimigos_da_fase){					coloca_setas();
			}
			
			}			
			break;
		}
		
		case antena:{
			/* Termina a partida */
			fim=1; 
			break;
		}
		
		case tanque:{
			if(--u->vida==0){
				/* Explode */
				for(i=0;i<5;i++){
				nova_unidade(u->explosao,
				u->x+20+aleatorio(-10,10),
				u->y+20+aleatorio(-10,10), NULL);
				}
				
				/* Morre */
				novo_jogador();
			}
			break;
		}
	}
}


/*
HOUVE_COLISAO
Recebe uma unidade, uma lista de unidade, uma lista de relevos e verifica se houve alguma coisao.
x,y,lar,alt:  Retangulo a ser considerado em todas as colisoes.
tal: unidade em questÃƒÂ£o. Para verificar se ela nao colidiu com ela mesma.
lista_u: Lista encadeada de unidades para serem testadas.
lista_r: Lista encadeada de relevos para serem testados.
*/
Resposta* houve_colisao(int x1, int y1, int x2, int y2, Unidade *tal){
	/* Ponteiros para percorrer a unidade */
	 Relevo *p_r = r_raiz;
	 Unidade *p_u = u_raiz;
	/* Resposta temporaria */
	Resposta *tmp = malloc(sizeof(Resposta));
	if(tmp == NULL){
	    printf("Erro alocando resposta...");
	    exit(1);
	}
	tmp->u = NULL;
	tmp->r = NULL;

	/* Checa se tem alguma coisa na unidade tal*/
	if (tal!=NULL){
		/* Primeiro checa colisoes com o relevo.
		Percorre a lista de relevos e se encontra uma unica colisao
		sai da funao retornando 1. */
		while(p_r!=NULL){
			if((colisao( x1 , y1, x2, y2,
				p_r->x + p_r->ix, p_r->y + p_r->iy,
				p_r->x + p_r->fx, p_r->y + p_r->fy))
				&&(p_r->solidez>0)){
					tmp->r = p_r;
					return(tmp);
				}
			p_r = p_r->prox;
		}

		/* Percorre a lista de unidades. Verificando se ele colidiu
		com alguem. Se ele colidiu, verifica se ele nao colidiu com
		ele mesmo (o que sempre vai ocorrer). Se houver uma colisao
		retorna 1. */

		while(p_u!=NULL){
			if((colisao( x1 , y1, x2, y2,
				p_u->x + p_u->ix, p_u->y + p_u->iy,
				p_u->x + p_u->fx, p_u->y + p_u->fy))
				&&(p_u!=tal)&&(p_u->solidez>0)){
					tmp->u = p_u;
					return(tmp);
				}
			p_u = p_u->prox;
		}
	}
	return(tmp);
}

/*
DENTRO_DO_CENARIO
Recebe um x,y e verifica se estao dentro do cenario
*/
int dentro_do_cenario(Unidade *u){
	int p_x = u->x + u->velocidade*cosseno(u->direcao);
	int p_y = u->y + u->velocidade*seno(u->direcao);
	return ((p_x<0)||
			(p_y<0)||
			(p_x>320-u->largura)||
			(p_y>320-u->altura+10));	
}

/*
UNIDADE_ANDA
Recebe uma unidade e faz ela andar.
u: uma unidade
Retorna a proxima unidade daquele u.
*/
void anda_unidade(Unidade *u, Mapa *mp){
	int p_x = u->x, p_y = u->y; /* Proximos x e y */
	int colidiu = 0; /* 0 se nao colidiu, 1 se colidiu. */
	Resposta *resp = NULL;

	/*Mostra lista */
	//mostra_lista_unidade(u_raiz);

	switch(u->tipo){
		/* Trata o tipo tanque */
		case tanque:{
			if(u->temperatura>0)
				u->temperatura--;

			if(u->ligado){
				/* Atualiza a localizacao */
				p_x += u->velocidade*cosseno(u->direcao);
				p_y += u->velocidade*seno(u->direcao);

				/* Verifica se esta dentro dos limites do cenario */
				colidiu = dentro_do_cenario(u);
				
				/* Verifa colisao */
				resp = houve_colisao(
				 p_x + u->ix , p_y + u->iy,
				 p_x + u->fx,  p_y + u->fy, u);

				/* Se um dos dois e nao nulo. Colidiu.*/
				colidiu|=(resp->u)||(resp->r);

				/* Tratamento da colisao */
				if(!colidiu){
					/* Nao colidiu */
					u->x = p_x;
					u->y = p_y;
				}
				
				/* Seta de fim de fase */
				if(resp->u)
					if(resp->u->tipo==seta_vermelha){
						fim_da_fase = 1;
						direcao_proxima_fase = resp->u->direcao;
					}

				u->quadro = (u->quadro+1)%u->n_quadros;
			}
			break;
		}

		/* Trata o tipo perseguidor */
		case perseguidor:{
			if(u->temperatura > 0)
				u->temperatura--;
			if(u->ligado){
				/* Atualiza a localizacao */
				p_x += u->velocidade*cosseno(u->direcao);
				p_y += u->velocidade*seno(u->direcao);

				/* Verifica se esta dentro
				dos limites do cenario */
				if(u->estado != entrar_em_campo){
					colidiu = dentro_do_cenario(u);
				}

				/* Verifa colisao */
				resp = houve_colisao(
					p_x + u->ix , p_y + u->iy,
					p_x + u->fx,  p_y + u->fy, u);

				/* Se um dos dois eh nao nulo. Colidiu.*/
				colidiu|=(resp->u)||(resp->r);						 
				
				if(!colidiu){
					/* Nao colidiu */
					u->x = p_x;
					u->y = p_y;
				} else { /* Colidiu */
					desliga(u);
				}
				/* Atualia o sprite*/
				u->quadro = (u->quadro+1)%u->n_quadros;
			}
			break;
		}

		case antena:{
			u->quadro = (u->quadro+1)%u->n_quadros;
			break;
		}

		case explosao_simples:{
			u->quadro++;
			if(u->quadro>u->n_quadros)tira_da_lista_unidade(u);
				break;
		}

		case explosao_tijolos:{
			u->quadro++;
			if(u->quadro>u->n_quadros)tira_da_lista_unidade(u);
			break;
		}
	
		case explosao_parede:{
			u->quadro++;
			if(u->quadro>u->n_quadros)tira_da_lista_unidade(u);
			break;
		}
		
		case explosao_fogo:{
			u->quadro++;
			if(u->quadro>u->n_quadros)tira_da_lista_unidade(u);
			break;
		}
		
		case explosao_areia:{
			u->quadro++;
			if(u->quadro>u->n_quadros)tira_da_lista_unidade(u);
			break;
		}		
		
		case seta_vermelha:{
			u->quadro = (u->quadro+1)%u->n_quadros;
			break;
		}	
		
		case seta_verde:{
			u->quadro = (u->quadro+1)%u->n_quadros;
			break;
		}	
		
		case tiro_canhao:{
				/* Atualiza a localizacao */
				p_x += u->velocidade*cosseno(u->direcao);
				p_y += u->velocidade*seno(u->direcao);

				/* Verifica se esta dentro dos limites do cenario */
				colidiu = dentro_do_cenario(u);

				/* Verifa colisao */
				resp = houve_colisao(
				 p_x + u->ix , p_y + u->iy,
				 p_x + u->fx,  p_y + u->fy, u);

				/* Se um dos dois eh nao nulo. Colidiu.*/
				colidiu|=(resp->u)||(resp->r);			

				/* Tratamento da colisao */
				if(!colidiu){
					/* Nao colidiu */
					u->x = p_x;
					u->y = p_y;
				}else{
					/* Avisa o colidido que ele levou um tiro (relevo)*/
					if(resp->r)
						levou_tiro_relevo(resp->r);

					/* Avisa o colidido que ele levou um tiro (unidade)*/
					/* Se nao foi um inteligente que atirou 
					num inteligênte, entao levou tiro.
					Inteligênte aqui eh IA. */
					if(resp->u)
						if
						(!((u->dono->inteligente)&&
						(resp->u->inteligente)))
						levou_tiro_unidade(resp->u);
					
					/* Adiciona a explosao */
					if(resp->r)
						nova_unidade(resp->r->explosao, u->x, u->y, NULL);
					if(resp->u)
						nova_unidade(resp->u->explosao, u->x, u->y, NULL);

					/* Destroi o tiro */
					tira_da_lista_unidade(u);
					u->dono->n_tiros--;
				}
			break;
		}
	}
	if(resp != NULL)free(resp);
}

/*
UNIDADE_GIRA_90
UNIDADE_GIRA_180
UNIDADE_GIRA_270
Recebe uma unidade e gira a direcao dela
*/
void unidade_gira_90(Unidade *u){
	if (u->direcao<3) u->direcao++;
		else u->direcao=0;
	u->modo = u-> direcao;
}

void unidade_gira_180(Unidade *u){
	if(u->direcao<2) u->direcao+=2;
	    else u->direcao-=2;
	u->modo = u-> direcao;
}

void unidade_gira_270(Unidade *u){
	if(u->direcao==0) u->direcao=3;
		else u->direcao-=1;
	u->modo = u-> direcao;
}

/*
PARA_ESQUERDA
PARA_DIREITA
PARA_CIMA
PARA_BAIXO
Recebe uma unidade e poe na direcao indicada pelo nome da funcao

u: unidade em questao.
*/
void para_esquerda(Unidade *u){
	u->direcao =oeste;
	u->modo = u-> direcao;
}

void para_direita(Unidade *u){
	u->direcao = leste;
	u->modo = u-> direcao;
}

void para_cima(Unidade *u){
	u->direcao = norte;
	u->modo = u-> direcao;
}

void para_baixo(Unidade *u){
	u->direcao = sul;
	u->modo = u-> direcao;
}
