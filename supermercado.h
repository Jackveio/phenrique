typedef struct usuario Usuario;
typedef struct item Item;

int login(Usuario* usuarios);

void cadastrar_usuario(Usuario** usuarios);

void excluir_usuario(Usuario** usuarios);

void cadastrar_item(Item** produtos);

void listar_itens(Item* produtos);

void editar_item(Item* produtos);

void excluir_item(Item** produtos);

void buscar_item(Item* produtos);

void freeUsuarios(Usuario* head);

void freeProdutos(Item* head);

void salvar_usuarios(Usuario* usuarios);

Usuario* carregar_usuarios();

void salvar_itens(Item* produtos);

Item* carregar_itens();

void freeUsuarios(Usuario* head);

void freeProdutos(Item* head);
