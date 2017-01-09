#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#define MAX100 100

typedef struct product
{
    //colocar um id
    //idd++, incrementar o idd automaticamente
    int id;
    char nome[MAX100];      //colocar as strings num vetor para conter os nomes dos varios produtos
    int categoria;
    int calorias;
    int lactose; //se tiver lactos->1, se nao tiver lactos->0
} PRODUCT;

typedef struct listCompras
{
    char name[MAX100];      //colocar as strings num vetor para conter os nomes das varias listas
    PRODUCT produtos[MAX100];
} SHOPPINGLIST;

void menu(); //acesso ao menu

int create_product(PRODUCT *produtos,int nCategorias); //cria produtos com as respetivas caracteristicas
void print_product(int nProdutos, PRODUCT produtos[MAX100]); //imprime os produtos criados
int create_ShoppingList(SHOPPINGLIST *listaCompras, PRODUCT *produto,int nCategorias); //cria listas e produtos com as respetivas caracteristicas
void print_ShoppingList(int nListas, int nProdutos, SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //imprime listas e produtos com as respetivas caracteristicas

void insert_product(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100],int nCategorias); //insere produtos numa lista
void edit_product(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100],int nCategorias); //edita produtos numa lista
void eliminate_product(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //elimina produtos numa lista

void print_categorie(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //lista por categoria
void print_Kcal(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //lista por intervalo de Kcal, sendo que vMin=valor minimo e vMax=Valor maximo
void print_lactose(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //lista por existencia ou nao de lactose

void save_in_file(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //guarda listas num ficheiro.txt
void read_in_file(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]); //le as listas de um ficheiro.txt

int create_categorie(int Categoria[MAX100],int nCategorias); //cria uma categoria e verifica se esta existe
void print_categorie2(int Categoria[MAX100],int nCategorias); //imprime uma categoria
#endif // BIBLIOTECA_H_INCLUDED
