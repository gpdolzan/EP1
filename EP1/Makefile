CFLAGS = -Wall -g  # gerar "warnings" detalhados e infos de depuração
LDLIBS = -lm       # ligar com a biblioteca matemática

objs = analise.o floatManager.o

# regra default (primeira regra)
all: analise

# regras de ligacao
analise: $(objs)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# regras de compilação
analise.o: analise.c floatManager.h
	$(CC) $(CFLAGS) -c -o $@ $<

floatManager.o: floatManager.c floatManager.h
	$(CC) $(CFLAGS) -c -o $@ $<

# remove arquivos temporários
clean:
	-rm -f $(objs) *~

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f analise
