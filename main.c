#include <stdio.h>
#include <stdlib.h>

//Lista 11 e 12
//Autor: Pedro Vitor Melo Bitencourt
//Observação: Poderia ter colocado um, por exemplo, #define MAX_SIZE NUM, em que o NUM seria um valor, pois isto facilitaria na hora de trocar a quantidade máxima de caracteres que o nome do contato pode ter

struct data_nascimento{
    int dia;
    int mes;
    int ano;
};

struct contato{
    char nome[31];  //No celular, poderia ter colocado long int, pois, se não me engano, ocupa menos espaço do que variáveis double
    double celular; //Double para não ter erro ao ler o número de celular, pois este possui muitos dígitos // Acabei de lembrar que poderia ter usado long int, mas já está no final do prazo
    struct data_nascimento data_de_nascimento; //variável do tipo struct data_nascimento
};

//Procedimento para inserir um contato à agenda
void Inserir_contato(struct contato contato1[], int n){
    printf("Digite o nome do contato: ");
    gets(contato1[n].nome); //Troquei o "fgets" por "gets" devido a um problema na leitura do arquivo por causa do "\n" mesmo sendo "perigoso"
    printf("Digite o numero do contato (DDXXXXXXXXX): ");
    scanf("%lf", &contato1[n].celular);
    printf("Digite a data de nascimento do contato (DD MM YYYY): ");
    scanf("%d %d %d", &contato1[n].data_de_nascimento.dia, &contato1[n].data_de_nascimento.mes, &contato1[n].data_de_nascimento.ano);
}

//Procedimento para exibir os contatos da agendas
void exibir(struct contato contato1[], int n){ //"n" é a posição do contato no vetor estrutura contato
    printf("\nO nome do contato e: %s\n", contato1[n].nome); //Os nomes que são carregados pelo arquivo estão vindo com um "\n"
    printf("O numero do contato e: %.0lf\n", contato1[n].celular);
    printf("A data de nascimento do contato e: %d/%d/%d\n", contato1[n].data_de_nascimento.dia, contato1[n].data_de_nascimento.mes, contato1[n].data_de_nascimento.ano);
}

int strlen(char string[]){ //Função que retorna o tamanho da string
    int tamanho = 0;
    for(int i = 0; string[i] != '\0' && string[i] != '\n'; i++){ //Enquanto não haver o caracter nulo (\0) ou um "\n". O "\n" devido ao último contato do arquivo
        tamanho++;                                               //que terá um "\n" para possibilitar a leitura da quantidade de linhas do arquivo
    }
    return tamanho;
}

void copia(char origem[], char destino[]){ //Função que copia a string de origem na string de destino
    int i = 0;
    for(i = 0; origem[i] != '\0'; i++){
        destino[i] = origem[i];
    }
    destino[i] = '\0';
}

int Excluir_contato(struct contato contato1[], int n){ //"n" é a quantidade de contatos
    int indice_deletar = 0, i = 0, j = 0;
    indice_deletar = Procurar_nome(contato1, n); //Vai procurar em qual posição está o contato que se deseja deletar
    if(indice_deletar >= 0){ //Se o valor retornado for maior ou igual a 0, ou seja, achar o contato, vamos exclui-lo
        for(i = 0; i < n; i++){ //Vai percorrer todos os contatos até achar a posição do contato que se deseja deletar
            if(i == indice_deletar){ //Quando achar esse índice, os dados do contato dessa posição assumirão os dados do próximo
                for(j = i; j < n; j++){ //E, assim por diante, até acabar a quantidade de contatos
                    copia(contato1[j+1].nome, contato1[j].nome);
                    contato1[j].celular = contato1[j+1].celular;
                    contato1[j].data_de_nascimento.dia = contato1[j+1].data_de_nascimento.dia;
                    contato1[j].data_de_nascimento.mes = contato1[j+1].data_de_nascimento.mes;
                    contato1[j].data_de_nascimento.ano = contato1[j+1].data_de_nascimento.ano;
                }
                printf("O primeiro contato que apareceu foi deletado com sucesso!\n"); //Somente o contato que possuir a substring digitada pelo usuário e tiver a menor posição no vetor será excluído
            }
        }
    }
    else{ //Se não achar o contato na função Procurar_contato
        return 0;
    }
    return 1; //Se achar o contato
}

int Procurar_nome(struct contato contato[], int n){ //"n" é a quantidade de contatos da agenda
    char proc_nome[31]; //Nome ou partes do nome do contato que se quer procurar ou deletar
    int i = 0, j = 0, k = 0, indice_contato_encontrado = 0;
    int igual = 0, tamanho_proc_nome = 0, tamanho_contato = 0, tudo_igual = 0; //"igual" e "tudo_igual" são variáveis de controle
    printf("Qual contato voce quer procurar ou deletar: ");
    fgets(proc_nome, 31, stdin);
    for(i = 0; i < n; i++){
        tamanho_proc_nome = strlen(proc_nome);
        tamanho_contato = strlen(contato[i].nome);
        igual = 0; //Resetar o valor para as próximas checagens
        k = 0; //Resetar o valor para as próximas checagens
        for(j = 0; j < tamanho_contato; j++){ //Vai percorrer todos caracteres do contato
            if(contato[i].nome[j] == proc_nome[k]){ //Se o caracter da posição "j" do contato na posição "i" for igual ao caracter do nome que a pessoa procurou na posição "k"
                igual++; //Aumentar a quantidade de letras iguais entre o nome do contato e o nome do contato que está sendo procurado
                k++; //Temos que aumentar a variável "k" para olhar o próximo caracter do nome que está sendo procurado
                if(igual == tamanho_proc_nome && tudo_igual == 0){ //Colocar "tudo_igual" == 0 para pegar o primeiro contato com o nome colocado caso for exclui-lo
                    tudo_igual = 1; //Se a quantidade de letras iguais é o mesmo que o tamanho da substring digitada pelo usuário para procurar ou deletar um contato
                    indice_contato_encontrado = i; //pegar o indice para excluir caso necessario
                    printf("\nContato(s) encontrado(s):");
                    printf("\nNome do contato: %s\n", contato[i].nome);
                    printf("Numero do contato: %.0lf\n", contato[i].celular);
                    printf("Data de nascimento do contato: %d/%d/%d\n", contato[i].data_de_nascimento.dia, contato[i].data_de_nascimento.mes, contato[i].data_de_nascimento.ano);
                    printf("\n\n");
                }
                else if(igual == tamanho_proc_nome && tudo_igual == 1){ //Se não for o primeiro contato achado com a substring digitada, mas possuir tal substring
                    printf("Nome do contato: %s\n", contato[i].nome);
                    printf("Numero do contato: %.0lf\n", contato[i].celular);
                    printf("Data de nascimento do contato: %d/%d/%d\n", contato[i].data_de_nascimento.dia, contato[i].data_de_nascimento.mes, contato[i].data_de_nascimento.ano);
                    printf("\n\n");
                }
            }
            else{
                igual = 0; //Resetar os valores, pois pode achar o nome colocado em outras posições do nome do contato
                k = 0; //Resetar, porque teve algum caracter que não é igual
            }
        }
    }
    if(tudo_igual == 0){ //Se não achar nenhum contato com a substring digitada
        printf("Contato nao encontrado!\n");
        indice_contato_encontrado = -10; //Fazer isso para facilitar a execução da função Excluir_contato
    }
    return indice_contato_encontrado; //Retornando valor para ajudar na função Excluir_contato
}

int main(){
    char escolha, tipo_abertura_arquivo;
    int quantidade_contatos = 0, i = 0, exibir_contatos = 0, quantidade_linhas_arquivo = 0, caracter = 0, caracter2 = 0; //caracter e caracter2 servem para o momento da leitura do arquivo agenda
    char string[31]; //Para colocar o nome do contato na posição do vetor de estrutura contato na hora de CARREGAR a agenda
    int dia = 0, mes = 0, ano = 0, fechar = 0; //Para colocar a data de nascimento do contato na posição do vetor de estrutura contato na hora de CARREGAR a agenda
    double celular = 0; //Para colocar o celular do contato na posição do vetor de estrutura contato na hora de CARREGAR a agenda
    struct contato *contato1 = (struct contato*)malloc(1 * sizeof(struct contato));

    FILE *contatos_salvar_texto = fopen("contatos_texto.txt", "a"); //Vai escrever no arquivo agenda todos os contatos sem sobrescrevê-los
    FILE *contatos_salvar_binario = fopen("contatos_texto_binario.txt", "ab"); //Mesma explicação só que para arquivo binário
    FILE *contatos_carregar; //Será usado para carregar todos os contatos existentes na agenda

    if(contatos_salvar_texto == NULL || contatos_salvar_binario == NULL){ //Se acontecer algum erro na hora de abrir o arquivo, fechar o programa
        printf("Erro na abertura do arquivo!\n");
        return 0;
    }
    //Opções para abrir o arquivo - Texto ou binário
    printf("Digite 'T' para carregar a agenda do arquivo texto\n");
    printf("\nDigite 'B' para carregar a agenda do arquivo binario\n");
    scanf("%c", &tipo_abertura_arquivo);
    switch(tipo_abertura_arquivo){
        case 'T': contatos_carregar = fopen("contatos_texto.txt", "r"); //Abrir o arquivo texto
            if(contatos_carregar == NULL){ //Se acontecer algo de errado na abertura do arquivo
                printf("Erro na abertura do arquivo\n");
                return 0;
            }
            else{
                do{ //do-while para contar quantas linhas tem no arquivo contatos
                    caracter = fgetc(contatos_carregar);
                    if(caracter == '\n'){ //Somente quando achar um "\n" no arquivo vai contar uma linha. Por isso, na hora de gravar os contatos na agenda,
                        quantidade_linhas_arquivo++;//Coloquei um "\n" no final se for o último contato do vetor
                    }
                    if(caracter != EOF){
                        caracter2 = caracter; //Caracter2 vai servir como um auxiliar para saber se há só um contato ou 2 devido ao "\n"
                    }
                }while(caracter != EOF);
                fseek(contatos_carregar, 0, SEEK_SET); //voltar para o inicio do arquivo para voltar a lê-lo do início

                if(quantidade_linhas_arquivo == 0){ //Se a quantidade de linhas for igual a zero, então não há nenhum contato no arquivo agenda
                    quantidade_contatos = 0;
                }
                else{
                    quantidade_contatos = (quantidade_linhas_arquivo + 1);
                    if(quantidade_contatos == 2 && caracter2 == '\n'){ //Caso tenha 1 contato somente na agenda, mas já que ele é o primeiro, tem um "\n" depois
                        quantidade_contatos = 1; //Aí para evitar contar um contato a mais no arquivo do que realmente possui
                    }
                    contato1 = realloc(contato1, (quantidade_contatos + 1) * sizeof(struct contato)); //Reallocando a memória que precisa para colocar todos os
                                                                                                    //contatos da agenda no vetor de estruturas usado no programa (contato1)
                    while(!feof(contatos_carregar)){ //Enquanto não for o fim do arquivo agenda
                        fscanf(contatos_carregar, " %[^|]| %lf %d %d %d", string, &celular, &dia, &mes, &ano); //Lendo cada contato que está na agenda e armazenando no vetor
                        copia(string, contato1[i].nome); //[^|]| -> Vai ler tudo até achar um "|"
                        contato1[i].celular = celular;
                        contato1[i].data_de_nascimento.dia = dia;
                        contato1[i].data_de_nascimento.mes = mes;
                        contato1[i].data_de_nascimento.ano = ano;
                        i++; //Somar "+1" para armazenar o próximo contato em outra posição do vetor
                    }
                }
            }
            break;
        case 'B': contatos_carregar = fopen("contatos_texto_binario.txt", "rb"); //Leitura de arquivo binário
            if(contatos_carregar == NULL){
                printf("Erro na abertura do arquivo\n");
                return 0;
            }
            else{
                do{ //do-while para contar quantas linhas tem no arquivo contatos
                    caracter = fgetc(contatos_carregar);
                    if(caracter == '\n'){
                        quantidade_linhas_arquivo++;
                    }
                    if(caracter != EOF){
                        caracter2 = caracter; //Caracter2 vai servir como um auxiliar para saber se há só um contato ou 2 devido ao "\n"
                    }
                }while(caracter != EOF);
                fseek(contatos_carregar, 0, SEEK_SET); //voltar para o inicio do arquivo

                if(quantidade_linhas_arquivo == 0){
                    quantidade_contatos = 0;
                }
                else{
                    quantidade_contatos = (quantidade_linhas_arquivo + 1); //Mesmas explicações da parte da leitura do arquivo texto
                    if(quantidade_contatos == 2 && caracter2 == '\n'){
                        quantidade_contatos = 1;
                    }
                    contato1 = realloc(contato1, (quantidade_contatos + 1) * sizeof(struct contato));

                    while(!feof(contatos_carregar)){
                        fscanf(contatos_carregar, " %[^|]| %lf %d %d %d", string, &celular, &dia, &mes, &ano);
                        copia(string, contato1[i].nome);
                        contato1[i].celular = celular;
                        contato1[i].data_de_nascimento.dia = dia;
                        contato1[i].data_de_nascimento.mes = mes;
                        contato1[i].data_de_nascimento.ano = ano;
                        i++;
                    }
                }
            }
            break;
    }

    while(1){ //Laço infinito que será finalizado quando "escolha" for igual a 'S'
        printf("             AGENDA\n");
        printf("\nDigite 'I' para inserir um contato\n");
        printf("Digite 'P' para procurar um contato\n");
        printf("Digite 'E' para excluir um contato\n");
        printf("Digite 'C' para exibir todos os contatos da agenda\n");
        printf("Digite 'S' para sair da agenda\n");
        printf("\n");
        printf("Qual a sua escolha? ");
        scanf(" %c", &escolha);
        getchar();

        switch(escolha){
            case 'I': Inserir_contato(&contato1[0], quantidade_contatos); quantidade_contatos++;
                    contato1 = realloc(contato1, (quantidade_contatos + 1) * sizeof(struct contato)); //Realocando mais espaço de memória devido ao novo contato inserido
                    break; //Inserir um contato
            case 'P': Procurar_nome(contato1, quantidade_contatos); break; //Procurar um contato
            case 'E': //Excluir um contato
                 if(Excluir_contato(contato1, quantidade_contatos) == 1){ //Se achar o contato que o usuário quer deletar - Fazer essa estrutura de condição para caso não ache e não acabe diminuindo a quantidade de contatos e diminuindo o espaço alocado
                    contato1 = realloc(contato1, ((quantidade_contatos - 1) * sizeof(struct contato))); quantidade_contatos--; break;} //Excluir um contato
                 else{
                    printf("Ja que nao foi encontrado o contato digitado, nao foi possivel deleta-lo\n");
                    break;
                 }
            case 'S': printf("Fim do programa\n");
                    //Fechar os arquivos para abri-los novamente e sobrescrevê-los com os contatos que restaram na agenda - Mais fácil do que deletar o contato desejado da agenda
                    fclose(contatos_salvar_texto); fclose(contatos_salvar_binario); fclose(contatos_carregar);
                    contatos_salvar_texto = fopen("contatos_texto.txt", "w"); contatos_salvar_binario = fopen("contatos_texto_binario.txt", "wb");
                    for(fechar = 0; fechar < quantidade_contatos; fechar++){ //Percorrer todos os contatos do vetor estrutura e gravá-los no arquivo
                        if(fechar >= 0 && fechar < quantidade_contatos - 1 || fechar == quantidade_contatos-1 && quantidade_contatos == 1){ //Para separar certinho na hora de calcular o número de linhas, precisa desse "\n"
                            fprintf(contatos_salvar_texto, "%s|%.0lf %d %d %d\n", contato1[fechar].nome, contato1[fechar].celular, contato1[fechar].data_de_nascimento.dia, contato1[fechar].data_de_nascimento.mes, contato1[fechar].data_de_nascimento.ano);
                            fprintf(contatos_salvar_binario, "%s|%.0lf %d %d %d\n", contato1[fechar].nome, contato1[fechar].celular, contato1[fechar].data_de_nascimento.dia, contato1[fechar].data_de_nascimento.mes, contato1[fechar].data_de_nascimento.ano);
                        }
                        else if(fechar == quantidade_contatos - 1 && quantidade_contatos > 1){ //Se for o último contato, não vai imprimir o "\n" para não afetar a contagem de contatos no arquivo agenda
                            fprintf(contatos_salvar_texto, "%s|%.0lf %d %d %d", contato1[fechar].nome, contato1[fechar].celular, contato1[fechar].data_de_nascimento.dia, contato1[fechar].data_de_nascimento.mes, contato1[fechar].data_de_nascimento.ano);
                            fprintf(contatos_salvar_binario, "%s|%.0lf %d %d %d", contato1[fechar].nome, contato1[fechar].celular, contato1[fechar].data_de_nascimento.dia, contato1[fechar].data_de_nascimento.mes, contato1[fechar].data_de_nascimento.ano);
                            }
                    }
                    fclose(contatos_salvar_binario); fclose(contatos_salvar_texto); free(contato1); //Fechar os arquivos e liberar o espaço de memória alocado
                    return 0;
            case 'C': //Exibir todos os contatos da agenda
                for(exibir_contatos = 0; exibir_contatos < quantidade_contatos; exibir_contatos++){
                    exibir(contato1, exibir_contatos);
                }
                break;
            default: printf("Opcao invalida! Tente novamente!\n"); break; //Caso não escolha nenhuma da opções do menu
        }
        printf("\n");
        //system("pause"); - Deve ser usado junto com o "cls" para não limpar a tela rapidamente sem ter tempo de visualizar o que foi impresso na tela
        //system("cls"); - Limpa a tela
    } //Sem o return 0 aqui pois nunca chegaria nele devido ao loop, que só será finalizado caso o usuário digite 'S'
}
