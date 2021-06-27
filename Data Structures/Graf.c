#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	char name;
	int x;
	struct node *next;
}NODE;

typedef struct graph{
	int numVertices;
	NODE **adjList;
}GRAPH;

NODE *createNode(char string, int adet) {
  NODE *newNode = (NODE*)malloc(sizeof(NODE));
  newNode->name = string;
  newNode->x = adet;
  newNode->next = NULL;
  return newNode;
}  

GRAPH *createGraph(int vertices) {
	GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph->numVertices = vertices;
	
	graph->adjList = (NODE**)malloc(vertices * sizeof(NODE*));
	
	int i;
	for (i=0;i<vertices;i++){
	  	graph->adjList[i] = NULL;
	}
	
	addGraph(graph);
	return graph;
} 

void addGraph(GRAPH *graph){
	int i, sorgu;
	char tut;
	printf("\nSorgu nodelarinin isimlerini ve kac defa sorgulandigini giriniz.");
	
	for(i=0;i<graph->numVertices;i++){
		printf("\nIsim: ");
		scanf(" %c", &tut);
		printf("Sorgu: ");
		scanf("%d", &sorgu);
		
		graph->adjList[i] = createNode(tut, sorgu);

		graph->adjList[i]->name = tut;
		graph->adjList[i]->x = sorgu;
	}
}

void addEdge(GRAPH *graph, char s, char d) {
	int i=0, tut=1, tut2=1;
	int a,b;
	
	while(i<graph->numVertices && (tut || tut2)){

		if(graph->adjList[i]->name == s){
			a = i;
			tut=0;
		}
		if(graph->adjList[i]->name == d){
			b = i;
			tut2=0;
		}
		i++;
	}
	
	if(tut != 0 || tut2 != 0){
		printf("HATALI GIRIS\n");
	}
	else{
		NODE *newNode = createNode(graph->adjList[b]->name, graph->adjList[b]->x);
		newNode->next = graph->adjList[a]->next;
		graph->adjList[a]->next = newNode;
		
		newNode = createNode(graph->adjList[a]->name, graph->adjList[a]->x);
		newNode->next = graph->adjList[b]->next;
		graph->adjList[b]->next = newNode;	
	}
}

void printGraph(GRAPH *graph) {
	int v;
	printf("\n");
	for (v=0;v<graph->numVertices;v++) {
		NODE *temp = graph->adjList[v];
		printf("Vertex %c:\n ", temp->name);

		temp=temp->next;
   	 	while (temp) {
      		printf("%c -> ", temp->name);
      		temp = temp->next;
    	}
    	printf("\n");
 	}
}
  
GRAPH *yap(){
	
	int toplam, tut=0, sakla=1, kontrol;
	char node1, node2;

	printf("\nNode sayisi giriniz: ");
	scanf("%d", &toplam);
		
	GRAPH *graph = createGraph(toplam);	

	printf("\nAralarinda baglanti olan nodelar varsa 1'e yok ise 0'a basiniz : ");
	scanf("%d", &kontrol);
		
	while(kontrol == 1){
		printf("Baglantisi olan iki nodeun isimlerini giriniz : ");
		scanf(" %c", &node1);
		scanf(" %c", &node2);
	
		addEdge(graph, node1, node2);

		printf("Baska baglanti var ise 1 yoksa 0 giriniz : ");
		scanf("%d", &kontrol);		
	}
	return graph;
}

GRAPH *concatanateGraph(int vertices) {
	GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph->numVertices = vertices;
	
	graph->adjList = (NODE**)malloc(vertices * sizeof(NODE*));
	
	int i;
	for (i=0;i<vertices;i++){
	  	graph->adjList[i] = NULL;
	}
	return graph;
}

int control(GRAPH *graph1, GRAPH *graph2){
	int i,j;
	int tut, sonuc;
	for(i=0;i<graph1->numVertices;i++){
		for(j=0;j<graph2->numVertices;j++){
			if(graph1->adjList[i]->name == graph2->adjList[j]->name){
				tut++;	
			}
		}
	}
	sonuc = graph1->numVertices + graph2->numVertices - tut;
	return sonuc;
}

int graphControl(GRAPH *newGraph, char name, char name2){
	int a;
	a = newGraph->numVertices;
	int tut=1,i=0;
	
	while(i<a){
		NODE *temp = newGraph->adjList[i];
		temp = temp->next;
		if(newGraph->adjList[i]->name == name){
			while(tut==1){
				if(temp == NULL){
					break;
				}
				
				if(temp->name == name2){
					tut=0;
				}
				temp=temp->next;
			}
			
			if(tut == 0){
				return 0;
			}
			else{
				return 1;
			}
		}
		i++;
	}
}

void merge(GRAPH *newGraph, GRAPH *graph){
	int i;
	int tut=0;
	
	for(i=0;i<graph->numVertices;i++){
		NODE *temp = graph->adjList[i];
		temp = temp->next;
		while(temp != NULL){
			tut = graphControl(newGraph, graph->adjList[i]->name, temp->name);
			
			if(tut == 1){
				addEdge(newGraph, graph->adjList[i]->name, temp->name);
			}
			temp = temp->next;
		}
	}
}

GRAPH *mergeGraph(GRAPH *graph1, GRAPH *graph2){
	int a,i,j,tut=0, kontrol;
	
	a = control(graph1, graph2);
	
	GRAPH *newGraph = concatanateGraph(a);
	
	for(i=0;i<graph1->numVertices;i++){
		newGraph->adjList[i] = createNode(graph1->adjList[i]->name, graph1->adjList[i]->x);
		
		newGraph->adjList[i]->name = graph1->adjList[i]->name;
		newGraph->adjList[i]->x = graph1->adjList[i]->x;

		tut++;
	}
	
	for(i=0;i<graph2->numVertices;i++){
		kontrol = 0;
		for(j=0;j<graph1->numVertices;j++){
			if(graph2->adjList[i]->name == graph1->adjList[j]->name){
				kontrol = 1;
			}
		}
		
		if(kontrol == 0){
			
			newGraph->adjList[tut] = createNode(graph2->adjList[i]->name, graph2->adjList[i]->x);
			
			newGraph->adjList[tut]->name = graph2->adjList[i]->name;
			newGraph->adjList[tut]->x = graph2->adjList[i]->x;
			tut++;
		}
	}
	merge(newGraph, graph1);
	
	merge(newGraph, graph2);
	
	printf("\nBIRLESTIRILEN GRAF\n");
	printGraph(newGraph);
	
	return newGraph;
}

void findNodes(GRAPH *graph, char isim){
	int i,j;
	int deger=-1, deger2=-1, deger3=-1;
	char tut, tut2, tut3, sakla;
	
	for(i=0;i<graph->numVertices;i++){
		if(graph->adjList[i]->name == isim){
			NODE* temp = graph->adjList[i];
			temp = temp->next;
			printf("\nEn cok aranan ilk 3 komsu : ");
			for(j=0;j<3;j++){
				if(j==0){
					while(temp != NULL){
						if(temp->x >= deger){
							deger = temp->x;
							tut = temp->name;
						}
						temp = temp->next;
					}
					printf("%c ", tut);
				}
				
				if(j==1){
					while(temp != NULL){
						if(temp->x >= deger2){
							if(temp->name != tut){
								deger2 = temp->x;
								tut2 = temp->name;
							}
						}
						temp = temp->next;
					}
					printf("%c ", tut2);
				}
				
				if(j==2){
					while(temp != NULL){
						if(temp->x >= deger3){
							if(temp->name != tut && temp->name != tut2){
								deger3 = temp->x;
								tut3 = temp->name;
							}
						}
						temp = temp->next;
					}
					printf("%c ", tut3);
				}
				
				temp = graph->adjList[i];
				temp = temp->next;
			}
			sakla = graph->adjList[i]->name;
			graph->adjList[i]->x = graph->adjList[i]->x + 1;
			printf("\n%c nodeunun yeni degeri : %d",graph->adjList[i]->name, graph->adjList[i]->x);
		}
	}
	for(i=0;i<graph->numVertices;i++){
		NODE *temp = graph->adjList[i];
		temp = temp->next;
		while(temp != NULL){
			if(temp->name == sakla){
				temp->x = temp->x + 1;
			}
			temp = temp->next;
		}
	}
}

int main(){
	
	char node1, node2;

	GRAPH *graph1;
	printf("***Lutfen ilk sorgu grafi icin islemleri gerceklestirin.\n");
	printf("Node isimleri char seklinde tutulmustur.\n");
	graph1 = yap();
	
	GRAPH *graph2;
	printf("\n***Lutfen ikinci sorgu grafi icin islemleri gerceklestirin.\n");
	graph2 = yap();
	
	GRAPH *newGraph = mergeGraph(graph1, graph2);

	char sorgula;
	int deger;
	int dondur;
	
	printf("\nSorgulama yapmak icin 1'e yoksa 0'a basiniz : ");
	scanf("%d", &deger);
	
	while(deger == 1){
		printf("\nLutfen sorgulamak istediginiz dugumun ismini giriniz : ");
		scanf(" %c", &sorgula);
		
		findNodes(newGraph, sorgula);
		
		printf("\n\nSorgulamaya devam etmek icin 1'e yoksa 0'a basiniz.\n");
		scanf("%d", &deger);
	}
	return 0;
}
