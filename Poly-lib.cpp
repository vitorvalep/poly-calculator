#include "Poly.h"


Poly::Poly(unsigned n)
{
    D = n + 1;
    a = new double[D];
    for(unsigned int i = 0; i < n ; i++)
        a[i] = 0.0;
    a[n] = 1.0;
    /*for(unsigned int i = 0; i < D ; i++)
    {
        //só para testes.
        cout<<a[i]<<endl;
    }*/

}

void Poly::create(unsigned n)
{
    D = n + 1;
    a = new double[D];
    for(unsigned int i = 0; i < D ; i++)
        a[i] = 0.0;
    a[n] = 1.0;
}

void Poly::recriar(unsigned n)
{
    clear();
    create(n);
}

void Poly::operator=(const Poly& p)
{
    if(this != &p)
    {
        if(D == p.D)
            for(unsigned int i=0; i<D; i++)
                a[i] = p.a[i];
        else
        {
            clear();
            copy(p);
        }
    }
}

ostream &operator<<(ostream& o, const Poly& p)
{
    if(p.empty())
        o<<' ';
    else
    {
        for(int i=p.getGrau(); i>=0; i--)
        {
            if(p.getGrau()==0 && i==0)
                o<<p.a[i];
            else
            {
                if(i>0)
                {
                    if(p.a[i]!=0.0)
                    {
                        if(p.a[i]<0.0 )
                            o<<'-';
                        else if(i!=p.getGrau())
                            o<<'+';
                        if(fabs(p.a[i])!=1.0)
                            o<<fabs(p.a[i])<<'*';

                        o<<'x';
                        if(i>1)
                            o<<'^'<<i;
                    }
                }
                else if(fabs(p.a[i])!=0.0)
                    p.a[i]<0.0 ? o<<'-'<<fabs(p.a[i]):o<<'+'<<fabs(p.a[i]);
            }
        }
    }
    return o;
}

istream &operator>>(istream& in, Poly& p)
{
    double temp;
    if(p.empty())
        cout<<"Erro: Polinômio vazio."<<endl;
    for(int i = p.getGrau(); i>=0; i--)
    {
        if(p.D == 1)
        {
            cout<<"x^"<<i<<":";
            in >> temp;
        }
        else
        {
            if(i == p.getGrau())
            {
                do
                {
                    cout<<"x^"<<i<<":";
                    in >> temp;
                    if(i==p.getGrau() && temp==0.0)
                    {
                        cout<<"Erro: Coeficiente nulo."<<endl;

                    }
                }
                while(temp == 0.0);
            }
            else
            {
                cout<<"x^"<<i<<":";
                in >> temp;
            }
        }
        p.a[i] = temp;

    }

    return in;
}

bool Poly::salvar(const string path) const
{
    bool temp = true;
    ofstream stream_out(path.c_str());

    if (!stream_out.is_open())
        temp = false;

    stream_out << "POLY "<< D << endl;

    for(unsigned i=0; i<D; i++)
        stream_out<<a[i]<<" ";

    stream_out.close();
    return temp;
}

bool Poly::ler(const string path)
{
    ifstream stream_in(path.c_str());
    if (!stream_in.is_open())
        return false;

    string header;
    int D_temp;
    stream_in >> header;

    if (!stream_in.good()|| header!= "POLY")
        return false;

    stream_in >> D_temp;
    if (!stream_in.good() || D_temp<0)
        return false;

    recriar (D_temp - 1);

    for (int i = 0; i<=getGrau(); i++)
        stream_in >> a[i];

    stream_in.close();
    return true;
}

double Poly::getValor(double v) const
{
    double r = 0.0;
    if(empty())
        return 0.0;
    else
    {
        for(unsigned i=0; i<D; i++)
            r += pow(v,i)*a[i];
        return r;
    }
}

void Poly::setCoef(unsigned i, double v)
{
    if((i>=D || (int(i)==getGrau() && v==0.0)) && (getGrau() != 0))
    {
        if(i>=D)
            cerr<<"ERRO: Indice invalido"<<endl;
        else
            cerr<<"ERRO: "<<endl;
    }
    else
        a[i] = v;
}

const Poly Poly::operator+(const Poly& p) const
{
    if(empty() || isZero()) return p;
    if(p.empty() || p.isZero()) return *this;

    Poly temp(max(getGrau(), p.getGrau()));

    for(unsigned i=0; i<temp.D; i++)
        temp.a[i] = getCoef(i) + p.getCoef(i);

    temp.reduce();
    return temp;
}
const Poly Poly::operator-(const Poly& p) const
{
    if(empty() || isZero()) return p;
    if(p.empty() || p.isZero()) return *this;

    Poly temp(max(getGrau(), p.getGrau()));
    for(unsigned i=0; i<temp.D; i++)
        temp.a[i] = getCoef(i) - p.getCoef(i);

    temp.reduce();
    return temp;
}
const Poly Poly::operator-() const
{
    if(empty()) return *this;
    if(isZero()) return *this;

    Poly temp(getGrau());
    for (unsigned i=0; i<D; i++) temp.a[i] = -a[i];
    return temp;
}

const Poly Poly::operator*(const Poly& p) const
{
    if(empty())
        return *this;
    if(p.empty())
        return p;
    if(isZero() && (!p.isZero()))
        return *this;
    if(!isZero() &&(p.isZero()))
        return p;

    Poly temp(getGrau()+ p.getGrau());
    for(int i=D; i>=0; i--)
    {
        for(int j=p.D; j>=0; j--)
        {
            if(getCoef(i)!=0.0 && p.getCoef(j)!=0.0)
            {
                temp.a[i+j] += a[i]*p.a[j];
            }
        }
    }
    temp.reduce();
    temp.a[temp.getGrau()] = temp.a[temp.getGrau()] - 1 ;
    return temp;
}

void Poly::copy(const Poly& p)
{
    create(p.D - 1);
    for(unsigned int i=0; i<D; i++)
        a[i] = p.a[i];
}

void Poly::clear()
{
    if(a!=nullptr)
    {
        delete[] a;
        a = nullptr;
        D = 0;
    }
}

void Poly::reduce()
{
    unsigned n = getGrau();
    unsigned D_temp = D;
    while(a[n] == 0.0)
    {
        D_temp--;
        n--;
        double* temp = new double[D_temp];

        for (unsigned j=0; j<D_temp; j++)
            temp[j] = a[j];

        clear();
        a = temp;
        D = D_temp;
    }
}
