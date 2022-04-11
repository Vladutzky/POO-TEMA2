
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Complex {
    double parte_reala, parte_imaginara;
    friend class Matrice_Complexa;

public:
    double GetParteReala() const {
        return parte_reala;
    }

    double GetParteImaginara() const {
        return parte_imaginara;
    }

    void SetParteImaginara(float x){
         parte_imaginara=x;
    }

    void SetParteReala(float x) {
         parte_reala=x;
    }

    void Afisare(ostream &out) {
        Complex c;
        if (parte_reala == 0 && parte_imaginara == 0)
            cout << 0;
        else {
            if (parte_reala != 0)
                cout << parte_reala;
            if (parte_imaginara > 0) {
                if (parte_reala != 0)
                    cout << "+" << parte_imaginara << "*i";
                else cout << parte_imaginara << "*i";
            } else if (parte_imaginara < 0)
                cout << parte_imaginara << "*i";
        }
    }

    // - constructor fara param. - ni l da compilatorul daca nu il dam noi(doara daca nu avem definit alt constructor)
    Complex() {
        parte_reala = parte_imaginara = 0;
    }

    Complex(double d, double s) : parte_reala(d), parte_imaginara(s) {}          // - constructor cu param.

    Complex(Complex &c) :                                                        // - constructor de copiere
            parte_reala(c.parte_reala),
            parte_imaginara(c.parte_imaginara) {}

    ~Complex() {} // - destructor (~)


    
    friend ostream &operator<<(ostream &out, Complex &nr){
        nr.Afisare(out);
        return out;
    }

    friend istream &operator>>(istream &in, Complex &nr) {
        cout << "parte reala: ";
        in >> nr.parte_reala;
        cout << "parte imaginara: ";
        in >> nr.parte_imaginara;
        return in;
    }

    Complex &operator+(const Complex &nr) {
        Complex *suma = new Complex;
        suma->parte_reala = parte_reala + nr.parte_reala;
        suma->parte_imaginara = parte_imaginara + nr.parte_imaginara;
        return *suma;
    }
     Complex &operator-(const Complex &nr)
    {
        Complex *dif = new Complex;
        dif->parte_reala = parte_reala - nr.parte_reala;
        dif->parte_imaginara = parte_imaginara - nr.parte_imaginara;
        return *dif;
    }

    Complex &operator*(const Complex &nr) {
        Complex *produs = new Complex;
        produs->parte_reala = parte_reala * nr.parte_reala - parte_imaginara * nr.parte_imaginara;
        produs->parte_imaginara = parte_reala * nr.parte_imaginara + parte_imaginara * nr.parte_reala;
        return *produs;
    }

    Complex& operator=(const Complex& c) {
        parte_reala = c.parte_reala;
        parte_imaginara = c.parte_imaginara;
        return *this;
    }

};


class Matrice{
    protected:
     static int aparitii_matrice_oarecare,aparitii_matrice_patratica; 
     Complex **v;
     public:
     
   
     void aparitii_patratica()
    {
        aparitii_matrice_patratica++;
    }
    
     void aparitii_oarecare()
    {
        aparitii_matrice_oarecare++;
    }

     void reset_patratica()
     {
         aparitii_matrice_patratica=0;
     }
     void reset_oarecare()
     {
         aparitii_matrice_oarecare=0;
     }

    static void afisare_aparitii_patratica()
    {
        cout<<aparitii_matrice_patratica;
    }
     static void afisare_aparitii_oarecare()
    {
        cout<<aparitii_matrice_oarecare;
    }

    Matrice(int a=0, int b=0) {
      
        this->v=new Complex*[a];
        
        for (int i = 0; i < a; i++) {
            
            this->v[i] = new Complex[b];
        }
        
        
    }


    Matrice(int a,int b, Complex x)
       {   
           this->v=new Complex*[a];
           for(int i=0;i<a;i++)
            {
                this->v[i]=new Complex[b];
                for (int j = 0; j < b; j++)
                     this->v[i][j] = x;
            }
 
       }

     Matrice(Matrice &M,int a,int b) {
        
        this->v = new Complex *[a];

        for (int i = 0; i < a; i++) {
            this->v[i] = new Complex[b];
            for (int j = 0; j < b; j++)
                this->v[i][j] = M.v[i][j];
        }
    }

    virtual ~Matrice()
    {
        
        delete v;
    }




    Complex **get_v()
    {
        return v;
    }
    void get_vivid()
    {
        cout<<v[2][1];
    }
    virtual void afisare() {}
    virtual void determinant_main() {}
    virtual void diagonala() {}
   
};


class Matrice_oarecare: public Matrice{
    
    protected:
   
    int lin,col;
    
    public:
    
    
     Matrice_oarecare(int lin1, int col1):Matrice(lin1,col1)
    {     
        lin=lin1;
        col=col1;
        // Complex x;
        // cin>>x;
        this->v=new Complex *[lin];
        for (int i = 0; i < lin; i++) 
        {   
            this->v[i] = new Complex[col];
        } 
       
            }

    Matrice_oarecare(int a,int b, Complex x):Matrice(a,b,x)
       {   this->lin=a;
           this->col=b;
           this->v=new Complex*[a];
           for(int i=0;i<a;i++)
            {
                this->v[i]=new Complex[b];
                for (int j = 0; j < b; j++)
                     this->v[i][j] = x;
            }
           
       }
    

   
    Matrice_oarecare(Matrice_oarecare &M):Matrice(M)
    {
        this->lin=M.lin;
        this->col=M.col;
        this->v = new Complex *[lin];

        for (int i = 0; i < lin; i++) {
            this->v[i] = new Complex[col];
            for (int j = 0; j < col; j++)
                this->v[i][j] = M.v[i][j];
        }
         for(int i=0;i<lin;i++)
           {for(int j=0;j<col;j++)
             cout<<v[i][j]<<" ";
            cout<<endl;} 
    }
       ~Matrice_oarecare()
    {
        for(int i=0; i<lin; i++)
            delete[]v[i];
        delete v;
    }


    
    static void SumaElemente(Matrice_oarecare &M);  //antet metoda statica
    Complex *&operator[](int &index) {
        return v[index];
    }

    Matrice_oarecare &operator=(Matrice_oarecare const &M) {
        lin = M.lin;
        col = M.col;
        v = new Complex *[lin];
        for (int i = 0; i < lin; i++)
           {
           v[i] = new Complex [col];
            for (int j = 0; j < col; j++)
                v[i][j] = M.v[i][j];
           }
 
        return *this;
    }

    void afisare(){

        for (int i=0; i<lin; i++)
        {
            for (int j=0; j<col; j++)
                cout<<v[i][j]<<" ";
            cout<<endl;
        }
    }
    friend ostream &operator<<(ostream &out, Matrice_oarecare &M) {
        for (int i = 0; i < M.lin; i++) {
            for (int j = 0; j < M.col; j++)
                out << M[i][j] << " ";
            out << '\n';
        }
        return out;
    }

    friend istream &operator>>(istream &in, Matrice_oarecare &M) {

        cout << "Intoruduceti " << M.lin * M.col << " elemente:\n";
        for (int i = 0; i < M.lin; i++) {
            for (int j = 0; j < M.col; j++) {
                cout << "elementul de pe pozitia " << i + 1 << "," << j + 1 << "\n";
                in >> M[i][j];
            }
        }
        return in;
    }

      void diagonala()
    {
         int contor_diag=0;

         for(int i=0;i<lin;i++)
             for(int j=0;j<col;j++)
                if(i!=j)
                  if(v[i][j].GetParteImaginara()||v[i][j].GetParteReala())
                   contor_diag++;
        if(contor_diag)
          cout<<"Matricea nu este diagonala"<<endl;
          else cout<<"Matricea este diagonala"<<endl;

    }
     
};


class Matrice_patratica: public Matrice{
    protected:
    int dim;
    
    public:
     
     Matrice_patratica(int dim):Matrice(dim,dim)
    {     
        this->dim=dim;
        // Complex x;
        // cin>>x;
        this->v=new Complex *[dim];
        for (int i = 0; i < dim; i++) 
        {   
            this->v[i] = new Complex[dim];
        } 
           
        
            }

    Matrice_patratica(int dim, Complex x):Matrice( dim, dim, x)
       {   this->dim=dim;
           this->v=new Complex*[dim];
           for(int i=0;i<dim;i++)
            {
                this->v[i]=new Complex[dim];
                for (int j = 0; j < dim; j++)
                     this->v[i][j] = x;
            }
          
       }

   
    Matrice_patratica(Matrice_patratica &M):Matrice(M) {
        this->dim=M.dim;
        this->v = new Complex *[dim];

        for (int i = 0; i < dim; i++) {
            this->v[i] = new Complex[dim];
            for (int j = 0; j < dim; j++)
                this->v[i][j] = M.v[i][j];
        }
         for(int i=0;i<dim;i++)
           {for(int j=0;j<dim;j++)
             cout<<v[i][j]<<" ";
            cout<<endl;} 
    }

     ~Matrice_patratica()
    {
        for(int i=0; i<dim; i++)
            delete[]v[i];
        delete v;
    }
    
    Complex *&operator[](int &index) {
        return v[index];
    }
      void diagonala()
    {
         int contor_diag=0;

         for(int i=0;i<dim;i++)
             for(int j=0;j<dim;j++)
                if(i!=j)
                  if(v[i][j].GetParteImaginara()||v[i][j].GetParteReala())
                   contor_diag++;
        if(contor_diag)
          cout<<"Matricea nu este diagonala"<<endl;
          else cout<<"Matricea este diagonala"<<endl;

    }

    Matrice_patratica &operator=(Matrice_patratica const &M) {
        dim = M.dim;
        v = new Complex *[dim];
        for (int i = 0; i < dim; i++){

            
            for (int j = 0; j < dim; j++)
                this->v[i][j] = M.v[i][j];
        }

        return *this;
    }


    friend ostream &operator<<(ostream &out, Matrice_patratica &M) {
        for (int i = 0; i < M.dim; i++) {
            for (int j = 0; j < M.dim; j++)
                out << M[i][j] << " ";
            out << '\n';
        }
        
    Complex det;
    det = M.determinant(M,M.dim);
    cout<< "Determinantul matricei patratice este ";
    cout << det << endl;

        return out;
    }

    friend istream &operator>>(istream &in, Matrice_patratica &M) {

        cout << "Intoruduceti " << M.dim * M.dim << " elemente:\n";
        for (int i = 0; i < M.dim; i++) {
            for (int j = 0; j < M.dim; j++) {
                cout << "elementul de pe pozitia " << i + 1 << "," << j + 1 << "\n";
                in >> M[i][j];
            }
        }
        return in;
    } 
    void afisare(){
   
    int n=dim;
    Complex det;
    Matrice_patratica M = *this;
    det = M.determinant(M,n);
    cout<< "Determinantul matricei patratice este ";
    cout << det << endl;


    }
    void determinant_main()
    {
        int n=dim;
        Complex det;
       Matrice_patratica M = *this;
       det = M.determinant(M,n);
       cout<< "Determinantul matricei patratice este ";
       cout << det << endl;

    }
    Complex determinant(Matrice_patratica &M, int n)
    {
        Complex det;
        det.SetParteReala(0);
        det.SetParteImaginara(0);
        Matrice_patratica submatrix(n);
        if (n == 1)
            return M.v[0][0];
        if (n == 2)
            return (M.v[0][0] * M.v[1][1]) - (M.v[1][0] * M.v[0][1]);

        else
        {
            for (int x = 0; x < n; x++)
            {
                int subi = 0;
                for (int i = 1; i < n; i++)
                {
                    int subj = 0;
                    for (int j = 0; j < n; j++)
                    {
                        if (j == x)
                            continue;
                        submatrix.v[subi][subj] = M.v[i][j];
                        subj++;
                    }
                    subi++;
                }
                Complex a(pow(-1, x), 0);
                det = det + (a * M.v[0][x] * determinant(submatrix, n - 1));
            }
        }
        return det;
    }


};

void Print(Matrice *M)
{
    M -> afisare();
    cout<<endl;
}
void dety(Matrice *M)
{
    M->determinant_main();

}
void diag(Matrice *M)
{
    M -> diagonala();
    cout<<endl;
}
int Matrice::aparitii_matrice_oarecare;
int Matrice::aparitii_matrice_patratica;
int main()
{
    
    int a,b,k;
     int n;


    int optiune=0;
    while(optiune!=11)
    {   cout<<"------MATRICI COMPLEXE------"<<endl<<endl;
        cout<<"1.Initializare matrice oarecare"<<endl;
        cout<<"2.Initializare matrice patratica"<<endl;
        cout<<"3.Initializare matrice oarecare cu o variabila"<<endl;
        cout<<"4.Initializare matrice patratica cu o variabila"<<endl;
        cout<<"5.Citire matrice oarecare"<<endl;
        cout<<"6.Citire matrice patratica"<<endl;
        cout<<"7.Verificare daca o matrice oarecare este diagonala"<<endl;
        cout<<"8.Verificare daca o matrice patratica este diagonala"<<endl;
        cout<<"9.Afisare determinant matrice patratica"<<endl;
        cout<<"10.Citire n matrici de oricare fel"<<endl;
        cout<<"11.Iesiti din program"<<endl;
        cout<<"Alegeti optiunea: ";
        cin >> optiune;
        if(optiune==1)
        { 
            int linii1,coloane1;
            cout<<"introduceti numarul de linii:";
            cin>>linii1;
            cout<<"introduceti numarul de coloane:";
            cin>>coloane1;
            Matrice_oarecare OP1(linii1,coloane1);
            cout<<"Matricea dumneavoastra este: "<<endl<<OP1;

        }
        else if(optiune==2)
        {
            int dim1;
            cout<<"introduceti dimensiunea matricei:";
            cin>>dim1;
            Matrice_patratica OP2(dim1);
            cout<<"Matricea dumneavoastra este: "<<endl<<OP2;
        }
        else if(optiune==3)
        {
            Complex variabila_3;
            cout<<"Introduceti variabila:"<<endl;
            cin>>variabila_3;
            int linii3,coloane3;
            cout<<"introduceti numarul de linii:";
            cin>>linii3;
            cout<<"introduceti numarul de coloane:";
            cin>>coloane3;
            Matrice_oarecare OP3(linii3,coloane3,variabila_3);
            cout<<"Matricea dumneavoastra este: "<<endl<<OP3;
        }
        else if(optiune==4)
        {
            Complex variabila_4;
            cout<<"Introduceti variabila:"<<endl;
            cin>>variabila_4;  
            int dim4;
            cout<<"introduceti dimensiunea matricei:";
            cin>>dim4;
            Matrice_patratica OP4(dim4,variabila_4);
            cout<<"Matricea dumneavoastra este: "<<endl<<OP4; 
        }
        else if(optiune==5)
        {   int linii5,coloane5;
            cout<<"introduceti numarul de linii:";
            cin>>linii5;
            cout<<"introduceti numarul de coloane:";
            cin>>coloane5;
            Matrice_oarecare OP5(linii5,coloane5);
            cin>>OP5;
            cout<<"Matricea dumneavoastra este: "<<endl<<OP5;
            
        }
        else if(optiune==6)
        {
            int dim6;
            cout<<"introduceti dimensiunea matricei:";
            cin>>dim6;
            Matrice_patratica OP6(dim6);
            cin>>OP6;
            cout<<"Matricea dumneavoastra este: "<<endl<<OP6;
            
        }
        else if(optiune==7)
        { 
           int linii7,coloane7;
            cout<<"introduceti numarul de linii:";
            cin>>linii7;
            cout<<"introduceti numarul de coloane:";
            cin>>coloane7;
            Matrice_oarecare OP7(linii7,coloane7);
            cin>>OP7;
            OP7.diagonala();
            
        }
        else if(optiune==8)
        {
             int dim8;
            cout<<"introduceti dimensiunea matricei:";
            cin>>dim8;
            Matrice_patratica OP8(dim8);
            cin>>OP8;
            OP8.diagonala();
        }
        else if(optiune==9)
        {
            int dim9;
            cout<<"introduceti dimensiunea matricei:";
            cin>>dim9;
            Matrice_patratica OP9(dim9);
            cin>>OP9;
            Complex det;
            det = OP9.determinant(OP9,dim9);
            cout<< "Determinantul matricei patratice este ";
            cout << det << endl;
           
        }
        else if(optiune==10)
        {   vector<Matrice*> Matrice_diverse;
             Matrice R;
             R.reset_oarecare();
             R.reset_patratica();
            cout<<"Cate elemente doriti sa introduceti?: ";
            cin>>n;
        for(int i=0;i<n;++i)
        {   
        int optiune;
        Matrice LVP;
        cout<<"Oarecare sau patratica(1/2): ";
        cin>>optiune;
        if(optiune==1){
            LVP.aparitii_oarecare();
            cout<<"Introduceti numarul de linii:";
            cin>>a;
            cout<<"Introduceti numarul de coloane:";
            cin>>b;
            Matrice_oarecare *s=new Matrice_oarecare(a,b);
            cin>>*s;
            Matrice_diverse.push_back(s);
            cout<<*s;
        }
        else {
            
            LVP.aparitii_patratica();
            cout<<"Introduceti dimensiunea:";
            cin>>a;
            Matrice_patratica *s=new Matrice_patratica(a);
            cin>>*s;
            Matrice_diverse.push_back(s);
            cout<< *s;
        }
        
        }
        int optiune_n=0;
        while(optiune_n!=6)
        {
            cout<<"1.Afiseaza o matrice cu un index dat"<<endl;
            cout<<"2.Afiseaza cate matrici oarecare sunt"<<endl;
            cout<<"3.Afiseaza cate matrici patratice sunt"<<endl;
            cout<<"4.Afiseaza determinantul unei matrice cu index dat."<<endl;
            cout<<"5.Afiseaza daca o matrice cu un index dat este diagonala"<<endl;
            cout<<"6.Iesiti din subprogram"<<endl;
            cout<<"Alegeti optiunea:";
            cin>>optiune_n;
            if(optiune_n==1)
            {
              int index_1;
              cout<<"indexul este:";
              cin>>index_1;
              cout<<"Matricea dumneavoastra este: "<<endl;
              Print(Matrice_diverse[index_1]);
            }
            else if(optiune_n==2)
            {
               cout<<"Numarul de matrici oarecare este: ";
                 Matrice::afisare_aparitii_oarecare();
               cout<<endl;
        
            }
            else if(optiune_n==3)
            {     
                cout<<"Numarul de matrici patratice este: ";
                Matrice::afisare_aparitii_patratica();    
                cout<<endl;    
            }
            else if(optiune_n==4)
            {
              int index_4;
              cout<<"indexul este:";
              cin>>index_4;
              if(dynamic_cast<Matrice_patratica*>(Matrice_diverse[index_4]))
              dety(Matrice_diverse[index_4]);
              else cout << "Matricea este oarecare" << endl << endl;

            }
            else if(optiune_n==5)
            {
              int index_5;
              cout<<"indexul este:";
              cin>>index_5;
              diag(Matrice_diverse[index_5]);
            }
            


        }
            
        }
        
    }
   
    return 0;
}