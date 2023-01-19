#include <iostream>
#include<math.h>

using namespace std;


// tipuri de varaibile
struct numar{
    int v; // valoarea din lista
    numar *urm; // legatura catre urmatorul element din lista
}; // structura elemente lista simplu inlantuita

struct numar2{
    int v; // valoarea din lista
    numar2 *prec; // legatura catre precedentull element din lista
    numar2 *urm; // legatura catre urmatorul element din lista
}; // structura elemente lista dublu inlantuita

struct lista2{
    numar2 *prim;
    numar2 *ultim;
}; // structura primul si ultimul element din lista dublu inlantuita

// tip de variabila pentru adunarea si inmultirea de polinoame
struct monom{
    int grad;
    float coef;
    monom *urm;
}; // structura elementelor care compun un polinom

//variabile globale
float x[20];

//functiile utilizatorului
numar *creare_lista()
{
    numar *cap, *u, *c;
    int x, n;
    cout<<"creare lista!"<<endl;
    // creare capat lista
    cout<<"Valoare cap lista x = "; cin>>x;
    cap=new numar;
    cap->v=x;
    cap->urm=NULL;
    u=cap; // ultimul element din lista
    cout<<"Numarul de elemente care se adauga in lista la cearea listei n = "; cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout<<"Valoare de adaugat in lista x = "; cin>>x;
        c=new numar;
        c->v=x;
        c->urm=NULL;
        u->urm=c; // stabileste legatura intre ultimul elemnt si noul element adaugat
        u=c; // c devine ultimul element
    }
    return cap;
}
void parcurgere_lista(numar *cap)
{
    numar *c;
    if (cap == NULL)
        cout<<"Lista este vida!"<<endl;
    else
    {
        c=cap;
        while (c != NULL)
        {
            cout<<c->v<<" ";
            c=c->urm;
        }

    }

}

numar *modificare_in_lista(numar *cap, int y, int w)
{
    numar *c;
    for(c=cap; c!=NULL; c=c->urm)
    {
        if (c->v == y)
            c->v=w;
    }
    return cap;
}

numar *stergere_din_lista(numar *cap)
{
    int cont=0;
    int s;
    numar *c, *p;

    do
    {
        if (cap == NULL)
            cout<<"Lista este vida! Nu sunt valori de sters!"<<endl;
        else
        {
            //sterge elementul cu valoarea s de cate ori apare in lista
            cout<<"Valoare de sters s = ";
            cin>>s;
            int nrs=0; // numara de cate ori am sters s din lista
            // stergem valoarea s daca se afla la inceput la lista
            while (cap->v == s)
            {
                cap=cap->urm;
                nrs++;
                if (cap == NULL)
                    break;
            }
            if (cap !=NULL)
            {
                c=cap->urm;
                p=cap; // precedentul elementului curent c
                while (c!=NULL)
                {
                    if (c->v == s)
                    {
                        // sterge din lista pe c
                        p->urm=c->urm;
                        nrs++;
                        c=c->urm;
                    }
                    else
                    {
                        p=c;
                        c=c->urm;
                    }
                }
            }
            cout<<"Elementul de sters "<<s<<" a fost sters de "<<nrs<<" ori"<<endl;
            cout<<"Lista ramasa este: ";
            parcurgere_lista(cap);
            cout<<endl;
        }
        cout<<"Continua stergerea [0/1]? ";
        cin>>cont;
    }
    while (cont);
    return cap;
}


numar *adaugare_in_lista(numar *cap,int a)
{
    int opa;
    numar *p;
    do
    {
        cout<<endl<<"Tip adaugare:"<<endl;
        cout<<"1. Adaugare la inceput de lista:"<<endl;
        cout<<"2. Adaugare dupa element din interiorul listei:"<<endl;
        cout<<"3. Adaugare la sfarsitul listei:"<<endl;
        cout<<"0. Incheiere adaugare!"<<endl;
        cout<<"Optiune adaugare: "; cin>>opa;
        switch (opa)
        {
       case 1: // adauga la inceput
           p=new numar;
           p->v=a;
           p->urm=cap;
           cap=p;
           parcurgere_lista(cap);
           cout<<endl;
        break;
       case 2:
        break;
       case 3:
        break;
       case 0:
        cout<<"incheiat adaugare!"<<endl;
        break;
       default:
        cout<<"Optiune invalida!"<<endl;
        break;
        }// end switch
    }while(opa);
    return cap;
}
void radix_sort(int n, int v[100])
{

    // (1)
    int y[n],aux,i,j,p,s,r,k;
    int maxim = 0;
    // sirul initial neordonat
    cout<<"Sirul initial neordonat: ";
    for(i=0;i<n;i++)
        {
          cout<<v[i]<<" ";
          if(v[i]>maxim)
            maxim=v[i];
        }
    cout<<endl;
    int M=0,M1;//M = numarul maxim de cifre ale numerelor din sir
    while(maxim/10!=0)
    {
        M++;
        maxim=maxim/10;
    }
    M++;
    // end (1)

    // (2)
    int C[n][M]; // C = matricea de cifre ale numerelor de ordonat
    //initializam matricea de cifre
    for(i=0;i<n;i++)
        for(j=0;j<=M-1;j++)
          C[i][j]=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<=M-1;j++)
            y[j]=0;
        aux=v[i];
        M1=0;
        while(aux!=0)
        {
            y[M1]=aux%10;
            aux=aux/10;
            M1++;
        }
        for(j=0;j<=M1-1;j++)
            C[i][M-1-j]=y[j];
    }
    // end (2)
    // scrie matricea de cifre
    cout<<"Matricea de cifre initiala este:"<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<=M-1;j++)
            cout<<C[i][j]<<" ";
        cout<<endl;
    }

    for(j=M-1; j>=0; j--) // parcurge clasele de cifre din matricea C, adica colonele din C de la ultima spre prima
    {
        i=0;
        for(k=0;k<=9;k++) //cautam cifrele de la 0 la 9 din fiecare coloana
        {
            for(s=i;s<=n-1;s++) // cauta cifra k in coloana j
            {
                if(C[s][j]==k)
                {
                    for(r=0;r<=M-1;r++)
                        y[r] = C[s][r];

                    for(p=s; p>=i+1;p--) // translateaza cu o linie in jos , numerele de i la s
                    {
                        for(r=0;r<=M-1;r++)
                            C[p][r] = C[p-1][r];
                    }
                    for(r=0;r<=M-1;r++) //pune in linia i numarul care in coloan j are cifra k
                        C[i][r] = y[r];
                    i++;
                }
            }
        }
        cout<<"Ordonarea dupa clasa j = "<<j<<endl;
        cout<<"Matricea de cifre cu clasa j orodnata este:"<<endl;
        for(int i1=0; i1<n; i1++)
        {
            for(int j1=0; j1<=M-1; j1++)
                cout<<C[i1][j1]<<" ";
            cout<<endl;
        }
    }

    // (3)
    for(i=0;i<=n-1;i++)
        y[i] = 0;
    i=0;
    while(i<=n-1) // recontruieste numerele ordonate in matricea C
    {
        y[i]=C[i][0];
        for(j=1;j<=M-1;j++)
            y[i] = y[i]*10+C[i][j];
        i++;
    }
    cout<<endl<<"Vectorul sortat este: ";
    for(i=0;i<n;i++)
        cout<<y[i]<<" ";
    cout<<endl;
}
















void cautare_secventiala(){
    float y;
    int n;
    cout<<"introduceti numarul de valori "; cin>>n;
    cout<<"introduceti valorile vectorului "<<endl;
    cout<<"introduceti valoarea cautata ";cin>>y;
    float x[n];
    for(int i=0;i<n;i++)
        cin>>x[i];
    int c=0;
    for(int i=0;i<n;i++)
        if(x[i]==y)
            c++;
    if(c==0)
        cout<<"valoarea cautata nu se afla in sir";
    else
        cout<<y<<" se afla de "<<c<<" ori in sirul dat";

}
void cautare_binara(int s,int d,float x[],float y){
    int m;
    if(s<d){
        m=(s+d)/2;
        if(y==x[m])
            cout<<y<<" se afla in sir pe pozitia "<<m;
        else{
            if(y<x[m]){
                if(s<=m-1){
                    cautare_binara(s,m-1,x,y);}
            }
            else
                cautare_binara(m+1,d,x,y);
        }
    }

    else{
        if(y==x[s])
            cout<<y<<" se afla in sir pe pozitia "<<s;
        else
            cout<<y<<" nu se afla in sir";
    }

}
void interclasare(int s,int m,int d, float x[]){
    int i=s,j=m+1,k=0;
    int y[100];
    while(i<=m&&j<=d){
        if(x[i]<=x[j]){
            y[k]=x[i];
            k++;
            i++;
        }
        else{
            y[k]=x[j];
            k++;
            j++;
        }

    }
    if(i<=m)
        for(int r=i;r<=m;r++){
            y[k]=x[r];
            k++;
        }
    if(j<=d)
        for(int r=j;r<=d;r++){
            y[k]=x[r];
            k++;
    }
    for(int r=0;r<k;r++)
        x[s+r]=y[r];
    }
void shellsort(){
    int n,j,i;
    cout<<"introduceti numarul de valori "; cin>>n;
    cout<<"introduceti valorile vectorului "<<endl;
    float x[100];
    for(int i=0;i<n;i++)
        cin>>x[i];

    int pas =n/2,aux;
    while(pas>=1){
        i=0;
        while(i+pas<=n-1){
            j=i;
            aux=x[i+pas];
            while(x[j]>aux&&j>=0){
                x[j+pas]=x[j];
                j=j-pas;
            }
            x[j+pas]=aux;
            i++;
        }
    pas=pas/2;
    }
    for(int i=0;i<n;i++)
        cout<<x[i]<<" ";
}
void insertionsort(){
    int n,j;
    cout<<"introduceti numarul de valori "; cin>>n;
    cout<<"introduceti valorile vectorului "<<endl;
    float x[100];
    for(int i=0;i<n;i++)
        cin>>x[i];


    for(int i=0;i<n;i++){
        int aux=x[i];
        j=i-1;
        while(x[j]>aux&&j>=0){
            x[j+1]=x[j];
            j--;
        }
        x[j+1]=aux;
    }
    for(int i=0;i<n;i++)
        cout<<x[i]<<" ";


}

void QuickSort(int s, int d, float x[],int n)
{
    // ordoneaza subsirul x[s], ....x[d]
    int i, j;
    float pivot,aux;
    cout<<"********************"<<endl;
    for(i=s;i<=d;i++ )
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;
    cout<<"s = "<<s<<endl;
    cout<<"d = "<<d<<endl;
    if (s<d)
    {

        // alegem pivotul x[s];
        pivot=x[s];
        //cauta poziti corecta a pivotului
        int c=0; //c numara cate elemente sunt mai mici decat pivot
        for (i=s+1; i<=d; i++)
        {
          if (x[i] <= pivot)
            c++;
        }
        // poziti pivotului este s+c
        // aduce pivotul pe pozitia corecta prin interschimbare cu pozitia s
        aux=x[s]; x[s]=x[s+c]; x[s+c]=aux;
        // separa in subsiruri
        i=s;
        j=d;
        // partitionare sir
        while (i<j)
        {
            while (x[i]<pivot) i++;
            while (x[j]>=pivot) j--;
            if (i<j)
            {
                //schimba x[i] cu x[j]
                aux=x[i]; x[i]=x[j]; x[j]=aux;
                if (i<d) i++;
                if (j>s) j--;
            }
        }// end while
            cout<<"i = "<<i<<endl;
            cout<<"j = "<<j<<endl;
            cout<<"Sub sirul: ";
            for(int k=s;k<=d;k++ )
            {
              cout<<x[k]<<" ";
            }
            cout<<endl;
            //elemnetele x[i],...x[i-1] sunt <= cu x[i]
            for(int k=s; k<i; k++)
                cout<<x[k]<<"  ";
            cout<<"< "<<x[i]<<" >= ";
            //elementele x[i+1],...x[d] sunt >= cu x[i]
            for(int k=i+1; k<=d; k++)
                cout<<x[k]<<"  ";
            cout<<endl;
            cout<<" ++++++++++ "<<endl;
            QuickSort(s,s+c-1,x,n);
            QuickSort(s+c+1,d,x,n);
    }
}
void merge_sort(int s,int d,float x[]){
    int m;
    if(s<d){
        m=(s+d)/2;
        merge_sort(s,m,x);
        merge_sort(m+1,d,x);
        interclasare(s,m,d,x);
    }
    }


void countingsort(){
    int n;
    int v[100];
    cout<<"Introduceti numarul de valori"<<endl;;cin>>n;
    cout<<"Introduceti valorile"<<endl;
    for(int i=0;i<n;i++)
        cin>>v[i];
    int aux[100];
    int y[100];
    for(int i=0;i<n;i++) //initializam cu 0
        aux[i]=0;
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(v[i]<=v[j])
                aux[j]++;
            else
                aux[i]++;
    for(int j=0;j<n;j++)
        y[aux[j]]=v[j];
    for(int i=0;i<n;i++)
        cout<<y[i]<<" ";




}
void selectionsort(){
    int i, j, mini,x;
    int v[100],n;
    cout<<"Introduceti numarul de valori"<<endl;
    cin>>n;
    cout<<"Introduceti valorile pentru sortare"<<endl;
    for(int i=0;i<n;i++)
            cin>>v[i];
    for (i = 0; i < n-1; i++)
    {
        mini = i;
        for (j = i+1; j < n; j++){
            if(v[mini]>v[j])
                mini=j;
        }
         if(i!=mini){
                x=v[i];
                v[i]=v[mini];
                v[mini]=x;
            }

        }


    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
}
void bubblesort(){
    int v[100],n,x;
    cout<<"Introduceti numarul de valori"<<endl;
    cin>>n;
    cout<<"Introduceti valorile pentru sortare"<<endl;
    for(int i=0;i<n;i++)
            cin>>v[i];
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(v[i]>v[j]){
                x=v[i];
                v[i]=v[j];
                v[j]=x;
        }
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";


}
void ec_grad_2(){
float a,b,c,d,x1,x2;
    cout<<"a=";cin>>a;
    cout<<"b=";cin>>b;
    cout<<"c=";cin>>c;
    if(a==0)
            cout<<"Nu este ec de gradul 2";
    else{
    if(a!=0)
     {
        d=b*b-4*a*c;

    if(d>0)
         {
          x1=(-b+sqrt(d))/(2*a);
          x2=(-b-sqrt(d))/(2*a);
          cout<<"x1="<<x1<<endl;
          cout<<"x2="<<x2<<endl;
         }
    if(d==0){
        x1=-b/2*a;
        cout<<"x1,2= "<<x1<<endl;
    }
    if(d<0){
            float r,im;
            r=-b/(2*a);
            im=sqrt(-d)/(2*a);
            cout<<"x1="<<r<<"+i*"<<im<<endl;
            cout<<"x2="<<r<<"-i*"<<im<<endl;


    }
     }


    }
}
void inmultire_matrice(int n,int m,int p,int r,float A[10][10],float B[10][10])
{
    float C[10][10]={0};
    int i,j,k;

    if (m!=p)
        cout<<"Nu se pot inmulti A si B\n";
    else
    {
        for(i=0; i<n; i++)
            for(j=0; j<r; j++)
            {
                C[i][j]=0;
                for(k=0; k<m; k++)
                    C[i][j]+=A[i][k]*B[k][j];
            }
         cout<<"Afisam matricea produs C = \n";
         for(i=0; i<n; i++)
           {
            for(j=0; j<r; j++)
               cout<<C[i][j]<<"  ";
            cout<<endl;
           }
    }
}

bool numar_prim(int m)
{
    //verifica daca m este numar prim

    for(int i=2; i<=m/2; i++)
    {
        if (m % i ==0) return false;
    }
    return true;
}
void divizori(int n){
    int m=n,k=0,dd=2,p;
    int d[100],e[100];
    while(m>1){
        p=0;
        while(m%dd==0){
            p++;
            m=m/dd;
        }
        if(p>0){
            d[k]=dd;
            e[k]=p;
            k++;
        }
        dd++;

    }
    cout<<"n=";
    for(int i=0;i<k;i++){
        cout<<d[i]<<"^"<<e[i];
        if(i<k-1)
            cout<<"*";
    }
}

// functii pentru liste dublu inlantuite

lista2 *creare_lista2()
{
    lista2 *L2;
    numar2 *pr, *ul, *c;
    int x, N;
    cout<<"creare lista!"<<endl;
    // creare capate lista:prim si ultim elemnt
    cout<<"Valoare cap lista x = "; cin>>x;
    pr=new numar2; // primul element din lista
    ul=new numar2;
    pr->v=x;
    pr->prec=NULL;
    pr->urm=NULL;
    ul=pr; // ultimul element din lista
    L2=new lista2;
    L2->prim=pr;
    L2->ultim=ul;
    cout<<"Numarul de elemente care se adauga in lista la cearea listei N = "; cin>>N;
    for(int i=1; i<=N; i++)
    {
        cout<<"Valoare de adaugat in lista x = "; cin>>x;
        c=new numar2;
        c->v=x;
        c->prec=ul;
        c->urm=NULL;
        ul->urm=c; // stabileste legatura intre ultimul elemnt si noul element adaugat
        ul=c; // c devine ultimul element
    }
    L2->ultim=ul;
    return L2;
}

void parcurgere_lista_direct(numar2 *pr)
{
    numar2 *c;
    if (pr == NULL)
        cout<<"Lista este vida!"<<endl;
    else
    {
        c=pr;
        while (c != NULL)
        {
            cout<<c->v<<" ";
            c=c->urm;
        }
    }
}

void parcurgere_lista_invers(numar2 *ul)
{
    numar2 *c;
    if (ul == NULL)
        cout<<"Lista este vida!"<<endl;
    else
    {
        c=ul;
        while (c != NULL)
        {
            cout<<c->v<<" ";
            c=c->prec;
        }
    }
}

 lista2 *adaugare_in_lista2(lista2 *L2,int a)
{
    int opa;
    numar2 *p, *pr, *ul;

    pr=L2->prim;
    ul=L2->ultim;
    do
    {
        cout<<endl<<"Tip adaugare:"<<endl;
        cout<<"1. Adaugare la inceput de lista dublu inlantuita:"<<endl;
        cout<<"2. Adaugare dupa element din interiorul listei:"<<endl;
        cout<<"3. Adaugare la sfarsitul listei:"<<endl;
        cout<<"0. Incheiere adaugare!"<<endl;
        cout<<"Optiune adaugare: "; cin>>opa;
        switch (opa)
        {
       case 1: // adauga la inceput
           p=new numar2;
           p->v=a;
           p->prec=NULL;
           p->urm=pr;
           pr->prec=p;
           pr=p;
           parcurgere_lista_direct(pr);
           cout<<endl;
        break;
       case 2: // adauga dupa element cu valoare data din lista
           // citim valoarea dupa care se adauga
           int y;
           numar2 *c; // c - elementul curent din lista
           cout<<"Valoare dupa care se face adaugarea y = "; cin>>y;
           c=pr;
           while (c!= NULL)
           {
               if (c->v == y)
               {
                   // adauga valoare a dupa y
                   if (c->urm == NULL) // c este ultimul element din lista
                   {
                       p=new numar2;
                       p->v=a;
                       p->prec=c;
                       p->urm=NULL;
                       c->urm=p;
                       c=c->urm;
                       // se modifica ultimul element
                       ul=p;
                   }
                   else // c se afla in interiorul listei
                   {
                       p=new numar2;
                       p->v=a;
                       p->prec=c;
                       p->urm=c->urm;
                       (c->urm)->prec=p;
                       c->urm=p;
                       c=c->urm;
                   }
               }
               c=c->urm;
           }// end while *c
           parcurgere_lista_direct(pr);
           cout<<endl;
        break;
       case 3: // adauga la sfarsitul la listei
            p=new numar2;
            p->v=a;
            p->prec=ul;
            p->urm=NULL;
            ul->urm=p;
            ul=p;
            parcurgere_lista_direct(pr);
            cout<<endl;
        break;
       case 0:
        cout<<"incheiat adaugare!"<<endl;
        break;
       default:
        cout<<"Optiune invalida!"<<endl;
        break;
        }// end switch
    }while(opa);
    L2->prim=pr;
    L2->ultim=ul;
    return L2;
}

lista2 *stergere_din_lista2(lista2 *L2)
{
    int cont=0; //indicator de continuare sau nu stergere
    int s; // s = valoarea care se sterge din lista

    numar2 *c;

    do
    {
        if (L2->prim == NULL)
            cout<<"Lista este vida! Nu sunt valori de sters!"<<endl;
        else
        {
            //sterge elementul cu valoarea s de cate ori apare in lista
            cout<<"Valoare de sters s = ";
            cin>>s;
            int nrs=0; // numara de cate ori am sters s din lista
            // stergem valoarea s daca se afla la inceput la lista
            while ((L2->prim)->v == s)
            {
                ((L2->prim)->urm)->prec=NULL;
                L2->prim=(L2->prim)->urm;
                nrs++;
                if (L2->prim == NULL)
                    break;
            }
            if (L2->prim !=NULL)
            {
                c=(L2->prim)->urm;
                //p=cap; // precedentul elementului curent c
                while (c!=NULL)
                {
                    if (c->v == s)
                    {
                        // sterge din lista pe c
                        (c->prec)->urm=c->urm;
                        if ((c->urm) == NULL) // c este ultimul element si va fi sters
                          {
                            // se schimba ultimul element din lista
                           L2->ultim=c->prec;
                          }
                          else
                            (c->urm)->prec=c->prec;
                        nrs++;
                        c=c->urm;
                    }
                    else
                    {
                        //p=c;
                        c=c->urm;
                    }
                }
            }
            cout<<"Elementul de sters "<<s<<" a fost sters de "<<nrs<<" ori"<<endl;
            cout<<"Lista ramasa este: "<<endl;;
            parcurgere_lista_direct(L2->prim);
            cout<<endl;
            parcurgere_lista_invers(L2->ultim);
            cout<<endl;
        }
        cout<<"Continua stergerea [0/1]? ";
        cin>>cont;
    }
    while (cont);
    return L2;
}

lista2 *modificare_in_lista2(lista2 *L2, int y, int w)
{
    numar2 *c;
    for(c=L2->prim; c!=NULL; c=c->urm)
    {
        if (c->v == y)
            c->v=w;
    }
    return L2;
}


// FUNCTII PENTRU STIVE

numar *creare_stiva()
{
    numar *cap, *c;
    int x, n;
    cout<<"creare stiva!"<<endl;
    // creare capat stiva
    cout<<"Valoare cap stiva x = "; cin>>x;
    cap=new numar;
    cap->v=x;
    cap->urm=NULL;

    cout<<"Numarul de elemente care se adauga in stiva la cearea listei n = "; cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout<<"Valoare de adaugat in lista x = "; cin>>x;
        c=new numar;
        c->v=x;
        c->urm=cap;
       cap=c; // noul capat al stivei
    }
    return cap;
}

void parcurgere_stiva(numar *cap)
{
    numar *c;
    if (cap == NULL)
        cout<<"Stiva este vida!"<<endl;
    else
    {
        c=cap;
        while (c != NULL)
        {
            cout<<c->v<<endl;
            c=c->urm;
        }
    }

}

numar *stergere_din_stiva(numar *cap)
{
    cap=cap->urm;
    return cap;
}

numar *adaugare_in_stiva(numar *cap, int a)
{
    numar *c;
    c=new numar;
    c->v=a;
    c->urm=cap;
    cap=c; // noul capat al stivei
    return cap;
}

// FUNCTII PENTRU COZI

lista2 *adaugare_in_lista2_coada(lista2 *L2)
{
    int opa;
    numar2 *p, *pr, *ul;
    int ad;

    pr=L2->prim;
    ul=L2->ultim;
    do
    {
        cout<<"citeste valoare de adaugat: "; cin>>ad;
        // adauga la sfarsitul cozii
        p=new numar2;
        p->v=ad;
        p->prec=ul;
        p->urm=NULL;
        ul->urm=p;
        ul=p;
        parcurgere_lista_direct(pr);
        cout<<endl;
        cout<<endl<<"Continua adaugare [0/1]?"; cin>>opa;
    }while(opa);
    L2->prim=pr;
    L2->ultim=ul;
    return L2;
}

lista2 *stergere_din_lista2_coada(lista2 *L2)
{
    int cont=0; //indicator de continuare sau nu stergere

    do
    {
        if (L2->prim == NULL)
            cout<<"Coada este vida! Nu sunt valori de sters!"<<endl;
        else
        {
            //sterge prima valoare din coada

            if ((L2->prim)->urm != NULL)
               {
                   ((L2->prim)->urm)->prec=NULL;
               }
             parcurgere_lista_direct(L2->prim);
             cout<<endl;
             L2->prim=(L2->prim)->urm;
        }
        cout<<"Continua stergerea [0/1]? ";
        cin>>cont;
    }while (cont);
    return L2;
}
// functii pentru polinoame

monom *citeste_polinom()
{
    monom *p, *u, *m;
    int g;
    float c;
    int n;
    // creare capat polinom
    cout<<"Grad primul monom g= "; cin>>g;
    cout<<"Coeficientul primului monom c= "; cin>>c;
    p=new monom;
    p->grad=g;
    p->coef=c;
    p->urm=NULL;
    u=p; // ultimul element din polinom
    cout<<"Numarul de monoame ale polinomului = "; cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout<<"Grad monom g= "; cin>>g;
        cout<<"Coeficient monom c= "; cin>>c;
        m=new monom;
        m->grad=g;
        m->coef=c;
        m->urm=NULL;
        u->urm=m; // stabileste legatura intre ultimul monom si noul monom adaugat
        u=m; // c devine ultimul element
    }
    return p;
}

void  afisare_polinom(monom *p)
{
    monom *m;

    if (p==NULL)
        cout<<"Nu exista polinomul!"<<endl;
    else
    {
        m=p;
        while (m !=NULL)
        {
            if (m->coef >=0)
                cout<<"+"<<m->coef<<"*X^"<<m->grad;
            else
                cout<<m->coef<<"*X^"<<m->grad;
            m=m->urm;
        }
    }
    cout<<endl;
    cout<<" a terminat afisarea "<<endl;
}
// adunarea polinoamelor

monom *reducere_termeni(monom *s)
{
     monom *c, *c1, *r1;

    cout<<endl<<"s la inceput = ";
    afisare_polinom(s);
    cout<<endl;
    if (s != NULL)
    {
        c=s;
        while (c->urm != NULL)
        {
            // compara gradul lui c cu gradul monoamelor urmatoare
            c1=c->urm; // c1 parcurge monomele urmatoare dupa c
            r1=c; // r1 = monomul precedent lui c1
            while (c1 != NULL)
            {
                if ((c->grad ) == (c1->grad))
                {
                    // aduna coeficientul din c1 la coeficientul lui c
                    c->coef=c->coef + c1->coef;
                    // stergem c1 din lista s
                    r1->urm=c1->urm;
                    c1=c1->urm;
                }
                else
                {
                    r1=c1;
                    c1=c1->urm;
                }
            }
            cout<<endl<<"s = ";
            afisare_polinom(s);
            cout<<endl;
            c=c->urm;
            if (c == NULL)
                break;
        }
    }
    return s;
}

 monom *aduna_polinoame(monom *p1, monom *p2)
 {
     monom *s, *c, *r, *u, *sr;

     // initializam lista monom suma
     s=new monom;
     s->grad=p1->grad;
     s->coef=p1->coef;
     s->urm=NULL;
     u=s;// ultimul element aduagt in suma s

     // adaugam pe p1 in s
     c=p1->urm;
     while (c!=NULL)
     {
         r= new monom;
         r->grad=c->grad;
         r->coef=c->coef;
         r->urm=NULL;
         u->urm=r;
         u=r;
         c=c->urm;
     }
    // adaugam pe p2 in s
     c=p2;
     while (c!=NULL)
     {
         r= new monom;
         r->grad=c->grad;
         r->coef=c->coef;
         r->urm=NULL;
         u->urm=r;
         u=r;
         c=c->urm;
     }
     cout<<endl<<"s = ";
     afisare_polinom(s);
     cout<<endl;
     // reducerea termenilor asemenea
     sr=reducere_termeni(s);
     return sr;
 }

numar *creare_lista_ordonata()
{
    numar *cap, *u, *c, *p, *r;
    int x, n;
    cout<<"Creare lista ordonata!"<<endl;
    // creare capat lista
    cout<<"Valoare cap initial lista x = "; cin>>x;
    cap=new numar;
    cap->v=x;
    cap->urm=NULL;
    u=cap; // ultimul element din lista
    cout<<"Numarul de elemente care se adauga in lista la cearea listei ordonate n = "; cin>>n;
    for(int i=1; i<=n; i++)
    {
        cout<<"Valoare de adaugat in lista ordonata x = "; cin>>x;
        c=new numar;
        c->v=x;
        c->urm=NULL;
        // daca x este mai mic decat capatul listei
        if (x < cap->v)
        {
            c->urm=cap;
            cap=c;
        }
        else
        {
            if (x>=u->v) // se adauga dupa ultimul element
            {
                u->urm=c;
                u=c;
            }
            else // se adauga in interiorul listei
            {
                p=cap;  //precedentul elementului curent
                r=cap->urm; // elementul curent
                while (x > r->v)
                  {
                      p=r;
                      r=r->urm;
                  }
                 // insereaza valoare x intre p->v si r->v
                 c->urm=r;
                 p->urm=c;
            }
        }
        parcurgere_lista(cap);
        cout<<endl;
    }
    return cap;
}


int main()
{
    //declaratii de variabile
    int op, op1, op2,op3,m,p,r;
    int n;
    bool ok;
    float A[10][10], B[10][10];

    do
    {
       cout<<"\n Program ASD - subgrupa 1332A\n";
       cout<<"1. Probleme simple "<<endl;
       cout<<"2. Algoritmi de sortare"<<endl;
        cout<<"3. Liste dinamice"<<endl;

       // se vor adauga alte capitole

       cout<<"0. Incheiere program! "<<endl;

       cout<<"Citeste optiune: "; cin>>op;
       switch (op)
       {
           case 1:
              {
           do
           {
            cout<<"\n Capitolul 1. Probleme simple\n";
            cout<<"           1.1. Rezolvare completa ecuatie de gradul al doilea"<<endl;
            cout<<"           1.2. Inmultirea a doua matrice"<<endl;
            cout<<"           1.3. Verificare numar prim"<<endl;
            cout<<"           1.4. Descompunere in factori primi"<<endl;

            cout<<"           1.0. Incheiere capitol 1!"<<endl;

            cout<<"  Citeste optiune capitol 1: "; cin>>op1;
            switch (op1)
            {
            case 1:
                {
                    cout<<"\n Ecuatia de gradul al doilea \n";
                    ec_grad_2();
                    break;
                }
            case 2:
                {
                    cout<<" Inmultirea a doua matrice\n";
                    cout<<"Numar de linii pentru matricea A n = "; cin>>n;
                    cout<<"Numar de coloane pentru matricea A m = "; cin>>m;
                    cout<<"Citeste matricea A:\n";
                    for(int i=0; i<n; i++)
                        for(int j=0; j<m; j++)
                          cin>>A[i][j];
                    cout<<"Numar de linii pentru matricea B p = "; cin>>p;
                    cout<<"Numar de coloane pentru matricea B r = "; cin>>r;
                    cout<<"Citeste matricea B:\n";
                    for(int i=0; i<p; i++)
                        for(int j=0; j<r; j++)
                          cin>>B[i][j];
                    inmultire_matrice(n,m,p,r,A,B);
                    break;

                    break;
                }
            case 3:
                {
                    cout<<"Verificare numar prim\n";
                    cout<<"Numarul  n = "; cin>>n;
                    ok=numar_prim(n);
                    if (ok)
                        cout<<"Numarul "<<n<<" este prim\n";
                    else
                        cout<<"Numarul "<<n<<" nu este prim\n";
                    break;
                }
            case 4:
                {
                    cout<<"Introduceti numarul"<<endl;cin>>n;
                    divizori(n);
                    break;
                }
            case 0:
                cout<<"Incheiere capitol 1!\n";
                break;
            default:
                cout<<"Optiune invalida!\n";
                break;
            }//end switch capitol 1
          }while(op1); //end while capitol 1
            break;
        }

           case 2:
          {
           do
           {
            cout<<"\n Capitolul 2. Algoritmi de sortare\n";
            cout<<"           2.1. Bubble sort "<<endl;
            cout<<"           2.2. Selection sort"<<endl;
            cout<<"           2.3. Counting sort"<<endl;
            cout<<"           2.4. Merge sort  "<<endl;
            cout<<"           2.5. Quicksort   "<<endl;
            cout<<"           2.6. Sortarea prin insertie   "<<endl;
            cout<<"           2.7. Shell sort  "<<endl;
            cout<<"           2.8. Radix sort  "<<endl;
            cout<<"           2.9. Cautare secventiala"<<endl;
            cout<<"           2.10. Cautare binara"<<endl;
            cout<<"           2.0. Incheiere capitol 2!"<<endl;

            cout<<"  Citeste optiune capitol 2: "; cin>>op2;
            switch (op2)
            {
                case 1:{
                    bubblesort();
                    break;
                }
                case 2:{
                    selectionsort();
                    break;
                    }
                case 3:{
                    countingsort();
                    break;
                    }
                case 4:{
                    cout<<"introduceti numarul de valori "; cin>>n;
                    cout<<"introduceti valorile vectorului"<<endl;
                    float v[100];
                    int s=0;
                    int d=n-1;
                    for(int i=0;i<n;i++)
                        cin>>v[i];

                    merge_sort(s,d,v);
                    for(int i=0;i<n;i++)
                        cout<<v[i]<<" ";
                    break;
                }
                case 5:{
                    cout<<"introduceti numarul de valori "; cin>>n;
                    cout<<"introduceti valorile vectorului"<<endl;
                    float v[100];
                    int s=0;
                    int d=n-1;
                    for(int i=0;i<n;i++)
                        cin>>v[i];
                    QuickSort(s,d,v,n);
                    for(int i=0;i<n;i++)
                        cout<<v[i]<<" ";
                    break;
                }
                case 6:{
                    insertionsort();
                break;}
                case 7:{
                    shellsort();

                break;}
                case 8:{
                cout<<"Introduceti numarul de valori"<<endl;cin>>n;
                int v[n];
                cout<<"Introduceti valorile"<<endl;
                for(int i=0;i<n;i++)
                    cin>>v[i];
                radix_sort(n,v);
                break;
                }
                case 9:{

                break;}

                case 10:{
                    int y;
                    cout<<"introduceti numarul de valori "; cin>>n;
                    cout<<"introduceti valorile vectorului"<<endl;
                    float v[100];
                    int s=0;
                    int d=n-1;
                    for(int i=0;i<n;i++)
                        cin>>v[i];
                    cout<<"Introduceti valoarea cautata ";cin>>y;
                    merge_sort(s,d,v);
                    if(y<x[0]||y>x[n-1])
                        cout<<" Valoarea cautata nu se afla in sir";
                    else
                        cautare_binara(s,d,v,y);

                }
            }//end switch capitol 2
           }while(op2); //end while capitol 2
            break;
          }


            // vor veni case -uri pentru celelalte capitole
            case 3:{
                do
           {
             cout<<"LISTE DINAMICE"<<endl;
             cout<<"   3.1. Liste simplu inlantuite"<<endl;
             cout<<"   3.2. Liste dublu inlantuite"<<endl;
             cout<<"   3.3. Stive"<<endl;
             cout<<"   3.4. Cozi"<<endl;
             cout<<"   3.5. Creare unei liste de numere intregi ordonate (din citire)"<<endl;
             cout<<"   3.6. Interclasarea a doua 2 liste de numere intregi ordonate"<<endl;
             cout<<"   3.7. Adunarea polinoamelor cu liste dinamice"<<endl;
             cout<<"   3.8. Inmultirea polinoamelor cu liste dinamice"<<endl;
             cout<<"   3.9. Verificarea corectitudinii parantezelor intr-o expresie aritmetica, cu stive"<<endl;
             cout<<"   3.0. Exit capitol 3!"<<endl;
             // mai adaugam  aplicatii

             cout<<"Optiune capitol 3: "; cin>>op3;
             switch (op3)
             {
             case 1: //liste simplu inlantuite
                {
                numar *lista;

                // creare lista
                lista=creare_lista();
                cout<<"Lista dupa creare este: ";
                parcurgere_lista(lista);
                cout<<endl;
                // stergere din lista
                lista=stergere_din_lista(lista);
                cout<<"Lista dupa stergere este: ";
                parcurgere_lista(lista);
                cout<<endl;
                // adaugare in lista
                int ad;
                cout<<"citeste valoare de adaugat: "; cin>>ad;
                lista=adaugare_in_lista(lista,ad);
                cout<<"Lista dupa adaugare este: ";
                parcurgere_lista(lista);
                cout<<endl;
                // modificare element in lista
                int y,w;
                cout<<"Modificare a elementului y = "; cin>>y;
                cout<<"cu valoarea w = ";cin>>w;
                lista=modificare_in_lista(lista,y,w);
                cout<<"Lista dupa modificare este: ";
                parcurgere_lista(lista);
                cout<<endl;
                break;
                }

              case 2: // liste dublu inlantuite
               {
                lista2 *L; // contine adresele primului si ultimului element din lista
                //numar2 *p, *u, *c; // p = primul element din lista
                                   // u = ultimul elemnt din lista
                                   // c = elementul curent din lista


                // creare lista dublu inlantuita
                L=creare_lista2();
                cout<<"Lista dupa creare este: "<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(L->prim);
                cout<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(L->ultim);
                cout<<endl<<endl;

                // adaugare in lista dublu inlantuita
                int ad;
                cout<<"citeste valoare de adaugat: "; cin>>ad;
                L=adaugare_in_lista2(L,ad);
                cout<<"Lista dupa adaugare este: "<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(L->prim);
                cout<<endl<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(L->ultim);
                cout<<endl;
                cout<<endl;

                // stergere din lista dublu inlantuita
                L=stergere_din_lista2(L);
                cout<<"Lista dubla dupa stergere este: ";
                cout<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(L->prim);
                cout<<endl<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(L->ultim);
                cout<<endl<<endl;

                // modificare element in lista
                int y,w;
                cout<<"Modificare a elementului y = "; cin>>y;
                cout<<"cu valoarea w = ";cin>>w;
                L=modificare_in_lista2(L,y,w);
                cout<<"Lista dupa modificare este: ";
                cout<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(L->prim);
                cout<<endl<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(L->ultim);
                cout<<endl<<endl;
                break;
               }

              case 3: //stive
             {
                 numar *stiva;

                // creare stiva
                stiva=creare_stiva();
                cout<<"Stiva dupa creare este: "<<endl;
                parcurgere_stiva(stiva);
                cout<<endl;
                // stergere din stiva
                stiva=stergere_din_stiva(stiva);
                cout<<"Stiva dupa stergere este: "<<endl;
                parcurgere_stiva(stiva);
                cout<<endl;
                // adaugare in stiva
                int ad;
                cout<<"citeste valoare de adaugat: "; cin>>ad;
                stiva=adaugare_in_stiva(stiva,ad);
                cout<<"Stiva dupa adaugare este: "<<endl;
                parcurgere_stiva(stiva);
                cout<<endl;
                 break;
             }
              case 4: // cozi
                {
                lista2 *C; // contine adresele primului si ultimului element din lista

                // creare coada ca lista dublu inlantuita
                C=creare_lista2();
                cout<<"Coada dupa creare este: "<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(C->prim);
                cout<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(C->ultim);
                cout<<endl<<endl;

                // adaugare in coada

                C=adaugare_in_lista2_coada(C);
                cout<<"Coada dupa adaugare este: "<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(C->prim);
                cout<<endl<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(C->ultim);
                cout<<endl;
                cout<<endl;

                // stergere din lista dublu inlantuita
                C=stergere_din_lista2_coada(C);
                cout<<"Coada dupa stergere este: ";
                cout<<endl;
                cout<<"direct: ";
                parcurgere_lista_direct(C->prim);
                cout<<endl<<endl;
                cout<<"invers: ";
                parcurgere_lista_invers(C->ultim);
                cout<<endl<<endl;
                    break;
                }

              case 5: // creare unei liste ordonata din citire
                {
                    numar *lo;
                    lo=creare_lista_ordonata();
                    cout<<"Lista creata ordonat este: ";
                    parcurgere_lista(lo);
                    cout<<endl;
                    break;
                }
              case 6: // interclasarea a doua liste ordonate

                break;

              case 7: // adunarea a doua polinoame
                  monom *p1, *p2, *p;
                  cout<<"citeste primul polinom p1:"<<endl;
                  p1=citeste_polinom();
                  cout<<endl<<"p1 = ";
                  afisare_polinom(p1);
                  cout<<endl;
                  cout<<"citeste al doilea polinom p2:"<<endl;
                  p2=citeste_polinom();
                  cout<<endl<<"p2 = ";
                  afisare_polinom(p2);
                  cout<<endl;
                  p=aduna_polinoame(p1,p2);
                  cout<<endl<<" suma = ";
                  afisare_polinom(p);
                  cout<<endl;
                break;


              case 0:
                {
                    cout<<"Terminat capitol 3!"<<endl;
                    break;
                }
              default:
                {
                    cout<<"Optiune invalida capitol 3!"<<endl;
                    break;
                }
             }// end swicth op3
           }while(op3); // end do - while cap3
           break;
            }

           case 0:
               {
                  cout<<"Bye! Bye!"<<endl;
                  break;
               }
           default:
            {
                cout<<"Optiunea aleasa nu e valida!"<<endl;
                break;
            }




       }// end switch meniu principal
    }while(op!=0);
    return 0;
}