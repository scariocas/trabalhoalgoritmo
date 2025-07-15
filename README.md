# trabalhoalgoritmo
Trabalho de algoritmos - Faculdade

# Principais Decisões de Design
Hierarquia de Classes para Elementos

Implementei uma classe base abstrata Elemento com as classes derivadas Pessoa e Produto para demonstrar polimorfismo e herança. Isso permite adicionar novos tipos de elementos sem modificar as estruturas de dados.

Lista Não Ordenada com Array Dinâmico
Optei por implementar a lista não ordenada usando um array dinâmico com redimensionamento automático (dobrando a capacidade quando necessário). Isso oferece bom desempenho para a maioria das operações, exceto inserções/remoções no início.

Pilha por Composição
Implementei a Pilha usando composição com a classe ListaNaoOrdenada para maximizar o reuso de código. A pilha usa apenas as operações de inserir/remover no final da lista, que são operações O(1) amortizadas.

Fila Circular Eficiente
Implementei a Fila como uma estrutura independente usando um array circular com redimensionamento. Esta abordagem oferece operações O(1) amortizadas para enfileirar e desenfileirar.

Lista Simplesmente Encadeada
Implementei uma lista encadeada tradicional com nós contendo ponteiros para os elementos. Esta implementação é mais eficiente para inserções/remoções no início que a lista baseada em array.

Árvore Binária de Busca Recursiva
Implementei a ABB com métodos recursivos para inserção, busca e remoção. Esta abordagem é mais elegante e fácil de entender para uma estrutura inerentemente recursiva como árvores.

Gerenciamento de Memória
Todas as estruturas são responsáveis por desalocar os elementos que contêm quando são destruídas, prevenindo memory leaks.


# Tabela:
Lista não ordenada: 
-InserirNoInicio, O(n), Requer deslocar todos os elementos.
-InserirNoFinal, O(1) amortizado, redimensionamento ocasional.
-RemoverPrimeiro, O(n), Requer deslocar todos os elementos.
-RemoverUltimo O(1).
-RemoverPolold O(n).
-BuscarPelold O(n).
-AlterarPelold, O(n).
-empilhar, O(1) amortizado, Usa InserirNoFinal da lista.
-desempilhar, O(1), Usa RemoverUltimo da lista.
-consultarTopo O(1), Implementação simplificada.
-enfileirar O(1) amortizado, Redimensionamento ocasional.
-desenfileirar, O(1).

Encadeada:
-inserirNoInicio, O(1)
-inserirNoFim, O(n), Precisa percorrer até o final.
-removerPelold, O(n).
-buscarPelold, O(n).

Árvore Binária:
-inserir, O(h).
-removerPelold, O(h).
-buscarPelold, O(h).
-percursos, O(n), Visita todos os nós.

h=altura da árvore.
