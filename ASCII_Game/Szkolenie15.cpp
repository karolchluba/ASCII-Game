// Rodzazje wzorc�w projektowych:
// kreacyjne, strukturalne, czynno�ciowe

// do wzorca kreacyjnego zaliczamy:
// singleton, factory method, builder
// strukturalne:
// adapter, fasada
// czynno�ciowe:
// strategia, dj - dependency injection


// SINGLETON:
// - zapewnia istnienie tylko i wy��cznie jednej instancji danej klasy
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

