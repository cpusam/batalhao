/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: perspectiva.h                             *
* Descrição: Cuida da perpectiva visual do jogo.     *  
* Se um objeto está atrás de uma árvore, a árvore é  *
* desenhada depois do objeto.                        *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponível sob licensa GPL.     *
******************************************************/

/*
DESENHA_PP
Aqui a mágica acontece. Para cada posição da matriz de perpectiva desenha na tela
percorrendo de cima para baixo, da direita para esquerda.
PROVISSORIO. 32*32*o(desenha_pp())
Tem um puta problema aqui, de desenhar a lista toda checando parametros. Muito ruim. Mas quebra um galho.
*/
void desenha_pp(){
	int i,j,px,py;
	Unidade *pu;
 	Relevo *pr;

	for(j=0;j<32;j++){
	for(i=0;i<32;i++){
		pu = u_raiz;
		while(pu!=NULL){
			px = pu->x/32;
			py = (pu->y+pu->iy)/32;
			if((px==i)&&(py==j))
				desenha_unidade(pu);
			pu=pu->prox;
		}
		pr = r_raiz;
		while(pr!=NULL){
			px = pr->x/32;
			py = (pr->y+pr->iy)/32;
			if((px==i)&&(py==j))
				desenha_relevo(pr);
			pr=pr->prox;
		}

		}
	}
}
