# INF610 - Trabalho Prático 2

Trabalho Prático 2 da disciplina INF610 - Estruturas de Dados e Algoritmos, no programa de mestrado em Ciência da Computação pela Universidade Federal de Viçosa.

## Compilação

Tendo o `make` e o `g++` instalado, basta executar o comando `make`.

## Uso

```bash
$ ./bin/inf610-tp2 (one|multi) (euler|hamilton) (IncMatrix|AdjMatrix|AdjList) <input-fp> [<output-fp>]
```

- `one` ou `multi` indica o modo de execução: `one` executa o problema em apenas um grafo, `multi` executa o problem em todos os grafos. No modo `one`, os resultados são impressos na saída padrão. No modo `multi`, os resultados resumidos são impressos em arquivo.
- `euler` ou `hamilton` indica qual dos problemas deve ser testado.
- `IncMatrix`, `AdjMatrix` ou `AdjList` indica qual representação de grafo deve ser usada.
- `<input-fp>` indica o arquivo de entrada com a lista de grafos.
- `<output-fp>` é opcional, sendo necessário apenas quando o modo é `multi`, indica em qual arquivo devem ser escritos os resultados.

O formato de entrada para os arquivos de teste deve seguir o seguinte padrão. Deve conter pelo menos uma repetição de um conjunto de linhas contendo em cada uma dois números inteiros. A primeira linha indica respectivamente quantos vértices e quantas arestas. As linhas seguintes, sendo uma para cada aresta, indica sobre quais vértices aquela aresta incide. A numeração dos vértices é 0-indexada.