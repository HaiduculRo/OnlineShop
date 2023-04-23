#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <vector>
using namespace std;
class IOInterface{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const= 0;
};
class Produs: public IOInterface {
protected:
    static int contProd;
    const int idProd;
    char *brand; ///{Adidas}
    string model;
    int stoc;
    float pret;
public:
    ///functii
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
    ///constructori
    Produs();
    Produs(char *brand, string model, int stoc, float pret);
    Produs(const Produs&);
    Produs& operator=(const Produs& Obj);
    bool operator ==(const Produs &obj);
    bool operator >(const Produs &obj);
    operator string();
    ///functii friend
    friend ostream& operator <<(ostream&, const Produs& c1);
    friend istream& operator >>(istream&,  Produs& obj);

    friend void afisare2(const Produs &Obj);
    ///getteri
    string getBrand(){return this->brand;}
    string getModel(){return this->model;}
    int getStoc() {return this->stoc;}
    float getPret(){return this->pret;}
    const int getId(){return this->idProd;}
    ///setteri
    void setBrand(char *x){
        if (this->brand != NULL) {
            delete[] this->brand;
            this->brand = NULL;
        }
        this->brand = new char[strlen(x) + 1];
        strcpy(this->brand, x);
    }
    void setModel(string x){this->model = x;}
    void setStoc(int x) {this->stoc = x;}
    void setPret(float x){this->pret = x;}
    ///destructor
    virtual ~Produs(){
        if(this -> brand != NULL){
            delete[] this->brand;
            this->brand = NULL;
        }
    }
};

int Produs::contProd=6500;
///supraincarcare operatori

Produs& Produs::operator=(const Produs &Obj) {
    if(this != &Obj) {
        if (this->brand != NULL) {
            delete[] this->brand;
            this->brand = NULL;
        }
        this->brand = new char[strlen(Obj.brand) + 1]; ///memorie alocata
        strcpy(this->brand, Obj.brand); /// atribuire valoare
        this->model = Obj.model;
        this->stoc = Obj.stoc;
        this->pret = Obj.pret;
    }
    return *this;
}

bool Produs::operator==(const Produs& obj) {
    return strcmp(this->brand,obj.brand)==0 and this->model==obj.model and this->stoc==obj.stoc and this->pret==obj.pret;
}
bool Produs::operator>(const Produs& obj){
    return this->pret > obj.pret;
}
Produs::operator string(){
    return this->model;
}

ostream& Produs::afisare(ostream& os) const{

    os << "id Produs: " << this->idProd<<endl;
    os << "brand: " <<this->brand<<endl;
    os << "model: " <<this->model<<endl;
    os << "Stoc: " << this->stoc <<endl;
    os << "Pret: " << this->pret <<endl;
    return os;
}
/// >> <<
ostream& operator <<(ostream& out, const Produs& c1){
    return c1.afisare(out);
}

istream& operator >>(istream& in,  Produs& obj){
    return obj.citire(in);
}
istream& Produs::citire(istream& in){

    cout << "Afisare informatii relevante: " << endl;

    cout << "Brand: ";
    char aux[100];
    in >> aux;
    if(this->brand != NULL){
        delete[] this->brand;
    }
    this->brand = new char[strlen(aux)+1];
    strcpy(this->brand, aux);

    cout << "Model: ";
    in >> this->model;

    cout << "Stoc: ";
    in >> this->stoc;

    cout << "Pret: ";
    in >> this->pret;

    cout << endl;
    return in;
}
///initializare anonim
///initializare_anonim
Produs::Produs():idProd(contProd++){ ///initializare_anonim
    brand = new char[strlen("Anonim")+1];
    strcpy(brand,"Anonim");
    model = "Anonim";
    stoc = 0;
    pret = 0;
}
Produs::Produs(char *brand, string model, int stoc, float pret) :idProd(contProd++) {
    this->brand = new char[strlen(brand)+1]; ///memorie alocata
    strcpy(this->brand,brand); /// atribuire valoare
    this->model = model;
    this->stoc = stoc;
    this->pret = pret;

}
Produs::Produs(const Produs& Obj):idProd(contProd++) {
    this->brand = new char[strlen(Obj.brand)+1]; ///memorie alocata
    strcpy(this->brand,Obj.brand); /// atribuire valoare
    this->model = Obj.model;
    this->stoc = Obj.stoc;
    this->pret = Obj.pret;
}
class Tricou: virtual public Produs{
protected:
    string color_tricou;
    char gen_tricou;
    string marime;
    string type_tricou;
public:
    Tricou();
    Tricou(char *brand, string model, int stoc, float pret, string color_tricou, char gen_tricou, string marime, string type_tricou);
    Tricou(const Tricou&);
    ///operator
    Tricou& operator=(const Tricou&);
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
    ///friend
    virtual ~Tricou() {}
};
///copil
Tricou::Tricou() :Produs(){
    this->color_tricou = "none";
    this->gen_tricou = 'X';
    this->marime = "none";
    this->type_tricou = "none";
}
Tricou& Tricou::operator=(const Tricou &Obj) {
    if(this != &Obj) {
        Produs::operator=(Obj);
        this->color_tricou = Obj.color_tricou;
        this->gen_tricou = Obj.gen_tricou;
        this->marime = Obj.marime;
        this->type_tricou = Obj.type_tricou;
    }
    return *this;
}
Tricou::Tricou(const Tricou &obj):Produs(obj){
    this->color_tricou = obj.color_tricou;
    this->gen_tricou = obj.gen_tricou;
    this->marime = obj.marime;
    this->type_tricou = obj.type_tricou;
}
Tricou::Tricou(char *brand, string model, int stoc, float pret, string color_tricou, char gen, string marime, string type):
        Produs(brand, model, stoc, pret){
    this->color_tricou = color_tricou;
    this->gen_tricou = gen;
    this->marime = marime;
    this->type_tricou = type;
}
istream& Tricou::citire(istream& in){
    this->Produs::citire(in);
    cout<<"Culoare : ";
    in>>this->color_tricou;

    cout<<"Gen : ";
    in>>this->gen_tricou;

    cout<<"Marime : ";
    in>>this->marime;

    cout<<"Type : ";
    in>>this->type_tricou;
    return in;
}
ostream& Tricou::afisare(ostream& os) const{
    this->Produs::afisare(os);
    os << endl;
    os<<"Culoare : "<<this->color_tricou<<endl;
    os<<"Gen : "<<this->gen_tricou<<endl;
    os<<"Type : " <<this->type_tricou<<endl;
    os << endl;
    return os;
}
class Blugi: virtual public Produs{
protected:
    string color_blugi;
    char gen;
    int lungime;
    int latime;
    string type;
public:
    Blugi();
    Blugi(char *brand, string model, int stoc, float pret, string color_blugi, char gen, int lungime,int latime, string type);
    Blugi(const Blugi& obj);
    ///operator
    Blugi& operator=(const Blugi& obj);

    ///friend
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
    virtual ~Blugi() {}
};

///copil
Blugi::Blugi() :Produs(){
    this->color_blugi = "none";
    this->gen = 'X';
    this->lungime = 0;
    this->latime = 0;
    this->type = "none";
}
Blugi::Blugi(const Blugi &obj):Produs(obj){
    this->color_blugi = obj.color_blugi;
    this->gen = obj.gen;
    this->lungime = obj.lungime;
    this->latime = obj.latime;
    this->type = obj.type;
}
Blugi::Blugi(char *brand, string model, int stoc, float pret, string color_blugi, char gen, int lungime,int latime, string type):
        Produs(brand, model, stoc, pret){
    this->color_blugi = color_blugi;
    this->gen = gen;
    this->lungime = lungime;
    this->latime = latime;
    this->type = type;
}
Blugi& Blugi::operator=(const Blugi &Obj) {
    if(this != &Obj) {
        Produs::operator=(Obj);
        this->color_blugi = Obj.color_blugi;
        this->gen = Obj.gen;
        this->latime = Obj.latime;
        this->lungime = Obj.lungime;

        this->type = Obj.type;
    }
    return *this;
}
istream& Blugi::citire(istream& in){
    cout<<"=Blugi=\n";
    this->Produs::citire(in);
    cout<<"Culoare : ";
    in>>this->color_blugi;

    cout<<"Gen : ";
    in>>this->gen;

    cout<<"Lungime : ";
    in>>this->lungime;

    cout<<"Latime : ";
    in>>this->latime;

    cout<<"Type : ";
    in>>this->type;
    return in;
}
ostream& Blugi::afisare(ostream& os) const{
    this->Produs::afisare(os);
    os << endl;
    os<<"Culoare : "<<this->color_blugi<<endl;
    os<<"Gen : "<<this->gen<<endl;
    os<<"Lungime : "<<this->lungime<<endl;
    os<<"Latime : "<<this->latime<<endl;
    os<<"Type : " <<this->type<<endl;
    os << endl;
    return os;
}
class Pachet: public Tricou, public Blugi{
    bool cadou;
public:
    Pachet(){
        this->cadou = false;
    }
    Pachet(char *brand, string model, int stoc, float pret, string color_tricou, char gen, string marime,
           string color_blugi,  string type_tricou, string type, int lungime, int latime, char gen_tricou):
                    Produs(brand, model, stoc, pret),
                    Tricou(brand, model, stoc, pret, color_tricou, gen_tricou, marime, type_tricou),
                    Blugi(brand, model, stoc, pret, color_blugi, gen, lungime, latime ,type)
                    {
        this->cadou = cadou;
    }
    Pachet(const Pachet& obj):Produs(obj.brand, obj.model, obj.stoc, obj.pret), Tricou(obj){
        this->cadou = obj.cadou;
    }
    Pachet& operator =(const Pachet& obj);
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
    virtual ~Pachet(){}
};

Pachet &Pachet::operator=(const Pachet &obj) {
    if(this != &obj){
        Tricou::operator=(obj);
        Blugi::operator=(obj);
        this->cadou = obj.cadou;
    }
    return *this;
}

istream &Pachet::citire(istream & in) {

    cout<<"=PACHET=\n";
    Tricou::citire(in);
    cout << "Introduceti lungimea Pantalonilor\n";
    in>> this->lungime;
    cout << "Introduceti latimea Pantalonilor\n";
    in>> this->latime;
    cout << "Introduceti Tipul Pantalonilor\n";
    in>> this->type;
    return in;
}

ostream &Pachet::afisare(ostream &os) const {
    Tricou::afisare(os);
    cout << "lungimea Pantalonilor: ";
    os <<this->lungime<<endl;
    cout << "latimea Pantalonilor: ";
    os <<this->latime<<endl;
    cout << "tip Pantalonilor: ";
    os <<this->type<<endl;
    return os;
}
class Comanda {
private:
    static int contorId;
    const int idComanda;
    string localitate;
    bool transport;
    int nrProduse;///{2}
    int* produse; ///{2019,2014} list<int> produse;
    int* cantitate;
    float spret;
public:

    ///cosntructorii
    Comanda();
    Comanda(string localitate,
            bool transport, int nrProduse, int* produse, int* cantitate, float spret);
    Comanda(const Comanda& Obj);
    Comanda& operator=(const Comanda & Obj);

    /// getteri
    int static getContorId();
    int getIdComanda(){return this->idComanda;}
    string getlocalitate(){return this->localitate;}
    const int* getproduse() const {return this->produse;}
    int getnrProduse(){return this->nrProduse;}
    int getPrice(){return this->spret;}

    ///setteri
    void setPrice(float x){ this->spret = x;}
    void setlocalitate(string x){ this->localitate = x; this->transport = true;}

    /// functii
    void afisare();
    void citire();

    /// functii friend
    friend void afisare2(const Comanda& obj);
    friend ostream& operator <<(ostream& out, const Comanda& obj);
    friend istream& operator >>(istream& in, Comanda& obj);

    Comanda& operator ++();
    Comanda operator ++(int);
    Comanda operator +(const Comanda &);
    Comanda operator +(int);
    Comanda operator *(int);
    friend Comanda operator+(int a, Comanda);
    bool operator == (const Comanda &a);
    int operator [] (int);
    operator string();
    operator float()const; ///implicit
    operator float();///explicit
//    friend Comanda operator+(Comanda, int a); i.e linia 45
    ~Comanda(){

        if(this->produse!=NULL)
        {
            delete[] this->produse;
            this->produse=NULL;
        }
        if(this->cantitate!=NULL)
        {
            delete[] this->cantitate;
            this->cantitate=NULL;
        }

    }
};
int Comanda::contorId=5000;
Comanda::operator string(){
    return this->localitate;
}
Comanda::operator float(){
    return this->spret;
}
Comanda::operator float()const{
    return this->spret;
}
int Comanda::operator [] (int a)

{
    if(this->produse == NULL)
        throw runtime_error("Ani votare nu are elemente");
    if(a<0 || a>this->nrProduse)
        throw runtime_error("index invalid");
    else
        return this->produse[a];
}
bool Comanda::operator == (const Comanda &a)
{
    return this->localitate == a.localitate;
}
Comanda operator+(int a, Comanda obj)
{
    return obj+a;
}
Comanda Comanda::operator +(int a)
{
    Comanda aux(*this);
    if (aux.produse != NULL)
        delete [] aux.produse;
    if (aux.cantitate != NULL)
        delete [] aux.cantitate;
    aux.produse = new int[aux.nrProduse + 1];
    aux.cantitate = new int[aux.nrProduse + 1];
    for (int i = 0;  i<this->nrProduse; i++)
    {
        aux.produse[i] = this->produse[i];
        aux.cantitate[i] = this->cantitate[i];
    }
    aux.produse[this->nrProduse] = a;
    aux.cantitate[this->nrProduse] = 1;
    aux.nrProduse++;
    return aux;
}
Comanda Comanda::operator *(int a)
{   Comanda aux(*this);
    if (aux.produse != NULL)
        delete [] aux.produse;
    if (aux.cantitate != NULL)
        delete [] aux.cantitate;
    aux.produse = new int[aux.nrProduse];
    aux.cantitate = new int[aux.nrProduse];
    for (int i = 0;  i<this->nrProduse-1; i++)
    {
        aux.produse[i] = this->produse[i];
        aux.cantitate[i] = this->cantitate[i];
        cout<<aux.produse[i]<<' '<< aux.cantitate[i]<<endl;
    }
    aux.produse[this->nrProduse-1] = this->produse[this->nrProduse-1];
    aux.cantitate[this->nrProduse-1] = a;
    return aux;
}
Comanda Comanda::operator +(const Comanda &b)
{
    Comanda aux(*this);
    aux.spret = this->spret+aux.spret;
    aux.localitate = this->localitate + aux.localitate;
    return aux;
}

Comanda& Comanda::operator ++()
{
    this->spret++;
    return *this;
}

Comanda Comanda::operator ++(int)
{
    Comanda aux(*this);
    this->spret++;
    return aux;
}

Comanda& Comanda::operator=(const Comanda& Obj){

    if(this!=&Obj){
        if(this->produse!=NULL)
        {
            delete[] this->produse;
            this->produse=NULL;
        }
        if(this->cantitate!=NULL)
        {
            delete[] this->cantitate;
            this->cantitate=NULL;
        }
        this->localitate=Obj.localitate;
        this->transport=Obj.transport;
        this->nrProduse=Obj.nrProduse;
        this->produse=new int[Obj.nrProduse];
        for(int i=0;i<nrProduse;i++)
            this->produse[i]=Obj.produse[i];
        this->cantitate=new int[Obj.nrProduse];
        for(int i=0;i<nrProduse;i++)
            this->cantitate[i]=Obj.cantitate[i];
        this->spret=Obj.spret;


    }
    return *this;

}
/// tipul Instanta::numele metodei +implemenatrea
int Comanda::getContorId(){return Comanda::contorId;}
Comanda::Comanda():idComanda(contorId++){
    localitate="Anonim";
    transport=false;
    nrProduse=0;
    produse=NULL;
    cantitate = NULL;
    spret=0;
}

Comanda::Comanda(string localitate, bool transport, int nrProduse, int* produse,
                 int* cantitate, float spret) :idComanda(contorId++){

    this->localitate=localitate;
    this->transport=transport;
    this->nrProduse=nrProduse;
    this->produse=new int[nrProduse];
    for(int i=0;i<nrProduse;i++)
        this->produse[i]=produse[i];
    this->cantitate=new int[nrProduse];
    for(int i=0;i<nrProduse;i++)
        this->cantitate[i]=cantitate[i];
    this->spret=spret;
}
Comanda::Comanda(const Comanda& Obj):idComanda(contorId++){
    this->localitate=Obj.localitate;
    this->transport=Obj.transport;
    this->nrProduse=Obj.nrProduse;
    this->produse=new int[Obj.nrProduse];
    for(int i=0;i<nrProduse;i++)
        this->produse[i]=Obj.produse[i];
    this->cantitate=new int[nrProduse];
    for(int i=0;i<nrProduse;i++)
        this->cantitate[i]=cantitate[i];
    this->spret=Obj.spret;
}

void Comanda::afisare(){

    cout << "Afisare informatii relevante: " << endl;
    cout << "ID: " << this->idComanda << endl;
    cout << "localitate: " << this->localitate << endl;
    cout << "transport: " << (this->transport ? "Da" : "Nu") << endl;
    cout <<"NR PRODUSE: " <<this<<nrProduse<<'\n';
    cout << "Produse : ";
    for(int i=0; i<this->nrProduse; i++){
        cout << this->produse[i] << " ";
        cout<< this->cantitate[i]<<" ";
        cout<<endl;
    }
    cout << endl;
    cout << "Inaltimea: " << this->spret << " m" << endl;
}

void afisare2(const Comanda& obj){
    cout << "Afisare informatii relevante: " << endl;
    cout << "ID: " << obj.idComanda << endl;
    cout << "localitate: " << obj.localitate << endl;
    cout << "transport: " << (obj.transport ? "Da" : "Nu") << endl;
    cout << "Nr produse: " << obj.nrProduse << endl;

    cout << "Comenzi : ";
    for(int i=0; i<obj.nrProduse; i++){
        cout << obj.produse[i] << " ";
        cout<< obj.cantitate[i]<<" ";
        cout<<endl;
    }
    cout << endl;
    cout << "Pret Total: " << obj.spret << " m" << endl;
}

void Comanda::citire(){

    cout << "Afisare informatii relevante: " << endl;
    cout << "localitate: ";
    cin >> this->localitate;

    cout << "transport: ";
    cin >> this->transport;

    cout << "Nr Produse?";
    cin >> this->nrProduse;

    cout << "Produse :  ";
    if(this->produse != NULL){
        delete[] this->produse;
    }
    if(this->cantitate != NULL){
        delete[] this->cantitate;
    }
    this->produse = new int[this->nrProduse];
    this->cantitate = new int[this->nrProduse];
    for(int i=0; i<this->nrProduse; i++){
        cout<<"Produs : ";
        cin >> this->produse[i];
        cout<<'\n';
        cout<<"Cantitate : ";
        cin >> this->cantitate[i];
        cout<<'\n';
    }

    cout << "Suma Totala: ";
    cin >> this->spret;

    cout << endl;
}

ostream& operator <<(ostream& out, const Comanda& obj){

    out << "Afisare informatii relevante: " << endl;
    out << "ID: " << obj.idComanda << endl;
    out << "localitate: " << obj.localitate << endl;
    out << "transport: " << (obj.transport ? "Da" : "Nu") << endl;
    out << "Nr Produse: \n"<<obj.nrProduse<<endl;
    out << "Nr Produse: ";
    for(int i=0; i<obj.nrProduse; i++){
        out << obj.produse[i] << " ";
        out<< obj.cantitate[i]<<" ";
        out<<endl;
    }
    out << endl;
    out << "Suma Totala: " << obj.spret << " m" << endl;

    return out;
}

istream& operator >>(istream& in, Comanda& obj){

    cout << "localitate: ";
    in >> obj.localitate;

    cout << "transport: ";
    in >> obj.transport;

    cout << "Nr produse? ";
    in >> obj.nrProduse;

    cout << "Produse :  ";
    if(obj.produse != NULL){
        delete[] obj.produse;
    }
    if(obj.cantitate != NULL){
        delete[] obj.cantitate;
    }
    obj.produse = new int[obj.nrProduse];
    for(int i=0; i<obj.nrProduse; i++){
        in >> obj.produse[i];
        in >> obj.cantitate[i];
    }

    cout << "Suma totala: ";
    in >> obj.spret;

    cout << endl;
    return in;
}
class Client{
private:
    static int contorIdC;
    const int idUser;
    string parola;
    char *nume;
    char *prenume;
    int varsta;
    bool premium;
    int nr_comenzi;
    int* comenzi;
    float stotal;
    float puncte;
    ///TODO Comenzi+
public:
    ///construcvtori
    Client();
    Client(char *nume, char *prenume, string parola, int varsta,  bool premium, int nr_comenzi, int* comenzi,float stotal, float puncte);
    Client(const Client& Obj);
    int static getcontorIdC();
    /// operatori
    Client& operator=(const Client & Obj);
    Client& operator++();
    Client operator++(int);
    Client& operator-(const float &Obj);
    Client operator +(int x);
    Client& operator*(const float &Obj);
    Client operator+(Comanda x);
    bool operator ==(const Client &obj);
    bool operator >(const Client &obj);
    int operator [] (int);
    operator string ();
    ///functii friend
    friend ostream& operator <<(ostream& out, const Client& c1);
    friend istream& operator >>(istream& in,  Client& obj);
    friend void afisare2(const Client &Obj);
    friend Client operator+(int x, Client &obj);
    friend Client operator*(int x, Client &obj);
    friend Client operator+(Comanda x, Client &obj);
    const int* getCo() const {return this->comenzi;}

    ///functii
    void afisare();
    void citire();
    ///geteri
    string getNume(){return this->nume;}
    string getPrenume(){return this->prenume;}
    string getParola(){return this->parola;}
    int getVarsta(){return this->varsta;}
    bool getPremium(){return this->premium;}
    int getNrComenzi(){return this->nr_comenzi;}
    float getStotal(){return this->stotal;}
    int getUserId(){return Client::idUser;}
    int getComenzi(int x) const {return this->comenzi[x];}
    ///seterti
    void setnume(char *x){
        if (this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }
        this->nume = new char[strlen(x) + 1];
        strcpy(this->nume, x);
    }
    void setComanda(int *x){
        if (this->comenzi != NULL) {
            delete[] this->comenzi;
            this->comenzi = NULL;
        }
        this->nr_comenzi++;
        this->comenzi = new int[nr_comenzi];
    }
    void setparola(string x){this->parola = x;}
    void setvarsta(int x){this->varsta = x;}
    void setSPret(float x){
        this->stotal = x;
        this->puncte = x/66; /// 1.5% cashback
        if(x >=1000)
            this->premium = true;
    }
    ///destructor
    ~Client(){
        if(this->nume!=NULL)
        {
            delete[] this->nume;
            this->nume=NULL;
        }

        if(this->prenume!=NULL)
        {
            delete[] this->prenume;
            this->prenume=NULL;
        }
        if(this->prenume!=NULL)
        {
            delete[] this->comenzi;
            this->comenzi=NULL;
        }

    }
};
int Client::contorIdC=2000;
Client& Client::operator=(const Client& Obj) {

    if (this != &Obj) {
        if (this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }

        if (this->prenume != NULL) {
            delete[] this->prenume;
            this->prenume = NULL;
        }
        if(this->comenzi!=NULL)
        {
            delete[] this->comenzi;
            this->comenzi=NULL;
        }
        this->nume = new char[strlen(Obj.nume) + 1];/// doar am alocat memorie
        strcpy(this->nume, Obj.nume);/// atribui valoarea
        this->prenume = new char[strlen(Obj.prenume) + 1];/// doar am alocat memorie
        strcpy(this->prenume, Obj.prenume);/// atribui valoarea
        this->parola = Obj.parola;
        this->varsta = Obj.varsta;
        this->premium = Obj.premium;
        this->nr_comenzi = Obj.nr_comenzi;
        this->comenzi = new int[Obj.nr_comenzi];
        for(int i=0;i<nr_comenzi;i++)
            this->comenzi[i] = Obj.comenzi[i];


        this->stotal = Obj.stotal;
        this->puncte = Obj.puncte;
    }
    return *this;
}
/// << >> afisare citire
void Client::afisare(){
    cout<< "Afisare Pereche Papusci : " <<endl;
    cout<<"-----------------------------"<<endl;
    cout << "id Client: " << this->idUser<<endl;
    cout << "Nume: " <<this->nume<<endl;
    cout << "Prenume: " <<this->prenume<<endl;
    cout << "Parola :" << this->parola<<endl;
    cout << "Varsta: "<< this->varsta <<endl;
    cout << "Cont Premium ? : " << this->premium <<endl;
    cout<< "numar comenzi : "<<this->nr_comenzi<<endl;
    for(int i=0; i<this->nr_comenzi; i++) {
        cout << this->comenzi[i] << " ";
    }
    cout << "Suma totala cheltuita : " << this->stotal <<endl;
    cout << "Puncte Bonus : "<< this->puncte<<endl;
}
void afisare2(const Client& Obj){
    cout<< "Afisare Pereche Papusci : " <<endl;
    cout<<"-----------------------------"<<endl;
    cout << "id Client: " << Obj.idUser<<endl;
    cout << "Nume: " <<Obj.nume<<endl;
    cout << "Prenume: " <<Obj.prenume<<endl;
    cout << "Parola: " <<Obj.parola<<endl;
    cout << "Varsta: "<< Obj.varsta <<endl;
    cout << "Cont Premium ? : " << Obj.premium <<endl;
    cout<< "numar comenzi : "<<Obj.nr_comenzi<<endl;
    for(int i=0; i<Obj.nr_comenzi; i++) {
        cout << Obj.comenzi[i] << " ";
    }
    cout << "Suma totala cheltuita : " << Obj.stotal <<endl;
    cout << "Puncte Bonus : "<< Obj.puncte<<endl;
}
/// >> <<
ostream& operator <<(ostream& out, const Client& c1){
    out<< "Afisare Pereche Papusci : " <<endl;
    out<<"-----------------------------"<<endl;
    out << "id User: " << c1.idUser<<endl;
    out << "Nume: " <<c1.nume<<endl;
    out << "Prenume: " <<c1.prenume<<endl;
    out << "Parola: " <<c1.parola<<endl;
    out << "Varsta: " <<c1.varsta<<endl;
    out << "Cont Premium ?: "<<c1.premium<<endl;
    out<< "numar comenzi : "<<c1.nr_comenzi<<endl;
    for(int i=0; i<c1.nr_comenzi; i++) {
        out << c1.comenzi[i] << " ";
    }
    cout<<'\n';
    out << "Suma totala cheltuita : "<<c1.stotal<<endl;
    out << "Puncte bonus " <<c1.puncte<<endl;
    return out;
}
istream& operator >>(istream& in,  Client& obj){
    cout<<"Nume: ";
    char aux[100];
    in >> aux;
    if(obj.nume != NULL){
        delete[] obj.nume;
    }
    obj.nume = new char[strlen(aux)+1];
    strcpy(obj.nume, aux);

    cout << "Prenume: ";
    in >> aux;
    if(obj.prenume != NULL){
        delete[] obj.prenume;
    }
    obj.prenume = new char[strlen(aux)+1];
    strcpy(obj.prenume, aux);

    cout << "Parola: ";
    in >> obj.parola;

    cout << "Varsta: ";
    in >> obj.varsta;
    cout<<endl;
    cout<<"ID TAU PENTRU LOGARE : ";
    cout<<obj.idUser;
    return in;
/**
    cout << "Cont Premium: ";
    in >> obj.premium;

    cout << "Nr comenzi efectuate? ";
    cin >> obj.nr_comenzi;

    cout << "Comenzi : ? ";
    if(obj.comenzi != NULL){
        delete[] obj.comenzi;
    }
    obj.comenzi = new int [obj.nr_comenzi];
    for(int i=0; i<obj.nr_comenzi; i++){
        cout<<"comanda cu nr : ";
        in >> obj.comenzi[i];
    }

    cout << "Pret total: ";
    in >> obj.stotal;

    cout << "Puncte bonus: ";
    in >> obj.stotal;
    return in;
*/
}
void Client::citire(){

    cout << "Afisare informatii relevante: " << endl;

    cout<<"Nume: ";
    char aux[100];
    cin >> aux;
    if(this-> nume != NULL){
        delete[] this-> nume;
    }
    this-> nume = new char[strlen(aux)+1];
    strcpy(this-> nume, aux);

    cout << "Prenume: ";
    cin >> aux;
    if(this->prenume != NULL){
        delete[] this-> prenume;
    }
    this->prenume = new char[strlen(aux)+1];
    strcpy(this-> prenume, aux);

    cout << "Parola: ";
    cin >> this-> parola;

    cout << "Varsta: ";
    cin >> this-> varsta;

    cout << "Cont Premium: ";
    cin >> this-> premium;

    cout << "Nr comenzi efectuate? ";
    cin >> this->nr_comenzi;

    cout << "Comnzi :  \n";
    if(this->comenzi != NULL){
        delete[] this->comenzi;
    }
    this->comenzi = new int[this->nr_comenzi];
    for(int i=0; i<this->nr_comenzi; i++){
        cout<<"comanda cu nr : ";
        cin >> this->comenzi[i];
    }

    cout << "Pret total: ";
    cin >> this-> stotal;

    cout << "Puncte bonus: ";
    cin >> this-> stotal;
}
///adunare


///float + adunare ???


Client& Client::operator-(const float & Obj){
    this->puncte = puncte - Obj;
    return *this;
}

Client& Client::operator*(const float & Obj){
    this->puncte = puncte * Obj;
    return *this;
}
Client& Client::operator++(){
    this->varsta = varsta + 1 ;
    return *this;
}
Client Client::operator++(int){
    Client aux(*this);
    operator++();
    return aux;
}
Client Client::operator+(int x) {
    Client aux(*this);
    if(aux.comenzi != NULL)
    {   ///cout<<"Daaaa\n";
        delete [] aux.comenzi;}
    aux.comenzi = new int[aux.nr_comenzi + 1];
    for(int i=0;i<this->nr_comenzi;i++){
        aux.comenzi[i]=this->comenzi[i];
    }
    aux.comenzi[this->nr_comenzi] = x;
    aux.nr_comenzi++;
    return aux;
}
Client operator*(int x, Client &obj){
    return obj*x;
}
Client operator+(int x, Client &obj){
    return obj+x;
}
Client Client::operator+(Comanda x) {
    Client aux(*this);
    if(aux.comenzi != NULL)
    {   ///cout<<"Daaaa\n";
        delete [] aux.comenzi;}
    aux.comenzi = new int[aux.nr_comenzi + 1];
    for(int i=0;i<this->nr_comenzi;i++){
        aux.comenzi[i]=this->comenzi[i];
    }
    aux.comenzi[this->nr_comenzi] = x.getIdComanda();
    aux.nr_comenzi++;
    return aux;
}
Client operator+(Comanda x, Client &obj){
    return obj+x;
}

bool Client::operator==(const Client& obj) {
    if(strcmp(this->nume,obj.nume)==0 and strcmp(this->prenume,obj.prenume)==0 and this->varsta==obj.varsta and this->premium==obj.premium and this->nr_comenzi==obj.nr_comenzi){
        for(int i=0;i<obj.nr_comenzi;i++){
            if(this->comenzi[i]!=obj.comenzi[i])
                return 0;
        }
        return 1;
    }
    return 0;
}
bool Client::operator>(const Client& obj){
    return this->stotal > obj.stotal;
}
int Client::operator [] (int a){
    if(this->nr_comenzi == 0)
        throw runtime_error("Ani votare nu are elemente");
    if(a<0 || a>this->nr_comenzi)
        throw runtime_error("index invalid");
    else
        return this->comenzi[a];
}
Client::operator string() {
    return this->parola;
}
int Client::getcontorIdC(){return Client::contorIdC;}
Client::Client():idUser(contorIdC++){
    nume = new char[strlen("ANONIM")+1];
    strcpy(nume,"Anonim");/// atribui valoarea
    prenume = new char[strlen("ANONIM")+1];
    strcpy(prenume,"Anonim");/// atribui valoarea
    parola = "****";
    varsta= 0;
    premium = false;
    nr_comenzi=0;
    comenzi=NULL;
    stotal = 0;
    puncte = 0;
}
Client::Client(char *nume, char *prenume, string parola, int varsta, bool premium, int nr_comenzi, int *comenzi  ,float stotal, float puncte):idUser(contorIdC++) {
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=new char[strlen(nume)+1];
    strcpy(this->prenume,nume);
    this->parola = parola;
    this->varsta = varsta;
    this->premium = premium;
    this->nr_comenzi = nr_comenzi;
    this->comenzi = new int[nr_comenzi];
    for(int i=0;i<nr_comenzi;i++)
        this->comenzi[i] = comenzi[i];
    this->stotal = stotal;
    this->puncte = puncte;
}
Client::Client(const Client &Obj):idUser(contorIdC++) {
    this->nume=new char[strlen(Obj.nume)+1];
    strcpy(this->nume,Obj.nume);
    this->prenume=new char[strlen(Obj.nume)+1];
    strcpy(this->prenume,Obj.nume);
    this->parola = Obj.parola;
    this->varsta = Obj.varsta;
    this->premium = Obj.premium;
    this->nr_comenzi = Obj.nr_comenzi;
    this->comenzi = new int[Obj.nr_comenzi];
    for(int i=0;i<nr_comenzi;i++)
        this->comenzi[i] = Obj.comenzi[i];
    this->stotal = Obj.stotal;
    this->puncte = Obj.puncte;
}
class Inventar{
    Produs* produs;
public:
    friend istream & operator >>(istream& in, Inventar& coppy){
        cout<<"#1 Tricouri\n";
        cout<<"#2 Blugi\n";
        cout<<"#3 Pachet Promo\n";
        int k;
        cout<<"Comanda : ";
        cin>>k;
        cout<<endl;
        if(k == 1){
            coppy.produs = new Tricou();
        }
        if(k == 2){
            coppy.produs = new Blugi();
        }
        if(k == 3){
            coppy.produs = new Pachet();
        }
        // TODO diamant
        in>>*coppy.produs;
        return in;
    }
    friend ostream& operator<<(ostream& os, const Inventar& obj){
        os<<*obj.produs<<endl;
        return os;
    }
    Produs* getProdus() {return this->produs;}
};
class Catalog{
    list<Inventar> inventar;
    vector<Produs*> prd;
public:
    void addProdus();
    const void showInventar();
    void modifyProdus(int cod_produs);
    Produs* operator [] (int);
};
void Catalog::addProdus(){
    Inventar i;
    cin >> i;
    prd.push_back(i.getProdus());
}
const void Catalog::showInventar(){
    cout<<prd.size()<<"\n";
    for(int i = 0; i < prd.size(); i++)
        cout << *prd[i] << endl;
    cout<<"===========================\n";
}
void Catalog::modifyProdus(int cod_produs){
    for(int i=0; i<prd.size(); i++)
        if(prd[i]->getId() == cod_produs){
            cout << "MODIFICARI\n" << endl;
            cout<<"================\n";
            cout << "\n1-Pret";
            cout << "\n2-Stoc";
            cout << "\n3-STOP";
            cout << "\n3-COMANDA : ";
            int comanda;
            cin>>comanda;
            if(comanda == 1){
                cout << "MODIFICARI\n" << endl;
                cout<<"================\n";
                cout<<"Actual Price : "<<prd[i]->getPret()<<"\n";
                cout<<"New Price : ";
                float new_price;
                cin>>new_price;
                prd[i]->setPret(new_price);
            }
            else if(comanda == 2){
                cout << "MODIFICARI\n" << endl;
                cout<<"================\n";
                cout<<"Actual Stoc : "<<prd[i]->getStoc()<<"\n";
                cout<<"New Stoc : ";
                int new_stoc;
                cin>>new_stoc;
                prd[i]->setStoc(new_stoc);
            }
        }
}
Produs* Catalog::operator [] (int a){
    return this->prd[a];
}
int main() {
    ///date principale
    Catalog mag;
    int contClienti = 0;
    Client listaClienti[1000];
    int contComanda = 0;
    Comanda listaComenzi[1000];
    int key = 1111;
    int locClient = 0;
    int com;
    bool power_button = true;
    while(power_button) {
        /// Meniu principal

        cout << "Bine ati venit !!!" << endl;
        cout << "\n1-Admin;";
        cout << "\n2-Utilizator;";
        cout << "\n3-STOP";
        cout << endl;
        cout << "alageti comanda : ";
        cin >> com;
        system("CLS");
        ///------------------------------------------

        switch (com) {
            case 1: { ///admin
                cout << "Password : ";
                int password;
                cin >> password;
                system("CLS");
                /// system("CLS");
                if (password == key) {
                    bool okadmin = true;
                    while (okadmin) {
                        cout << "Comenzi Admin : ";
                        cout << "\n1-Adaugati Produse;";
                        cout << "\n2-Vizualizati Produse; ";
                        cout << "\n3-Modificare Produs";
                        cout << "\n4-Iesire\n ";
                        int comadmin;
                        cout << "alageti comanda : ";
                        cin >> comadmin;
                        system("CLS");
                        switch (comadmin) {
                            case 1: {
                                mag.addProdus();
                                break;
                            }
                            case 2: {
                                mag.showInventar();
                                break;
                            }
                            case 3: {
                                cout << "Cod Produs : ";
                                int cod_prod;
                                cin >> cod_prod;
                                mag.modifyProdus(cod_prod);
                                break;
                            }
                            case 4: {
                                okadmin = 0;
                            }
                        }
                    }
                }
                else {
                    system("CLS");
                    cout << "PAROLA GRESITA\n";

                }
                break;
            }
            case 2:{
                bool cuser = true;
                while(cuser) {
                    int menu_user;
                    cout << "\nProfil Utilizator\n";
                    cout << "++++++++++++++++++++++++";
                    cout << "\n1-Creere cont;";
                    cout << "\n2-Log in: ";
                    cout << "\n3-Iesire";
                    cout << "\nintroduceti comanda: ";
                    cin >> menu_user;
                    switch (menu_user) {
                        case 1: { /// CREARE CONT
                            cin >> listaClienti[contClienti++];
                            break;
                        }
                        case 2: { ///LOGARE

                            ///system("CLS");
                            int id_user;
                            string password;
                            cout << "\nCod Utilizator : ";
                            cin >> id_user;
                            cout << "\nParola : ";
                            cin >> password;
                            bool ok = false;
                            for (int i = 0; i <= contClienti and !ok; i++) {
                                if (listaClienti[i].getUserId() == id_user) {
                                    if (listaClienti[i].getParola().compare(password) == 0) {
                                        ok = true;
                                        locClient = i;
                                    }
                                }
                            }
                            system("CLS");
                            if (ok) {
                                cout << "\nBine ati venit !!!\n-----------------\n";
                                cout << "Comenzi : \n";
                                cout << "\n1-Comanda Noua";
                                cout << "\n2-Vezi comenzi efectuate";
                                cout << "\n3-Modificare Parola";
                                cout << "\n4-Iesire";
                                cout << "\n comanda :";
                                int comanda_user;
                                int index_comanda;
                                cin >> comanda_user;
                                system("CLS");
                                switch (comanda_user) {
                                    case 1: {
                                        bool ok_comanda = true;
                                        Comanda Comanda_noua;
                                        while (ok_comanda) {
                                            cout << "\n1-Cumpara;";
                                            cout << "\n2-Confirmare";
                                            cout << "\n3-Iesire; \n";
                                            cout << "comanda 1/2/3: ";
                                            int cbuy = 0;
                                            cin >> cbuy;
                                            system("CLS");
                                            switch (cbuy) {
                                                case 1: {
                                                    bool BuyPapuci = true;
                                                    int cursor = 0;
                                                    while(BuyPapuci){
                                                        cout<<*mag[cursor];
                                                        cout << "Comenzi PRODUSE : ";
                                                        cout << "\n1-Inapoi;";
                                                        cout << "\n2-Inainte;";
                                                        cout << "\n3-Adauga in cos;";
                                                        cout << "\n4-Iesire; \n---------------\n";
                                                        cout<<"Comanda : ";
                                                        int comanda_papuci;
                                                        cin>>comanda_papuci;
                                                        system("CLS");
                                                        switch (comanda_papuci) {
                                                            case 1:{
                                                                cursor--;
                                                                break;
                                                            }
                                                            case 2:{
                                                                cursor++;
                                                                break;
                                                            }
                                                            case 3:{
                                                                cout<<"\nNr Bucati :";
                                                                int y;
                                                                cin>>y;
                                                                system("CLS");
                                                                if(mag[cursor]->getPret() >= y) {
                                                                    int stoc_nou = mag[cursor]->getStoc() - y;
                                                                    mag[cursor]->setStoc(stoc_nou);
                                                                    cout<<stoc_nou<<endl;
                                                                    listaComenzi[contComanda] = listaComenzi[contComanda] + mag[cursor]->getId();
                                                                    listaComenzi[contComanda] = listaComenzi[contComanda] * y;
                                                                    cout<<listaComenzi[contComanda];

                                                                    float s = y * mag[cursor]->getPret();
                                                                    s = s + listaComenzi[contComanda].getPrice();
                                                                    listaComenzi[contComanda].setPrice(s);
                                                                }
                                                                break;

                                                            }
                                                            case 4:{
                                                                BuyPapuci = false;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                    break;
                                                }
                                                case 2: {
                                                    int tr;
                                                    cout<<"\nDoriti Transport ? 1-da//0-nu ";
                                                    cin>>tr;
                                                    if(tr==1) {
                                                        string yy;
                                                        cout << "\nLocalitate : ";
                                                        cin >> yy;
                                                        listaComenzi[contComanda].setlocalitate(yy);
                                                    }
                                                    system("CLS");
                                                    cout<<"\n**********\nComanda a fost inregistrata\n*************\n";
                                                    cout<<listaComenzi[contComanda]<<endl;
                                                    listaClienti[locClient] = listaClienti[locClient]+listaComenzi[contComanda].getIdComanda();
                                                    float s_total = listaClienti[locClient].getStotal();
                                                    s_total += listaComenzi[contComanda].getPrice();
                                                    cout<<endl<<s_total<<endl;
                                                    listaClienti[locClient].setSPret(s_total);
                                                    cout<<listaClienti[locClient];
                                                    contComanda++;

                                                    break;
                                                }
                                                case 3: {
                                                    ok_comanda = false;
                                                    break;
                                                }

                                            }
                                        }
                                        break;
                                    }
                                    case 2:{
                                        cout<<"*****************\n   Profilul Vostru   \n*****************\n";
                                        cout<<listaClienti[locClient];
                                        cout<<"*******************\n*******************";
                                        int k = listaClienti[locClient].getNrComenzi();
                                        for(int i=0;i<k;i++) {
                                            int y = listaClienti[locClient].getComenzi(i);
                                            for (int j = 0; j <= contComanda; j++) {
                                                if (listaComenzi[j].getIdComanda() == y) {
                                                    cout<<"===========================\n";
                                                    cout << "\nURMATOAREA COMANDA\n";
                                                    cout << listaComenzi[j];
                                                }
                                            }
                                        }
                                        cout<<"===========================\n";
                                        break;
                                    }
                                    case 3:{
                                        cout<<"\n Schimbare Parola\n-------------";
                                        cout<<"\nParola Noua : ";
                                        string parola;
                                        cin>>parola;
                                        system("CLS");
                                        for(int i=0;i<contClienti;i++)
                                            if(listaClienti[i].getUserId() == id_user)
                                                listaClienti[i].setparola(parola);
                                        break;
                                    }
                                    case 4:{
                                        ok=false;
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        case 3:{
                            cuser = false;
                            break;
                        }
                    }
                }
                break;
            }
            case 3:{
                power_button = false;
                break;
            }
        }
    } /// final
    Pachet j;
    Produs* p = new Pachet();
    j.citire(cin);
    j.afisare(cout);
/**
    vector<Produs*> test;
    Produs* add_test;
    add_test = new Blugi();
    cin>>*add_test;
    test.push_back(add_test);
    cout<< *test[0];
*/
    return 0;
}
/**
    vector<Produs*> test;
    Produs* add_test;
    add_test = new Blugi();
    cin>>*add_test;
    test.push_back(add_test);
    cout<< *test[0];
*/
