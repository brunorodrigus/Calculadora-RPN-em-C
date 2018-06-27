/*
REFERÊNCIAS BIBLIOGRAFICAS
Deitel, H.M, Deitel, P.J, Como programar em C, 2.ed 1994
ONLINE
Eduardo Casavella, A Biblioteca Math.h, Disponível em:http://linguagemc.com.br/a-biblioteca-math-h/>. Acesso em: 01/04/2017.
Autor não especificado, Basic Concept of Stack, Disponível em: <http://www.c4learn.com/data-structure/stack-pop-operation-remove-element/>. Acesso em: 01/04/2017.
Daniel Atilio, Entendendo Pilha e Fila, Disponível em: <https://terminaldeinformacao.com/2013/07/23/entendendo-pilha-e-fila/>. Acesso em: 01/04/2017.
Anderson L. G. Quilles, Cláudio H. Bitto, Sônia Ferreira Lopes Toffoli e Ulysses Sodré, TRIGONOMETRIA :: Seno, cosseno e tangente, Disponivel em: <http://www.uel.br/projetos/matessencial/trigonom/trigo03.htm>. Acesso em: 04/04/2017.
Apostila C Progressivo, Pilha em C, Disponível em: <http://www.cprogressivo.net/2014/05/Pilhas-Stack-em-C-O-Que-E-Como-Implementar-Tutorial-C-Estrutura-de-Dados.html>. Acesso em: 04/04/2017.*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main() 
{
	clearKeyboardBuffer();
	//HEAD recebe NULL para inicio
	_CALC *HEAD = NULL; 
	// Chamada da função menu
	menu(HEAD); 
	// Limpeza de HEAD
	free(HEAD); 
}
