#ifndef ABB_H
#define ABB_H

#include "NoABB.h"

class ABB
{
private:
	NoABB *raiz;

public:
	ABB();
	~ABB();
	bool vazia();
	void insere(int valor);
	NoABB *busca(int valor);
	void remove(int valor);
	void imprimeEmLargura();
	void imprimeOrdemCrescente();
	void imprimeVisualizacao();
	void destroiArvore();

	// atividade 04/04
	int soma();
	float media();
	bool ehCompleta();
	bool ehCheia();
	void imprimeIntervalo(int x, int y);
	bool estritamenteBinaria();
	int maioresQue(int valor);
	float mediaNivel(int nivel);
	int alturaNos();
};

#endif
