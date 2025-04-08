#ifndef NOABB_H
#define NOABB_H

class NoABB
{
private:
	int valor;
	int altura;
	NoABB *esq;
	NoABB *dir;

public:
	// resolver no quadro primeiro
	NoABB(int valor);
	~NoABB();
	int getValor();
	NoABB *getEsq();
	NoABB *getDir();
	void setValor(int valor);
	void setEsq(NoABB *no);
	void setDir(NoABB *no);
	int getAltura();
	void setAltura(int altura);

	// exercícios
	void insere(int valor);
	NoABB *busca(int valor);
	void imprimeOrdemCrescente();
	void imprimeVisualizacao(int n);

	// resolver no quadro por último
	NoABB *remove(NoABB *no, int valor);


	//atividade 04/04
	int soma();
	float media();
	bool ehCompleta();
	bool ehCheia();
	void imprimeIntervalo(int x, int y);
	bool estritamenteBinaria();
	int maioresQue(int valor);
	float mediaNivel(int nivel);
	int alturaNos();
	int contadorNos();
	bool ehCompletaAux(NoABB *no, int index, int total);
};

#endif
