#ifndef _POLY_H_
#define _POLY_H_
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//criar
//D = Num+1;
//a = new double[D];

class Poly{
private:
    ///dimensão do polinomio
    unsigned int D;
    ///array de coeficientes
    double* a;
    ///copia polinomio
    void copy(const Poly& p);//ok
    void create(unsigned n);//ok
    void reduce();//ok

public:
    ///Construtores
    inline Poly(): D(0), a(nullptr){} //ok
    inline Poly(const Poly& p) {copy(p);}//ok

    explicit Poly(unsigned n);//ok

    ///Destrutor
    inline ~Poly() {clear();}//ok

    ///Desaloca memoria e torna D = 0
    void clear();//ok

    ///recriar
    void recriar(unsigned n);//ok

    ///define valores de coeficintes de um polinomio
    void setCoef(unsigned i, double v);//ok

    ///Salvar polinômio em arquivo
    bool salvar(const string path) const;//ok

    ///Ler polinômio de arquivo
    bool ler(const string path);//ok

    ///funções de interface
    inline int getGrau() const {return int(D)-1;}//ok
    inline bool isZero()const {return D==1 && a[0]==0.0;}//ok
    inline bool empty() const {return D==0;}//ok
    inline double getCoef(unsigned i) const {return (i>=D ? 0.0 : a[i]);}//ok
    double getValor(double v) const;//ok

    ///sobrecarga de operadores
    void operator=(const Poly& p);//ok
    inline double operator[](unsigned i) const{return getCoef(i);}//ok
    inline double operator()(double v) const {return getValor(v);}//ok
    friend ostream &operator<<(ostream& o, const Poly& P);//ok
    friend istream &operator>>(istream& in, Poly& p);//ok
    const Poly operator+(const Poly& P) const;//ok
    const Poly operator-(const Poly& P) const;//ok
    const Poly operator-()const;//ok
    const Poly operator*(const Poly& P) const;//ok



};
#endif
