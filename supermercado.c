#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "supermercado.h"

#define limite_NOME_TAMANHO 50
#define limite_EMAIL_TAMANHO 80
#define limite_SENHA_TAMANHO 20
#define MAX_TENTATIVAS_LOGIN 3

struct usuario {
    char nome[limite_NOME_TAMANHO];
    char senha[limite_SENHA_TAMANHO];
    char email[limite_EMAIL_TAMANHO];
    struct Usuario* next;
};

struct item {
    char nome[limite_NOME_TAMANHO];
    float preco;
    int quantidade;
    float desconto;
    struct Item* next;
};

int login(Usuario* usuarios) {
    char nome[limite_NOME_TAMANHO];
    char senha[limite_SENHA_TAMANHO];
    int tentativas_restantes = MAX_TENTATIVAS_LOGIN;

    while (tentativas_restantes > 0) {
        printf("Login (tentativas restantes: %d)\n", tentativas_restantes);
        printf("Nome de usuÃ¡rio: ");
        scanf("%s", nome);
        printf("Senha: ");
        scanf("%s", senha);

        Usuario* current = usuarios;
        while (current != NULL) {
            if (strcmp(current->nome, nome) == 0 && strcmp(current->senha, senha) == 0) {
                printf("Login realizado com sucesso!\n");
                return 1;
            }
            current = current->next;
        }

        printf("Nome de usuario ou senha invalida. Por favor, tente novamente.\n");
        tentativas_restantes--;
    }

    printf("Excedido o numero maximo de tentativas. Retornando ao menu principal.\n");
    return 0;
}

int validar_email(char email[], Usuario* usuarios) {
    if (strlen(email) >= limite_EMAIL_TAMANHO || strchr(email, '@') == NULL) {
        return 0;
    }

    Usuario* current = usuarios;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void cadastrar_usuario(Usuario** usuarios) {
    char nome[limite_NOME_TAMANHO];
    char senha[limite_SENHA_TAMANHO];
    char email[limite_EMAIL_TAMANHO];

    printf("Cadastro de novo usuario\n");
    printf("Nome de usuÃ¡rio: ");
    scanf("%s", nome);
    printf("Senha: ");
    scanf("%s", senha);
    printf("E-mail: ");
    scanf("%s", email);

    if (!validar_email(email, *usuarios)) {
        printf("E-mail invalido ou ja cadastrado. Por favor, forneça um e-mail valido.\n");
        return;
    }

    Usuario* newUser = (Usuario*)malloc(sizeof(Usuario));
    strcpy(newUser->nome, nome);
    strcpy(newUser->senha, senha);
    strcpy(newUser->email, email);
    newUser->next = *usuarios;

    *usuarios = newUser;

    printf("Cadastro realizado com sucesso!\n");
}

void excluir_usuario(Usuario** usuarios) {
    char nome[limite_NOME_TAMANHO];
    printf("Digite o nome do usuÃ¡rio que deseja excluir: ");
    scanf("%s", nome);

    Usuario* current = *usuarios;
    Usuario* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *usuarios = current->next;
            }
            free(current);
            printf("Usuario excluído com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Usuario nao encontrado.\n");
}



void cadastrar_item(Item** produtos) {
    char nome[limite_NOME_TAMANHO];

    printf("Nome do item: ");
    scanf("%s", nome);

    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->nome, nome);
    printf("Preço do item: ");
    scanf("%f", &newItem->preco);
    printf("Quantidade do item: ");
    scanf("%d", &newItem->quantidade);
    printf("Desconto (em porcentagem): ");
    scanf("%f", &newItem->desconto);

    newItem->next = *produtos;
    *produtos = newItem;

    printf("Item cadastrado com sucesso!\n");
}

void listar_itens(Item* produtos) {
    if (produtos == NULL) {
        printf("Nao tem itens cadastrados.\n");
        return;
    }

    printf("Lista de Itens:\n");
    while (produtos != NULL) {
        printf("Nome: %s | Preço: %.2f | Quantidade: %d | Desconto: %.2f%%\n", produtos->nome, produtos->preco, produtos->quantidade, produtos->desconto);
        produtos = produtos->next;
    }
}

void editar_item(Item* produtos) {
    char nome[limite_NOME_TAMANHO];
    printf("Digite o nome do item que deseja editar:");
    scanf("%s", nome);

    while (produtos != NULL) {
        if (strcmp(produtos->nome, nome) == 0) {
            printf("Digite o novo nome do item: ");
            scanf("%s", produtos->nome);
            printf("Digite o novo preço do item: ");
            scanf("%f", &produtos->preco);
            printf("Digite a nova quantidade do item: ");
            scanf("%d", &produtos->quantidade);
            printf("Digite o novo desconto (em porcentagem): ");
            scanf("%f", &produtos->desconto);
            printf("Item editado com sucesso!\n");
            return;
        }
        produtos = produtos->next;
    }

    printf("Item nao encontrado.\n");
}

void excluir_item(Item** produtos) {
    char nome[limite_NOME_TAMANHO];
    printf("Digite o nome do item que deseja excluir: ");
    scanf("%s", nome);

    Item* current = *produtos;
    Item* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *produtos = current->next;
            }
            free(current);
            printf("Item excluÃ­do com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Item nao encontrado.\n");
}

void buscar_item(Item* produtos) {
    char nome[limite_NOME_TAMANHO];
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nome);

    int encontrado = 0;
    while (produtos != NULL) {
        if (strcmp(produtos->nome, nome) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s | Preco: %.2f | Quantidade: %d | Desconto: %.2f%%\n", produtos->nome, produtos->preco, produtos->quantidade, produtos->desconto);
            encontrado = 1;
            break;
        }
        produtos = produtos->next;
    }

    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}

void freeUsuarios(Usuario* head) {
    Usuario* current = head;
    while (current != NULL) {
        Usuario* nextUser = current->next;
        free(current);
        current = nextUser;
    }
}

void freeProdutos(Item* head) {
    Item* current = head;
    while (current != NULL) {
        Item* nextItem = current->next;
        free(current);
        current = nextItem;
    }
}

void salvar_usuarios(Usuario* usuarios) {
    FILE* file = fopen("usuarios.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuÃ¡rios.\n");
        return;
    }

    while (usuarios != NULL) {
        fwrite(usuarios, sizeof(Usuario), 1, file);
        usuarios = usuarios->next;
    }

    fclose(file);
}

Usuario* carregar_usuarios() {
    FILE* file = fopen("usuarios.dat", "rb");
    if (file == NULL) {
        return NULL; // Arquivo ainda nÃ£o existe
    }

    Usuario* head = NULL;
    Usuario* tail = NULL;
    Usuario* newUser;

    while (1) {
        newUser = (Usuario*)malloc(sizeof(Usuario));
        if (fread(newUser, sizeof(Usuario), 1, file) != 1) {
            free(newUser);
            break;
        }

        newUser->next = NULL;

        if (head == NULL) {
            head = newUser;
        } else {
            tail->next = newUser;
        }
        tail = newUser;
    }

    fclose(file);
    return head;
}

void salvar_itens(Item* produtos) {
    FILE* file = fopen("itens.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }

    while (produtos != NULL) {
        fwrite(produtos, sizeof(Item), 1, file);
        produtos = produtos->next;
    }

    fclose(file);
}

Item* carregar_itens() {
    FILE* file = fopen("itens.dat", "rb");
    if (file == NULL) {
        return NULL; 
    }

    Item* head = NULL;
    Item* tail = NULL;
    Item* newItem;

    while (1) {
        newItem = (Item*)malloc(sizeof(Item));
        if (fread(newItem, sizeof(Item), 1, file) != 1) {
            free(newItem);
            break;
        }

        newItem->next = NULL;

        if (head == NULL) {
            head = newItem;
        } else {
            tail->next = newItem;
        }
        tail = newItem;
    }

    fclose(file);
    return head;
}
