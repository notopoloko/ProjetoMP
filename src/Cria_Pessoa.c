#include <Grafo.h>

int cria_pessoa(){

	FILE *fp;
	char name[100], cidade[30], CEP[20], CPF[20],USER[200];
	int numeroamigos;

	

	if (fp = fopen("Users", "ab") == NULL){
		printf("Error");
		exit(1);
	}
	fwrite(USER,strlen(USER),1,fp);
	fwrite(&numeroamigos,sizeof(int),1,fp);
	fclose(fp);
}