all: vm
	gcc -o vm vm.c
	
clean:
	rm -rf *o vm 
