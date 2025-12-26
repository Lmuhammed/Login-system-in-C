# Makefile

program: main.c 
	gcc -o "LoginSystem"  main.c 

clean:
	rm -f  LoginSystem login

