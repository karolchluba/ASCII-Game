// Rodzazje wzorców projektowych:
// kreacyjne, strukturalne, czynnościowe

// do wzorca kreacyjnego zaliczamy:
// singleton, factory method, builder
// strukturalne:
// adapter, fasada
// czynnościowe:
// strategia, dj - dependency injection


// SINGLETON:
// - zapewnia istnienie tylko i wyłącznie jednej instancji danej klasy
#include <iostream>
using namespace std;

class Singleton {
private:
    //const static int liczbaKol = 4;
    static Singleton* instancja;
    Singleton() {}

public:
    static Singleton* getInstancja() {
        if (instancja == NULL) {
            instancja = new Singleton();
        }

        return instancja;
    }
};

Singleton* Singleton::instancja = NULL;

int main() {
    Singleton* s = Singleton::getInstancja(); // Ok
    Singleton* r = Singleton::getInstancja();

    cout << s << r;


    //cout << Singleton::liczbaKol;
}

