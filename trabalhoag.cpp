#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Classe Elemento e suas derivadas
class Elemento {
protected:
    int ID;

public:
    Elemento(int id) : ID(id) {}
    virtual ~Elemento() {}

    int getID() const { return ID; }
    virtual void imprimirInfo() const = 0;
};

class Pessoa : public Elemento {
private:
    string nome;
    int idade;

public:
    Pessoa(int id, string nome, int idade) 
        : Elemento(id), nome(nome), idade(idade) {}

    void imprimirInfo() const override {
        cout << "Pessoa - ID: " << ID << ", Nome: " << nome 
             << ", Idade: " << idade << endl;
    }
};

class Produto : public Elemento {
private:
    string descricao;
    double preco;

public:
    Produto(int id, string descricao, double preco) 
        : Elemento(id), descricao(descricao), preco(preco) {}

    void imprimirInfo() const override {
        cout << "Produto - ID: " << ID << ", Descrição: " << descricao 
             << ", Preço: " << preco << endl;
    }
};

// Lista Não Ordenada
class ListaNaoOrdenada {
private:
    Elemento** elementos;
    int capacidade;
    int tamanho;

    void redimensionar() {
        capacidade *= 2;
        Elemento** novo = new Elemento*[capacidade];
        for (int i = 0; i < tamanho; i++) {
            novo[i] = elementos[i];
        }
        delete[] elementos;
        elementos = novo;
    }

public:
    ListaNaoOrdenada(int capacidadeInicial = 10) 
        : capacidade(capacidadeInicial), tamanho(0) {
        elementos = new Elemento*[capacidade];
    }

    ~ListaNaoOrdenada() {
        for (int i = 0; i < tamanho; i++) {
            delete elementos[i];
        }
        delete[] elementos;
    }

    void InserirNoInicio(Elemento* elem) {
        if (tamanho == capacidade) redimensionar();
        for (int i = tamanho; i > 0; i--) {
            elementos[i] = elementos[i-1];
        }
        elementos[0] = elem;
        tamanho++;
    }

    void InserirNoFinal(Elemento* elem) {
        if (tamanho == capacidade) redimensionar();
        elementos[tamanho++] = elem;
    }

    Elemento* RemoverPrimeiro() {
        if (tamanho == 0) throw out_of_range("Lista vazia");
        Elemento* removido = elementos[0];
        for (int i = 0; i < tamanho-1; i++) {
            elementos[i] = elementos[i+1];
        }
        tamanho--;
        return removido;
    }

    Elemento* RemoverUltimo() {
        if (tamanho == 0) throw out_of_range("Lista vazia");
        return elementos[--tamanho];
    }

    Elemento* RemoverPeloId(int id) {
        for (int i = 0; i < tamanho; i++) {
            if (elementos[i]->getID() == id) {
                Elemento* removido = elementos[i];
                for (int j = i; j < tamanho-1; j++) {
                    elementos[j] = elementos[j+1];
                }
                tamanho--;
                return removido;
            }
        }
        return nullptr;
    }

    Elemento* BuscarPeloId(int id) const {
        for (int i = 0; i < tamanho; i++) {
            if (elementos[i]->getID() == id) {
                return elementos[i];
            }
        }
        return nullptr;
    }

    bool AlterarPeloId(int id, Elemento* novoElem) {
        for (int i = 0; i < tamanho; i++) {
            if (elementos[i]->getID() == id) {
                delete elementos[i];
                elementos[i] = novoElem;
                return true;
            }
        }
        return false;
    }

    void imprimirTodos() const {
        for (int i = 0; i < tamanho; i++) {
            elementos[i]->imprimirInfo();
        }
    }

    int getTamanho() const { return tamanho; }
};

// Pilha usando ListaNaoOrdenada
class Pilha {
private:
    ListaNaoOrdenada lista;

public:
    void empilhar(Elemento* elem) {
        lista.InserirNoFinal(elem);
    }

    Elemento* desempilhar() {
        return lista.RemoverUltimo();
    }

    Elemento* consultarTopo() const {
        if (lista.getTamanho() == 0) return nullptr;
        // Implementação simplificada para demonstração
        return lista.BuscarPeloId(lista.getTamanho() - 1);
    }

    bool pilhaVazia() const {
        return lista.getTamanho() == 0;
    }

    void imprimirPilha() const {
        cout << "Conteúdo da Pilha (topo último):" << endl;
        for (int i = lista.getTamanho() - 1; i >= 0; i--) {
            lista.BuscarPeloId(i)->imprimirInfo();
        }
    }
};

// Fila eficiente
class Fila {
private:
    Elemento** elementos;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;

    void redimensionar() {
        capacidade *= 2;
        Elemento** novo = new Elemento*[capacidade];
        
        for (int i = 0; i < tamanho; i++) {
            novo[i] = elementos[(inicio + i) % tamanho];
        }
        
        delete[] elementos;
        elementos = novo;
        inicio = 0;
        fim = tamanho;
    }

public:
    Fila(int capacidadeInicial = 10) 
        : capacidade(capacidadeInicial), inicio(0), fim(0), tamanho(0) {
        elementos = new Elemento*[capacidade];
    }

    ~Fila() {
        for (int i = 0; i < tamanho; i++) {
            delete elementos[(inicio + i) % capacidade];
        }
        delete[] elementos;
    }

    void enfileirar(Elemento* elem) {
        if (tamanho == capacidade) redimensionar();
        elementos[fim] = elem;
        fim = (fim + 1) % capacidade;
        tamanho++;
    }

    Elemento* desenfileirar() {
        if (tamanho == 0) throw out_of_range("Fila vazia");
        Elemento* removido = elementos[inicio];
        inicio = (inicio + 1) % capacidade;
        tamanho--;
        return removido;
    }

    bool filaVazia() const {
        return tamanho == 0;
    }

    void imprimirFila() const {
        cout << "Conteúdo da Fila:" << endl;
        for (int i = 0; i < tamanho; i++) {
            elementos[(inicio + i) % capacidade]->imprimirInfo();
        }
    }
};

// Lista Simplesmente Encadeada
class ListaSimplesmenteEncadeada {
private:
    class No {
    public:
        Elemento* dado;
        No* proximo;
        
        No(Elemento* elem) : dado(elem), proximo(nullptr) {}
    };

    No* inicio;
    int tamanho;

public:
    ListaSimplesmenteEncadeada() : inicio(nullptr), tamanho(0) {}
    
    ~ListaSimplesmenteEncadeada() {
        No* atual = inicio;
        while (atual != nullptr) {
            No* proximo = atual->proximo;
            delete atual->dado;
            delete atual;
            atual = proximo;
        }
    }

    void inserirNoInicio(Elemento* elem) {
        No* novo = new No(elem);
        novo->proximo = inicio;
        inicio = novo;
        tamanho++;
    }

    void inserirNoFim(Elemento* elem) {
        No* novo = new No(elem);
        
        if (inicio == nullptr) {
            inicio = novo;
        } else {
            No* atual = inicio;
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
            }
            atual->proximo = novo;
        }
        tamanho++;
    }

    Elemento* removerPeloId(int id) {
        No* anterior = nullptr;
        No* atual = inicio;
        
        while (atual != nullptr && atual->dado->getID() != id) {
            anterior = atual;
            atual = atual->proximo;
        }
        
        if (atual == nullptr) return nullptr;
        
        if (anterior == nullptr) {
            inicio = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        
        Elemento* removido = atual->dado;
        delete atual;
        tamanho--;
        return removido;
    }

    Elemento* buscarPeloId(int id) const {
        No* atual = inicio;
        while (atual != nullptr) {
            if (atual->dado->getID() == id) {
                return atual->dado;
            }
            atual = atual->proximo;
        }
        return nullptr;
    }

    void imprimirLista() const {
        No* atual = inicio;
        cout << "Lista Simplesmente Encadeada:" << endl;
        while (atual != nullptr) {
            atual->dado->imprimirInfo();
            atual = atual->proximo;
        }
    }

    int getTamanho() const { return tamanho; }
};

// Árvore Binária de Busca
class ArvoreBinariaBusca {
private:
    class No {
    public:
        Elemento* dado;
        No* esquerda;
        No* direita;
        
        No(Elemento* elem) : dado(elem), esquerda(nullptr), direita(nullptr) {}
    };

    No* raiz;

    void destruirRecursivamente(No* no) {
        if (no != nullptr) {
            destruirRecursivamente(no->esquerda);
            destruirRecursivamente(no->direita);
            delete no->dado;
            delete no;
        }
    }

    No* inserirRecursivo(No* no, Elemento* elem) {
        if (no == nullptr) return new No(elem);
        
        if (elem->getID() < no->dado->getID()) {
            no->esquerda = inserirRecursivo(no->esquerda, elem);
        } else if (elem->getID() > no->dado->getID()) {
            no->direita = inserirRecursivo(no->direita, elem);
        }
        
        return no;
    }

    No* buscarRecursivo(No* no, int id) const {
        if (no == nullptr || no->dado->getID() == id) return no;
        
        if (id < no->dado->getID()) {
            return buscarRecursivo(no->esquerda, id);
        } else {
            return buscarRecursivo(no->direita, id);
        }
    }

    No* encontrarMinimo(No* no) {
        while (no != nullptr && no->esquerda != nullptr) {
            no = no->esquerda;
        }
        return no;
    }

    No* removerRecursivo(No* no, int id) {
        if (no == nullptr) return nullptr;
        
        if (id < no->dado->getID()) {
            no->esquerda = removerRecursivo(no->esquerda, id);
        } else if (id > no->dado->getID()) {
            no->direita = removerRecursivo(no->direita, id);
        } else {
            if (no->esquerda == nullptr) {
                No* temp = no->direita;
                delete no->dado;
                delete no;
                return temp;
            } else if (no->direita == nullptr) {
                No* temp = no->esquerda;
                delete no->dado;
                delete no;
                return temp;
            }
            
            No* temp = encontrarMinimo(no->direita);
            no->dado = temp->dado;
            no->direita = removerRecursivo(no->direita, temp->dado->getID());
        }
        
        return no;
    }

    void emOrdemRecursivo(No* no) const {
        if (no != nullptr) {
            emOrdemRecursivo(no->esquerda);
            no->dado->imprimirInfo();
            emOrdemRecursivo(no->direita);
        }
    }

    void preOrdemRecursivo(No* no) const {
        if (no != nullptr) {
            no->dado->imprimirInfo();
            preOrdemRecursivo(no->esquerda);
            preOrdemRecursivo(no->direita);
        }
    }

    void posOrdemRecursivo(No* no) const {
        if (no != nullptr) {
            posOrdemRecursivo(no->esquerda);
            posOrdemRecursivo(no->direita);
            no->dado->imprimirInfo();
        }
    }

public:
    ArvoreBinariaBusca() : raiz(nullptr) {}
    
    ~ArvoreBinariaBusca() {
        destruirRecursivamente(raiz);
    }

    void inserir(Elemento* elem) {
        raiz = inserirRecursivo(raiz, elem);
    }

    Elemento* buscarPeloId(int id) const {
        No* no = buscarRecursivo(raiz, id);
        return (no == nullptr) ? nullptr : no->dado;
    }

    void removerPeloId(int id) {
        raiz = removerRecursivo(raiz, id);
    }

    void emOrdem() const {
        cout << "Percurso em Ordem:" << endl;
        emOrdemRecursivo(raiz);
    }

    void preOrdem() const {
        cout << "Percurso Pré-Ordem:" << endl;
        preOrdemRecursivo(raiz);
    }

    void posOrdem() const {
        cout << "Percurso Pós-Ordem:" << endl;
        posOrdemRecursivo(raiz);
    }
};

// Funções auxiliares para criação de elementos
Elemento* criarPessoa() {
    int id, idade;
    string nome;
    
    cout << "ID: ";
    cin >> id;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Idade: ";
    cin >> idade;
    
    return new Pessoa(id, nome, idade);
}

Elemento* criarProduto() {
    int id;
    double preco;
    string descricao;
    
    cout << "ID: ";
    cin >> id;
    cout << "Descrição: ";
    cin.ignore();
    getline(cin, descricao);
    cout << "Preço: ";
    cin >> preco;
    
    return new Produto(id, descricao, preco);
}

Elemento* criarElemento() {
    int tipo;
    cout << "Tipo de elemento (1-Pessoa, 2-Produto): ";
    cin >> tipo;
    
    if (tipo == 1) return criarPessoa();
    else return criarProduto();
}

// Menu principal
void menuPrincipal() {
    ListaNaoOrdenada lista;
    Pilha pilha;
    Fila fila;
    ListaSimplesmenteEncadeada listaEncadeada;
    ArvoreBinariaBusca arvore;

    while (true) {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Lista Não Ordenada" << endl;
        cout << "2. Pilha" << endl;
        cout << "3. Fila" << endl;
        cout << "4. Lista Simplesmente Encadeada" << endl;
        cout << "5. Árvore Binária de Busca" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        
        int opcao;
        cin >> opcao;
        
        if (opcao == 0) break;
        
        switch (opcao) {
            case 1: {
                // Menu Lista Não Ordenada
                while (true) {
                    cout << "\n===== LISTA NÃO ORDENADA =====" << endl;
                    cout << "1. Inserir no início" << endl;
                    cout << "2. Inserir no final" << endl;
                    cout << "3. Remover primeiro" << endl;
                    cout << "4. Remover último" << endl;
                    cout << "5. Remover por ID" << endl;
                    cout << "6. Buscar por ID" << endl;
                    cout << "7. Alterar por ID" << endl;
                    cout << "8. Imprimir lista" << endl;
                    cout << "0. Voltar" << endl;
                    cout << "Escolha uma opção: ";
                    
                    int op;
                    cin >> op;
                    if (op == 0) break;
                    
                    int id;
                    Elemento* elem;
                    
                    switch (op) {
                        case 1:
                            elem = criarElemento();
                            lista.InserirNoInicio(elem);
                            break;
                        case 2:
                            elem = criarElemento();
                            lista.InserirNoFinal(elem);
                            break;
                        case 3:
                            try {
                                elem = lista.RemoverPrimeiro();
                                cout << "Removido: ";
                                elem->imprimirInfo();
                                delete elem;
                            } catch (exception& e) {
                                cout << e.what() << endl;
                            }
                            break;
                        case 4:
                            try {
                                elem = lista.RemoverUltimo();
                                cout << "Removido: ";
                                elem->imprimirInfo();
                                delete elem;
                            } catch (exception& e) {
                                cout << e.what() << endl;
                            }
                            break;
                        case 5:
                            cout << "ID para remover: ";
                            cin >> id;
                            elem = lista.RemoverPeloId(id);
                            if (elem) {
                                cout << "Removido: ";
                                elem->imprimirInfo();
                                delete elem;
                            } else {
                                cout << "ID não encontrado!" << endl;
                            }
                            break;
                        case 6:
                            cout << "ID para buscar: ";
                            cin >> id;
                            elem = lista.BuscarPeloId(id);
                            if (elem) {
                                elem->imprimirInfo();
                            } else {
                                cout << "ID não encontrado!" << endl;
                            }
                            break;
                        case 7:
                            cout << "ID para alterar: ";
                            cin >> id;
                            elem = criarElemento();
                            if (lista.AlterarPeloId(id, elem)) {
                                cout << "Elemento alterado com sucesso!" << endl;
                            } else {
                                cout << "ID não encontrado!" << endl;
                                delete elem;
                            }
                            break;
                        case 8:
                            lista.imprimirTodos();
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                }
                break;
            }
            case 2: {
                // Menu Pilha
                while (true) {
                    cout << "\n===== PILHA =====" << endl;
                    cout << "1. Empilhar" << endl;
                    cout << "2. Desempilhar" << endl;
                    cout << "3. Consultar topo" << endl;
                    cout << "4. Verificar se está vazia" << endl;
                    cout << "5. Imprimir pilha" << endl;
                    cout << "0. Voltar" << endl;
                    cout << "Escolha uma opção: ";
                    
                    int op;
                    cin >> op;
                    if (op == 0) break;
                    
                    Elemento* elem;
                    
                    switch (op) {
                        case 1:
                            elem = criarElemento();
                            pilha.empilhar(elem);
                            break;
                        case 2:
                            if (pilha.pilhaVazia()) {
                                cout << "Pilha vazia!" << endl;
                            } else {
                                elem = pilha.desempilhar();
                                cout << "Desempilhado: ";
                                elem->imprimirInfo();
                                delete elem;
                            }
                            break;
                        case 3:
                            elem = pilha.consultarTopo();
                            if (elem) {
                                cout << "Topo: ";
                                elem->imprimirInfo();
                            } else {
                                cout << "Pilha vazia!" << endl;
                            }
                            break;
                        case 4:
                            cout << (pilha.pilhaVazia() ? "Pilha vazia!" : "Pilha não vazia!") << endl;
                            break;
                        case 5:
                            pilha.imprimirPilha();
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                }
                break;
            }
            case 3: {
                // Menu Fila
                while (true) {
                    cout << "\n===== FILA =====" << endl;
                    cout << "1. Enfileirar" << endl;
                    cout << "2. Desenfileirar" << endl;
                    cout << "3. Verificar se está vazia" << endl;
                    cout << "4. Imprimir fila" << endl;
                    cout << "0. Voltar" << endl;
                    cout << "Escolha uma opção: ";
                    
                    int op;
                    cin >> op;
                    if (op == 0) break;
                    
                    Elemento* elem;
                    
                    switch (op) {
                        case 1:
                            elem = criarElemento();
                            fila.enfileirar(elem);
                            break;
                        case 2:
                            if (fila.filaVazia()) {
                                cout << "Fila vazia!" << endl;
                            } else {
                                elem = fila.desenfileirar();
                                cout << "Desenfileirado: ";
                                elem->imprimirInfo();
                                delete elem;
                            }
                            break;
                        case 3:
                            cout << (fila.filaVazia() ? "Fila vazia!" : "Fila não vazia!") << endl;
                            break;
                        case 4:
                            fila.imprimirFila();
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                }
                break;
            }
            case 4: {
                // Menu Lista Simplesmente Encadeada
                while (true) {
                    cout << "\n===== LISTA SIMPLESMENTE ENCADEADA =====" << endl;
                    cout << "1. Inserir no início" << endl;
                    cout << "2. Inserir no final" << endl;
                    cout << "3. Remover por ID" << endl;
                    cout << "4. Buscar por ID" << endl;
                    cout << "5. Imprimir lista" << endl;
                    cout << "0. Voltar" << endl;
                    cout << "Escolha uma opção: ";
                    
                    int op;
                    cin >> op;
                    if (op == 0) break;
                    
                    int id;
                    Elemento* elem;
                    
                    switch (op) {
                        case 1:
                            elem = criarElemento();
                            listaEncadeada.inserirNoInicio(elem);
                            break;
                        case 2:
                            elem = criarElemento();
                            listaEncadeada.inserirNoFim(elem);
                            break;
                        case 3:
                            cout << "ID para remover: ";
                            cin >> id;
                            elem = listaEncadeada.removerPeloId(id);
                            if (elem) {
                                cout << "Removido: ";
                                elem->imprimirInfo();
                                delete elem;
                            } else {
                                cout << "ID não encontrado!" << endl;
                            }
                            break;
                        case 4:
                            cout << "ID para buscar: ";
                            cin >> id;
                            elem = listaEncadeada.buscarPeloId(id);
                            if (elem) {
                                elem->imprimirInfo();
                            } else {
                                cout << "ID não encontrado!" << endl;
                            }
                            break;
                        case 5:
                            listaEncadeada.imprimirLista();
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                }
                break;
            }
            case 5: {
                // Menu Árvore Binária de Busca
                while (true) {
                    cout << "\n===== ÁRVORE BINÁRIA DE BUSCA =====" << endl;
                    cout << "1. Inserir" << endl;
                    cout << "2. Remover por ID" << endl;
                    cout << "3. Buscar por ID" << endl;
                    cout << "4. Percorrer em ordem" << endl;
                    cout << "5. Percorrer pré-ordem" << endl;
                    cout << "6. Percorrer pós-ordem" << endl;
                    cout << "0. Voltar" << endl;
                    cout << "Escolha uma opção: ";
                    
                    int op;
                    cin >> op;
                    if (op == 0) break;
                    
                    int id;
                    Elemento* elem;
                    
                    switch (op) {
                        case 1:
                            elem = criarElemento();
                            arvore.inserir(elem);
                            break;
                        case 2:
                            cout << "ID para remover: ";
                            cin >> id;
                            arvore.removerPeloId(id);
                            cout << "Elemento removido (se existia)" << endl;
                            break;
                        case 3:
                            cout << "ID para buscar: ";
                            cin >> id;
                            elem = arvore.buscarPeloId(id);
                            if (elem) {
                                elem->imprimirInfo();
                            } else {
                                cout << "ID não encontrado!" << endl;
                            }
                            break;
                        case 4:
                            arvore.emOrdem();
                            break;
                        case 5:
                            arvore.preOrdem();
                            break;
                        case 6:
                            arvore.posOrdem();
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                }
                break;
            }
            default:
                cout << "Opção inválida!" << endl;
        }
    }
}

int main() {
    menuPrincipal();
    return 0;
}