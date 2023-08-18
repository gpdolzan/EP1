# EP1 - ICC

Essa atividade foi realizada pelos alunos Tulio Padua Dutra (tpd20 - GRR20206155) e Gabriel Pimentel Dolzan (gpd20 - GRR20209948).

## Como compilar

<p>Para compilar esse programa basta utilizar o Makefile que vem junto com os arquivos-fonte. Basta estar no mesmo diretorio que o Makefile e digitar o comando 
``` bash
Make
```
pelo terminal, isso ira gerar um arquivo executavel chamado analise.</p>

<p>Caso queira remover arquivos temporarios, ou seja, arquivos-objeto gerados para a compilacao, basta digitar
```bash
Make clean
```
e estes arquivos serao deletados.</p>

<p>Se quiser remover todos os arquivos gerados pela compilacao, ou seja, arquivos-objeto e o executavel, basta digitar
```bash
Make purge
```
, que estes arquivos serao deletados.</p>

## Como rodar o programa

<p>Caso voce nao tenha compilado o programa, por favor, siga as instrucoes da secao anterior.

Para rodar o programa, basta digitar no terminal
```bash
./analise
```
e o programa ira rodar.</p>

## Como funciona o programa

<p>O programa como descrito na especificacao, le os seguintes dados: x1 o1 x2 o2 x3 o3 x4 o4 x5. Sendo todos os valores x numeros de ponto flutuante e os valores o sendo do tipo char que indicam alguma operacao matematica basica, ou seja, adicao, subtracao, multiplicacao e divisao.</p>

<p>Apos esses valores serem colocados, basta clicar a tecla enter e o programa executara, obtendo como saida os intervalos das operacoes realizadas, juntamente com todos os erros relativos e absolutos, tambem foram calculadas as ULPs.</p>

## OBSERVACOES

<p>Foi adicionado um arquivo "input" para facilitar a execucao do programa, para utiliza-lo basta digitar no terminal
```bash
./analise < input
```
e o programa ira rodar.</p>
