VPATH = src
CODE := calcSum pickMax bubleSort factorial generatePermutation
all: $(CODE)
%:%.o
	gcc $< -o $@
%.o:%.c
	gcc -c $< -o $@
.PHONY: clean
clean:
	rm -f *.o