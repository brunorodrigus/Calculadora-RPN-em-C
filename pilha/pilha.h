#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Estrutura da calculadora, com apenas a vari�vel num para armazenamento dos valores e um ponteiro da mesma estrutura para o proximo
struct _CALC {
	float num;
	struct _CALC *prox;
};
// Fun��o aproveitada da disponibilizada pelo professor em sala para limpeza do buffer do teclado
void clearKeyboardBuffer()
{
	fseek(stdin, 0, SEEK_END);
}
// Inser��o na pilha recebendo o HEAD e o valor a ser inserido na pilha por parametro
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

// Percorre a pilha para exibi-la na impress�o, baseada na fun��o recursiva trabalhada em sala no trabalho anterior
void listarPilha(_CALC **HEAD)
{
	if (*HEAD == NULL) {
		printf("\nFim da pilha ou pilha vazia!\n\n");
		return;
	}
	printf("\n>> %.5f <<", (*HEAD)->num);
	listarPilha(&(*HEAD)->prox);
}

// Remocao de elemento da pilha, utilizada para um elemento, se n�o existir usuario � informado atraves do printf do else
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

// Fun��o recursiva para liberar toda a pilha, utilizada na op��o C (limpar dados) e tamb�m ao fim do programa para n�o deixar memoria j� utilizada preenchida 
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

// Menu com as op��es de calculos disponiveis para serem realizados
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
	
	// As opera��es de inser��o de PI na pilha e C (limpar) n�o necessitam de nenhum elemento j� adicionado para serem executadas
	if (toupper(opc2) == 'K') // Toupper realiza a convers�o para char maiusculo lido do teclado anteriormente 
	{
		float pi = 3.14159;
		// Chama a fun��o para inserir o valor de PI na pilha
		inserePilha(&(*HEAD), pi); 
		return;
	}
	if (toupper(opc2) == 'A')
	{
		// C (Limpar) zera os valores da pilha atraves da chamada da fun��o recursiva
		liberaPilha(&(*HEAD)); 
		return;
	}
	// Essas opera��es necessitam de pelo menos um elemento j� adicionado na pilha
	if (*HEAD != NULL && (toupper (opc2) == 'H') || (toupper(opc2) == 'I') || (toupper(opc2) == 'J') || (toupper(opc2) == 'L') || (toupper(opc2) == 'M'))
	{
		// Variavel temporaria 2 recebe o HEAD para realiza��o dos calculos
		_CALC *temp2 = *HEAD;

		// Variaveis criadas para armazenar os valores do resultado da convers�o para radianos e resultado final a ser reinserido na pilha
		float res, res_radianos; 
		
		// Calculo de Seno
		if (toupper(opc2) == 'H') 
		{
			// Convers�o de graus para radianos 
			res_radianos = (temp2->num)* 3.14159 / 180; 
			// Calculo do seno com radiano j� convertido
			res = sinf(res_radianos); 
		}
		// Calculo de Tangente, de graus (previamente informado na pilha para radianos)
		if (toupper(opc2) == 'I') 
		{
			// Convers�o de graus para radianos 
			res_radianos = (temp2->num)* 3.14159 / 180; 
			// Calculo da tangente com radiano j� convertido
			res = tanf(res_radianos); 
		}
		// Calculo de Cosseno
		if (toupper(opc2) == 'J') 
		{
			// Convers�o de graus para radianos 
			res_radianos = (temp2->num)* 3.14159 / 180;  
			// Calculo do cosseno com radiano j� convertido
			res = cosf(res_radianos); 
		}
		// Invers�o de Sinal do valor da pilha
		if (toupper(opc2) == 'L') 
		{
			// Multiplicando por -1 as regras de sinais j� s�o aplicadas automaticamente 
			res = temp2->num*-1; 
		}
		// Logaritmo base 2
		if (toupper(opc2) == 'M') 
		{
			res = logf(temp2->num);
		}
		// Redefini��o do campo num de HEAD
		(*HEAD)->num = res; 
		return;
	}
	// Se n�o h� elementos suficientes para realizar abaixo, usuario sera informado
	if (*HEAD == NULL || (*HEAD)->prox == NULL) 
	{
		printf("Nao ha elementos suficientes!\n");
		return;
	}
	// A variavel recebe o proximo do head
	_CALC *temp1 = (*HEAD)->prox; 
	// Esta variavel recebe o head 
	_CALC *temp2 = *HEAD; 
	// Variaveis criadas para manipula��o dos calculos
	float num1, num2, res; 
	// Recebe o valor do pr�ximo de head
	num1 = temp1->num;
    // Recebe o valor de head	
	num2 = (*HEAD)->num; 

	// Subtra��o 
	if (toupper(opc2) == 'B') 
	{
		res = num1 - num2;
	}
	// Multiplica��o
	if (toupper(opc2) == 'C')
	{
		res = num1 * num2;
	}
	// Divis�o
	if (toupper(opc2) == 'D') 
	{
		res = num2 / num1;
	}
	// Soma
	if (toupper(opc2) == 'E')
	{
		res = num1 + num2;
	}
	// Potencia��o
	if (toupper(opc2) == 'F')
	{
		res = pow(num2, num1);
	}
	// Raiz en�sima
	if (toupper(opc2) == 'G')
	{
		res = pow(num2, (1.0 / num1));
	}
	// Ap�s realizar a opera��o temp1 recebe o resultado, passado para head na sequencia 
	temp1->num = res; 
	*HEAD = temp1;
	// temp2 � liberada pois de dois elementos utilizados somente um volta para a pilha (temp1)
	free(temp2); 
	return;
}
// Fun��o para exibi��o do menu e chamada das op��es atrav�s dele
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