#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Estrutura da calculadora, com apenas a variável num para armazenamento dos valores e um ponteiro da mesma estrutura para o proximo
struct _CALC {
	float num;
	struct _CALC *prox;
};
// Função aproveitada da disponibilizada pelo professor em sala para limpeza do buffer do teclado
void clearKeyboardBuffer()
{
	fseek(stdin, 0, SEEK_END);
}
// Inserção na pilha recebendo o HEAD e o valor a ser inserido na pilha por parametro
void inserePilha(_CALC **HEAD, float numero) 
{
	_CALC *novoValor = (_CALC*)malloc(sizeof(_CALC));
	if (novoValor == NULL)
	{
		printf("Memoria nao alocada!\n");
		return;
	}
	if (*HEAD == NULL)
	{
		novoValor->prox = NULL;
		*HEAD = novoValor;
	}
	else
	{
		novoValor->prox = *HEAD;
		*HEAD = novoValor;
	}
	novoValor->num = numero;
}

// Percorre a pilha para exibi-la na impressão, baseada na função recursiva trabalhada em sala no trabalho anterior
void listarPilha(_CALC **HEAD)
{
	if (*HEAD == NULL) {
		printf("\nFim da pilha ou pilha vazia!\n\n");
		return;
	}
	printf("\n>> %.5f <<", (*HEAD)->num);
	listarPilha(&(*HEAD)->prox);
}

// Remocao de elemento da pilha, utilizada para um elemento, se não existir usuario é informado atraves do printf do else
void removePilha(_CALC **HEAD)
{
	if (*HEAD != NULL)
	{
		_CALC *temp = *HEAD;
		*HEAD = (*HEAD)->prox;
		free(temp);
	}
	else
	{
		printf("Remocao de todos os valores ja realizada!\n");
		return;
	}
}

// Função recursiva para liberar toda a pilha, utilizada na opção C (limpar dados) e também ao fim do programa para não deixar memoria já utilizada preenchida 
void liberaPilha(_CALC **HEAD)
{
	if (*HEAD == NULL)
	{
		return;
	}
	_CALC *prox_pilha = (*HEAD)->prox;
	free(*HEAD);
	*HEAD = NULL;
	liberaPilha(&prox_pilha);
}

// Menu com as opções de calculos disponiveis para serem realizados
void menuCalculo(_CALC **HEAD) 
{
	char opc2;
	clearKeyboardBuffer();
	printf("\nA - C(LIMPAR)\n");
	printf("B - Subtracao\n");
	printf("C - Multiplicacao\n");
	printf("D - Divisao\n");
	printf("E - Soma\n");
	printf("F - X ^ Y (Potencia)\n");
	printf("G - Raiz N\n");
	printf("H - Seno\n");
	printf("I - Tangente\n");
	printf("J - Cosseno\n");
	printf("K - Pi\n");
	printf("L - CHS (Inverter sinal)\n");// inverter o sinal do valor
	printf("M - Ln (Logaritmo)\n");
	printf("OPCAO: \n");
	scanf_s("%c", &opc2);
	
	// As operações de inserção de PI na pilha e C (limpar) não necessitam de nenhum elemento já adicionado para serem executadas
	if (toupper(opc2) == 'K') // Toupper realiza a conversão para char maiusculo lido do teclado anteriormente 
	{
		float pi = 3.14159;
		// Chama a função para inserir o valor de PI na pilha
		inserePilha(&(*HEAD), pi); 
		return;
	}
	if (toupper(opc2) == 'A')
	{
		// C (Limpar) zera os valores da pilha atraves da chamada da função recursiva
		liberaPilha(&(*HEAD)); 
		return;
	}
	// Essas operações necessitam de pelo menos um elemento já adicionado na pilha
	if (*HEAD != NULL && (toupper (opc2) == 'H') || (toupper(opc2) == 'I') || (toupper(opc2) == 'J') || (toupper(opc2) == 'L') || (toupper(opc2) == 'M'))
	{
		// Variavel temporaria 2 recebe o HEAD para realização dos calculos
		_CALC *temp2 = *HEAD;

		// Variaveis criadas para armazenar os valores do resultado da conversão para radianos e resultado final a ser reinserido na pilha
		float res, res_radianos; 
		
		// Calculo de Seno
		if (toupper(opc2) == 'H') 
		{
			// Conversão de graus para radianos 
			res_radianos = (temp2->num)* 3.14159 / 180; 
			// Calculo do seno com radiano já convertido
			res = sinf(res_radianos); 
		}
		// Calculo de Tangente, de graus (previamente informado na pilha para radianos)
		if (toupper(opc2) == 'I') 
		{
			// Conversão de graus para radianos 
			res_radianos = (temp2->num)* 3.14159 / 180; 
			// Calculo da tangente com radiano já convertido
			res = tanf(res_radianos); 
		}
		// Calculo de Cosseno
		if (toupper(opc2) == 'J') 
		{
			// Conversão de graus para radianos 
			res_radianos = (temp2->num)* 3.14159 / 180;  
			// Calculo do cosseno com radiano já convertido
			res = cosf(res_radianos); 
		}
		// Inversão de Sinal do valor da pilha
		if (toupper(opc2) == 'L') 
		{
			// Multiplicando por -1 as regras de sinais já são aplicadas automaticamente 
			res = temp2->num*-1; 
		}
		// Logaritmo base 2
		if (toupper(opc2) == 'M') 
		{
			res = logf(temp2->num);
		}
		// Redefinição do campo num de HEAD
		(*HEAD)->num = res; 
		return;
	}
	// Se não há elementos suficientes para realizar abaixo, usuario sera informado
	if (*HEAD == NULL || (*HEAD)->prox == NULL) 
	{
		printf("Nao ha elementos suficientes!\n");
		return;
	}
	// A variavel recebe o proximo do head
	_CALC *temp1 = (*HEAD)->prox; 
	// Esta variavel recebe o head 
	_CALC *temp2 = *HEAD; 
	// Variaveis criadas para manipulação dos calculos
	float num1, num2, res; 
	// Recebe o valor do próximo de head
	num1 = temp1->num;
    // Recebe o valor de head	
	num2 = (*HEAD)->num; 

	// Subtração 
	if (toupper(opc2) == 'B') 
	{
		res = num1 - num2;
	}
	// Multiplicação
	if (toupper(opc2) == 'C')
	{
		res = num1 * num2;
	}
	// Divisão
	if (toupper(opc2) == 'D') 
	{
		res = num2 / num1;
	}
	// Soma
	if (toupper(opc2) == 'E')
	{
		res = num1 + num2;
	}
	// Potenciação
	if (toupper(opc2) == 'F')
	{
		res = pow(num2, num1);
	}
	// Raiz enésima
	if (toupper(opc2) == 'G')
	{
		res = pow(num2, (1.0 / num1));
	}
	// Após realizar a operação temp1 recebe o resultado, passado para head na sequencia 
	temp1->num = res; 
	*HEAD = temp1;
	// temp2 é liberada pois de dois elementos utilizados somente um volta para a pilha (temp1)
	free(temp2); 
	return;
}
// Função para exibição do menu e chamada das opções através dele
void menu(_CALC *HEAD) 
{
	int opc = 0;
	float numero = 0;
	clearKeyboardBuffer();
	while (opc != -1) {
		printf("1. Insercao na Pilha\n");
		printf("2. Remover da Pilha\n");
		printf("3. Listar Pilha\n");
		printf("4. Operacoes\n");
		printf("0. Sair\n");
		printf("OPCAO:\n");
		scanf_s("%d", &opc);
		switch (opc) {
		case 1:
			printf("Informe o numero: ");
			scanf_s("%f", &numero);
			printf("\n\n");
			inserePilha(&HEAD, numero);
			break;
		case 2:
			removePilha(&HEAD);
		case 3:
			listarPilha(&HEAD);
			break;
		case 4:
			menuCalculo(&HEAD);
			break;
		case 0:
			opc = -1;
			printf("Saindo...");
			liberaPilha(&HEAD);
			break;
		default:
			printf("\nOpcao invalida!\n");
			break;
		}
	}
}