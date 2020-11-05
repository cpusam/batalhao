/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: colisao.h                                 *
* Descrição: definições do jogo (constantes e        * 
* algumas funções)                                   *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponível sob licensa GPL.     *
******************************************************/

/*
COLISAO
pega dois retangulos e diz se eles colidem.

a figura diz tudo:
a---------+
|         |
|  c------|--+
|  |      |  |
+---------b  |
   |         | 
   +---------d
retorna 1 se colidem, 0 se não.
*/
int colisao(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy){
	return (!((ax > dx)||(bx < cx)||(ay > dy)||(by < cy)));
}
