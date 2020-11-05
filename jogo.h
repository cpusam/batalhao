/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: jogo.h                                    *
* Descricao: Utilitarios de interface com o SDL,     *
* teclado e clico de vida do jogo.                   * 
* por José Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponi­vel sob licensa GPL.    *
******************************************************/

#include<time.h>

int pausado=0;
int delay =0;

/* Guarda a posicao atual das teclas. SDLK_LAST é o numero de códigos de tecla*/
char teclado[SDLK_LAST];

/*
DESENHA_QUADRO
Desenha um pequeno quadro negro no canto da tela.
*/
void desenha_quadro(){
	SDL_Rect destino;
	destino.x = 0;
	destino.y = 346;
	destino.w = 320;
	destino.h = 32;
	SDL_FillRect(tela,&destino,SDL_MapRGB(tela->format,0,0,0) );	
}

/*
DESENHA_PAINEL
Desenha o painel do jogo (deixei separado porque so eh usada um vez)
*/
void desenha_painel(){
	SDL_Rect fonte, destino;
	
	if(img_painel){
		fonte.x = 0;
		fonte.y= 0;
		fonte.w = img_painel->w;
		fonte.h = img_painel->h;

		destino.x = xoff;
		destino.y = yoff;
		destino.w = img_painel->w;
		destino.h = img_painel->h;
		SDL_BlitSurface( img_painel, &fonte, tela, &destino );
	}else{
		printf("\n[ERRO] Parametro Nulo, em funcao desenha_painel\n");
		exit(1);
	}		
}

/*
LIMPA O TECLADO
Toda tecla recebe 0
*/
void limpa_teclado(){
	int i;
		
	for(i=0;i<SDLK_LAST;i++) teclado[i]=0;
}

/* 
INICIAR JOGO
Chama as funcoes do SDL que tem que ser chamadas, cria a tela, seta a resolucao Nomeia a janela. E chama os recursos.
*/
void prepara_jogo(int largura, int altura){
	int i;

	/* Calcula a semente para numeros aleatorios */
	 srand (time (0));

	/* Inicializa o video e procura por erros*/
	if (SDL_Init(SDL_INIT_VIDEO)!=0){
		printf("Nao foi possivel inicializar o SDL: %s\n",
		SDL_GetError());
		exit(1);
	}

	/* Assegura-se que o SDL_Quit sera chamado quando o programa sair.*/
	atexit(SDL_Quit);


	/* Tenta setar o modo de video.*/
	tela =SDL_SetVideoMode(tela_largura,tela_altura,16,
	SDL_DOUBLEBUF|SDL_HWSURFACE);
	if(tela==NULL){
		printf("Nao foi possivel inicializar o modo de video: %s\n",
		SDL_GetError());
		exit(1);
	}

	/* Chama os recursos */
	abre_recursos();

	/* Seta um icone */	
	//SDL_WM_SetIcon(img_hud_tanque, NULL);

	/* Limpa o teclado */
	limpa_teclado();
}

/*
NOVO_JOGO
Prepara o cenario e as unidades.
*/
void novo_jogo(char *primeiromapa){
	if(primeiromapa){
		m1 = novo_mapa(primeiromapa,0,0);
	}else{
		m1 = novo_mapa("mapas/WeAreUnderAttack.mapa",0,0);
	//"mapas/WeAreUnderAttack.mapa"
	}
	
	/* Começa com 3 inimigos */
	novo_inimigo();
	novo_inimigo();
	novo_inimigo();
	
	jogador = nova_unidade(tanque, pre_jogador.x, pre_jogador.y,NULL);
	antena1 = nova_unidade(antena, pre_antena.x, pre_antena.y, NULL);
	
	hvidas = novo_hud(vidas,30,378);
 	capture = novo_hud(logo,25,25);
	hpausa = novo_hud(pausa, 25,25);
	hfim = novo_hud(fim_do_jogo, 0, 0);
	sombreamento = novo_hud(sombra, 0, 0);
	quantos_inimigos = novo_hud(Hinimigos, 30, 400);
	contador_balas = novo_HMostrador(N_BALAS_DO_JOGADOR,N_BALAS_DO_JOGADOR,341,71);	
	contador_vida = novo_HMostrador(VIDA_TANQUE_JOGADOR, VIDA_TANQUE_JOGADOR,341,156);		
	display_pontos = novo_DisplayNumerico(75,360);
	
	/* Fonte */
	teste = nova_Fonte(50,50);
}

/*
PROXIMA_FASE
Chama a proxima fase, se baseia na variavel global direcao_proxima_fase e no vetor de proximas fases do mapa.h
*/
void proxima_fase(){
	destroi_lista_unidade(u_raiz);
	destroi_lista_relevo(r_raiz);
	
	switch (direcao_proxima_fase){
			case 0:{
				m1 = novo_mapa(proximo_norte,0,0);
				break;
				}
			case 1:{
				m1 = novo_mapa(proximo_leste,0,0);
				break;
				}
			case 2:{
				m1 = novo_mapa(proximo_sul,0,0);
				break;
				}
			case 3:{
				m1 = novo_mapa(proximo_oeste,0,0);
				break;
				}
	}
	
	/* Começa com 3 inimigos */
	novo_inimigo();
	novo_inimigo();
	novo_inimigo();
	
	jogador = nova_unidade(tanque, pre_jogador.x, pre_jogador.y,NULL);
	antena1 = nova_unidade(antena, pre_antena.x, pre_antena.y, NULL);
	
}

/*
DESENHA_FANTASMAS
Desenha as figuras em cima das proprias figuras com uma tinta mais fraca.
Assim eh possi­vel ver as unidades mesmo fora da viao.
raiz: Raiz para a lista encadeada de unidades 
*/
void desenha_fantasmas(Unidade *raiz){
	Unidade *p = raiz;
	while(p!=NULL){
		SDL_SetAlpha(p->img, SDL_SRCALPHA, 128);
		desenha_unidade(p);
		SDL_SetAlpha(p->img, SDL_SRCALPHA, 255);
		p = p->prox;
	}
}

/*
FIM_DA_APLICACAO
Chama todas as funcoes de liberar memoria
*/
/* Libera a meoria */	
void fim_da_aplicacao(){
	destroi_lista_unidade(u_raiz);
	destroi_lista_relevo(r_raiz);
	destroi_recursos();	
	//gtk_main_quit();
	SDL_Quit();
	//exit(0);
}


//gint evento_teclado(GtkWidget *widget, GdkEventKey *event){
	/*printf("apertou %d \n", event->keyval);*/
	
	/* Eh feito mas eh o jeito, conversao do GTK para SDL */
	/* Coloca 1 quando a tecla eh pressionada e zero quando eh solta*/
/*
	if(event->keyval==65361) 
		teclado[SDLK_LEFT] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==65362) 
		teclado[SDLK_UP] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==65363) 
		teclado[SDLK_RIGHT] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==65364) 
		teclado[SDLK_DOWN] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==32)
		teclado[SDLK_SPACE] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==112)
		teclado[SDLK_p] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==65299)
		teclado[SDLK_p] = (event->type==GDK_KEY_PRESS);
	if(event->keyval==102)
		teclado[SDLK_f] = (event->type==GDK_KEY_PRESS);
	return TRUE;
}
*/

SDL_Event evento;
int foi_iniciado = 0;

int faz_teclado (int *fim ){
	//adiciona repetição de teclas
	if (!foi_iniciado) {
		foi_iniciado = 1;
		SDL_EnableKeyRepeat(1000 / 60, 1000 / 60);
	}

	while (SDL_PollEvent(&evento)) {
		/* Tecla Seta Esquerda */
		
		if (evento.type == SDL_KEYDOWN) {
			//if(teclado[SDLK_LEFT]){
			if (evento.key.keysym.sym == SDLK_LEFT) {
				para_esquerda(jogador);
				liga(jogador);
			}

			/* Tecla Seta Direita */
			//if(teclado[SDLK_RIGHT]){
			if (evento.key.keysym.sym == SDLK_RIGHT) {
				para_direita(jogador);
				liga(jogador);
			}

			/* Tecla Seta Cima */
			//if(teclado[SDLK_UP]){
			if (evento.key.keysym.sym == SDLK_UP) {
				para_cima(jogador);
				liga(jogador);
			}

			/* Tecla Seta Baixo */
			//if(teclado[SDLK_DOWN]){
			if (evento.key.keysym.sym == SDLK_DOWN) {
							para_baixo(jogador);
				liga(jogador);
			}
			
			/* Magica da jogabilidade! */
			/*
			if((!teclado[SDLK_LEFT])&&(!teclado[SDLK_RIGHT])
			&&(!teclado[SDLK_UP])&&(!teclado[SDLK_DOWN]))
			*/
		

			/* Tecla espaco */
			//if(teclado[SDLK_SPACE])
			if (evento.key.keysym.sym == SDLK_SPACE)
				atira(jogador);
			
			/* Tecla F */
			//if(teclado[SDLK_f])
			if (evento.key.keysym.sym == SDLK_f)
				SDL_WM_ToggleFullScreen(tela);
			

			/* Tecla P */	
			//if(teclado[SDLK_p]){
			if (evento.key.keysym.sym == SDLK_p) {
				pausado = 1- pausado;
				hpausa.ligado = 1 - hpausa.ligado;
			}
		}

		if (evento.type == SDL_KEYUP) {
			if((evento.key.keysym.sym == SDLK_LEFT) || (evento.key.keysym.sym == SDLK_RIGHT)
				|| (evento.key.keysym.sym == SDLK_UP) || (evento.key.keysym.sym == SDLK_DOWN))
					desliga(jogador);
		}

		if (evento.type == SDL_QUIT) {
			*fim = 1;
		}
	}
	return 0;
}


//para o controle de FPS
Uint32 tempo_agora;
Uint32 tempo_antes;
const Uint32 FPS_TEMPO = 1000 / 60;

/*
FAZ
Ciclo de vida do jogo.
*/
//gint faz(gpointer data)
int faz (  ){
	tempo_antes = SDL_GetTicks();
	Unidade *p = u_raiz;
	
	desenha_mapa_chao(&m1);
	desenha_quadro();
	desenha_pp();
	desenha_fantasmas(u_raiz);	 
	
	if((!pausado)&&(!fim)){	    
	    while(p!=NULL){
			if(p->inteligente)
				pensa(p);
			anda_unidade(p,&m1);
			p = p->prox;
	    }
	}

	fim |= (n_vidas == 0);
	
	/* Painel */		
	desenha_painel();
	
	/* HUDs */
	desenha_hud(&hvidas);
	desenha_hud(&hpausa);
	desenha_hud(&quantos_inimigos);
	desenha_HMostrador(&contador_balas, jogador->max_tiros, jogador->max_tiros - jogador->n_tiros);
	desenha_HMostrador(&contador_vida, VIDA_TANQUE_JOGADOR, jogador->vida);
	
	desenha_DisplayNumerico(&display_pontos, pontos);
	
	if (fim){ 
		liga_hud(&hfim);
		liga_hud(&sombreamento);
	}
	
	if(fim_da_fase){
		liga_hud(&sombreamento);
		if(delay++>100){
			proxima_fase();
			desliga_hud(&sombreamento);
			fim_da_fase = 0;
			delay=0;
		}			
	}
	
	desenha_hud(&sombreamento);
	
	desenha_hud(&hfim);
	desenha_hud(&capture);
	
	faz_teclado(&fim);
	
	SDL_UpdateRect(tela,0,0,tela->w,tela->h);

	//controle de FPS
	tempo_agora = SDL_GetTicks() - tempo_antes;
	if (tempo_agora < FPS_TEMPO) {
		SDL_Delay(FPS_TEMPO - tempo_agora);
	}
	else {
		SDL_Delay(FPS_TEMPO);
	}
	
	if (fim)
		return 0;
	return 1;
}
