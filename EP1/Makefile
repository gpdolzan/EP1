CFLAGS = -Wall -g  # gerar "warnings" detalhados e infos de depuração
LDLIBS = -lm       # ligar com a biblioteca matemática

objs = main.o floatManager.o

# regra default (primeira regra)
all: analise

# regras de ligacao
analise: $(objs)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# regras de compilação
main: analise.c FloatType.h
	$(CC) $(CFLAGS) -c -o $@ $<

FloatType.o: FloatType.c FloatType.h
	$(CC) $(CFLAGS) -c -o $@ $<

# remove arquivos temporários
clean:
	-rm -f $(objs) *~

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f analise
