#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "supermercado.h"

int exibir_opcoes_iniciais() {
    int opcao;
    printf("\opções iniciais:\n");
    printf("1. Cadastrar usuario\n");
    printf("2. Login\n");
    printf("3. Excluir cadastro\n");
    printf("Escolha uma opções: ");
    scanf("%d", &opcao);
    return opcao;
}

void mensagem_boas_vindas() {
    printf("Bem-vindo ao Sistema de Compras!\n");
}

int exibir_menu() {
    int escolha;
    printf("\nMenu:\n");
    printf("1. Cadastrar item\n");
    printf("2. Listar itens\n");
    printf("3. Editar item\n");
    printf("4. Excluir item\n");
    printf("5. Buscar item\n");
    printf("0. Sair\n");
    printf("Escolha uma opções: ");
    scanf("%d", &escolha);
    return escolha;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Usuario* usuarios = carregar_usuarios();
    Item* produtos = carregar_itens();

    int opcao;
    do {
        opcao = exibir_opcoes_iniciais();

        switch (opcao) {
            case 1:
                cadastrar_usuario(&usuarios);
                break;
            case 2:
                while (!login(usuarios));
                break;
            case 3:
                excluir_usuario(&usuarios);
                break;
            default:
                printf("Opcoes invalidas. Por favor, escolha uma opcao invalida.\n");
        }
    } while (opcao != 2);

    mensagem_boas_vindas();

    int escolha;
    do {
        escolha = exibir_menu();

        switch (escolha) {
            case 1:
                cadastrar_item(&produtos);
                break;
            case 2:
                listar_itens(produtos);
                break;
            case 3:
                editar_item(produtos);
                break;
            case 4:
                excluir_item(&produtos);
                break;
            case 5:
                buscar_item(produtos);
                break;
            case 0:
                printf("Saindo...\n");
                printf("Obrigado por utilizar o Sistema de Compras! Volte sempre e tenha um Ã³timo dia!\n");
                break;
            default:
                printf("Opcao invalida. Por favor, escolha uma opcao invalida.\n");
        }
    } while (escolha != 0);

    salvar_usuarios(usuarios);
    salvar_itens(produtos);
    freeUsuarios(usuarios);
    freeProdutos(produtos);

    return 0;
}
