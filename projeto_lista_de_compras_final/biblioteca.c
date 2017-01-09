#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

PRODUCT produtos[MAX100]; //funçao create_product
PRODUCT produto[MAX100]; //funçao create_ShoppingList
SHOPPINGLIST listaCompras[MAX100]; //funçao create_ShoppingList
int Categoria[MAX100]; //funcao create_categorie

void menu()
{
    int option=0;
    int nCategorias=0;
    char option1='\0';
    char option2='\0';
    char option3='\0';



    printf("\nLISTA DE COMPRAS\n\n");
    printf("\nPressione [1] para criar categorias de produtos\n");
    printf("\nPressione [2] para criar produtos\n");
    printf("\nPressione [3] para criar listas de compras\n");
    printf("\nPressione [4] para inserir, eliminar e editar os produtos das listas de compras\n");
    printf("\nPressione [5] para listar os produtos da lista de compras por categoria, por intervalo de kcal e por produtos com ou sem lactose\n");
    printf("\nPressione [6] para ler/gravar as listas de compras ja criadas\n");
    printf("\nPressione [0] para sair\n\n");
    printf("\nOpcao escolhida: ");
    scanf("%d",&option);
    switch (option)
    {
    case 1:
        printf("\n\n-------CRIAR CATEGORIA-------\n");
        printf("\nInsira o numero de categorias a criar: ");
        scanf("%d",&nCategorias);
        create_categorie(Categoria,nCategorias);
        print_categorie2(Categoria,nCategorias);
        menu();
        break;
    case 2:
        printf("\n\n-------CRIAR PRODUTOS-------\n");
        create_product(produtos,nCategorias);
        menu();
        break;
    case 3:
        printf("\n\n-------CRIAR LISTA DE COMPRAS-------\n");
        create_ShoppingList(listaCompras,produto,nCategorias);
        menu();
        break;
    case 4:
        printf("\nIntroduza a opcao: \ni->inserir produtos nas listas de compras\n\nd->eliminar produtos das listas de compras\n\ne->editar produtos das listas de compras\n");
        scanf(" %c",&option1);

        switch (option1)
        {
        case 'i':
            insert_product(listaCompras,produto,nCategorias);
            break;
        case 'd':
            eliminate_product(listaCompras,produto);
            break;
        case 'e':
            edit_product(listaCompras,produto,nCategorias);
            break;
        }

        menu();
        break;
    case 5:
        printf("\nIntroduza a opcao: \nc->listar os produtos da lista de compras por categoria\n\nk->listar os produtos da lista de compras por intervalo de kcal\n\nl->Listar os produtos da lista de compras por produtos com ou sem lactose\n");
        scanf(" %c",&option2);

        switch (option2)
        {
        case 'c':
            print_categorie(listaCompras,produto);
            break;
        case 'k':
            print_Kcal(listaCompras,produto);
            break;
        case 'l':
            print_lactose(listaCompras,produto);
            break;
        }
        menu();
        break;
    case 6:
        printf("\nIntroduza a opcao: \nr->ler listas de compras de um ficheiro.txt\n\ng->gravar listas de compras num ficheiro.txt\n");
        scanf(" %c",&option3);
        switch(option3)
        {
        case 'r':
            read_in_file(listaCompras,produto);
            break;
        case 'g':
            save_in_file(listaCompras,produto);
            break;
        }
        menu();
        break;
    case 0:
        break;
    default:
        printf("\nOpcao invalida!\n");
        menu();
        break;
    }
}

/*So consegue armazenar um produto*/
int create_product(PRODUCT *produtos,int nCategorias)
{
    int i=0,j=0;
    char option;
    int nProdutos=0;
    produtos->id=0;

    printf("\nInsira o numero de produtos a criar: ");
    scanf("%d",&nProdutos);

    for(i=0; i<nProdutos; i++)
    {
        printf("\nIntroduza um nome do produto %d: ",i+1);
        fflush(stdin);  // limpa o buffer
        gets(produtos[i].nome);
        printf("\nIntroduza a categoria do produto %d: ",i+1);
        scanf("%d",&produtos[i].categoria);

        for(j=0; j<nCategorias; j++)
        {
            if(produtos[i].categoria!=Categoria[j])
            {
                printf("\nCategoria nao existente. Deseja criar? ( s -> sim / n -> nao): ");
                scanf(" %c",&option);

                switch (option)
                {
                case 's':
                    create_categorie(Categoria,1);
                    break;
                case 'n':
                    ;
                    break;
                }
            }
        }

        printf("\nIntroduza a quantidade de KCal do produto %d: ",i);
        scanf("%d",&produtos[i].calorias);
        printf("\nIntroduza a existencia de lactose ( 1 ) ou nao ( 0 ) do produto %d: ",i);
        scanf("%d",&produtos[i].lactose);
        produtos[i].id++;
    }
    print_product(nProdutos,produtos);
    return nProdutos;
}

int create_categorie(int Categoria[MAX100],int nCategorias)
{
    int i=0;

    for(i=0; i<nCategorias; i++)
    {

        printf("\nIntroduza a %d categoria: ",i+1);
        scanf("%d",&Categoria[i]);
    }

    return 0;
}

void print_categorie2(int Categoria[20],int nCategorias)
{
    int i=0;
    for(i=0; i<nCategorias; i++)
    {

        printf("\nCategoria %d: %d\n",i+1,Categoria[i]);

    }
}

void print_product(int nProdutos, PRODUCT produtos[MAX100])
{
    int i=0;

    for(i=0; i<nProdutos; i++)
    {
        printf("\nNome do produto %d: %s\n",i+1,produtos[i].nome);
        printf("\nCategoria do produto %d: %d\n",i+1,produtos[i].categoria);
        printf("\nCalorias do produto %d: %d\n",i+1,produtos[i].calorias);
        if(produtos[i].lactose==1)
        {
            printf("\nO produto %d tem lacotose\n",i+1);
        }
        else if(produtos[i].lactose==0)
        {
            printf("\nO produto %d nao tem lacotose\n",i+1);
        }
    }
}

int create_ShoppingList(SHOPPINGLIST *listaCompras, PRODUCT *produto,int nCategorias)
{
    int i=0,j=0,k=0;
    listaCompras->produtos->id=0;

    char option;

    int nListas=0,nProdutos=0;

    printf("\nInsira o numero de listas de compras a criar: ");
    scanf("%d",&nListas);


    for(i=0; i<nListas; i++)
    {
        printf("\nIntroduza o nome da lista %d: ",i+1);
        fflush(stdin);
        gets(listaCompras[i].name);

        printf("\nIntroduza o numero de produtos a criar: ");
        scanf("%d",&nProdutos);

        for(j=0; j<nProdutos; j++)
        {
            printf("\nIntroduza um nome do produto %d: ",j+1);
            fflush(stdin);  // limpa o buffer
            gets(listaCompras[i].produtos[j].nome);
            printf("\nIntroduza a categoria do produto %d: ",j+1);
            scanf("%d",&listaCompras[i].produtos[j].categoria);

            for(k=0; k<nCategorias; k++)
            {
                if(produtos[i].categoria!=Categoria[k])
                {
                    printf("\nCategoria nao existente. Deseja criar? ( s -> sim / n -> nao): ");
                    scanf(" %c",&option);

                    switch (option)
                    {
                    case 's':
                        create_categorie(Categoria,1);
                        break;
                    case 'n':
                        ;
                        break;
                    }
                }
            }

            printf("\nIntroduza a quantidade de KCal do produto %d: ",j+1);
            scanf("%d",&listaCompras[i].produtos[j].calorias);
            printf("\nIntroduza a existencia de lactose ( 1 ) ou nao ( 0 ) do produto %d: ",j+1);
            scanf("%d",&listaCompras[i].produtos[j].lactose);
            listaCompras[i].produtos[j].id++;
        }
    }
    return nListas;
}

void print_ShoppingList(int nListas, int nProdutos, SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100]) //NAO CONLUIDO!!! problemas com a leitura dos nomes e se uma lista tiver mais que um produto
{
    int i=0,j=0;

    for(i=0; i<nListas; i++)
    {
        printf("\nNome da lista %d: %s\n",i+1,listaCompras[i].name);
        fflush(stdin);
        for(j=0; j<nProdutos; j++)
        {
            printf("\nNome do produto %d: %s\n",j+1,listaCompras[i].produtos[j].nome);
            fflush(stdin);
            printf("\nCategoria do produto %d: %d\n",j+1,listaCompras[i].produtos[j].categoria);
            printf("\nCalorias do produto %d: %d\n",j+1,listaCompras[i].produtos[j].calorias);
            if(listaCompras[i].produtos[j].lactose==1)
            {
                printf("\nO produto %d tem lacotose\n",j+1);
            }
            else if(listaCompras[i].produtos[j].lactose==0)
            {
                printf("\nO produto %d nao tem lacotose\n",j+1);
            }
        }
    }
}

void insert_product(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100],int nCategorias)
{
    int produtos=0,i=0,j=0,k=0;
    char lista[MAX100],option;

    int nListas=0;
    int nProdutos=0;

    printf("\nInsira o numero de listas de compras a verificar: ");
    scanf("%d",&nListas);

    fflush(stdin);
    printf("\nIndique qual a lista a inserir o produto: ");
    gets(lista);

    for(j=0; j<nListas; j++)
    {
        if(strcmp(lista,listaCompras[j].name)==0) //verifica se um o nome inserido é igual ao nome da lista
        {
            if(listaCompras[j].produtos[i].id!=0)
                listaCompras[j].produtos[i].id+=1; //para começar na posiçao a seguir, da dos produtos ja existentes

            printf("\nInsira o numero de produtos da lista de compras: ");
            scanf("%d",&nProdutos);

            printf("\nInsira quantos produtos a colocar na lista: ");
            scanf("%d",&produtos);

            for(i=nProdutos; i<nProdutos+produtos; i++) //i=numero de produtos existentes +1
            {

                printf("\nIntroduza um nome do produto %d: ",i+1);
                fflush(stdin);  // limpa o buffer
                gets(listaCompras[j].produtos[i].nome);
                printf("\nIntroduza a categoria do produto %d: ",i+1);
                scanf("%d",&listaCompras[j].produtos[i].categoria);

                for(k=0; k<nCategorias; k++)
                {
                    if(listaCompras[j].produtos[i].categoria!=Categoria[k])
                    {
                        printf("\nCategoria nao existente. Deseja criar? ( s -> sim / n -> nao): ");
                        scanf(" %c",&option);

                        switch (option)
                        {
                        case 's':
                            create_categorie(Categoria,1);
                            break;
                        case 'n':
                            ;
                            break;
                        }
                    }
                }

                printf("\nIntroduza a quantidade de KCal do produto %d: ",i+1);
                scanf("%d",&listaCompras[j].produtos[i].calorias);
                printf("\nIntroduza a existencia de lactose ( 1 ) ou nao ( 0 ) do produto %d: ",i+1);
                scanf("%d",&listaCompras[j].produtos[i].lactose);
            }
        }

    }
    print_ShoppingList(nListas,(nProdutos+produtos),listaCompras,produto);
}

void edit_product(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100],int nCategorias)
{
    int produtos=0,i=0,j=0,k=0,l=0;
    char lista[MAX100];
    char nomeProduto[MAX100];
    char option;

    int nListas=0;
    int nProdutos=0;

    printf("\nInsira o numero de listas de compras a verificar: ");
    scanf("%d",&nListas);

    fflush(stdin);
    printf("\nIndique qual a lista a editar o produto: ");
    gets(lista);


    for(j=0; j<nListas; j++)
    {
        printf("\nInsira o numero de produtos da lista de compras: ");
        scanf("%d",&nProdutos);
        if(strcmp(lista,listaCompras[j].name)==0) //verifica se um o nome inserido é igual ao nome da lista
        {
            listaCompras[j].produtos[i].id+=1;

            fflush(stdin);
            printf("\nInsira quantos produtos a editar na lista: ");
            scanf("%d",&produtos);

            for(i=0; i<produtos; i++)
            {
                fflush(stdin);
                printf("\nIndique qual o nome do produto a editar: ");
                gets(nomeProduto);

                for(k=0; k<nProdutos; k++)
                {
                    if(strcmp(nomeProduto,listaCompras[j].produtos[k].nome)==0) //verifica se um o nome inserido é igual ao nome do produto
                    {
                        printf("\nIntroduza um nome do produto %d: ",k+1);
                        fflush(stdin);  // limpa o buffer
                        gets(listaCompras[j].produtos[k].nome);
                        printf("\nIntroduza a categoria do produto %d: ",k+1);
                        scanf("%d",&listaCompras[j].produtos[k].categoria);

                        for(l=0; l<nCategorias; l++)
                        {
                            if(listaCompras[j].produtos[k].categoria!=Categoria[l])
                            {
                                printf("\nCategoria nao existente. Deseja criar? ( s -> sim / n -> nao): ");
                                scanf(" %c",&option);

                                switch (option)
                                {
                                case 's':
                                    create_categorie(Categoria,1);
                                    break;
                                case 'n':
                                    ;
                                    break;
                                }
                            }
                        }

                        printf("\nIntroduza a quantidade de KCal do produto %d: ",k+1);
                        scanf("%d",&listaCompras[j].produtos[k].calorias);
                        printf("\nIntroduza a existencia de lactose ( 1 ) ou nao ( 0 ) do produto %d: ",k+1);
                        scanf("%d",&listaCompras[j].produtos[k].lactose);
                        listaCompras[j].produtos[k].id++;
                    }
                }
            }
        }
    }

    print_ShoppingList(nListas,nProdutos,listaCompras,produto);
}

void eliminate_product(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100])
{
    int produtos=0,i=0,j=0,k=0;
    char lista[MAX100];
    char nomeProduto[MAX100];

    int nListas=0;
    int nProdutos=0;

    printf("\nInsira o numero de listas de compras a verificar: ");
    scanf("%d",&nListas);

    fflush(stdin);
    printf("\nIndique qual a lista a eliminar o produto: ");
    gets(lista);

    for(j=0; j<nListas; j++)
    {
        printf("\nInsira o numero de produtos da lista de compras: ");
        scanf("%d",&nProdutos);

        if(strcmp(lista,listaCompras[j].name)==0) //verifica se um o nome inserido é igual ao nome da lista
        {
            listaCompras[j].produtos[i].id+=1;

            fflush(stdin);
            printf("\nInsira quantos produtos a eliminar na lista: ");
            scanf("%d",&produtos);

            for(i=0; i<produtos; i++)
            {
                fflush(stdin);
                printf("\nIndique qual o nome do produto a eliminar: ");
                gets(nomeProduto);
                for(k=0; k<nProdutos; k++)
                {
                    if(strcmp(nomeProduto,listaCompras[j].produtos[k].nome)==0) //verifica se um o nome inserido é igual ao nome do produto
                    {
                        strcpy(listaCompras[j].produtos[k].nome,listaCompras[j].produtos[k+1].nome);
                        listaCompras[j].produtos[k].categoria=listaCompras[j].produtos[k+1].categoria;
                        listaCompras[j].produtos[k].calorias=listaCompras[j].produtos[k+1].calorias;
                        listaCompras[j].produtos[k].lactose=listaCompras[j].produtos[k+1].lactose;
                        listaCompras[j].produtos[k].id++;

                        //diminuir nProdutos
                        nProdutos--;
                    }
                }
            }
        }
        print_ShoppingList(nListas,nProdutos,listaCompras,produto);
    }
}

void print_categorie(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100])
{
    int i=0,j=0;
    int nListas=0, nProdutos=0;
    printf("\nIntroduza o numero de listas: ");
    scanf("%d",&nListas);

    int cat=0; //listar em Kcal
    printf("\nIntroduza a categoria a pesquisar: ");
    scanf("%d",&cat);


    for(i=0; i<nListas; i++)
    {

        printf("\nIntroduza o numero de produtos: ");
        scanf("%d",&nProdutos);

        for(j=0; j<nProdutos; j++)
        {
            if(listaCompras[i].produtos[j].calorias==cat)
                printf("\nCategoria: %d - Produto: %d - Lista: %d\n",listaCompras[i].produtos[j].categoria,j+1,i+1);
        }
    }
}

void print_Kcal(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100])
{
    int i=0,j=0;


    int nListas=0, nProdutos=0;
    printf("\nIntroduza o numero de listas: ");
    scanf("%d",&nListas);

    int vMin=0,vMax=0; //listar em Kcal
    printf("\nIntroduza o valor minimo e valor maximo: ");
    scanf("%d %d",&vMin,&vMax);

    for(i=0; i<nListas; i++)
    {

        printf("\nIntroduza o numero de produtos: ");
        scanf("%d",&nProdutos);

        for(j=0; j<nProdutos; j++)
        {
            if(listaCompras[i].produtos[j].calorias>= vMin && listaCompras[i].produtos[j].calorias<=vMax)
                printf("\nKcal: %d - Produto: %d - Lista: %d\n",listaCompras[i].produtos[j].calorias,j+1,i+1);
        }
    }
}

void print_lactose(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100])
{
    int i=0,j=0;

    int nListas=0, nProdutos=0;
    printf("\nIntroduza o numero de listas: ");
    scanf("%d",&nListas);

    for(i=0; i<nListas; i++)
    {

        printf("\nIntroduza o numero de produtos: ");
        scanf("%d",&nProdutos);

        for(j=0; j<nProdutos; j++)
        {
            if(listaCompras[i].produtos[j].lactose==0)
                printf("\nNao tem lactose - Produto: %d - Lista: %d\n",j+1,i+1);
            else if(listaCompras[i].produtos[j].lactose==1)
                printf("\nTem lactose - Produto: %d - Lista: %d\n",j+1,i+1);
        }
    }
}

void save_in_file(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100])
{
    FILE *fp;
    int i=0,j=0;

    int nListas=0, nProdutos=0;

    fp=fopen("listas.txt","w");
    if(fp!=NULL)
    {
        printf("\nIntroduza o numero de listas: ");
        scanf("%d",&nListas);
        fprintf(fp,"Numero de listas: %d\n",nListas); //coloca o numero de listas no ficheiro

        for(i=0; i<nListas; i++)
        {
            printf("\nIntroduza o numero de produtos da lista %d: ",i+1);
            scanf("%d",&nProdutos);
            fprintf(fp,"Numero de produtos da lista %d: %d\n",i+1,nProdutos); //coloca o numero de produtos no ficheiro

            fprintf(fp,"Nome da lista %d: %s\n",i+1,listaCompras[i].name);

            for(j=0; j<nProdutos; j++)
            {
                fprintf(fp,"Nome do produto %d: %s\n",j+1,listaCompras[i].produtos[j].nome);
                fprintf(fp,"Categoria do produto %d: %d\n",j+1,listaCompras[i].produtos[j].categoria);
                fprintf(fp,"Calorias do produto %d: %d\n",j+1,listaCompras[i].produtos[j].calorias);
                if(listaCompras[i].produtos[j].lactose==1)
                {
                    fprintf(fp,"O produto %d tem lactose\n",j+1);
                }
                else
                {
                    fprintf(fp,"O produto %d nao tem lactose\n",j+1);
                }
            }
        }
        fclose(fp);
    }
    else
        printf("\nNao foi possivel criar o ficheiro desejado\n");
}

void read_in_file(SHOPPINGLIST listaCompras[MAX100], PRODUCT produto[MAX100])
{
    FILE *fp;
    int i=0,j=0;
    char linha[MAX100];
    char aux[MAX100];

    int nListas=0, nProdutos=0;

    fp=fopen("listas.txt","r");
    if(fp!=NULL)
    {
        fscanf(fp,"%*s %*s %*s %d\n", &nListas); //le o numero de listas do ficheiro para que o utilizador nao tenha de inserir

        printf("\nNumero de listas: %d\n",nListas);
        for(i=0; i<nListas; i++)
        {
            fscanf(fp,"%*s %*s %*s %*s %*s %*s %d\n",&nProdutos);//le o numero de produtos do ficheiro para que o utilizador nao tenha de inserir

            fgets(linha,sizeof(linha),fp);              //nome da lista
            linha[strlen(linha)-1]=0; 				    // retira quebra de linha
            strcpy(listaCompras[i].name, &linha[17]);   //copia para a lista de compras o seu nome

            printf("\nNumero de produtos da lista %d: %d\n",i+1,nProdutos);
            for(j=0; j<nProdutos; j++)
            {
                fgets(linha,sizeof(linha),fp);              //nome da produto
                linha[strlen(linha)-1]=0; 				    // retira quebra de linha
                strcpy(listaCompras[i].produtos[j].nome, &linha[19]);   //copia para a lista de compras o nome do produto

                fscanf(fp,"%*s %*s %*s %*s %d\n",&listaCompras[i].produtos[j].categoria); // ignore the string and store only the int
                fscanf(fp,"%*s %*s %*s %*s %d\n",&listaCompras[i].produtos[j].calorias);

                fgets(linha,sizeof(linha),fp);              //existencia ou nao de lactose
                linha[strlen(linha)-1]=0; 				    // retira quebra de linha

                if(j>=10)
                {
                    strcpy(aux,&linha[13]);   //copia para a lista de compras a existencia ou nao de lactose
                    if(strcmp(aux,"nao tem lactose")==0)
                    {
                        listaCompras[i].produtos[j].lactose=0;
                    }
                    else
                    {
                        listaCompras[i].produtos[j].lactose=1;
                    }
                }
                else
                {
                    strcpy(aux,&linha[12]);   //copia para a lista de compras a existencia ou nao de lactose
                    if(strcmp(aux,"nao tem lactose")==0)
                    {
                        listaCompras[i].produtos[j].lactose=0;
                    }
                    else
                    {
                        listaCompras[i].produtos[j].lactose=1;
                    }
                }
            }
        }
        fclose(fp);
    }
    else
        printf("\nNao foi possivel abrir o ficheiro desejado\n");


    print_ShoppingList(nListas,nProdutos,listaCompras,produto);
}
