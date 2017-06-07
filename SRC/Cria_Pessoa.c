#include <Grafo.h>

int cria_pessoa(){

	FILE *fp;
	char name[100], cidade[30], CEP[20], CPF[20],USER[200];
	int numeroamigos;

	if (fp = fopen("Users", "ab") == NULL){
		printf("Error");
		exit(1);
	}
	gets(name);
	gets(cidade);
	gets(CEP);
	gets(CPF);
	scanf("%d", &numeroamigos);
	strcat(USER,name);
	strcat(USER,"|");
	strcat(USER,cidade);
	strcat(USER,"|");
	strcat(USER,CEP);
	strcat(USER,"|");
	strcat(USER,CPF);
	fwrite(USER,strlen(USER),1,fp);
	fwrite(&numeroamigos,sizeof(int),1,fp);
	fclose(fp);
}