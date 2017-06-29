#ifndef TEST

#include <stdio.h>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "Grafo.h"

Grafo *G;
usuarios *User, *User1, *User2, *User3, *User4;
int NumeroUsuarios, NumeroAmigos;
char nom[] = "Rafael", nom1[] = "Marcelo", nom2[] = "Paula", nom3[] = "Andre", nom4[] = "Leandro", nom5[] = "Joao";
char cidade[] = "Aguas", cidade1[] = "Taguatinga", cidade2[] = "Ceilandia", cidade3[] = "Marajo", cidade4[] = "Olinda", cidade5[] = "Maceio";
char cep[] = "83201-23", cep1[] = "83201-10", cep2[] = "99901-23", cep3[] = "83211-29", cep4[] = "83101-03", cep5[] = "85201-26";
char cpf[] = "123583201-23", cpf1[] = "123544201-23", cpf2[] = "567899901-23", cpf3[] = "111183211-29", cpf4[] = "987583101-03", cpf5[] = "908385201-26";
char nomeArquivo[] = "BancodeDados.txt";


TEST(TestaExistencia, TestExist){ // Testando criação e existencia dos itens criados.
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

TEST(TestaInsercao, TestInsert){ // Testando inserção de elementos do grafo.
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
	ASSERT_TRUE(User->numeroAmigos == 1);
	destroi_Grafo(&G);
}

TEST(TestaAmizades, TestBrotherhood){ // Testando lista de amigos de uma usuario.
	printf("\n");
	G = cria_Grafo();
	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	User1 = cria_pessoaAuto(&G, nom1, cpf1, cep1, cidade1);
	User2 = cria_pessoaAuto(&G, nom2, cpf2, cep2, cidade2);
	User3 = cria_pessoaAuto(&G, nom3, cpf3, cep3, cidade3);
	User4 = cria_pessoaAuto(&G, nom4, cpf4, cep4, cidade4);
	ASSERT_TRUE(verifica_amizades(&User) == NULL);
	adiciona_amigos(&G, &User, &User1, 0);
	ASSERT_TRUE(User->numeroAmigos == 1);
	adiciona_amigos(&G, &User, &User2, 0);
	ASSERT_TRUE(User->numeroAmigos == 2);
	adiciona_amigos(&G, &User, &User3, 0);
	ASSERT_TRUE(User->numeroAmigos == 3);
	adiciona_amigos(&G, &User, &User4, 0);
	ASSERT_TRUE(User->numeroAmigos == 4);
	ASSERT_TRUE(verifica_amizades(&User) != NULL);

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

TEST(TestaAtualizacao, TestUpdate){ // Testando erros de Atualizacao de informações.
	printf("\n");
	G = cria_Grafo();
	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	ASSERT_TRUE(G->N_usuarios == 1);
	ASSERT_TRUE(strcmp(User->nome, nom) == 0);
	ASSERT_TRUE(strcmp(User->cep, cep) == 0);
	ASSERT_TRUE(strcmp(User->cpf, cpf) == 0);
	ASSERT_TRUE(strcmp(User->cidade, cidade) == 0);
	User = edita_nome(&G, &User, nom1); // A edição de nome aloca espaço para um usuario e transfere todos os dados do usuario de origem e depois o exclui.
	edita_cep(&G, &User, cep1);
	edita_cpf(&G, &User, cpf1);
	edita_cidade(&G, &User, cidade1);
	ASSERT_TRUE(strcmp(User->nome, nom1) == 0);
	ASSERT_TRUE(strcmp(User->cep, cep1) == 0);
	ASSERT_TRUE(strcmp(User->cpf, cpf1) == 0);
	ASSERT_TRUE(strcmp(User->cidade, cidade1) == 0);
	ASSERT_TRUE(G->N_usuarios == 1);
	destroi_Grafo(&G);
}

TEST(TestaRemocao, TestElimination){ // Testando erros de Remoção.
	printf("\n");
	G = cria_Grafo();

	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	User1 = cria_pessoaAuto(&G, nom1, cpf1, cep1, cidade1);
	User2 = cria_pessoaAuto(&G, nom2, cpf2, cep2, cidade2);
	User3 = cria_pessoaAuto(&G, nom3, cpf3, cep3, cidade3);
	User4 = cria_pessoaAuto(&G, nom4, cpf4, cep4, cidade4);
	ASSERT_TRUE(G->N_usuarios == 5);
	ASSERT_TRUE(existe_Grafo(G));
	exclui_usuario(&G, &User);
	exclui_usuario(&G, &User1);
	exclui_usuario(&G, &User2);
	exclui_usuario(&G, &User3);
	exclui_usuario(&G, &User4);
	ASSERT_TRUE(G->N_usuarios == 0);
	ASSERT_FALSE(existe_Grafo(G));
	destroi_Grafo(&G);
}

TEST(TestaPesquisa, TestSearch){ // Testando erros de Pesquisa.
	printf("\n");
	G = cria_Grafo();

	//Uma pesquisa retorna um usuario se usuario existir ou Null se não existir.
	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	User1 = cria_pessoaAuto(&G, nom1, cpf1, cep1, cidade1);
	ASSERT_TRUE(procura_nome(G, User->nome) != NULL);
	ASSERT_TRUE(procura_nome(G, User1->nome) != NULL);
	ASSERT_TRUE(procura_nome(G, nom2) == NULL);
	destroi_Grafo(&G);
}


TEST(TestaArquivo, TestFile){ // Testando erros no arquivo criado.
	printf("\n");
	G = cria_Grafo();
	User = cria_pessoaAuto(&G, nom, cpf, cep, cidade);
	ASSERT_TRUE(salva_Arquivo(&G) != NULL);
	ASSERT_TRUE(tamanho_Arquivo(nomeArquivo) > 0);
	destroi_Grafo(&G);
	ASSERT_TRUE(tamanho_Arquivo(nomeArquivo) <= 0);
}

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);

  	return RUN_ALL_TESTS();
}

#endif
