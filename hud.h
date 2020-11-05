/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: hud.h                                     *
* Descrição: HUDs. Gráficos não interativos para     *
* fins de informação.                                *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponível sob licensa GPL.     *
******************************************************/

/* Tipos de hud */
enum { vidas=0, logo, pausa, fim_do_jogo, sombra, Hinimigos};

typedef struct _Hudl {
/* Lógico */
	int x,y; /* Localização no cenário */		
	int tipo; /* O tipo de hud. Para as outras funções saberem */	
	int ligado;

/* Transparência */	
	int transparencia;

/* Sprite */
	SDL_Surface *img; /* Imagem com sprites */
	int n_quadros; /* Número de quadros da animação.(Linhas) */	
	int quadro; /* Quadro atual */
	int n_modos; /* Número de modos da animação.Ex: Norte, Sul. (Colunas)*/	
	int modo; /* Modo atual */
	int rapidez; /* Velocidade da animação */
	int largura, altura; /* Altura e Largura de cada sprite. */
}HUD;


typedef struct _HMostrador{
/* Lógico */
	int x,y; /* Localização no cenário */		
	
/* Sprite */
	SDL_Surface *img; /* Imagem com sprites */	
	int largura, altura; /* Altura e Largura de cada sprite. */	
}HMostrador;

/*
NOVO_HUD
Recebe alguns parâmetro e cria um hud.
tipo: tipo de hud.
x,y: posição no cenário
*/

HUD novo_hud(int tipo, int x, int y){
	HUD tmp;

	/* Para cada tipo de hud um tratamento*/
	switch(tipo){
		case vidas:{	
			tmp.tipo = vidas;
			tmp.x = x;
			tmp.y = y;
			tmp.ligado=1;

			tmp.img  = img_hud_tanque;
			tmp.n_quadros = 1;
			tmp.quadro = 0;
			tmp.n_modos = 1;
			tmp.modo = 0;
			tmp.rapidez = 1;
			tmp.largura = tmp.img->w;
			tmp.altura = tmp.img->h;	

			break;			
		}

		case logo:{	
			tmp.tipo = logo;
			tmp.img  = img_logo;
			tmp.x = (tela_largura-tmp.img->w)/2 ;
			tmp.y = (tela_altura-tmp.img->h)/2 ;
			tmp.ligado=1;

			tmp.transparencia= 255;
			SDL_SetAlpha(img_logo, SDL_SRCALPHA, tmp.transparencia);
			tmp.n_quadros = 1;
			tmp.quadro = 0;
			tmp.n_modos = 1;
			tmp.modo = 0;
			tmp.rapidez = 2;
			tmp.largura = tmp.img->w;
			tmp.altura = tmp.img->h;

			break;
		}

		case pausa:{	
			tmp.tipo = pausa;
			tmp.img  = img_pausa;
			tmp.x = (tela_largura-tmp.img->w)/2 ;
			tmp.y = (tela_altura-tmp.img->h)/2 ;
			tmp.ligado=0;
			
			tmp.transparencia= 0;
			SDL_SetAlpha(img_logo, SDL_SRCALPHA, tmp.transparencia);
			tmp.n_quadros = 1;
			tmp.quadro = 0;
			tmp.n_modos = 1;
			tmp.modo = 0;
			tmp.rapidez = 6;
			tmp.largura = tmp.img->w;
			tmp.altura = tmp.img->h;

			break;
		}

		case fim_do_jogo:{	
			tmp.tipo = fim_do_jogo;
			tmp.img  = img_fim;
			tmp.ligado=0;
			tmp.x = (tela_largura-tmp.img->w)/2 ;
			tmp.y = (tela_altura-tmp.img->h)/2 ;

			tmp.transparencia=0;
			SDL_SetAlpha(img_fim, SDL_SRCALPHA, tmp.transparencia);
			tmp.n_quadros = 1;
			tmp.quadro = 0;
			tmp.n_modos = 1;
			tmp.modo = 0;
			tmp.rapidez = 4;
			tmp.largura = tmp.img->w;
			tmp.altura = tmp.img->h;

			break;
		}
		
		case sombra:{	
			tmp.tipo = sombra;
			tmp.img  = NULL;
			tmp.ligado=0;
			tmp.x = 0;
			tmp.y = 0;
			tmp.transparencia=255;
			tmp.n_quadros = 1;
			tmp.quadro = 0;
			tmp.n_modos = 1;
			tmp.modo = 0;
			tmp.rapidez = 8;
			tmp.largura = tela_largura;
			tmp.altura = tela_altura;

			break;
		}
		
		case Hinimigos:{	
			tmp.tipo = Hinimigos;			
			tmp.ligado=1;
			tmp.img  = img_mini_inimigo;
			tmp.x = x;
			tmp.y = y;			
			tmp.n_quadros = 1;
			tmp.quadro = 0;
			tmp.n_modos = 1;
			tmp.modo = 0;
			tmp.rapidez = 1;
			tmp.largura = tmp.img->w;
			tmp.altura = tmp.img->h;
			break;
		}		
	}
	return tmp;
}

HMostrador novo_HMostrador(int total, int n, int x, int y){
	HMostrador tmp;
	
	tmp.img = img_mostrador;
	tmp.x = x;
	tmp.y = y;	
	tmp.largura = 36;
	tmp.altura = 36;
	
	return tmp;
}


void fade(SDL_Surface *screen, Uint32 rgb, Uint8 a)
{
	SDL_Surface *tmp=SDL_DisplayFormat(screen);
	SDL_FillRect(tmp,0,rgb);
	SDL_SetAlpha(tmp,SDL_SRCALPHA,a);
	SDL_BlitSurface(tmp,0,screen,0);
	SDL_FreeSurface(tmp);
}

/*
DESENHA_HUD
Recebe um hud e o desenha
u: Ponteiro para o hud a ser desenhado.
*/
void desenha_hud(HUD *u){
	int i,n;
	SDL_Rect fonte, destino;
	
	/* Para cada hud um comportamento */
	switch(u->tipo){
		case vidas:{
			fonte.x = (u->largura)*(u->modo);
			fonte.y= (u->altura)*(u->quadro);
			fonte.w = u->largura;
			fonte.h = u->altura;
			n = n_vidas-n_vidas_perdidas;

			for(i=0;i<n;i++){
				destino.x = u->x + i*u->largura + i*(u->largura/3);
				destino.y = u->y;
				destino.w = u->largura;
				destino.h = u->altura;
				SDL_BlitSurface( u->img, &fonte, tela, &destino );
			}
			break;
		}

		case logo:{
			fonte.x = 0;
			fonte.y = 0;
			fonte.w = u->largura;
			fonte.h = u->altura;
			destino.x = u->x;
			destino.y = u->y;
			destino.w = u->largura;
			destino.h = u->altura;
			SDL_BlitSurface( u->img, &fonte, tela, &destino );
			if((u->transparencia)-(u->rapidez)>0){
				u->transparencia-=u->rapidez;
			} else{
				u->transparencia =0;
			}
			SDL_SetAlpha(u->img, SDL_SRCALPHA, u->transparencia);
			break;
		}
			
		case pausa:{
			fonte.x = 0;
			fonte.y = 0;
			fonte.w = u->largura;
			fonte.h = u->altura;

			destino.x = u->x;
			destino.y = u->y;
			destino.w = u->largura;
			destino.h = u->altura;
			SDL_BlitSurface( u->img, &fonte, tela, &destino );
			if(u->ligado){
				if((u->transparencia)+(u->rapidez)<255){
					u->transparencia+=u->rapidez;
				} else{
					u->transparencia =255;
				}
			} else {
				if((u->transparencia)-(u->rapidez)>0){
					u->transparencia-=u->rapidez;
				} else{
					u->transparencia=0;
				}
			}
			SDL_SetAlpha(u->img, SDL_SRCALPHA, u->transparencia);
			break;
		}

		case fim_do_jogo:{
			fonte.x = 0;
			fonte.y = 0;
			fonte.w = u->largura;
			fonte.h = u->altura;

			destino.x = u->x;
			destino.y = u->y;
			destino.w = u->largura;
			destino.h = u->altura;
			SDL_BlitSurface( u->img, &fonte, tela, &destino );
			if(u->ligado){
				if((u->transparencia)+(u->rapidez)<255){
					u->transparencia+=u->rapidez;
				} else{
					u->transparencia =255;
				}
			} else {
				if((u->transparencia)-(u->rapidez)>0){
					u->transparencia-=u->rapidez;
				} else{
					u->transparencia=0;
				}
			}
			SDL_SetAlpha(u->img, SDL_SRCALPHA, u->transparencia);
			break;
		}
		
		case sombra:{
		/* Se 0 nao faz nada, se 255 pinta de preto, se 
		entre isso da um fade.*/
		if(u->transparencia==255){
			SDL_FillRect(tela,0,
			SDL_MapRGB(tela->format,0,0,0) );
		} else {
			if(u->transparencia>0){
			fade(tela,SDL_MapRGB(tela->format,0,0,0),
			u->transparencia);
		}
		}

			if(u->ligado){
				if((u->transparencia)+(u->rapidez)<255){
					u->transparencia+=u->rapidez;
				} else{
					u->transparencia =255;
				}
			} else {
				if((u->transparencia)-(u->rapidez)>0){
					u->transparencia-=u->rapidez;
				} else{
					u->transparencia=0;
				}
			}
		
			break;
		}
		
		case Hinimigos:{			
			fonte.x = 0;
			fonte.y = 0;
			fonte.w = u->largura;
			fonte.h = u->altura;
			n = n_inimigos_da_fase - n_inimigos_mortos;
			for(i=0;i<n;i++){
				destino.x = u->x + i*u->largura+i*3;
				destino.y = u->y;
				destino.w = u->largura;
				destino.h = u->altura;
				SDL_BlitSurface( u->img, &fonte, tela, &destino );
			}
			break;
		}
	}
}

void desenha_HMostrador(HMostrador *m, int total, int n){
	SDL_Rect fonte, destino;
	
	fonte.x = 36*(total-1);
	fonte.y = 36*n;
	fonte.w = m->largura;
	fonte.h = m->altura;
	destino.x = m->x;
	destino.y = m->y;
	destino.w = fonte.w;
	destino.h = fonte.h;
	SDL_BlitSurface(m->img, &fonte, tela, &destino);
}

void liga_hud(HUD *h){ h->ligado = 1; }
void desliga_hud(HUD *h){ h->ligado = 0; }
