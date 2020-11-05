/***************************************************** 
* Jogo Batalhão                                      * 
* Arquivo: recursos.h                                *
* Descrição: Administração de recursos multimídia.   *
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponível sob licensa GPL.     *
* Este bloco de código foi escrito a partir do       *
* trabalho de Michael Speck(kulkanie@gmx.net) do     *
* jogo Barrage, disponível sob GPL.                  *
******************************************************/

/* Declaração de Recursos */
SDL_Surface *img_tanque; /* Imagem do tanque a ser usada na unidade tanque. */
SDL_Surface *img_inimigo; /* Imagem do tanque a ser usada no inimigo*/
SDL_Surface *img_bandeira; /* Imagem de bandeira a ser usada em unidades */
SDL_Surface *img_arvore; /* Imagem de arvore a ser utilizada em relevos */
SDL_Surface *img_mercado; /* Imagem de mercado a ser utilizada em relevos */
SDL_Surface *img_parede_limpa; /* Imagem de parede limpa */
SDL_Surface *img_parede_suja; /* Imagem de parede suja */
SDL_Surface *img_pizzaria; /* Imagem da pizzaria */
SDL_Surface *img_comercial; /* Imagem do prédio comercial */
SDL_Surface *img_embaixada; /* Imagem do prédio comercial */
SDL_Surface *img_semaforo; /* Imagem do semaforo */
SDL_Surface *img_banca; /* Imagem de banca */
SDL_Surface *img_antena; /* Imagem de banca */
SDL_Surface *img_hud_tanque; /* Imagem tanque para hud.*/
SDL_Surface *img_pausa; /* Imagem para a pausa.*/
SDL_Surface *img_fim; /* Imagem para o fim do jogo.*/
SDL_Surface *img_logo; /* Imagem de logo do jogo */
SDL_Surface *img_mapa; /* Imagem do mapa de pixels */
SDL_Surface *img_tiro_canhao; /* Imagem de tiro de canhão */
SDL_Surface *img_hospital; /* Imagem de hospital*/
SDL_Surface *img_explosao_simples; /* Imagem de explosao simples */
SDL_Surface *img_explosao_tijolos; /* Imagem de explosao tijolos */
SDL_Surface *img_explosao_parede; /* Imagem de exploso de parede */
SDL_Surface *img_explosao_fogo; /* Imagem de exploso de fogo */
SDL_Surface *img_explosao_areia; /* Imagem de exploso de areia */
SDL_Surface *img_copperplate_blue; /* Imagem de fonte*/
SDL_Surface *img_mini_inimigo; /* Imagem de mini inimigo para hud*/
SDL_Surface *img_painel; /* Imagem do painel 3D */
SDL_Surface *img_mostrador; /* Display de 0 a 7 */
SDL_Surface *img_saco_de_areia_vertical; /* Sacos de areia */
SDL_Surface *img_setas_vermelhas; /* Setas vermelhas */
SDL_Surface *img_setas_verdes; /* Setas verdes */

/* Fontes */
SDL_Surface *img_fnt_monospace; /* Fonte monospace */
SDL_Surface *img_fnt_tecnoretro; /* Fonte TecnoRetro (so numeros)*/


/*
ABRE_IMAGE
Recebe o caminho de uma imagem e retorna um SDL_Surface com aquela imagem. Com otimização (DisplayFormat).

Parâmetros:
nome: nome da imagem a ser aberta. A imagem deve estar na pasta gfx.

Saída:
SDL_Surface: uma surperficie com a imagem dentro.
*/
static SDL_Surface *abre_imagem( char *nome )
{
	char path[128];
	SDL_Surface *tmp = 0, *surf = 0;
	snprintf( path, 128, "gfx/%s", nome ); path[127] = 0;
	printf( "abrindo %s ... ", path );
	tmp = SDL_LoadBMP( path );

	if ( tmp == 0 || (surf = SDL_DisplayFormat(tmp)) == 0 ) {
		printf("Um erro ocorreu: %s\n", SDL_GetError() );
		SDL_FreeSurface( tmp );
		exit(1);
	}

	SDL_FreeSurface( tmp );
	printf( "ok\n" );
	return surf;
}

static SDL_Surface *abre_imagem_com_transparencia(char *nome){
	char path[128];
	SDL_Surface *tmp = 0, *surf = 0;
	Uint32 cor_chave;

	snprintf( path, 128, "gfx/%s", nome ); path[127] = 0;
	printf( "abrindo %s ... ", path );
	tmp = SDL_LoadBMP( path );

	if ( tmp == 0 || (surf = SDL_DisplayFormat(tmp)) == 0 ) {
		printf("Erro\n");
		SDL_FreeSurface( tmp );
		exit(1);
	}

	/* Define a cor chave. A cor que vai ser a transparência */
	cor_chave = SDL_MapRGB(surf->format, 0,255,0);

	SDL_SetColorKey(surf,SDL_SRCCOLORKEY,cor_chave);

	SDL_FreeSurface( tmp );
	printf( "ok\n" );
	return surf;
}

/*
DESENHA
Desenha simplesmente uma surpefície(img) na outra(tela) dado um x e um y.

Parâmetros:
tela: ponteiro para a surpefície a onde será pintada. (destino)
img: porteiro para a superfície a ser pintada. (fonte)
x,y: o lugar onde vai ser pintado a superficie. Note que ela vai pintar a imagem inteira.
*/
void desenha(SDL_Surface *tela,SDL_Surface *img, int x, int y){
	SDL_Rect fonte, destino;
	/* Verifica se existe as surfaces */
	if((img)&&(tela)){
		fonte.x = 0; fonte.y=0;
		fonte.w = img->w; fonte.h = img->h;
		destino = fonte;
		destino.x = x; destino.y = y;
		SDL_BlitSurface( img, &fonte, tela, &destino );
	}else{
		printf("\n[ERRO] Parâmetro Nulo, em função Desenha\n");
		exit(1);
	}
}

/* Função abre_recursos. Abre um lista de recursos do jogo. */
void abre_recursos(){
	img_tanque = abre_imagem_com_transparencia("tanque.bmp");
	img_inimigo = abre_imagem_com_transparencia("inimigo.bmp");
	img_arvore = abre_imagem_com_transparencia("arvore.bmp");
	img_bandeira = abre_imagem_com_transparencia("bandeira.bmp");
	img_hud_tanque = abre_imagem_com_transparencia("tanquinho.bmp");
	img_logo = abre_imagem_com_transparencia("logo.bmp");
	img_mapa = abre_imagem("mapa.bmp");
	img_pausa = abre_imagem_com_transparencia("pausa.bmp");
	img_fim	= abre_imagem_com_transparencia("fimdojogo.bmp");
	img_mercado = abre_imagem("mercado.bmp");
	img_parede_limpa = abre_imagem("parede-vazia.bmp");
	img_parede_suja = abre_imagem("parede-suja.bmp");
	img_pizzaria = abre_imagem("pizzaria.bmp");
	img_comercial = abre_imagem("comercial.bmp");
	img_semaforo = abre_imagem_com_transparencia("semaforo.bmp");
	img_embaixada = abre_imagem("embaixada.bmp");
	img_banca = abre_imagem("banca.bmp");
	img_antena = abre_imagem_com_transparencia("antena.bmp");
	img_tiro_canhao = abre_imagem_com_transparencia("tiro-canhao.bmp");
	img_hospital = abre_imagem("hospital.bmp");
	img_explosao_simples = abre_imagem_com_transparencia("explosao_simples.bmp");
	img_explosao_tijolos = abre_imagem_com_transparencia("explosao_tijolos.bmp");
	img_explosao_parede = abre_imagem_com_transparencia("explosao_parede.bmp");
	img_explosao_fogo = abre_imagem_com_transparencia("explosao_fogo.bmp");
	img_copperplate_blue = abre_imagem_com_transparencia("24P_Copperplate_Blue.bmp");
	img_mini_inimigo = abre_imagem_com_transparencia("miniinimigo.bmp");
	img_painel = abre_imagem_com_transparencia("painel.bmp");
	img_mostrador = abre_imagem_com_transparencia("mostrador.bmp");	
	img_fnt_tecnoretro = abre_imagem("fnt_tecnoretro.bmp");
	img_saco_de_areia_vertical = abre_imagem_com_transparencia("sacodeareiavertical.bmp");
	img_explosao_areia = abre_imagem_com_transparencia("explosao_areia.bmp");
	img_fnt_monospace = abre_imagem_com_transparencia("fnt_monospace.bmp");
	img_setas_vermelhas = abre_imagem_com_transparencia("setas_vermelhas.bmp");	
	img_setas_verdes= abre_imagem_com_transparencia("setas_verdes.bmp");	
}

/* Função abre_recursos. Fecha uma lista de recursos do jogo. */
void destroi_recursos(){
	/* Destroi recursos uma a um*/
	SDL_FreeSurface(img_tanque);
	SDL_FreeSurface(img_inimigo);
	SDL_FreeSurface(img_arvore);
	SDL_FreeSurface(img_bandeira);
	SDL_FreeSurface(img_hud_tanque);
	SDL_FreeSurface(img_logo);
	SDL_FreeSurface(img_mapa);
	SDL_FreeSurface(img_pausa);
	SDL_FreeSurface(img_fim);
	SDL_FreeSurface(img_mercado);
	SDL_FreeSurface(img_parede_limpa);
	SDL_FreeSurface(img_parede_suja);
	SDL_FreeSurface(img_pizzaria);
	SDL_FreeSurface(img_comercial);
	SDL_FreeSurface(img_semaforo);
	SDL_FreeSurface(img_embaixada);
	SDL_FreeSurface(img_banca);
	SDL_FreeSurface(img_antena);
	SDL_FreeSurface(img_tiro_canhao);
	SDL_FreeSurface(img_hospital);
	SDL_FreeSurface(img_explosao_simples);
	SDL_FreeSurface(img_explosao_tijolos);
	SDL_FreeSurface(img_explosao_parede);
	SDL_FreeSurface(img_explosao_fogo);
	SDL_FreeSurface(img_copperplate_blue);	
	SDL_FreeSurface(img_mini_inimigo);
	SDL_FreeSurface(img_painel);
	SDL_FreeSurface(img_mostrador);
	SDL_FreeSurface(img_fnt_tecnoretro);
	SDL_FreeSurface(img_saco_de_areia_vertical);
	SDL_FreeSurface(img_explosao_areia);	
	SDL_FreeSurface(img_fnt_monospace);	
	SDL_FreeSurface(img_setas_vermelhas);
	SDL_FreeSurface(img_setas_verdes);
	
	/* Diz que destruiu */
	printf("Memoria das imagens liberada.\n");
}
