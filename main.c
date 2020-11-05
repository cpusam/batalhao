/***************************************************** 
* Jogo Batalhao                                      * 
* Arquivo: Main.c                                    *
* Descricao: Arquivo central, abre a tela, chama as  *
* outras funcoes.                                    *
* por Jose Maria Silveira Neto                       *
* e Marco Diego Aurelio Mesquita                     *
*                                                    *
* Este programa esta disponivel sob licensa GPL.     *
******************************************************/
#define VERSAO 17

#include<SDL/SDL.h>
//#include<gtk/gtk.h>
//#include<gdk/gdkx.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

//GtkWidget *janela;
SDL_Surface *tela;
SDL_Event evento;

#include"recursos.h"
#include"defs.h"
#include"mapa.h"
#include"colisao.h"
#include"hud.h"
#include"unidade.h"
#include"fonte.h"

HUD hvidas;
HUD capture;
HUD hpausa;
HUD hfim;
HUD sombreamento;
HUD quantos_inimigos;
HMostrador contador_balas;
HMostrador contador_vida;
DisplayNumerico display_pontos;
Fonte teste;
Mapa m1;

#include"ia.h"
#include"perspectiva.h"
#include"jogo.h"

/* Callback de teste*/
/*
static void print_hello(GtkWidget *w, gpointer   data ){
	g_message ("Hello, World!\n");
}
*/
/* Funcao de Debug, mostra as unidades*/
/*
static void mostra_unidades(GtkWidget *w, gpointer   data ){
	Unidade *p = u_raiz;
	printf("U");	
    while(p!=NULL){
		printf("->[%d,%d,%d]",p->tipo, p->x, p->y);
		p = p->prox;
    }    
	printf("-|\n");
}
*/

/* Funcao de Debug, mostra os relevos*/
/*
static void mostra_relevos(GtkWidget *w, gpointer   data ){
	Relevo *r = r_raiz;;
	printf("R");
    while(r!=NULL){
   		printf("->[%d,%d,%d]",r->tipo, r->x, r->y);
		r = r->prox;
    }    
	printf("-|\n");
}
*/
/*
SOBRE_BATALHAO
Uma dialogo de informações
*/
/*
static void sobre_batalhao(GtkWidget *w, gpointer   data ){
    char msg[] = "Batalhão\n  (c) 2004, 2005\nhttp://batalhao.codigolivre.org.br\n\nJosé Maria Silveira Neto\nMarco Diego Aurélio Mesquita\n\nEste jogo é um Software Livre, voce pode distribui-lo sob os termos da GPL v2.\n";
	GtkWidget *dialog, *label, *okay_button;
     

	dialog = gtk_message_dialog_new (NULL,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  msg
                                  );
 	gtk_dialog_run (GTK_DIALOG (dialog));
 	gtk_widget_destroy (dialog);
}
*/
/*
AJUDA
Um dialogo de ajuda 
*/
/*
static void ajuda(GtkWidget *w, gpointer   data ){
    char msg[] = "Objetivo:\nO objetivo principal do jogo é não deixar que o radar seja destruído.\n O segundo objetivo é destruir os tanques inimigos.\n\nComandos:\nUse as setas do teclado para movimentar o tanque.\nUse a tecla de espaço para atirar.\n";
	GtkWidget *dialog, *label, *okay_button;

	dialog = gtk_message_dialog_new (NULL,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  msg
                                  );
 	gtk_dialog_run (GTK_DIALOG (dialog));
 	gtk_widget_destroy (dialog);
}
*/

/* For the check button */
/*
static void print_toggle(gpointer callback_data,
			guint callback_action,
			GtkWidget *menu_item ){
	g_message ("Check button state - %d\n",
			GTK_CHECK_MENU_ITEM (menu_item)->active);
}
*/
/* For the radio buttons */
/*
static void print_selected(gpointer callback_data,
				guint callback_action,
				GtkWidget *menu_item ){
	if(GTK_CHECK_MENU_ITEM(menu_item)->active)
		printf("%d. Por enquanto so em portugues. ;)\n", callback_action);
}*/


/* Nosso menu, um vetor de estruturas de GtkItemFactoryEntry que definem cada item de menu*/
/*
static GtkItemFactoryEntry menu_items[] = {
{"/_Jogo",NULL,NULL,0,"<Branch>"},
{"/Jogo/Sa_ir","<CTRL>Q",fim_da_aplicacao,0,"<StockItem>", GTK_STOCK_QUIT},
{"/_Opções",NULL,NULL,0,"<Branch>"},
{"/Opções/Pausado",NULL,print_toggle,1,"<CheckItem>"},
{"/Opções/sep",NULL,NULL,0,"<Separator>"},
{"/Opções/Português",NULL,print_selected,1,"<RadioItem>"},
{"/_Debug",NULL,NULL,0,"<Branch>"},
{"/Debug/_Unidades","<control>U",mostra_unidades,0,"<StockItem>", GTK_STOCK_OPEN},
{"/Debug/_Relevos","<control>R",mostra_relevos,0,"<StockItem>", GTK_STOCK_OPEN},
{"/_Ajuda",NULL,NULL,0,"<LastBranch>"},
{"/_Ajuda/_Como jogar",NULL,ajuda,0,"<StockItem>",GTK_STOCK_HELP},
{"/_Ajuda/Sobre",NULL,sobre_batalhao,0,"<Item>"},
};
*/
//static gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

/* Retorna um widget menubar com o menu*/
//static GtkWidget *get_menubar_menu(GtkWidget *window){
	//GtkItemFactory *item_factory;
	//GtkAccelGroup *accel_group;
	
	/* Make an accelerator group (shortcut keys) */
	//accel_group = gtk_accel_group_new ();
	
	/* Make an ItemFactory (that makes a menubar) */
	//item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", accel_group);
	/* This function generates the menu items. Pass the item factory,
	 *      the number of items in the array, the array itself, and any
	 *           callback data for the the menu items. */
	//gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);

	/* Attach the new accelerator group to the window. */
	//gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

	/* Finally, return the actual menu bar created by the item factory. */
	//return gtk_item_factory_get_widget (item_factory, "<main>");
//}


/*
INFORMACOES
Imprime informacoes gerais do jogo.
*/
void informacoes(){	
	printf("Batalhao versao %d\n(c)2004,2005\n Jose Maria Silveira Neto e Marco Diego Aurelio Mesquita\nEste jogo eh um Software Livre, voce pode distribui-lo sob os termos da GPL v2.\n",VERSAO);	
}

/*
gint configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
	/* retirei pq quando redimensionava a tela carregava os recursos*/
	//tela = SDL_SetVideoMode(event->width, event->height, 0, 0);
	//prepara_jogo(event->width, event->height);
	//return TRUE ;
//}

/*
gint delete_event (GtkWidget *widget, GdkEventConfigure *event)
{
	gtk_main_quit();
	return TRUE ;
}*/

int main(int argc, char *argv[]){
	//GtkWidget *main_vbox, *menubar;		
			
	/* Pega a linha de comando */	
	if(argc > 0){		
		sprintf(proximo_norte,"%s",argv[1]);		
	}	
	
	/* Inicializa o GTK */
	//gtk_init(&argc, &argv);	
	
	/* Informacoes do jogo */
	informacoes();

    /* Cria a janela */
	//janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/*
	gtk_widget_set_usize(janela, tela_largura, tela_altura);
	gtk_window_set_title (GTK_WINDOW(janela), "Batalhão");
	gtk_widget_realize(janela);
	gtk_window_set_resizable(GTK_WINDOW(janela), FALSE);
	*/
	/* Adiciona os manipuladores de eventos */	
	/*
        gtk_widget_add_events(janela, GDK_BUTTON_PRESS_MASK);
        gtk_signal_connect(GTK_OBJECT(janela), "configure_event", 
			GTK_SIGNAL_FUNC(configure_event), 0);
        gtk_signal_connect(GTK_OBJECT(janela), "key_press_event", 
			GTK_SIGNAL_FUNC(evento_teclado), 0);
	gtk_signal_connect(GTK_OBJECT(janela), "key_release_event", 
			GTK_SIGNAL_FUNC(evento_teclado), 0);
        gtk_signal_connect(GTK_OBJECT(janela), "delete_event",
			GTK_SIGNAL_FUNC(delete_event), 0);
	g_signal_connect (G_OBJECT (janela), "destroy",
			G_CALLBACK (gtk_main_quit), NULL);
  */
	/* Hackeia para conseguir que o SDL use a janela GTK window */
	/*
	{ char SDL_windowhack[32];
		sprintf(SDL_windowhack,"SDL_WINDOWID=%ld",
			GDK_WINDOW_XWINDOW(janela->window));
		putenv(SDL_windowhack);
	}*/
	
	/* Prepara o jogo (janelas, telas, icones...) */
	prepara_jogo(tela_largura, tela_altura);
	
	/* Make a vbox to put the three menus in */
	//main_vbox = gtk_vbox_new (FALSE, 1);
	//gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);
	//gtk_container_add (GTK_CONTAINER (janela), main_vbox);

	/* Pega a barra de menu */
	//menubar = get_menubar_menu (janela);  

	/* Empacota a barra com o conteiner */
	//gtk_box_pack_start (GTK_BOX (main_vbox), menubar, FALSE, TRUE, 0);
	
	/* Cria o jogo */
	
	if(argc > 0){		
		novo_jogo(argv[1]);		
	}else{
		novo_jogo(NULL);		
	}
	
	
	/* Mostra os widgets */
	//gtk_widget_show_all(janela);
	  
	/* Chama o laco principal de tanto em tanto tempo */
	//g_timeout_add(22,faz, janela);
	
	/* E finalmente entra no loop do gtk_main e ao sair chama o SDL_Quit*/
	//gtk_main();
	while (faz() != 0) ;
	SDL_Quit();
	return 0;
}
