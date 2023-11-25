#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

#define Enter 13
#define Tab 9
#define BCKSPC 8

struct user
{
    char fullName[50];
    char email[50];
    char password[50];
    char username[50];
    char phone[50];
};

typedef struct {
    char nomeEmpresa[50];
    char nomeFantasia[50];
    int telefoneEmpresa;
    int cnpj;
    char razaoSocial[500];
    char emailEmpresa[50];
    char relatorioResiduos[500];
    char relatorioValor[500];
    struct {
        char rua[50];
        int numero;
        char bairro[50];
        char cidade[50];
        char estado[50];
        int CEP;
    }endereco;


}empresa;


void takeinput(char ch[50])
{
    fgets(ch,50,stdin);
    ch[strlen(ch)-1]='\0';
}

char generateUsername(char email[50],char username[50])
{
    int i;
    for(i=0;i<strlen(email);i++)
    {
        if (email[i] == '@')
        {
            break;
        }
        else
        {
            username[i] = email[i];
        }
    }
    username[i]='\0';
}

void takepassword(char pwd[50])
{

    fgets(pwd,50,stdin);
}



void display(){
    empresa e1;
    FILE *fp;
    fp = fopen("empresas.txt", "r");

    while(fread(&e1, sizeof(empresa),1,fp)){
        printf("\n----------------- %s -----------------", e1.nomeEmpresa);
        printf("\nNOME DA EMPRESA: %s", e1.nomeEmpresa);
        printf("\nNOME FANTASIA: %s", e1.nomeFantasia);
        printf("\nCNPJ DA EMPRESA: %d", e1.cnpj);
        printf("\nTELEFONE: %d", e1.telefoneEmpresa);
        printf("\nRAZAO SOCIAL: %s", e1.razaoSocial);
        printf("\nE-MAIL: %s", e1.emailEmpresa);
        printf("\n-----------------");
        printf("\nRELATORIO DE RESIDUOS: %s\n", e1.relatorioResiduos);
        printf("\nRELATORIO VALOR: %s\n", e1.relatorioValor);
        printf("\n-----------------");
        printf("\nESTADO: %s, CIDADE: %s, BAIRRO: %s, RUA: %s, NUMERO: %d", e1.endereco.estado, e1.endereco.cidade, e1.endereco.bairro, e1.endereco.rua, e1.endereco.numero );
        printf("\nCEP: %d", e1.endereco.CEP);
        printf("\n-----------------");
    }


    fclose(fp);

}

//cria uma ou mais empresas
void append(){
    empresa *e;
    FILE *fp;
    int n, i, j;

    printf("\nQuantas empresas quer cadastrar?\nQuantidade:\t");
    scanf("%d", &n);

    e = (empresa*)calloc(n, sizeof(empresa));
    fp = fopen("empresas.txt", "a");

    for(i = 0; i<n; i++){
        //informa��es da empresa
        int numEmp = i + 1;
        printf("\n-----------------");
        printf("\nNome da %d empresa: ", numEmp);
        fflush(stdin);
        scanf("%[^\n]", &e[i].nomeEmpresa);
        fflush(stdin);
        printf("\nNome Fantasia: ");
        scanf("%[^\n]", &e[i].nomeFantasia);
        fflush(stdin);
        printf("\nNumero de Telefone: ");
        scanf("%d", &e[i].telefoneEmpresa);
        fflush(stdin);
        printf("\nCNPJ (apenas numeros): ");
        scanf("%d", &e[i].cnpj);
        fflush(stdin);
        printf("\nRazao social: ");
        scanf("%[^\n]", &e[i].razaoSocial);
        fflush(stdin);
        printf("\nE-mail: ");
        scanf("%s", &e[i].emailEmpresa);
        fflush(stdin);
        printf("\nRelatorio de residuos: ");
        scanf("%[^\n]", &e[i].relatorioResiduos);
        fflush(stdin);
        printf("\nRelatorio de valor: ");
        scanf("%[^\n]", &e[i].relatorioValor);
        fflush(stdin);

        //endere�o
        printf("\n--Endereco da empresa--");
        printf("\nRua: ");
        scanf("%s", &e[i].endereco.rua);
        fflush(stdin);
        printf("\nNumero: ");
        scanf("%d", &e[i].endereco.numero);
        fflush(stdin);
        printf("\nBairro: ");
        scanf("%s", &e[i].endereco.bairro);
        fflush(stdin);
         printf("\nCidade: ");
        scanf("%s", &e[i].endereco.cidade);
        fflush(stdin);
        printf("\nEstado: ");
        scanf("%s", &e[i].endereco.estado);
        fflush(stdin);
        printf("\nCEP: ");
        scanf("%d", &e[i].endereco.CEP);
        fflush(stdin);
        printf("\n-----------------");
        fwrite(&e[i],sizeof(empresa),1,fp);
    }
    fclose(fp);
}

void numEmpresas(){
    empresa e1;
    FILE *fp;
    fp = fopen("empresas.txt", "r");

    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(empresa);
    printf("\n----------------------------------------------------");
    printf("\n Numero total de empresas cadastradas: %d", n);
    printf("\n----------------------------------------------------");
    fclose(fp);

}

void updateRelatorio(){
    empresa e1;
    int nCNPJ, found = 0;
    FILE *fp, *fp1;

    fp = fopen("empresas.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Coloque o numero do CNPJ da empresa (apenas  numeros) que deseja alterar : ");
    scanf("%d", &nCNPJ);

    while(fread(&e1, sizeof(empresa),1,fp))
    {

        if(e1.cnpj == nCNPJ){
            found = 1;
            printf("\n-------- Empresa: (%s) -------- ", e1.nomeEmpresa);
            fflush(stdin);
            printf("\nRelatorio de residuos: ");
            scanf("%[^\n]", &e1.relatorioResiduos);
            fflush(stdin);
            printf("\nRelatorio de valor: ");
            scanf("%[^\n]", &e1.relatorioValor);
            fflush(stdin);

        }
        fwrite(&e1, sizeof(empresa),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("empresas.txt", "w");

        while(fread(&e1,sizeof(empresa), 1, fp1)){
            fwrite(&e1,sizeof(empresa), 1,fp);
        }

        fclose(fp);
        fclose(fp1);
    }
    else{
        printf("\n----------------------------------------------------");
        printf("\nEmpresa nao encontrada");
        printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
        printf("\n----------------------------------------------------");
    }


    fclose(fp);
}


void updateEmpresas(){
    empresa e1;
    int nCNPJ, found = 0;
    FILE *fp, *fp1;

    fp = fopen("empresas.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Coloque o numero do CNPJ da empresa (apenas  numeros) que deseja alterar : ");
    scanf("%d", &nCNPJ);

    while(fread(&e1, sizeof(empresa),1,fp))
    {

        if(e1.cnpj == nCNPJ){
            found = 1;
            printf("\nNovo nome da empresa (%s) : ", e1.nomeEmpresa);
            fflush(stdin);
            scanf("%[^\n]", &e1.nomeEmpresa);
            fflush(stdin);
            printf("\nNome Fantasia: ");
            scanf("%[^\n]", &e1.nomeFantasia);
            fflush(stdin);
            printf("\nNumero de Telefone: ");
            scanf("%d", &e1.telefoneEmpresa);
            fflush(stdin);
            printf("\nCNPJ (apenas numeros): ");
            scanf("%d", &e1.cnpj);
            fflush(stdin);
            printf("\nRazao social: ");
            scanf("%s", &e1.razaoSocial);
            fflush(stdin);
            printf("\nE-mail: ");
            scanf("%s", &e1.emailEmpresa);
            fflush(stdin);
            printf("\nRelatorio de residuos: ");
            scanf("%[^\n]", &e1.relatorioResiduos);
            fflush(stdin);
            printf("\nRelatorio de valor: ");
            scanf("%[^\n]", &e1.relatorioValor);
            fflush(stdin);

            //endere�o
            printf("\n--Endereco da empresa--");
            printf("\nRua: ");
            scanf("%s", &e1.endereco.rua);
            fflush(stdin);
            printf("\nNumero: ");
            scanf("%d", &e1.endereco.numero);
            fflush(stdin);
            printf("\nBairro: ");
            scanf("%s", &e1.endereco.bairro);
            fflush(stdin);
             printf("\nCidade: ");
            scanf("%s", &e1.endereco.cidade);
            fflush(stdin);
            printf("\nEstado: ");
            scanf("%s", &e1.endereco.estado);
            fflush(stdin);
            printf("\nCEP: ");
            scanf("%d", &e1.endereco.CEP);
            fflush(stdin);
            printf("\n-----------------");
        }
        fwrite(&e1, sizeof(empresa),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("empresas.txt", "w");

        while(fread(&e1,sizeof(empresa), 1, fp1)){
            fwrite(&e1,sizeof(empresa), 1,fp);
        }

        fclose(fp);
        fclose(fp1);
    }
    else{
        printf("\n----------------------------------------------------");
        printf("\nEmpresa nao encontrada");
        printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
        printf("\n----------------------------------------------------");
    }


    fclose(fp);
}

void searchEmpresas(){
    empresa e1;
    int nCNPJ, found = 0;
    FILE *fp;
    fp = fopen("empresas.txt", "r");

    printf("Coloque o numero do CNPJ da empresa (apenas  numeros): ");
    scanf("%d", &nCNPJ);

    while(fread(&e1, sizeof(empresa),1,fp))
    {

        if(e1.cnpj == nCNPJ){
            found = 1;
            printf("\n--------- EMPRESA: %s --------- ", e1.nomeEmpresa);
            printf("\nNOME FANTASIA: %s", e1.nomeFantasia);
            printf("\nCNPJ DA EMPRESA: %d", e1.cnpj);
            printf("\nTELEFONE: %d", e1.telefoneEmpresa);
            printf("\nRAZAO SOCIAL: %s", e1.razaoSocial);
            printf("\nE-MAIL: %s", e1.emailEmpresa);
            printf("\n-----------------");
            printf("\nRELATORIO DE RESIDUOS: %s\n", e1.relatorioResiduos);
            printf("\nRELATORIO VALOR: %s\n", e1.relatorioValor);
            printf("\n-----------------");
            printf("\nESTADO: %s, CIDADE: %s, BAIRRO: %s, RUA: %s, NUMERO: %d", e1.endereco.estado, e1.endereco.cidade, e1.endereco.bairro, e1.endereco.rua, e1.endereco.numero );
            printf("\nCEP: %d", e1.endereco.CEP);
            printf("\n----------------------------------------------------");
        }

    }
    if(!found)
    {
        printf("\n----------------------------------------------------");
        printf("\nEmpresa nao encontrada");
        printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
        printf("\n----------------------------------------------------");
    }


    fclose(fp);
}


void relatorioEmpresas(){
    empresa e1;
    int nCNPJ, found = 0;
    FILE *fp;
    FILE *relatorio;
    fp = fopen("empresas.txt", "r");
    relatorio = fopen("relatorio.txt", "a");
    printf("Coloque o numero do CNPJ da empresa (apenas  numeros): ");
    scanf("%d", &nCNPJ);

    while(fread(&e1, sizeof(empresa),1,fp))
    {

        if(e1.cnpj == nCNPJ){
            found = 1;
            printf("\n--------- EMPRESA: %s --------- ", e1.nomeEmpresa);
            printf("\nRELATORIO DE RESIDUOS: %s\n", e1.relatorioResiduos);
            printf("\nRELATORIO VALOR: %s\n", e1.relatorioValor);
            printf("\nRelatorio baixado com sucesso, e possivel visualizar na pasta onde o programa foi instalado com o nome 'relatorio'");
            printf("\n----------------------------------------------------");
            fprintf(relatorio,"\n--------- EMPRESA: %s --------- \nRELATORIO DE RESIDUOS: %s\n\nRELATORIO VALOR: %s\n", e1.nomeEmpresa, e1.relatorioResiduos , e1.relatorioValor);
        }

    }
    if(!found)
    {
        printf("\n----------------------------------------------------");
        printf("\nEmpresa nao encontrada");
        printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
        printf("\n----------------------------------------------------");
    }

    fclose(relatorio);
    fclose(fp);
}


void delEmpresas(){
    empresa e1;
    int nCNPJ, opt, found = 0;
    FILE *fp, *fp1;

    fp = fopen("empresas.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Coloque o numero do CNPJ da empresa (apenas  numeros) que deseja apagar : ");
    scanf("%d", &nCNPJ);
    printf("Tem certeza que deseja apagar?:\n0. SIM\n1.NAO\nSua escolha:\t ");
    scanf("%d", &opt);

    if (opt == 0){

        while(fread(&e1, sizeof(empresa),1,fp))
        {

            if(e1.cnpj == nCNPJ){
                found = 1;
            } else{
                fwrite(&e1, sizeof(empresa),1,fp1);
            }
        }
        fclose(fp);
        fclose(fp1);
        if(found){
            fp1 = fopen("temp.txt", "r");
            fp = fopen("empresas.txt", "w");

            while(fread(&e1,sizeof(empresa), 1, fp1)){
                fwrite(&e1,sizeof(empresa), 1,fp);
            }
            printf("\nExcluido com sucesso");
            fclose(fp);
            fclose(fp1);
        }
        else{
            printf("\n----------------------------------------------------");
            printf("\nEmpresa nao encontrada");
            printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
            printf("\n----------------------------------------------------");
        }
    }



    fclose(fp);
}



void mainMenu(){
    int ch;

    do {
        printf("\n1. Cadastrar Empresa");
        printf("\n2. Mostrar empresas Cadastradas");
        printf("\n3. Numero de empresas");
        printf("\n4. Procurar Empresa");
        printf("\n5. Alterar Empresa");
        printf("\n6. Baixar relatorio");
        printf("\n7. Alterar Relatorio");
        printf("\n8. Apagar Empresa");
        printf("\n0. Sair");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch){
            case 0:
                printf("Finalizando...");
                exit(1);
            case 1:
                append();
            break;
            case 2:
                display();
            break;
            case 3:
                numEmpresas();
            break;
            case 4:
                searchEmpresas();
            break;
            case 5:
                updateEmpresas();
            break;
            case 6:
                relatorioEmpresas();
            break;
            case 7:
                updateRelatorio();
            break;
            case 8:
                delEmpresas();
            break;

            default:
                printf("\nopcao invalida\n");

        }
    }while(ch!=0);

    return 0;
}



int main()
{
    FILE *fp;
    int opt, usrFound = 0;
    struct user user;
    char password[50], password2[50],s[50];
    //system("chcp 65001");
    //setlocale(LC_ALL, "Portuguese");
    printf("\n\t\t\t\t------------Bem vindo a tela de Login------------\n");
    printf("\nPor favor escolha uma das operacoes abaixo");
    printf("\n1.Criar conta");
    printf("\n2.Fazer login");
    printf("\n3.Sair");

    printf("\n\nSua escolha:\t");
    scanf("%d",&opt);
    fgetc(stdin);

    switch(opt)
    {
    case 1:
    {
        system("cls");
        printf("\n\t\t\t\t------------Criar Conta------------\n");
        printf("\nSeu nome:\t");
        takeinput(user.fullName);
        printf("\nSeu email:\t");
        takeinput(user.email);
        printf("\nTelefone:\t");
        takeinput(user.phone);
        printf("\nSua senha:\t");
        takepassword(user.password);
        printf("Confirme sua senha: \t");
        takepassword(password2);

        if (!strcmp(user.password,password2))
        {
            generateUsername(user.email,user.username);
            fp = fopen("Users.dat","a+");
            fwrite(&user,sizeof(struct user),1,fp);
            if (fwrite != 0)
            {
                printf("\nCriacao da conta feita com sucesso, o seu username para login: %s. Por favor, anote.",user.username);
            }
            else
            {
                printf("\n\nAlgo deu errado, tente novamente");
            }
            fclose(fp);
            main();

        }
        else
        {
            printf("\nSenhas nao sao iguais");
            Beep(750,300);
        }
        break;
    }
    case 2:
    {
        system("cls");
        char username[50],pword[50];
        struct user usr;
        printf("\nEntre com seu username (gerado do seu email):\t");
        takeinput(username);
        printf("\nEntre com sua senha:\t");
        takepassword(pword);

        fp=fopen("Users.dat","r");
        while(fread(&usr,sizeof(struct user),1,fp))
        {
            if (!strcmp(usr.username,username))
            {
                if (!strcmp(usr.password,pword))
                {
                    system("cls");
                    printf("\n\t\t\t\t\t\tWelcome %s",usr.fullName);
                    printf("\n\n|Full Name:\t%s",usr.fullName);
                    printf("\n|Email:\t\t%s",usr.email);
                    printf("\n|Username:\t%s",usr.username);
                    printf("\n|Contact number:\t%s",usr.phone);
                    system("cls");
                    mainMenu();
                }
                else
                {
                    //printf("\n\nInvalid password!");
                    //Beep(800,300);
                }
                usrFound = 1;
            }
        }
        if (!usrFound)
        {
            Beep(800,300);
            printf("Cliente nao registrado!");
            main();

        }
        fclose(fp);
        break;
    }
    case 3:
    {
        system("cls");
        printf("\t\t\tbye bye");
    }
    }
    return 0;
}
