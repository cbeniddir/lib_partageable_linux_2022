
#include <iostream>
#include <dlfcn.h>

int main(int argc, char ** argv)
{
	int data1=3;
	int data2=5;

	int valeur;

	int choix = -1;

	while (choix != 1 &&  choix != 2) {
		std::cout << "Quel composant voulez-vous utiliser ? (1/2)" << std::endl;
		std::cin >> choix;
	}
	void* hndl = nullptr;

	if (choix == 1) {
		hndl = dlopen("./libComposant1.so", RTLD_LAZY);
	} else {
		hndl = dlopen("./libComposant2.so", RTLD_LAZY);
	}

	if (!hndl) {
		std::cerr << "dlopen : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	int (*fct) (int, int);

	if (choix == 1) {
		fct = (int (*) (int, int)) dlsym(hndl, "composant1");
	} else {
		fct = (int (*) (int, int)) dlsym(hndl, "composant2");
	}


	if (!fct) {
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Valeur : " <<  fct(data1, data2) << std::endl;

	dlclose(hndl);
	exit(EXIT_SUCCESS);
}
