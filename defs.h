/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: defs.h                                    *
* Descrição: definições do jogo (constantes e        * 
* algumas funções)                                   *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
******************************************************/

#define aleatorio(low,high) ((rand() % ((high)-(low)+1))+(low))
#define umouzero() (rand()%2)
#define MAX_TANQUES 10
#define VIDA_TANQUE_INIMIGO 2
#define VIDA_TANQUE_JOGADOR 1
#define N_BALAS_DO_JOGADOR 2
#define PONTOS_TANQUE_INIMIGO 10
#define tela_largura 401
#define tela_altura 430
#define calor_tiro_simples 15
#define xoff 0
#define yoff 26

/* Quatro direções possíveis nesse jogo */
enum { norte=0, leste, sul, oeste }; 

/* Tipo de unidade */
enum { 
tanque=0, perseguidor, antena, tiro_canhao, explosao_simples,explosao_tijolos, explosao_parede, explosao_fogo, explosao_areia, 
seta_vermelha, seta_verde};
	   
/*Ponto*/
typedef struct _pre_unidade{
	int x;
	int y;
	unsigned char tipo;	
	unsigned char direcao;
}Pre_unidade;

/* Numero de inimigos mortos*/
int n_inimigos_mortos=0;

/* Numero de vidas do jogador*/
int n_vidas=3;

/* Numero de vidas que o jogador perdeu*/
int n_vidas_perdidas=0;

/* Fim. 0 Nao, 1 Sim */
int fim=0;
int fim_da_fase=0;

/* Proxima fase */
int direcao_proxima_fase = 0;

/* Pontos do jogador */
unsigned int pontos=0;

/* Lista de inimigos a serem criados*/
Pre_unidade inimigos[20];
int indice_inimigos;
int n_inimigos_da_fase;


/* Lista de setas */
Pre_unidade setas[5];
int n_setas_da_fase;


/* Jogador e antena*/
Pre_unidade pre_jogador;
Pre_unidade pre_antena;
