#include "elemento.hpp"
#include <stdexcept>

#include <iostream>
using namespace std;


template<typename T>
class ListaEnc {

private:
	Elemento<T>* head;
	int size;

public:
	ListaEnc(){
		size = 0;
		head = 0;
	}

	~ListaEnc(){
		destroiLista();
	}

	void adicionaNoInicio(const T& dado){
		Elemento<T> *novo = new Elemento<T>(dado);
		if(novo == 0){
			throw runtime_error("Não adicionado novo elemento.");
		}
		size++;
		if(head != 0){
			novo->setProximo(head);
		}
		head = novo;
		return;
	}

	T recuperaDoInicio(){
		if(listaVazia()){
			throw runtime_error("Lista vazia, impossível recuperar do início.");
		}
		return head->getInfo();
	}

	T eliminaDoInicio(){
		if(listaVazia()){
			throw runtime_error("Lista vazia, impossível eliminar do início.");
		}
		Elemento<T> *aux = head;
		T dado = aux->getInfo();
		size--;
		if(size == 0){
			head = 0;
			return dado;
		}
		head = aux->getProximo();
		delete aux;
		return head->getInfo();
	}

	void adicionaNaPosicao(T dado, int pos){
		if(pos > size || pos < 0){
			throw runtime_error("Posição inválida: impossível adicionar elemento em posição específica.");
		}
		if(pos == 0){
			return adicionaNoInicio(dado);
		}
		Elemento<T> *anterior = head;
		for(int i = 1; i < pos; i++){
			anterior = anterior->getProximo();
		}
		Elemento<T> *novo = new Elemento<T>(dado, anterior->getProximo());
		if(novo == 0){
			throw runtime_error("Não foi possível alocar memória p/ novo elemento");
		}
		anterior->setProximo(novo);
		size++;
	}

	int posicao( T dado) {
		if(listaVazia()){
			throw runtime_error("Não foi possível encontrar posição: lista vazia.");
		}
		Elemento<T> *atual = head;
		for(int i = 0; i < size; i++){
			if( igual(atual->getInfo(), dado) ){
				return i;
			}
			atual = atual->getProximo();
		}
		throw runtime_error("Não foi possível encontrar posição: dado não está na lista.");
	}

	/* n funfa

	T* posicaoMem(T dado) {
		if(listaVazia()){
			throw runtime_error("Não foi possível encontrar posição de memória: lista vazia.");
		}
		Elemento<T> *atual = head;
		for(int i = 0; i < size; i++){
			if(igual(atual->getInfo(), dado)){
				return atual->getInfo();
			}
			atual = atual->getProximo();
		}
		throw runtime_error("Não foi possível encontrar posição de memória: dado não está na lista.");
	}
	*/

	bool contem(const T& dado){
		if(listaVazia()){
			throw runtime_error("Dado não está na lista: lista vazia.");
		}
		Elemento<T> *atual = head;
		for (int i = 0; i < size; i++) {
			if (atual->getInfo() == dado) {
				return true;
			}
			atual = atual->getProximo();
		}
		return false;
	}

	T eliminaDaPosicao(int pos){
		if (pos >= size || pos < 0) { //pq pos começa em 0
			throw runtime_error("Impossível retirar elemento: posição inválida.");
		}
		if(pos == 0){
			return eliminaDoInicio();
		}

		T retorno;
		Elemento<T> *anterior = head;
		for(int i = 0; i < pos-1; i++){
			anterior = anterior->getProximo();
		}

		Elemento<T> *eliminar = anterior->getProximo();
		retorno = eliminar->getInfo();
		anterior->setProximo(eliminar->getProximo());

		size--;
		delete eliminar;
		return retorno;
	}

	T recuperaDaPosicao(int pos){
		if (pos >= size || pos < 0) { //pq pos começa em 0
			throw runtime_error("Impossível recuperar elemento: posição inválida.");
		}
		if(pos == 0){
			return recuperaDoInicio();
		}
		Elemento<T> *atual = head;
		for(int i = 0; i < pos; i++){
			atual = atual->getProximo();
		}
		return atual->getInfo();
	}

	void adiciona(const T& dado){
		adicionaNaPosicao(dado, size);
	}

	T retira(){
		return eliminaDaPosicao(size-1); //pq começa em 0 a posição
	}

	T retiraEspecifico(const T& dado){
		int pos = posicao(dado);
		return eliminaDaPosicao(pos);
	}

	void adicionaEmOrdem(const T& data){
		if(listaVazia()){
			adicionaNoInicio(data);
		} else{

			Elemento<T> *atual = head;
			int pos = 1;
			while(pos < size && maior(data, atual->getInfo())){
				atual = atual->getProximo();
				pos++;
			}
			adicionaNaPosicao(data, pos);
		}
	}

	bool listaVazia() const{
		return size == 0;
	}

	bool igual(T dado1, T dado2){
		return (dado1 == dado2);
	}

	bool maior(T dado1, T dado2){
		return (dado1 > dado2);
	}

	bool menor(T dado1, T dado2){
		return (dado1 < dado2);
	}

	void destroiLista(){
		while(!listaVazia()){
				eliminaDoInicio();
		}
		delete head;
	}

	int getSize(){
		return size;
	}
};
