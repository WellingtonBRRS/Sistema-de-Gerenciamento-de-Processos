#include <stdio.h>
#include <stdlib.h>
#define TAM 10 //Nao serao feitos testes com mais de 10 recursos/processos

/////////////////////////CABECALHO///////////////////////// - CONTROLE - INT MAIN - Inicio = LINHA 20 / Termino = Linha 297
//
//Linha 21 ate 26 = Criacao de variaveis
//Linha 29 ate 72 = Leitura de valores e limpeza de vetores/matrizes
//Linha 95 ate 292 = Loop para execucao do software
//Linha 102 ate 142 = Execucao da opcao 1 - "Apresentar Situacao"
//Linha 148 ate 284 = Execucao da opcao 2 - "Efetuar Processamento"
//Linha 289 ate 291 = Execucao da opcao 3 - "Sair"
//
//				ETAPAS DE PROCESSAMENTO
//Linha 152 ate 165 = 1° Etapa
//Linha 171 ate 230 = 2° Etapa
//Linha 258 ate 274 = 3° Etapa
//

int main(){
	int *P,R[TAM][TAM];//P = Vetor para alocacao de recursos // R = Matriz para fila de solicitacoes de recursos
	int qRec,qPro;//Variaveis para passagem de tamanhos
	int end=0,temp=0,cont=0,encerrar=0,loop=0,deadlock=0,aux=0,bestWay=0,func=0,fimExec=0;//Variaveis auxiliares
	int are[TAM];//1 = Executando, 2 = Bloqueado, 3 = Terminado
	int qRecNecAloc=0;//quantidade de recursos que necessita alocar
	int qRecDisAloc=0;//quantidade de recursos disponiveis para alocar
	
	//Scan da quantidade de recursos e cricao do vetor de recursos
	printf("Digite a quantidade de Recursos: ");
	scanf("%d",&qRec);
	
	P = (int *) malloc(qRec * sizeof(int));
	
	//Scan da quantidade de processos e limpeza do vetor de processos
	printf("Digite a quantidade de Processos: ");
	scanf("%d",&qPro);
	
	for(int i=0;i<qPro;i++){
		for(int j=0;j<TAM;j++){
			R[i][j]=-1;
		}	
	}
	
	//Limpeza do vetor ARE[]
	for(int i=0;i<TAM;i++){
		are[i]=0;
	}
	
	
	//Scan de valores para o vetor de recursos
	printf("\n\nDigite a alocacao de cada recurso passando seu processo:\n");
	for(int i=0;i<qRec;i++){
		printf("Recurso %d - Processo: ",i+1);
		scanf("%d",&P[i]);
	}
	
	//Scan das solicitacoes de recursos dos processos
	printf("\n\nDigite as solicitacoes de recursos: (Digite 0 para ir ao proximo processo)");
	for(int i=0;i<qPro;i++){
		cont=0;
		end=0;
		printf("\n");
		while(end==0){
			printf("Processo %d solicita o recurso: ",i+1);
			scanf("%d",&R[i][cont]);
			if(R[i][cont]!=0){
				cont++;
			}else{
				end=1;
			}
		}
	}

	//Identifica e atualiza os estados dos processos
	for(int i=0;i<qPro;i++){
		temp=0;
		if(R[i][0]!=0){
			are[i]=2;
		}else{
			for(int j=0;j<qRec;j++){
				if(P[j]==i+1){
					are[i]=1;
					temp=1;
					break;
				}
			}
			if(temp==0){
				are[i]=3;
			}
		}
	}
	//--------------------
		
	//-----------------------LOOP PARA PROCESSAMENTO-----------------------
	while(encerrar==0){
		printf("\n\nOpcoes:\n1-Apresentar Situacao = 2- Efetuar processamento = 3- Sair:  ");
		scanf("%d",&func);
		
		
		//PARTE 1 - INFORMACOES
		//Apresentar Situacao
		if(func==1){
			printf("\n\n---------------INFORMACOES - LOOP %d---------------",loop);
			printf("\nRecursos:");
			
			
			for(int i=0;i<qRec;i++){
				if(P[i]!=0){
					printf(" R%d>P%d;",i+1,P[i]);
				}else{
					printf(" R%d-L;",i+1);
				}
			}

			for(int i=0;i<qPro;i++){
				printf("\nProcesso %d:",i+1);
				for(int j=0;j<qRec;j++){
					if(P[j]==i+1){
						printf(" R%d;",j+1);
					}
				}
				for(int j=0;j<TAM;j++){
					if(R[i][j]!=0){
						printf(" >R%d;",R[i][j]);		
					}else{
						break;
					}
				}
				if(are[i]==1)
					printf(" (E)");
				else if(are[i]==2)
					printf(" (B)");
				else if(are[i]==3)
					printf(" (T)");
			}
			printf("\n--------------------------------------------------\n");
			if(fimExec==1){
				printf("\n----------------HOUVE DEADLOCK!!!-----------------");
			}else if(fimExec==2){
				printf("\n---------Programa encerrado sem Deadlock!---------");
			}
		}
		
		
		//PARTE 2 - PROCESSAMENTO
		
		
		if(func==2 && fimExec==0){
			//---------------------------------------------------------------------------------------
			//Etapa 1
			//Verificar Processos sem soliticatao de recursos
			for(int i=0;i<qPro;i++){
				if(R[i][0]==0 && are[i]!=3){
					//Verificar sem ha recursos com alocacoes sendo usados por processos sem solicitacoes
					for(int j=0;j<qRec;j++){
						//se sim, encerra-se a alocacao
						if(P[j]==i+1){
							P[j]=0;
						}
					}
					//Marcar como terminado
					are[i]=3;
					deadlock=1;//houve alguma mudanca
				}
			}
			//---------------------------------------------------------------------------------------
		 
			//---------------------------------------------------------------------------------------
			//Etapa 2
			//Verifica se ha um melhor caminho para alocacao
			for(aux=0;aux<qPro;aux++){
				qRecNecAloc=0;//quantidade de recursos que necessita alocar
				qRecDisAloc=0;//quantidade de recursos disponiveis para alocar
				for(int i=0;i<qRec;i++){
					if(R[aux][i]!=0 && R[aux][i]!=-1){
						qRecNecAloc++;
					}
				}
				for(int i=0;i<qRec;i++){
					if(P[(R[aux][i])-1]==0 && R[aux][i]!=0 && are[aux]==2){//verificar necessidade da ultima condicao -----
						qRecDisAloc++;
					}
					if(R[aux][i+1]==0){
						break;
					}
				}
				if(qRecNecAloc==qRecDisAloc && qRecNecAloc!=0){
					bestWay=aux;
					for(int x=0;x<TAM;){
						if(R[bestWay][x]!=0 && R[bestWay][x]!=-1){
							if(P[(R[bestWay][x])-1]==0){
								P[(R[bestWay][x])-1]=bestWay+1;
								deadlock=1;
								for(int j=0;j<(TAM-1);j++){
									if(R[bestWay][j]!=-1){
										R[bestWay][j]=R[bestWay][j+1];
									}
								}
							}
						}else{
							break;
						}
					}
				}
			}
	 
			//Verifica se um processo necessita alocacao
			cont=0;
			for(int i=0;i<qPro;){
				if(R[i][cont]!=0 && R[i][cont]!=-1){
					//caso sim, o recurso sera alocado para tal processo, e,
					//sera removido o pedido de alocacao da matriz de processos "R[][]"
					//tambem será setados os valores uma casa a menos
					if(P[(R[i][cont])-1]==0){
						P[(R[i][cont])-1]=i+1;
						deadlock=1;
						for(int j=cont;j<(TAM-1);j++){
							if(R[i][j]!=-1){
								R[i][j]=R[i][j+1];
							}
						}
						cont=0;
					}else{
						cont++;
					}
				}else{
					i++;
					cont=0;
				}
			}
			//---------------------------------------------------------------------------------------
			
			//Identificar quando o programa sera encerrado
			if(deadlock==0){
				fimExec=1;
			}else{
				if(qPro>1){
					for(int i=0;i<(qPro-1);i++){
						if(are[i]!=are[i+1]){
							break;
						}else if(are[0]==3){
							if(i+1==qPro-1){
								fimExec=2;
								break;
							}
						}
					}
				}else{
					if(are[0]==3){
						fimExec=2;
					}
				}
			}
 		
			//---------------------------------------------------------------------------------------
			//Etapa 3
			//Identifica e atualiza os estados dos processos
		 	for(int i=0;i<qPro;i++){
				temp=0;
				if(R[i][0]!=0){
					are[i]=2;
				}else{
					for(int j=0;j<qRec;j++){
						if(P[j]==i+1){
							are[i]=1;
							temp=1;
							break;
						}
					}
					if(temp==0){
						are[i]=3;
					}
				}
			}
			//---------------------------------------------------------------------------------------
	
			printf("\nProcessamento Concluido com Sucesso!");	
			loop++;//Loop de processamento incrementado
			deadlock=0;//set de variavel para zero para recomeço de processamento
		}else{
			if(func == 2 && fimExec!=0){
				printf("\n\n===========NAO HA PROCESSAMENTOS PARA SEREM FEITOS===========");
			}
		}
		//----------------------------------------------------------------------------
		
		//PARTE 3 - SAIR
		
		if(func==3){
			encerrar=1;
		}
	}
	//-----------------------------FIM DO LOOP-----------------------------
	
	free(P);
	return 0;
}
