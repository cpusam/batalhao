/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: fonte.h                                   *
* Descrição: Sistema proprio de fontes para o jogo   *
* por José Maria Silveira Neto                       *
*                                                    *
* Este programa esta disponível sob licensa GPL.     *
******************************************************/
#include<string.h>

/* Estrutura para o display de pontos */
typedef struct _display_numerico{
	int x,y; /* Localizacao na tela */
	int n; /* Numero atual */	
	SDL_Surface *img; /* Imagem com a fonte */	
	int largura,altura; /* Largura e altura de cada letra*/
	
}DisplayNumerico;

/* Estrura de fonte */
typedef struct _fonte{
	SDL_Surface *img; /* Imagem com a fonte */
	int largura,altura; /* Largura e altura de cada letra*/	
}Fonte;

/*
NOVO_DISPLAY_NUMERICO
recebe um x,y e construi um displaynumerico
*/
DisplayNumerico novo_DisplayNumerico(int x, int y){	
	DisplayNumerico tmp;	
	tmp.img = img_fnt_tecnoretro;
	tmp.x = x;
	tmp.y = y;
	tmp.n = 0;
	tmp.largura = 9;	
	tmp.altura = 13;
	return tmp;	
}

/*
NOVAFONTE
Recebe um x,y e construi uma fonte
*/
Fonte nova_Fonte(int x, int y){	
	Fonte tmp;
	tmp.img = img_fnt_monospace;	
	tmp.largura = 11;	
	tmp.altura = 20;
	return tmp;
}

/*
DESENHA_DISPLAY_NUMERICO
Recebe um displaynumerico d e um numero n e o desenha.
*/
void desenha_DisplayNumerico(DisplayNumerico *d, int n){
	int i, numero;
	char texto[30];	
	SDL_Rect fonte, destino;
		
	sprintf(texto,"%d",n);
	
	for (i=0;i<strlen(texto);i++){
		numero = texto[i]-48;
		fonte.x = numero*d->largura;
		fonte.y = 0;
		fonte.w = d->largura;
		fonte.h = d->altura;
		destino.x = d->x+i*d->largura;
		destino.y = d->y;
		destino.w = d->largura;
		destino.h = d->altura;
		SDL_BlitSurface(d->img, &fonte, tela, &destino);
	}
}


/*
ESCREVE
Recebe uma string, uma fonte e a escreve
*/
void escreve(char *texto, int x, int y, Fonte *f){
	SDL_Rect fonte, destino;
	int i, saltos=0, carriage=0;
	char temp[256];	
	
	sprintf(temp,"%s",texto);
	
	for (i=0;i<strlen(temp);i++){
		/* Pula a linha ?*/
		if(temp[i]==10){			
			saltos++;
			carriage = 0;
		}
		/* Desenha */
		fonte.x = (temp[i]-32)*f->largura;
		fonte.y = 0;
		fonte.w = f->largura;
		fonte.h = f->altura;
		destino.x = x + (carriage* f->largura);
		destino.y = y + saltos*f->altura;
		destino.w = f->largura;
		destino.h = f->altura;
		carriage++;
		SDL_BlitSurface(f->img, &fonte, tela, &destino);
	}
}

/*
ESCREVE_COM_BORDA
Recebe uma string, uma fonte e a escreve
*/
void escreve_com_caixa(char *texto, int x, int y, Fonte *f){
	SDL_Rect fonte, destino, caixa;
	SDL_Surface *tmp = SDL_DisplayFormat(tela);	
	int i, saltos=0, carriage=0,carriage_maximo=0;	
	int distancia = 10;
	char temp[256];	
	
	sprintf(temp,"%s",texto);
	
	/* Calcula o tamanho da caixa */
	for (i=0;i<strlen(temp);i++){
		/* Pula a linha ?*/
		if(temp[i]==10){			
			saltos++;
			carriage = 0;
		}else{
			carriage++;
			if(carriage>carriage_maximo)
				carriage_maximo = carriage;		
		}
	}
	
	
	/* Desenha a caixa */
	SDL_SetAlpha(tmp,SDL_SRCALPHA,200);	
	caixa.x = x-distancia;
	caixa.y = y-distancia;
	caixa.w = 2*(distancia)+(carriage_maximo * f->largura);
	caixa.h = 2*(distancia)+((saltos+1) * f->altura);	
	SDL_FillRect(tmp,&caixa,SDL_MapRGB(tela->format,0,0,0));	
	SDL_BlitSurface(tmp,0,tela,0);
	SDL_FreeSurface(tmp);
	
	saltos = 0;
	carriage =0;
	
	for (i=0;i<strlen(temp);i++){
		/* Pula a linha ?*/
		if(temp[i]==10){			
			saltos++;
			carriage = 0;
			
		}else{
			/* Desenha */
			fonte.x = (temp[i]-32)*f->largura;
			fonte.y = 0;
			fonte.w = f->largura;
			fonte.h = f->altura;		
			destino.x = x + ((carriage++)* f->largura);
			destino.y = y + saltos*f->altura;
			destino.w = f->largura;
			destino.h = f->altura;		
			SDL_BlitSurface(f->img, &fonte, tela, &destino);
		}
	}	
}
