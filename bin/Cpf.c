/*********************************************************************************************************************/
//Criador; Lucas Dias dos Santos
/*********************************************************************************************************************/
//Bibliotecas
/*********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <windows.h>
/*********************************************************************************************************************/


//Variaveis globais
/*********************************************************************************************************************/
GtkBuilder *builder;
GtkWidget  *window;
GtkStack   *stack;
GtkListStore *modelo;
GtkLabel *label;
int tam = 0;
/*********************************************************************************************************************/


//Declarações de funções
/*********************************************************************************************************************/
void conversao_char_int(char cpf_char[14], int cpf_int[11]);
void conversao_int_char(char cpf_char[14], int cpf_int[11]);
void juntar_string(char *primeira,char *segunda,char *recebe);
void verificacao(int vet[11], int local, int opc);
void criacao(char cpf[14]);
void estado(int num);
void mensagem(char text[100], char secondary_text[100], char icon_name[100]);
//###########################################################
void on_main_window_destroy(GtkWidget *widget, gpointer data);
void on_button_verificar_ini_clicked(GtkWidget *widget, gpointer data);
void on_button_cria_ini_clicked(GtkWidget *widget, gpointer data);
void on_sair_clicked(GtkWidget *widget, gpointer data);
void on_button_verificar_cpf_verificar_clicked(GtkWidget *widget, gpointer data);
void on_button_verificar_cpf_voltar_clicked(GtkWidget *widget, gpointer data);
void on_button_criacao_cpf_criar_clicked(GtkWidget *widget, gpointer data);
void on_button_criacao_cpf_voltar_clicked(GtkWidget *widget, gpointer data);
//###########################################################
int main(int argc, char *argv[]);
/*********************************************************************************************************************/

//Funções
/*********************************************************************************************************************/
void conversao_char_int(char cpf_char[14], int cpf_int[11]){
	int i,j;

	for(i=0, j=0; j < 14; i++, j++){
		switch (cpf_char[j]){
            case 48:
				cpf_int[i] = 0;
					break;
			case 49:
                cpf_int[i] = 1;
					break;
			case 50:
				cpf_int[i] = 2;
					break;
			case 51:
				cpf_int[i] = 3;
					break;
			case 52:
				cpf_int[i] = 4;
					break;
			case 53:
				cpf_int[i] = 5;
					break;
			case 54:
				cpf_int[i] = 6;
					break;
			case 55:
				cpf_int[i] = 7;
					break;
			case 56:
				cpf_int[i] = 8;
					break;
			case 57:
				cpf_int[i] = 9;
					break;
			default :
                i--;
        }
    }
    if(i < 11){
        gtk_label_set_text(label,"CPF inválido!");
        mensagem("CPF incorreto!", "O CPF correspondente não contém a\n quantidade de números suficientes!", "dialog-error");
        tam = 0;
    }else{
        tam = 1;
    }
}
void conversao_int_char(char cpf_char[14], int cpf_int[11]){
	int i,j;

	for(i=0, j=0; i<14 && j < 11; i++, j++){
		if(i == 3 || i == 7){
            cpf_char[i] = '.';
            i++;
		}else if(i == 11){
            cpf_char[i] = '-';
            i++;
        }

		switch (cpf_int[j]){
            case 0:
				cpf_char[i] = '0';
					break;
			case 1:
                cpf_char[i] = '1';
					break;
			case 2:
				cpf_char[i] = '2';
					break;
			case 3:
				cpf_char[i] = '3';
					break;
			case 4:
				cpf_char[i] = '4';
					break;
			case 5:
				cpf_char[i] = '5';
					break;
			case 6:
				cpf_char[i] = '6';
					break;
			case 7:
				cpf_char[i] = '7';
					break;
			case 8:
				cpf_char[i] = '8';
					break;
			case 9:
				cpf_char[i] = '9';
					break;
        }
    }
}
void juntar_string(char *primeira,char *segunda,char *recebe){
    int i,j;
    for(i=0; primeira[i] != '\0'; i++)    {recebe[i] = primeira[i];}
    for(j=0; segunda[j]  != '\0'; i++,j++){recebe[i] = segunda[j];}
    recebe[i] = '\0';
}
void verificacao(int vet[11], int local, int opc){
	int acc=0,resto,digito;
	int i,j;

	for(i=0, j = local; i < (local-1) ; i++ , j--){
        acc += j * vet[i];
	}

	resto = acc % 11;

	if((resto == 1) || (resto == 0)){
        resto = 0;
    }else{
        resto = 11 - resto;
	}

	if(!opc){
        vet[local-1] = resto;
    }
    if(tam){
        //char texto[100],cpf[15];
        //conversao_int_char(cpf,vet);
        //juntar_string("O CPF;  ",cpf, texto);
        if( resto != vet[local - 1]){
            //juntar_string(texto,"  é inválido!",texto);
            gtk_label_set_text(label,"O CPF é inválido");
            //mensagem("Aviso!", texto, "dialog-error");
        }else{
            //juntar_string(texto," é válido!",texto);
            gtk_label_set_text(label,"O CPF é válido");
            //mensagem("Aviso!", texto, "emblem-default");
        }
    }
    tam = 0;
}
void criacao(char cpf[14]){
	time_t t;
	int i,j;
	int criado[11];

	srand((unsigned) time(&t));

	for(i=0;i<9;i++){
        criado[i] = rand() % 10;
    }
	verificacao(criado, 10 , 0);
	verificacao(criado, 11 , 0);

    conversao_int_char(cpf, criado);

}
void estado(int num){
	switch (num){
        case 0:
			printf("\nO CPF é correspondente ao estado brasileiro: Rio Grande do Sul.");
				break;
		case 1:
			printf("\nO CPF é correspondentes aos estados brasileiros:  Distrito Federal, Goiás, Mato Grosso do Sul e Tocantins.");
				break;
		case 2:
			printf("\nO CPF é correspondentes aos estados brasileiros: Pará, Amazonas, Acre, Amapá, Rondônia e Roraima.");
				break;
		case 3:
			printf("\nO CPF é correspondentes aos estados brasileiros: Ceará, Maranhão e Piauí.");
				break;
		case 4:
			printf("\nO CPF é correspondentes aos estados brasileiros: Pernambuco, Rio Grande do Norte, Paraíba e Alagoas.");
				break;
		case 5:
			printf("\nO CPF é correspondentes aos estados brasileiros: Bahia e Sergipe.");
				break;
		case 6:
			printf("\nO CPF é correspondente ao estado brasileiro: Minas Gerais.");
                break;
        case 7:
			printf("\nO CPF é correspondentes aos estados brasileiros: Rio de Janeiro e Espírito Santo.");
                break;
        case 8:
			printf("\nO CPF é correspondente ao estado brasileiro: São Paulo.");
				break;
		case 9:
			printf("\nO CPF é correspondentes aos estados brasileiros: Paraná e Santa Catarina.");
				break;
	}
}
void mensagem(char text[100], char secondary_text[100], char icon_name[100]){
    GtkMessageDialog *mensagem_dialogo = gtk_builder_get_object(builder, "mensagem");

    g_object_set(mensagem_dialogo, "text",           text,           NULL);
    g_object_set(mensagem_dialogo, "secondary_text", secondary_text, NULL);
    g_object_set(mensagem_dialogo, "icon_name",      icon_name,      NULL);

    gtk_widget_show_all(mensagem_dialogo);
    gtk_dialog_run     (mensagem_dialogo);
    gtk_widget_hide    (mensagem_dialogo);
}
void on_main_window_destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}
void on_button_verificar_ini_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack,"view_verificacao");
}
void on_button_cria_ini_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack,"view_criacao");
}
void on_sair_clicked(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}
void on_button_verificar_cpf_verificar_clicked(GtkWidget *widget, gpointer data){
    char *cad_cpf = gtk_entry_get_text(gtk_builder_get_object(builder, "cad_cpf"));
    int cpf[11];
    int i;
    label = GTK_LABEL(gtk_builder_get_object(builder, "label_verificacao"));
    conversao_char_int(cad_cpf,cpf);
	verificacao(cpf, 11 , 1);
}
void on_button_verificar_cpf_voltar_clicked(GtkWidget *widget, gpointer data){
    gtk_label_set_text(label," ");
    gtk_stack_set_visible_child_name(stack,"view_inicial");
}
void on_button_criacao_cpf_criar_clicked(GtkWidget *widget, gpointer data){
    char texto[100],cpf[15];
    label = GTK_LABEL(gtk_builder_get_object(builder, "label_criacao"));
    criacao(cpf);
    //juntar_string("CPF;  ",cpf,texto);
    gtk_label_set_text(label,cpf);
    //mensagem("CPF criado", texto, "emblem-default");
}
void on_button_criacao_cpf_voltar_clicked(GtkWidget *widget, gpointer data){
    gtk_label_set_text(label,"000.000.000-00");
    gtk_stack_set_visible_child_name(stack,"view_inicial");
}
//#################################
int main(int argc, char *argv[]){

    FreeConsole();
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("infos\\ui.glade");

    gtk_builder_add_callback_symbols(builder,
        "on_main_window_destroy",                    G_CALLBACK(on_main_window_destroy),
        "on_button_verificar_ini_clicked",           G_CALLBACK(on_button_verificar_ini_clicked),
        "on_button_cria_ini_clicked",                G_CALLBACK(on_button_cria_ini_clicked),
        "on_sair_clicked",                           G_CALLBACK(on_sair_clicked),
        "on_button_verificar_cpf_verificar_clicked", G_CALLBACK(on_button_verificar_cpf_verificar_clicked),
        "on_button_verificar_cpf_voltar_clicked",    G_CALLBACK(on_button_verificar_cpf_voltar_clicked),
        "on_button_criacao_cpf_criar_clicked",       G_CALLBACK(on_button_criacao_cpf_criar_clicked),
        "on_button_criacao_cpf_voltar_clicked",      G_CALLBACK(on_button_criacao_cpf_voltar_clicked),
        NULL);

    gtk_builder_connect_signals(builder,NULL);

    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    gtk_widget_show_all(window);
    gtk_main();
    return 0;

}
//#################################
/*********************************************************************************************************************/
