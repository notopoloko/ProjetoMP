#ifndef TEST

#include <stdio.h>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "Grafo.h"

/*

TEST(TestaValidade, TestPalavraValida){
	cria_Grafo()


	char str[30] = {"DDD"};
	printf("\n");
	ASSERT_TRUE(StringValida(str) == false);
	char str2[30] = {"III"};
	ASSERT_TRUE(StringValida(str2) == true);
	char str3[30] = {"LM"};
	ASSERT_TRUE(StringValida(str3) == false);
	char str4[30] = {"MC"};
	ASSERT_TRUE(StringValida(str4) == true);
}

TEST(TestaConversao, TestCaracterValido){
	printf("\n");
	ASSERT_TRUE(CharPraInt('X') == 10);
	ASSERT_FALSE(CharPraInt('V') == 1);
	ASSERT_TRUE(CharPraInt('I') == 1);
	ASSERT_TRUE(CharPraInt('V') == 5);
	ASSERT_FALSE(CharPraInt('M') == 1);
	ASSERT_TRUE(CharPraInt('M') == 1000);
	ASSERT_TRUE(CharPraInt('O') == 0);
	ASSERT_TRUE(CharPraInt('r') == 0);
}

TEST(TestaNumeroConvertido, TestInteiroPos){
	printf("\n");
	char str[30] = {"XI"};
	ASSERT_TRUE(ConverteString(str) == 11);
	char str2[30] = {"IX"};
	ASSERT_TRUE(ConverteString(str2) == 9);
	char str3[30] = {"XXXX"};
	ASSERT_TRUE(ConverteString(str3) == -1);
	char str4[30] = {"DCCCXLI"};
	ASSERT_TRUE(ConverteString(str4) == 841);
	char str5[30] = {"MMM"};
	ASSERT_TRUE(ConverteString(str5) == 3000);
	char str6[30] = {"MMMI"};
	ASSERT_TRUE(ConverteString(str6) == -1);
	char str7[30] = {"M"};
	ASSERT_FALSE(ConverteString(str7) == 10);
	ASSERT_TRUE(ConverteString(str7) == 1000);
	char str8[30] = {"O"};
	ASSERT_TRUE(ConverteString(str8) == -1);
}


TEST(TestaDestroiGrafo, String){
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	ASSERT_TRUE(G != NULL);
	destroi_Grafo(&G);
	ASSERT_TRUE(G == NULL);
}


TEST(TestaRemoveVertice, IntPos){
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	adiciona_Vertice(&G, 2);
	ASSERT_TRUE(G->N_Vertices == 2);
	remove_Vertice(&G, 1);
	ASSERT_TRUE(G->N_Vertices == 1);
	remove_Vertice(&G, 2);
	ASSERT_TRUE(G->N_Vertices == 0);
	destroi_Grafo(&G);
}


TEST(TestaRemoveAresta, IntPos){
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	adiciona_Vertice(&G, 2);
	adiciona_Aresta(&G, 1, 2);
	ASSERT_TRUE(G->N_Arestas == 1);
	remove_Aresta(&G, 1, 2);
	ASSERT_TRUE(G->N_Arestas == 0);
	destroi_Grafo(&G);
}

TEST(TestaExisteGrafo, String){
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	ASSERT_TRUE(existe_Grafo(G) == 1);
	destroi_Grafo(&G);
}

TEST(TestaRetornaNome, Grafo){
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	ASSERT_TRUE(existe_Grafo(G) == 1);
	destroi_Grafo(&G);
}

TEST(TestaRetornaVertice, Grafo){
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	ASSERT_TRUE(retorna_Vertice(G, 1) == 1);
	ASSERT_FALSE(retorna_Vertice(G, 1) == 5);
	destroi_Grafo(&G);
}

TEST(TestaRetornaAresta, Grafo){
	int valorVertice;
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	adiciona_Vertice(&G, 2);
	adiciona_Vertice(&G, 5);
	adiciona_Aresta(&G, 1, 2);
	valorVertice = retorna_Aresta(G, 1, 2);
	ASSERT_TRUE(valorVertice == 2);
	valorVertice = retorna_Aresta(G, 1, 5);
	ASSERT_TRUE(valorVertice != 2);
	destroi_Grafo(&G);
}


TEST(TestaProcuraVertice, Grafo){ // Usando a funcao procura vertice que retorna uma estrutura vertice se achar o vertice
							// a ser procurado e retorna uma estrutura erro, caso nao encontre. 
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	ListaVertice = procura_Vertice(G, 1); 
	ASSERT_TRUE(ListaVertice->nomeVertice != -1);
	ListaVertice = procura_Vertice(G, 4); 
	ASSERT_TRUE(ListaVertice->nomeVertice == -1);
	destroi_Grafo(&G);
}	

TEST(TestaProcuraAresta, Grafo){ // Usando a funcao procura aresta que retorna uma estrutura aresta se encontrar a aresta procurada
							//  e retorna uma estrutura erro, caso nao encontre.
	printf("\n");
	G = cria_Grafo(nomeGrafo); 
	adiciona_Vertice(&G, 1);
	adiciona_Vertice(&G, 2);
	adiciona_Aresta(&G, 1, 2);
	ListaAresta = procura_Aresta(G, 1, 2);
	ASSERT_TRUE(ListaAresta->nomeAresta != -1);
	ListaAresta = procura_Aresta(G, 1, 7);
	ASSERT_TRUE(ListaAresta->nomeAresta == -1);

	destroi_Grafo(&G);
}

TEST(TestaInsereVertice, IntPos){ // Testando erros de Insercao de vertices usando apenas inteiros Positivos.
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	NumeroVertices = G->N_Vertices;
	ASSERT_TRUE(NumeroVertices == 1);
	adiciona_Vertice(&G, 2);
	NumeroVertices = G->N_Vertices;
	ASSERT_TRUE(NumeroVertices == 2);
	adiciona_Vertice(&G, 3);
	NumeroVertices = G->N_Vertices;
	ASSERT_TRUE(NumeroVertices == 3);
	ASSERT_TRUE(ListaVertice != NULL);
	destroi_Grafo(&G);
}


TEST(TestaInsereAresta, Int){ // Testando erros de Insercao de arestas usando apenas inteiros.
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	ASSERT_TRUE(ListaVertice != NULL);
	adiciona_Vertice(&G, 2);
	adiciona_Vertice(&G, 3);
	ASSERT_TRUE(retorna_Vertice(G, 1) == 1);
	adiciona_Aresta(&G, 1, 2);
	NumeroArestas = G->N_Arestas;
	ASSERT_TRUE(NumeroArestas == 1);
	adiciona_Aresta(&G, 2, 3);
	NumeroArestas = G->N_Arestas;
	ASSERT_TRUE(NumeroArestas == 2);
	adiciona_Aresta(&G, 1, 3);
	NumeroArestas = G->N_Arestas;
	ASSERT_TRUE(NumeroArestas == 3);
	ListaAresta = procura_Aresta(G, 1, 2);
	ASSERT_TRUE(ListaAresta->nomeAresta = 2);
	ListaAresta = procura_Aresta(G, 1, 3);
	ASSERT_TRUE(ListaAresta->nomeAresta = 3);
	destroi_Grafo(&G);
}

TEST(TestaAtualizaVertice, Int){ // Testando erros de Atualizacao de Vertices usando apenas inteiros.
	printf("\n");
	G = cria_Grafo(nomeGrafo);
	adiciona_Vertice(&G, 1);
	ASSERT_TRUE(retorna_Vertice(G, 1) == 1);
	atualiza_Vertice(&G, 1, 3);
	ListaVertice = procura_Vertice(G, 3);
	ASSERT_TRUE(retorna_Vertice(G, 3) == 3);
	ASSERT_TRUE(ListaVertice->nomeVertice == 3);
	ASSERT_TRUE(retorna_Vertice(G, 3) == 3);
	destroi_Grafo(&G);
}


*/

Grafo *G;
usuarios *User, *User1;
int NumeroUsuarios, NumeroAmigos;
char nom[] = "Rafael", nom1[] = "Marcelo", nom2[] = "Paula", nom3[] = "Andre", nom4[] = "Leandro", nom5[] = "Joao";
char cidade[] = "Aguas", cidade1[] = "Taguatinga", cidade2[] = "Ceilandia", cidade3[] = "Marajo", cidade4[] = "Olinda", cidade5[] = "Maceio";
char cep[] = "83201-23", cep1[] = "83201-10", cep2[] = "99901-23", cep3[] = "83211-29", cep4[] = "83101-03", cep5[] = "85201-26";
char cpf[] = "123583201-23", cpf1[] = "123544201-23", cpf2[] = "567899901-23", cpf3[] = "111183211-29", cpf4[] = "987583101-03", cpf5[] = "908385201-26";

TEST(TestaExistencias, TestExist){
	printf("\n");
	G = cria_Grafo();
	ASSERT_TRUE(G != NULL);
	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	ASSERT_TRUE(User != NULL);
	ASSERT_TRUE(verifica_amizades(&User) == NULL);
	User1 = cria_pessoaAuto(&G, nom1, cpf1, cep1, cidade1);
	adiciona_amigos(&G, &User, &User1, 0);
	ASSERT_TRUE(verifica_amizades(&User) != NULL);
	destroi_Grafo(&G);
}

TEST(TestaInsercao, TestInsert){
	printf("\n");
	G = cria_Grafo();
	ASSERT_TRUE(G->N_usuarios == 0);
	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	ASSERT_TRUE(User->Amigos[verifica_letra(User1->nome[0])] == NULL);
	ASSERT_TRUE(G->N_usuarios == 1);
	User1 = cria_pessoaAuto(&G, nom1, cpf1, cep1, cidade1);
	adiciona_amigos(&G, &User, &User1, 0);
	ASSERT_TRUE(User1->Amigos[verifica_letra(User->nome[0])] != NULL);
	ASSERT_TRUE(G->N_usuarios == 2);
	destroi_Grafo(&G);
}

TEST(TestaVisualizacao, TestPreview){ // Testando erros de Impressao.
	printf("\n");
	G = cria_Grafo();

	cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	cria_pessoaAuto(&G, nom1, cpf1, cep1, cidade1);
	cria_pessoaAuto(&G, nom2, cpf2, cep2, cidade2);
	cria_pessoaAuto(&G, nom3, cpf3, cep3, cidade3);
	cria_pessoaAuto(&G, nom4, cpf4, cep4, cidade4);
	cria_pessoaAuto(&G, nom5, cpf5, cep5, cidade5);
	ASSERT_TRUE(G->N_usuarios == 6);
	//imprime_Grafo(G);
	ASSERT_TRUE(G != NULL);
	destroi_Grafo(&G);
}

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);

  	return RUN_ALL_TESTS();
}

#endif
