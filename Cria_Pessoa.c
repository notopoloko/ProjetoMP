#include <Grafo.h>

int cria_pessoa(char *name, char *city, char *CEP,char *CPF){

	FILE *fp;
	char USER[200];
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
	strcat(USER,city);
	strcat(USER,"|");
	strcat(USER,CEP);
	strcat(USER,"|");
	strcat(USER,CPF);
	strcat(USER,"|");
	fwrite(USER,strlen(USER),1,fp);
	fwrite(&numeroamigos,sizeof(int),1,fp);
	fclose(fp);
	return SUCCESS;
}