#include <stdio.h>



int main() {
    //criei varivéis referente a cada uma das informações das cartas.
    char estado, estado2; // inicial do estado.
    char Codigo1[4];      // código da carta.
    char Cidade1[50];     // nome da cidade.
    unsigned long int Habitantes1, Habitantes2; // número de habitantes.
    float Area1, Area2;          // tamanho da Cidade.
    float PIB1, PIB2;           // seu PIB.
    int Pontos1, Pontos2;          // e o Número de pontos turísticos.
    char Codigo2[4];      // usei números para diferenciar a primeira carta e a segunda carta, 1 para primeira e 2 para a segunda.
    char Cidade2[50];
    float PIBperCapita1, PIBperCapita2; // variáveis para armazenar o PIB per capita de cada cidade.
    float DensidadeDemografica1, DensidadeDemografica2, Inverso_DensidadeDemografica1, Inverso_DensidadeDemografica2, SuperPoder1, SuperPoder2; // variáveis para armazenar a densidade demográfica de cada cidade , inverso da densidade demográfica e o super poder.
   

    printf("Bem-Vindo ao Super Trunfo\n"); // usei printf para guiar o usuário e imprimir informações.
    printf("para começar, iremos cadastrar duas Cidades como cartas\n");  
    printf("Carta 1:\n");  // ínicio do cadastro da primeira carta.

    printf("Digite a inicial do Estado, de A-H:\n"); 
    scanf(" %c", &estado); // scanf irá guardar informação que o usuário irá digitar para a variavél 'estado' do tipo 'char', '%c' receberá o valor atribuido e irá imprimir quando chamado pelo printf.
    

    printf("agora crie um código para a carta, comece com a Incial do Estado,e depois finalize com um número de 01 a 04:\n");
    scanf("%s",Codigo1);   // foi usado '%s' pois a variavél referente é do tipo 'char' 'string'.

    printf("digite o nome da Cidade:\n");
    scanf("%s",Cidade1);   

    printf("digite o número de habitantes da Cidade:\n");
    scanf("%lu", &Habitantes1); // foi usado '%lu' porque a variavél referente é do tipo 'unsigned long int', receberá valores longos inteiros e sem sinal.

    printf("agora digite a área da cidade em km^2:\n");
    scanf("%f",&Area1);   // '%f' pois nesse caso a variavél referente é do tipo "float", receberá valores decimais.

    printf("quase acabando! agora digite o PIB da Cidade, não precisa ser exato:\n");  
    scanf("%f", &PIB1); 
    
    printf("por último, digite o número de pontos turísticos:\n");
    scanf("%d", &Pontos1);  // finalizando o cadastro da primeira carta.

    printf("pronto, terminamos o cadastro da primeira carta, agora vamos para o cadastro da segunda carta!\n")   ;
    printf("Carta 2:\n"); // início do cadastramento da segunda carta.

    printf("Digite a inicial do Estado, de A-H:\n");
    scanf(" %c", &estado2);

    printf("agora crie um código para a carta, começe com a Incial do Estado,e depois finalize com um número de 01 a 04:\n");
    scanf("%s",Codigo2);

    printf("digite o nome da Cidade:\n");
    scanf("%s",Cidade2);

    printf("digite o número de habitantes da Cidade:\n");
    scanf("%lu", &Habitantes2);

    printf("agora digite a área da cidade em km^2:\n");
    scanf("%f",&Area2);

    printf("quase acabando! agora digite o PIB da Cidade, não precisa ser exato:\n");  
    scanf("%f", &PIB2);

    printf("por último, digite o número de pontos turísticos:\n");
    scanf("%d", &Pontos2); //finalizando o cadastro da segunda carta.

    printf("pronto, terminamos o cadastro das cartas!\n")   ;

    //após o cadastro, será calculado o PIB per capita, o super poder, a densidade demográfica e seu inverso para cada cidade.

    PIBperCapita1 = (float) PIB1 / Habitantes1; // cálculo do PIB per capita da primeira cidade.
    PIBperCapita2 = (float) PIB2 / Habitantes2; // cálculo do PIB per capita da segunda cidade.

    DensidadeDemografica1 = (float) Habitantes1 / Area1; // cálculo da densidade demográfica da primeira cidade.
    DensidadeDemografica2 = (float) Habitantes2 / Area2; // cálculo da densidade demográfica da segunda cidade. DensidadeDemografica1 = (float) Habitantes1 / Area1; // cálculo da densidade demográfica da primeira cidade.

    Inverso_DensidadeDemografica1 = (float) 1 / DensidadeDemografica1; // cálculo do inverso da densidade demográfica da primeira cidade.
    Inverso_DensidadeDemografica2 = (float) 1 / DensidadeDemografica2; // cálculo do inverso da densidade demográfica da segunda cidade.

    SuperPoder1 = (float) Habitantes1 + Area1 + PIB1 + Pontos1 + PIBperCapita1 + Inverso_DensidadeDemografica1; // cálculo do super poder da primeira cidade.

    SuperPoder2 = (float) Habitantes2 + Area2 + PIB2 + Pontos2 + PIBperCapita2 + Inverso_DensidadeDemografica2; // cálculo do super poder da segunda cidade.

    //apresentação das cartas registradas para o usuário.

    printf("a seguir, informações das cartas criadas...\n");
    printf("\nCarta 1: \n"); 
    printf("Estado: %c\n", estado);
    printf("Código da carta: %s\n", Codigo1); 
    printf("Nome da cidade:%s,\n", Cidade1);
    printf("Número de habitantes: %lu, \n", Habitantes1);
    printf("Área:%.3f,\n", Area1);
    printf("PIB: %.3f,\n", PIB1); 
    printf("Número de Pontos Turistico:%d \n", Pontos1);
    printf("PIB per capita: %.2f\n", PIBperCapita1);
    printf("Densidade demográfica: %.2f\n", DensidadeDemografica1);
    printf("O Super Poder da Cidade é: %2.f \n", SuperPoder1);

    printf("\nCarta 2: \n");
    printf("Estado: %c\n", estado2);
    printf("Código da carta: %s\n", Codigo2); 
    printf("Nome da cidade:%s,\n", Cidade2);
    printf("Número de habitantes: %lu, \n", Habitantes2);
    printf("Área:%.3f,\n", Area2);
    printf("PIB: %.3f,\n", PIB2); 
    printf("Número de Pontos Turistico:%d \n", Pontos2);
    printf("PIB per capita: %.2f\n", PIBperCapita2);
    printf("Densidade demográfica: %.2f\n", DensidadeDemografica2);
    printf("O Super Poder da Cidade é: %2.f \n", SuperPoder2);

    /* 
    A seguir, iremos comparar ambas as cartas, e será atribuido 1 ponto para carta que tiver o maior valor em cada atributo e 0 para a carta que tiver o menor valor.

    No entanto a carta que tiver menor valor em Densidade demográfica, receberá 1 ponto, e a carta que tiver maior valor em Densidade demográfica receberá 0 pontos.

    se ambas as cartas tiverem o mesmo valor em algum atributo, ambas as cartas receberão pontos.

    A carta que tiver mais pontos no final, será a vencedora.
    */

    int PIB1xPIB2 = PIB1 >= PIB2;
    int PIB2xPIB1 = PIB2 >= PIB1;

    int Habitantes1xHabitantes2 = Habitantes1 >= Habitantes2;
    int Habitantes2xHabitantes1 = Habitantes2 >= Habitantes1;

    int Area1xArea2 = Area1 >= Area2;
    int Area2xArea1 = Area2 >= Area1; 

    int Pontos1xPontos2 = Pontos1 >= Pontos2;
    int Pontos2xPontos1 = Pontos2 >= Pontos1;

    int PIBperCapita1xPIBperCapita2 = PIBperCapita1 >= PIBperCapita2;
    int PIBperCapita2xPIBperCapita1 = PIBperCapita2 >= PIBperCapita1;

    int Densidade1xDensidade2 = DensidadeDemografica1 <= DensidadeDemografica2;
    int Densidade2xDensidade1 = DensidadeDemografica2 <= DensidadeDemografica1;

    int Poder1xPoder2 = SuperPoder1 >= SuperPoder2;
    int Poder2xPoder1 = SuperPoder2 >= SuperPoder1;

    int ScoreCarta1 = Habitantes1xHabitantes2 + Area1xArea2 + PIB1xPIB2 + Pontos1xPontos2 + PIBperCapita1xPIBperCapita2 + Densidade1xDensidade2 + Poder1xPoder2; // soma dos pontos da carta 1.

    int ScoreCarta2 = Habitantes2xHabitantes1 + Area2xArea1 + PIB2xPIB1 + Pontos2xPontos1 + PIBperCapita2xPIBperCapita1 + Densidade2xDensidade1 + Poder2xPoder1; // soma dos pontos da carta 2.

    // iremos iniciar a comparação entre as cartas, e o usuário irá escolher qual atributo deseja comparar.
  
    int opcao1, opcao2; // variável para armazenar a opção escolhida pelo usuário.
    int resultado1, resultado2; // variáveis para armazenar o resultado da primeira e segunda comparação.

    printf("\nAgora iremos comparar as cartas:\n");

    printf("Escolha um atributo para comparar:\n");

    printf("1 - Número de Habitantes\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Número de Pontos Turístico\n");
    printf("5 - PIB per capita\n");
    printf("6 - Densidade demográfica\n");
    printf("7 - Super Poder\n");
    printf("8 - Todos os atributos\n");

   scanf ("%d", &opcao1); // o usuário irá escolher qual atributo deseja comparar, e o valor será guardado na variável 'opcao'.

   switch (opcao1) {

    case 1: // caso o usuário escolha a opção 1, irá comparar o número de habitantes.

    printf("Comparando o número de habitantes:\n");

    resultado1 = Habitantes1 > Habitantes2 ? 1 : 0 ; // comparação entre o número de habitantes da carta 1 e da carta 2, se a carta 1 tiver mais habitantes, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 1.

    case 2: // caso o usuário escolha a opção 2, irá comparar a área.

    printf("Comparando a área:\n");

    resultado1 = Area1 > Area2 ? 1 : 0 ; // comparação entre a área da carta 1 e da carta 2, se a carta 1 tiver mais área, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 2.

    case 3: // caso o usuário escolha a opção 3, irá comparar o PIB.
    
    printf("Comparando o PIB:\n");

    resultado1 = PIB1 > PIB2 ? 1 : 0 ; // comparação entre o PIB da carta 1 e da carta 2, se a carta 1 tiver mais PIB, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 3.

    case 4: // caso o usuário escolha a opção 4, irá comparar o número de pontos turísticos.

    printf("Comparando o número de pontos turísticos:\n");

    resultado1 = Pontos1 > Pontos2 ? 1 : 0 ; // comparação entre o número de pontos turísticos da carta 1 e da carta 2, se a carta 1 tiver mais pontos turísticos, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 4.

    case 5 : // caso o usuário escolha a opção 5, irá comparar o PIB per capita.

    printf("Comparando o PIB per capita:\n");

    resultado1 = PIBperCapita1 > PIBperCapita2 ? 1 : 0 ; // comparação entre o PIB per capita da carta 1 e da carta 2, se a carta 1 tiver mais PIB per capita, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break;

    case 6: // caso o usuário escolha a opção 6, irá comparar a densidade demográfica.

    printf("Comparando a densidade demográfica:\n");

    resultado1 = DensidadeDemografica1 < DensidadeDemografica2 ? 1 : 0 ; // comparação entre a densidade demográfica da carta 1 e da carta 2, se a carta 1 tiver menos densidade demográfica, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 6.

    case 7: // caso o usuário escolha a opção 7, irá comparar o super poder.

    printf("Comparando o super poder:\n");

    resultado1 = SuperPoder1 > SuperPoder2 ? 1 : 0 ; // comparação entre o super poder da carta 1 e da carta 2, se a carta 1 tiver mais super poder, ela receberá 1 ponto, caso contrário, receberá 0 pontos.         

    break; // fim do case 7.
 
    case 8:

    printf("Comparando todos os atributos:\n");
    printf("Cada carta irá receber 1 ponto por atributo superior ao da outra.\n");
    printf("se houver empate, ambas as cartas receberão 1 ponto.\n");
    printf("A carta que tiver mais pontos no final, será a vencedora.\n");

    printf("\nA seguir, atribuiremos os pontos:\n");
    
    printf("\nCarta 1: %s\n", Cidade1);
    printf("Número de Habitantes: %d\n", Habitantes1xHabitantes2);
    printf("Área: %d\n", Area1xArea2);
    printf("PIB: %d\n", PIB1xPIB2);
    printf("Número de Pontos Turístico: %d\n", Pontos1xPontos2);
    printf("PIB per capita: %d\n", PIBperCapita1xPIBperCapita2);
    printf("Densidade demográfica: %d\n", Densidade1xDensidade2);
    printf("Super Poder: %d\n", Poder1xPoder2);

    printf("\nTotal de pontos: %d\n", ScoreCarta1);

    printf("\nCarta 2: %s\n", Cidade2);
    printf("Número de Habitantes: %d\n", Habitantes2xHabitantes1);
    printf("Área: %d\n", Area2xArea1);
    printf("PIB: %d\n", PIB2xPIB1);
    printf("Número de Pontos Turístico: %d\n", Pontos2xPontos1);
    printf("PIB per capita: %d\n", PIBperCapita2xPIBperCapita1);
    printf("Densidade demográfica: %d\n", Densidade2xDensidade1);
    printf("Super Poder: %d\n", Poder2xPoder1);

    printf("\nTotal de pontos: %d\n", ScoreCarta2);

    if (ScoreCarta1 > ScoreCarta2) { // comparação entre as cartas, se a carta 1 tiver mais pontos, ela é a vencedora.
        printf("\nA carta %s venceu!\n", Cidade1);
    } else if (ScoreCarta2 > ScoreCarta1) { // comparação entre as cartas, se a carta 2 tiver mais pontos, ela é a vencedora.
        printf("\nA carta %s venceu!\n", Cidade2);
    } else { // se ambas as cartas tiverem o mesmo número de pontos, o resultado é empate.
        printf("\nEmpate entre as cartas %s e %s!\n", Cidade1, Cidade2);
    }   printf("\nObrigado pela participação!\n");
        return 0;
    break; // fim do case 8.

    default: // caso o usuário escolha uma opção inválida.
        printf("Opção inválida! Tente novamente.\n");
        break; // fim do default.
    }
    
    printf("\nAgora, escolha um segundo atributo para comparar:\n");

    printf("1 - Número de Habitantes\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Número de Pontos Turístico\n");
    printf("5 - PIB per capita\n");
    printf("6 - Densidade demográfica\n");
    printf("7 - Super Poder\n");
    printf("8 - Todos os atributos\n");

    scanf("%d" ,opcao2); // o usuário irá escolher qual atributo deseja comparar, e o valor será guardado na variável 'opcao2'.

    if (opcao2 == opcao1){

    printf("\nVocê não pode escolher o mesmo atributo duas vezes!\n"); // caso o usuário escolha o mesmo atributo, será exibida uma mensagem de erro.

    } else {

    switch(opcao2) { // o usuário irá escolher qual atributo deseja comparar, e o valor será guardado na variável 'opcao2'.

        case 1: // caso o usuário escolha a opção 1, irá comparar o número de habitantes.

    printf("Comparando o número de habitantes:\n");

    resultado2 = Habitantes1 > Habitantes2 ? 1 : 0 ; // comparação entre o número de habitantes da carta 1 e da carta 2, se a carta 1 tiver mais habitantes, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 1.

    case 2: // caso o usuário escolha a opção 2, irá comparar a área.

    printf("Comparando a área:\n");

    resultado2 = Area1 > Area2 ? 1 : 0 ; // comparação entre a área da carta 1 e da carta 2, se a carta 1 tiver mais área, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 2.

    case 3: // caso o usuário escolha a opção 3, irá comparar o PIB.
    
    printf("Comparando o PIB:\n");

    resultado2 = PIB1 > PIB2 ? 1 : 0 ; // comparação entre o PIB da carta 1 e da carta 2, se a carta 1 tiver mais PIB, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 3.

    case 4: // caso o usuário escolha a opção 4, irá comparar o número de pontos turísticos.

    printf("Comparando o número de pontos turísticos:\n");

    resultado2 = Pontos1 > Pontos2 ? 1 : 0 ; // comparação entre o número de pontos turísticos da carta 1 e da carta 2, se a carta 1 tiver mais pontos turísticos, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 4.

    case 5 : // caso o usuário escolha a opção 5, irá comparar o PIB per capita.

    printf("Comparando o PIB per capita:\n");

    resultado2 = PIBperCapita1 > PIBperCapita2 ? 1 : 0 ; // comparação entre o PIB per capita da carta 1 e da carta 2, se a carta 1 tiver mais PIB per capita, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break;

    case 6: // caso o usuário escolha a opção 6, irá comparar a densidade demográfica.

    printf("Comparando a densidade demográfica:\n");

    resultado2 = DensidadeDemografica1 < DensidadeDemografica2 ? 1 : 0 ; // comparação entre a densidade demográfica da carta 1 e da carta 2, se a carta 1 tiver menos densidade demográfica, ela receberá 1 ponto, caso contrário, receberá 0 pontos.

    break; // fim do case 6.

    case 7: // caso o usuário escolha a opção 7, irá comparar o super poder.

    printf("Comparando o super poder:\n");

    resultado2 = SuperPoder1 > SuperPoder2 ? 1 : 0 ; // comparação entre o super poder da carta 1 e da carta 2, se a carta 1 tiver mais super poder, ela receberá 1 ponto, caso contrário, receberá 0 pontos.         

    break; // fim do case 7.
 
    case 8:

    printf("Comparando todos os atributos:\n");
    printf("Cada carta irá receber 1 ponto por atributo superior ao da outra.\n");
    printf("se houver empate, ambas as cartas receberão 1 ponto.\n");
    printf("A carta que tiver mais pontos no final, será a vencedora.\n");

    printf("\nA seguir, atribuiremos os pontos:\n");
    
    printf("\nCarta 1: %s\n", Cidade1);
    printf("Número de Habitantes: %d\n", Habitantes1xHabitantes2);
    printf("Área: %d\n", Area1xArea2);
    printf("PIB: %d\n", PIB1xPIB2);
    printf("Número de Pontos Turístico: %d\n", Pontos1xPontos2);
    printf("PIB per capita: %d\n", PIBperCapita1xPIBperCapita2);
    printf("Densidade demográfica: %d\n", Densidade1xDensidade2);
    printf("Super Poder: %d\n", Poder1xPoder2);

    printf("\nTotal de pontos: %d\n", ScoreCarta1);

    printf("\nCarta 2: %s\n", Cidade2);
    printf("Número de Habitantes: %d\n", Habitantes2xHabitantes1);
    printf("Área: %d\n", Area2xArea1);
    printf("PIB: %d\n", PIB2xPIB1);
    printf("Número de Pontos Turístico: %d\n", Pontos2xPontos1);
    printf("PIB per capita: %d\n", PIBperCapita2xPIBperCapita1);
    printf("Densidade demográfica: %d\n", Densidade2xDensidade1);
    printf("Super Poder: %d\n", Poder2xPoder1);

    printf("\nTotal de pontos: %d\n", ScoreCarta2);

    if (ScoreCarta1 > ScoreCarta2) { // comparação entre as cartas, se a carta 1 tiver mais pontos, ela é a vencedora.
        printf("\nA carta %s venceu!\n", Cidade1);
    } else if (ScoreCarta2 > ScoreCarta1) { // comparação entre as cartas, se a carta 2 tiver mais pontos, ela é a vencedora.
        printf("\nA carta %s venceu!\n", Cidade2);
    } else { // se ambas as cartas tiverem o mesmo número de pontos, o resultado é empate.
        printf("\nEmpate entre as cartas %s e %s!\n", Cidade1, Cidade2);
    }   printf("\nObrigado pela participação!\n");
        return 0;
    break; // fim do case 8.

    default: // caso o usuário escolha uma opção inválida.
        printf("Opção inválida! Tente novamente.\n");
        break; // fim do default.
    }

    if((resultado1 == 1 && resultado2 == 1)) {

        printf("\nA carta %s venceu!\n", Cidade1); 

    } else if ((resultado1 != resultado2)){

        printf("\n EMPATOU!\n"); 

    } else {
         
        printf("\nA carta %s venceu!\n", Cidade2); 

    }

    }
    
    printf("\nObrigado pela participação!\n");
    return 0;
}

