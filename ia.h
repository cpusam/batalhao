/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: ia.h                                      *
* Descricao: um pouquinho de inteligencia artificial *
* para os inimigos.                                  *
* por Jose Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponi­vel sob licensa GPL.    *
******************************************************/
#include<math.h>
#include<time.h>


/*
PENSA
Um funcao bem simples sao para o inimigo nao ficar parado. O inimigo corre atras
do jogador.
*/
void pensa(Unidade *u){
	int distancia_x, distancia_y;
	
	/* Renova a semente aleatoria*/
	srand( (unsigned)time( NULL ) );
	
	switch(u->estado){
		/* Estado perseguir */
		case perseguir:{			
			/*liga(u);
			distancia_x = jogador->x - inimigo->x;
			distancia_y = jogador->y - inimigo->y;

			if ( distancia_x < 0 ) para_esquerda(u);
			if ( distancia_x > 0 ) para_direita(u);
			if ( distancia_y < 0 ) para_cima(u);	
			if ( distancia_y > 0 ) para_baixo(u);*/
			break;
		}

		/* Estado entrar em campo (quando o tanque acaba de nascer)*/
		case entrar_em_campo:{
			liga(u);			
			switch(u->direcao){
				case norte:{
					/* nao implementado */					
					break;
				}
				case leste:{					
					if(u->x>0)
						u->estado = bate_e_gira;					
					break;
					
				}
				case sul:{
					if(u->y>0)
						u->estado = bate_e_gira;
					break;
				}
				case oeste:{
					if(u->x+u->largura<320)
						u->estado = bate_e_gira;
					break;
				}
			}			
			break;
		}

		/* Estado bate e gira */
		case bate_e_gira:{
			if(!u->ligado){
				srand(time(NULL));
				if(umouzero()){
					unidade_gira_90(u);
				} else {
					unidade_gira_270(u);
				}

				liga(u);
			}
			if(aleatorio(0,10)==0) atira(u);
			
			break;
		}
	}

}
