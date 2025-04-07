#include <iostream>
#include "NoABB.h"

using namespace std;

NoABB::NoABB(int valor)
{
	this->valor = valor;
	this->esq = NULL;
	this->dir = NULL;
}

NoABB::~NoABB()
{
	delete this->esq;
	delete this->dir;
}

int NoABB::getValor()
{
	return this->valor;
}

NoABB *NoABB::getEsq()
{
	return this->esq;
}

NoABB *NoABB::getDir()
{
	return this->dir;
}

void NoABB::setValor(int valor)
{
	this->valor = valor;
}

void NoABB::setEsq(NoABB *no)
{
	this->esq = no;
}

void NoABB::setDir(NoABB *no)
{
	this->dir = no;
}
int NoABB::getAltura()
{
	return this->altura;
}
void NoABB::setAltura(int altura)
{
	this->altura = altura;
}

void NoABB::insere(int valor)
{

	if (this->valor == valor)
	{
		cout << "Valor já existe na árvore." << endl;
		return;
	}
	if (valor < this->valor)
	{
		if (this->esq == NULL)
		{
			this->esq = new NoABB(valor);
		}
		else
		{
			this->esq->insere(valor);
		}
	}
	else
	{
		if (this->dir == NULL)
		{
			this->dir = new NoABB(valor);
		}
		else
		{
			this->dir->insere(valor);
		}
	}
}

NoABB *NoABB::busca(int valor)
{
	if (this->valor == valor)
	{
		return this;
	}
	else if (valor < this->valor)
	{
		if (this->esq != NULL)
		{
			return this->esq->busca(valor);
		}
	}
	else
	{
		if (this->dir != NULL)
		{
			return this->dir->busca(valor);
		}
	}
	return NULL;
}

NoABB *NoABB::remove(NoABB *no, int valor)
{
	if (valor < no->getValor())
		no->setEsq(no->remove(no->getEsq(), valor));
	else if (valor > no->getValor())
		no->setDir(no->remove(no->getDir(), valor));
	else
	{
		if (no->getEsq() == NULL && no->getDir() == NULL)
		{
			delete no;
			return NULL;
		}
		else if (no->getEsq() == NULL)
		{
			NoABB *temp = no->getDir();
			delete no;
			return temp;
		}
		else if (no->getDir() == NULL)
		{
			NoABB *temp = no->getEsq();
			delete no;
			return temp;
		}
		else
		{
			NoABB *temp = no->getDir();
			while (temp->getEsq() != NULL)
				temp = temp->getEsq();
			no->setValor(temp->getValor());
			no->setDir(no->remove(no->getDir(), temp->getValor()));
		}
	}
	return no;
}

void NoABB::imprimeOrdemCrescente()
{
	if (this->esq != NULL)
		this->esq->imprimeOrdemCrescente();
	cout << this->valor << " ";
	if (this->dir != NULL)
		this->dir->imprimeOrdemCrescente();
}

void NoABB::imprimeVisualizacao(int n)
{
	for (int i = 0; i < n; i++)
		cout << "--";
	cout << "(" << this->valor << ")" << endl;
	if (this->esq != NULL)
		this->esq->imprimeVisualizacao(n + 1); // pra mostrar em que nível está
	if (this->dir != NULL)
		this->dir->imprimeVisualizacao(n + 1);
}

void NoABB::imprimeIntervalo(int x, int y)
{
	if (this->valor >= x && this->valor <= y)
	{
		if (this->esq != NULL)
			this->esq->imprimeIntervalo(x, y);
		cout << this->valor << " ";
		if (this->dir != NULL)
			this->dir->imprimeIntervalo(x, y);
	}
	else if (this->valor < x && this->dir != NULL)
		this->dir->imprimeIntervalo(x, y);
	else if (this->valor > y && this->esq != NULL)
		this->esq->imprimeIntervalo(x, y);
}

bool NoABB::ehCompleta() // todos os níveis estão completos, exceto o último, que pode estar incompleto
{
	if (this->esq == NULL && this->dir == NULL)
		return true;

	if (this->esq == NULL && this->dir != NULL)
		return false;

	if (this->esq != NULL && this->dir == NULL)
		return this->esq->alturaNos() == 1 && this->esq->ehCompleta();

	int alturaEsq = this->esq->alturaNos();
	int alturaDir = this->dir->alturaNos();
	if (alturaEsq < alturaDir) // a altura da esquerda tem que ser maior ou igual à direita, não pode estar sobrando na direita
		return false;
	// se tem filho esquerdo e direito faz as duas buscas
	return this->esq->ehCompleta() && this->dir->ehCompleta();
}
bool NoABB::ehCheia() // perfeitamente cheia com dois filhos até o último nível
{
	if (this->esq == NULL && this->dir == NULL)
		return true;

	// v- só um dos dois tem filhos
	if (this->esq == NULL || this->dir == NULL)
		return false;

	// Verifica se as alturas das subárvores esquerda e direita são iguais, porque tem que estar no mesmo nível
	int alturaEsq = this->esq->alturaNos();
	int alturaDir = this->dir->alturaNos();
	if (alturaEsq != alturaDir)
		return false;

	return this->esq->ehCheia() && this->dir->ehCheia();
}
bool NoABB::estritamenteBinaria() // todos os nós têm 0 ou 2 filhos
{
	if (this->esq == NULL && this->dir == NULL)
		return true;
	if (this->esq != NULL && this->dir != NULL)
		return this->esq->estritamenteBinaria() && this->dir->estritamenteBinaria();
	return false;
}
int NoABB::maioresQue(int valor) // retorna quantos nós são maiores que o valor passado
{
	int cont = 0;
	if (this->valor > valor)
		cont++;
	if (this->esq != NULL)
		cont += this->esq->maioresQue(valor);
	if (this->dir != NULL)
		cont += this->dir->maioresQue(valor);
	return cont;
}
float NoABB::mediaNivel(int nivel) // passando recurssivamente nó por no e retorna a média dos nós do nível passado
{
	if (nivel == 0)
		return this->valor;
	float soma = 0;
	int cont = 0;
	if (this->esq != NULL)
	{
		soma += this->esq->mediaNivel(nivel - 1);
		cont++;
	}
	if (this->dir != NULL)
	{
		soma += this->dir->mediaNivel(nivel - 1);
		cont++;
	}
	if (cont == 0)
		return 0; // caso o nivel nao exista, não vai chegar nele
	return soma / cont;
}
int NoABB::alturaNos()
{
	int alturaEsq = 0;
	int alturaDir = 0;
	if (this->esq != NULL)
		alturaEsq = this->esq->alturaNos();
	if (this->dir != NULL)
		alturaDir = this->dir->alturaNos();
	this->altura = max(alturaEsq, alturaDir) + 1;
	return this->altura;
}
int NoABB::soma() // somando todos os valores da arvore
{
	int soma = this->valor;
	if (this->esq != NULL)
		soma += this->esq->soma();
	if (this->dir != NULL)
		soma += this->dir->soma();
	return soma;
}
int NoABB::contadorNos()
{
	int cont = 1;
	if (this->esq != NULL)
		cont += this->esq->contadorNos();
	if (this->dir != NULL)
		cont += this->dir->contadorNos();
	return cont;
}

float NoABB::media() // usa funções de soma e contador de nós para calcular a média
{
	float soma = this->soma();
	int cont = this->contadorNos();
	return soma / cont;
}
