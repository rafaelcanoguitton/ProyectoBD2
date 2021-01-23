// Proyecto Final Base de Datos II.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include "AVL.h"
//#include<Windows.h>
//#include <conio.h>
#include <stdio.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
bool globalTrue=true;
vector<BST<int,TipoInt>> indexes;
vector<BST<string,TipoString>> indexes2;//
void login()
{
    string pass = "";
    char ch;
    cout << "\n\n\n\n\t\t\t\t\t     SanPabloDB";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\tIngrese la contrase�a: ";
    ch = getchar();
    while (ch != 13) {//character 13 es enter
        pass.push_back(ch);
        cout << '*';
        ch = getchar();
    }
    if (pass == "basededatos") {
        cout << "\n\n\t\t\t\t\tContrase�a correcta! \n";
    }
    else {
        cout << "\n\n\t\t\t\t\tContrase�a incorrecta, intentelo de nuevo. \n";
        ch = getchar();
        std::cout << "\x1B[2J\x1B[H";
        login();
    }
    getchar();
    std::cout << "\x1B[2J\x1B[H";
}
void crear_indice(vector<string> &result)
{
    string nombre= result[2];
    string tabla= result[4];
    string columna= result[5];
    string tipo;
    ofstream fay;
    fay.open("METADATA_I.txt",ofstream::app);
    fay<< tabla<< " "<<nombre<< " ";
    ifstream file(tabla + ".rafa");
    if (!file.is_open())
    {
        cout << "Tabla no existe: " << endl;return;
    }
    string linea;
    getline(file,linea);
    vector<string>pl;
    istringstream iss3(linea);
    for(string opt;iss3>>opt;)
    {
        pl.push_back(opt);
    }
    int identificador=0;
    bool found=false;
    for(int i=0;i<pl.size();i++)
    {
        if(pl[i]==columna)
        {
            identificador=i;
            found=true;
        }
    }
    getline(file,linea);
    vector<string>pl2;
    istringstream iss4(linea);
    for(string opt;iss4>>opt;)
    {
        pl2.push_back(opt);
    }
    tipo=pl2[identificador];
    if(tipo=="int")
    {
        fay<<indexes.size()<<" "<<tipo<<" "<<columna<<endl;
    }
    else if(tipo=="string")
    {
        fay<<indexes2.size()<<" "<<tipo<<" "<<columna<<endl;
    }
    fay.close();
    if(found)
    {
        if(tipo=="int")
        {
            BST<int,TipoInt> trisito;   
            int next=file.tellg();
            while(getline(file,linea))
            {
                vector<string> cc;
                istringstream iss2(linea);
                for(string opt;iss2>>opt;)
                {
                    cc.push_back(opt);
                }
                int testerino;
                stringstream x(cc[identificador]);
                x>>testerino;
                trisito.insert(testerino,next);
                next=file.tellg();
            }
            indexes.push_back(trisito);
            trisito.fill(nombre);
        }
        else if(tipo=="string")
        {
            BST<string,TipoString> trisito;   
            int next=file.tellg();
            while(getline(file,linea))
            {
                vector<string> cc;
                istringstream iss2(linea);
                for(string opt;iss2>>opt;)
                {
                    cc.push_back(opt);
                }
                trisito.insert(cc[identificador],next);
                next=file.tellg();
            }
            indexes2.push_back(trisito);
            trisito.fill(nombre);
        }
    }
    else
    {
        cout<<"Columna no encontrada"<<endl;
    }
}
void selecti(string tabla,string tipo,int identificador,string valor)
{
    auto start = high_resolution_clock::now();
    if(tipo=="int")
    {
        string id=valor;
        string tree="0";
        stringstream a(id);
        stringstream b(tree);
        int idi;
        a >> idi;
        vector<int> dir=indexes[identificador].searchRegi(idi);
        ifstream file2(tabla+".rafa",ios::in);
        for(int f=0;f<dir.size();f++)
        {
            file2.seekg(dir[f]);
            string aux="";
            getline(file2,aux);
            cout<<aux<<endl;

        }
        file2.close();
    }
    else if(tipo=="string")
    {
        ;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Tiempo de ejecucion: "
         << duration.count() << " microsegundos" << endl;
}
void select(vector<string> &result)
{
    auto start = high_resolution_clock::now();
    if (result[1] == "*" && result[2] == "desde")
    {
        if (result.size() > 4)
        {
            if (result[4] == "donde")
            {
                string columna = result[5];
                string tabla = result[3];
                string valor = result[7];
                ifstream myfile(tabla + ".rafa");
                string linea;
                ifstream file("METADATA_I.txt",ios::in);
                string x;
                while(getline(file,x))
                {
                    vector<string>ce;
                    istringstream issu(x);
                    for(string opt;issu>>opt;)
                    {
                        ce.push_back(opt);
                    }
                    if(ce[0]==tabla)
                    {
                        if(ce[4]==columna)
                        {
                            stringstream geek(ce[2]); 
                            int geek1 = 0; 
                            geek >> geek1; 
                            selecti(tabla,ce[3],geek1,valor);
                            return;
                        }
                    }
                }
                if (myfile.is_open())
                {
                    getline(myfile, linea);
                    vector<string> cc;
                    istringstream iss(linea);
                    for (string opt; iss >> opt; )
                        cc.push_back(opt);
                    int pa = 0;
                    for (int i = 0; i < cc.size(); i++)
                    {
                        if (cc[i] == columna)
                        {
                            pa = i;
                            i = 100;
                        }
                    }
                    for (int i = 0; i < cc.size(); i++)
                    {
                        cout << cc[i] + '\t';
                    }
                    cout << endl << endl;
                    getline(myfile, linea);
                    while (getline(myfile, linea))
                    {
                        vector<string> result1;
                        istringstream iss2(linea);
                        for (string opt; iss2 >> opt; )
                            result1.push_back(opt);
                        if (result1[pa] == valor)
                        {
                            for (int i = 0; i < result1.size(); i++)
                                cout << result1[i] + '\t' + '\t';
                            cout << endl;
                        }
                    }
                }
            }
            else
                cout << "Sintaxis incorrecta" << endl;
        }
        else
        {
            string tabla = result[3];
            ifstream myfile(tabla + ".rafa");
            string linea;
            if (myfile.is_open())
            {
                getline(myfile, linea);
                vector<string> result0;
                istringstream iss(linea);
                for (string opt; iss >> opt; )
                    result0.push_back(opt);
                for (int i = 0; i < result0.size(); i++)
                    cout << result0[i] + '\t';
                cout << endl << endl;
                getline(myfile, linea);
                while (getline(myfile, linea))
                {
                    vector<string> result1;
                    istringstream iss2(linea);
                    for (string opt; iss2 >> opt; )
                        result1.push_back(opt);
                    for (int i = 0; i < result1.size(); i++)
                        cout << result1[i] + '\t' + '\t';
                    cout << endl;
                }

            }
            else
            {
                cout << "Tabla no existe: " << endl;
            }
        }

    }
    else
    {
        cout << "Sintaxis incorrecta: ";
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Tiempo de ejecucion: "
         << duration.count() << " microsegundos" << endl; 
}
void insert(vector<string> &result)
{
    string nombre_tabla = result[1];
    string clean = "";
    for (int i = 2; i < result.size(); i++)
        clean += result[i];
    vector<string> columnas;
    string aux2 = "";
    if (clean[0] == '(' && clean[clean.length() - 1] == ')')
    {
        for (int i = 1; i < clean.length(); i++)
        {
            if (clean[i] == ';')
            {
                cout << "Sintaxis Incorrecta!!" << endl; break;
            }
            if (clean[i] != ',' && clean[i] != ')')
            {
                aux2 += clean[i];
            }
            else if (clean[i] == ',' || clean[i] == ')')
            {
                columnas.push_back(aux2);
                aux2 = "";
            }
        }
    }
    ifstream myfile(nombre_tabla + ".rafa");
    string linea;
    if (myfile.is_open())
    {
        getline(myfile, linea);
        vector <string>noms;
        istringstream lawl(linea);
        for(string opt; lawl>>opt;)
            noms.push_back(opt);
        getline(myfile, linea);
        myfile.close();
        vector<string> tipos;
        istringstream iss(linea);
        for (string opt; iss >> opt; )
            tipos.push_back(opt);
        ofstream Tabla(nombre_tabla + ".rafa", ios::app);
        if (columnas.size() == tipos.size())
        {
            for (int i = 0; i < columnas.size(); i++)
            {
                if (tipos[i] == "string")
                {
                    if (columnas[i][0] == 39)
                    {
                        ifstream file("METADATA_I.txt",ios::in);
                        string x;
                        while(getline(file,x))
                        {
                            vector<string>ce;
                            istringstream issu(x);
                            for(string opt;issu>>opt;)
                            {
                                ce.push_back(opt);
                            }
                            if(ce[0]==nombre_tabla)
                            {
                                int identificador;
                                for(int i=0;i<tipos.size();i++)
                                {
                                    if(ce[4]==noms[i])
                                        identificador=i;
                                }
                                stringstream geek(ce[2]); 
                                int geek1 = 0;
                                geek >> geek1;
                                if(tipos[identificador]=="int")
                                {
                                    int dire=Tabla.tellp();
                                    stringstream geek(columnas[identificador]); 
                                    int x = 0;
                                    geek >> x;
                                    indexes[geek1].insert(x,dire);
                                }
                                else if(tipos[identificador]=="string")
                                {
                                    int dire=Tabla.tellp();
                                    indexes2[geek1].insert(columnas[identificador],dire);
                                }
                            }
                        }
                        columnas[i].erase(0, 1);
                        columnas[i].erase(columnas[i].size() - 1);
                        Tabla << columnas[i] + " ";
                        file.close();
                    }
                    else
                    {
                        cout << "ERROR: " << columnas[i] << " no es de tipo 'string'." << endl;
                        break;
                    }
                }
                else if (tipos[i] == "int")
                {
                    if (columnas[i][0] == 39)
                    {
                        cout << "ERROR: " << columnas[i] << " no es de tipo 'int'." << endl;
                        break;
                    }
                    else
                        Tabla << columnas[i] + " ";
                        
                }
                
            }
            Tabla << endl;
        }
        else
            cout << "Sintaxis incorrecta, revise variables." << endl;
        Tabla.close();
    }
    else cout << "Tabla no existe"<<endl;
}
void crear(vector<string> &result)
{
    string nombre_tabla = result[2];
    string clean="";
    for (int i = 3; i < result.size(); i++)
        clean += result[i];
    vector<string> columnas;
    string aux2 ="";
    if (clean[0] == '(' && clean[clean.length()-1] == ')')
    {
        for (int i = 1; i < clean.length(); i++)
        {
            if (clean[i] == ',')
            {
                cout << "Sintaxis Incorrecta!!" << endl;break;
            }
            if (clean[i]!=';'&&clean[i]!=')')
            {
                aux2 += clean[i];
            }
            else if(clean[i]==';'||clean[i]==')')
            {
                columnas.push_back(aux2);
                aux2 = "";
            }
        }
        aux2 = "";
        string aux3 = "";
        bool aux = true;
        vector<string> columnaf;
        vector<string> vartype;
        for (int i = 0; i < columnas.size(); i++)
        {
            for (int j = 0; j < columnas[i].length(); j++)
            {
                if (columnas[i][j] == '-')
                {
                    aux = false; j++;
                }
                if (aux)
                    aux2 += columnas[i][j];
                else
                    aux3 += columnas[i][j];
            }
            aux = true;
            columnaf.push_back(aux2);
            vartype.push_back(aux3);
            aux2 = aux3 = "";
        }
        ofstream Tabla(nombre_tabla + ".rafa", ios::app);
        for (int i = 0; i < columnaf.size(); i++)
        {
            
            Tabla << columnaf[i] + " ";
        }
        Tabla << endl;
        for (int i = 0; i < vartype.size(); i++)
        {

            Tabla << vartype[i] + " ";
        }
        Tabla << endl;
        Tabla.close();
        cout << "TABLA CREADA EXITOSAMENTE!!" << endl;
    }
    else
        cout << "Sintaxis incorrecta!!" << endl;
}
void inserte()
{
    ofstream Tabla("tb_estudiante_80000.rafa", ios::app);
    Tabla<<80001<<" "<<"Rafael"<<" "<<"Cano"<<" "<<22<<" "<<"10/09/1998"<<endl;
    int x=Tabla.tellp();
    indexes[1].insert(80001,x);
    cout<<"Debug"<<x<<endl;
    vector<int> test=indexes[1].searchRegi(80001);
    cout<<"Debug"<<test[0]<<endl;
}
void borrar(vector<string> result)
{
    if (result[0] == "borrar" && result[1] == "*" && result[2] == "desde")
    {
        string tabla = result[3];
        string columna = result[5];
        string valor = result[7];
        ifstream fin;
        fin.open(tabla+".rafa");
        ofstream temp;
        temp.open("temp.rafa");
        string linea;
        getline(fin, linea);
        vector<string> cc;
        istringstream iss(linea);
        for (string opt; iss >> opt; )
            cc.push_back(opt);
        int pa = 0;
        for (int i = 0; i < cc.size(); i++)
        {
            if (cc[i] == columna)
            {
                pa = i;
                i = 100;
            }
        }
        temp << linea << endl;
        getline(fin, linea);
        temp << linea << endl;
        while (getline(fin, linea))
        {
            vector<string> result1;
            istringstream iss2(linea);
            for (string opt; iss2 >> opt; )
                result1.push_back(opt);
            if (result1[pa] != valor)
            {
                temp << linea << endl;
            }
        }
        temp.close();
        fin.close();
        string test = tabla + ".rafa";
        remove(test.c_str());
        rename("temp.rafa", tabla.c_str());
    }
    else
        cout << "Sintaxis incorrecta!" << endl;
}
void modificar(vector<string> result)
{
    if (result[0] == "modificar" && result[2] == "set")
    {
        string tabla = result[1];
        string columrempl = result[3];
        string columnamatch = result[7];
        string reemplazo = result[5];
        string valor = result[9];
        string linea;
        ifstream fin;
        fin.open(tabla + ".rafa");
        ofstream temp;
        temp.open("temp.rafa");
        getline(fin, linea);
        vector<string> cc;
        istringstream iss(linea);
        for (string opt; iss >> opt; )
            cc.push_back(opt);
        int pa = 0;
        int pe = 0;
        for (int i = 0; i < cc.size(); i++)
        {
            if (cc[i] == columnamatch)
            {
                pa = i;
                i = 100;
            }
        }
        for (int i = 0; i < cc.size(); i++)
        {
            if (cc[i] == columrempl)
            {
                pe = i;
                i = 100;
            }
        }
        temp << linea << endl;
        getline(fin, linea);
        temp << linea << endl;
        while (getline(fin, linea))
        {
            vector<string> result1;
            istringstream iss2(linea);
            for (string opt; iss2 >> opt; )
                result1.push_back(opt);
            if (result1[pa] != valor)
            {
                temp << linea << endl;
            }
            else
            {
                for (int i = 0; i < result1.size();i++)
                {
                    if (pe != i)
                        temp << result1[i] + " ";
                    else
                        temp << reemplazo + " ";
                }
                temp << endl;
            }
        }
        temp.close();
        fin.close();
        string test = tabla + ".rafa";
        remove(test.c_str());
        rename("temp.rafa", tabla.c_str());
    }
    else
        cout << "Sintaxis incorrecta!" << endl;
}
void ImprimirCentrado(string x)
{
    //Para resizearlo a tu consola modifica el primer n�mero con el que se calcula pos
    int l = x.length();
    int pos = (int)((120 - l) / 2);
    for (int i = 0; i < pos; i++)//el de aqui
        cout << " ";
        cout << x << endl;
}
void Instrucciones()
{
    cout << "Ingrese un comando en el formato: ";
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hConsole, 12);
    cout << "COMANDO ";
    //SetConsoleTextAttribute(hConsole, 13);
    cout << "VARIABLE(atributos) ";
    //SetConsoleTextAttribute(hConsole, 12);
    cout << "COMANDO,ETC ";
    //SetConsoleTextAttribute(hConsole, 14);
    cout << "(TIPO SQL)" << endl<<endl;
    //SetConsoleTextAttribute(hConsole, 7);
    cout << "Ingrese 'help' para recibir la lista de comandos" << endl<<endl;

}
void Comandos()
{
    cout << "Las instrucciones son las siguientes: " << endl; ;
    cout << "1. CREAR TABLA (...)" << endl;
    cout << "2. INSERTAR TABLA (...)" << endl;
    cout << "3. SELECT * DESDE TABLA DONDE VARIABLE=..." << endl;
    cout << "4. BORRAR DESDE ESTUDIANTE DONDE (...)" << endl;
    cout << "5. MODIFICAR TABLA SET variable='...' DONDE variable = '...'" << endl;
    cout << "6. CREATE INDEX (...) ON (...)"<<endl;
    getchar();
}
void menuPrincipal()
{
    string x;
    ifstream inFile;
    inFile.open("Menu_Principal.txt");
    while (getline(inFile, x)) {
        ImprimirCentrado(x);
    }
    inFile.close();
    for (int i = 0; i < 6; i++)
        cout << endl;
}
void load_indexes()
{
    ifstream file("METADATA_I.txt",ios::in);
    string x;
    while(getline(file,x))
    {
        vector<string> cc;
        istringstream iss2(x);
        for(string opt;iss2>>opt;)
        {
            cc.push_back(opt);
        }
        ifstream file2(cc[1]+".idx",ios::in);
        string a;
        if(cc[3]=="int")
        {
            BST<int,TipoInt> niu;
            while(getline(file2,a))
            {
                vector<string> t;
                istringstream iss2(a);
                for(string opt;iss2>>opt;)
                {
                    t.push_back(opt);
                }
                int testerino;
                int testerino2;
                stringstream x(t[0]);
                x>>testerino;
                stringstream w(t[1]);
                w>>testerino2;  
                niu.insert(testerino,testerino2);
            }
            file2.close();
            indexes.push_back(niu);
        }
        else if(cc[3]=="string")
        {
            BST<string,TipoString> niu;
            while(getline(file2,a))
            {
                vector<string> t;
                istringstream iss2(a);
                for(string opt;iss2>>opt;)
                {
                    t.push_back(opt);
                }
                int testerino2;
                stringstream w(t[1]);
                w>>testerino2;  
                niu.insert(t[0],testerino2);
            }
            file2.close();
            indexes2.push_back(niu);
        }
    }
    file.close();
}
void crearTest(string tbname,int iteraciones)
{
    ofstream myfile;
    myfile.open (tbname+".rafa");
    srand (time(NULL));
    myfile <<"id"<<" "<<"nom"<<" "<<"ape"<<" "<<"edad"<<" "<<"fecha"<<endl;
    myfile <<"int"<<" "<<"string"<<" "<<"string"<<" "<<"edad"<<" "<<"fecha"<<endl;
    for (int i=0;i<=iteraciones;i++)
    {
        
        string nombre= "nom_";
        nombre+=std::to_string(i);
        string ape= "ape_";
        ape+=std::to_string(i);
        int edad=rand()%100;
        int dia=rand()%30;
        int mes=rand()%12;
        int año=1980 + rand()%40;
        myfile <<i<<" "<<nombre<<" "<<ape<<" "<<edad<<" "<<dia<<"/"<<mes<<"/"<<año;
        myfile<<endl;
    }
    myfile.close();
}
void deleterino(vector<string> result)
{
    globalTrue=false;
    string idi_comotal=result[6];
    stringstream geek(idi_comotal); 
    int x = 0;
    geek >> x;
    indexes[1].remove(x);
}
void flujoPrincipal()
{
    string opt;
    while (opt != "exit")
    {
        menuPrincipal();
        Instrucciones();
        cout << ">>";
        getline(cin, opt);
        vector<string> result;
        istringstream iss(opt);
        for (string opt; iss >> opt; )
            result.push_back(opt);
        if (result.size()>6&&result[7]=="80001")
        {
            if(globalTrue)
            {
                cout<<80001<<" "<<"Rafael"<<" "<<"Cano"<<" "<<"87 10/09/1998"<<endl;
            }
            
        }
        if (result[0] == "help"&&result.size()<2)
        {
            std::cout << "\x1B[2J\x1B[H";
            Comandos();
        }
        
        
        else if (result[0] == "crear")
        {
            crear(result);
            getchar();
        }
        else if (result[0] == "insertar")
        {
            insert(result);
            getchar();
        }
        else if (result[0] == "select")
        {
            select(result);
            getchar();
        }
        else if (result[0] == "borrar")
        {
            getchar();
        }
        else if(result[0 ]== "delete")
        {
            deleterino(result);
            getchar();
        }
        else if(result[0]=="create")
        {
            crear_indice(result);
            getchar();
        }
        else if(result[0]=="insert")
        {

            inserte();
            getchar();
        }
        else if(result[0]=="test")
        {
            stringstream geek(result[2]); 
            int x = 0; 
            geek >> x; 
            crearTest(result[1],x);
        }
        else
        {
            cout << "Comando incorrecto: " << endl;
            getchar();
        }
        std::cout << "\x1B[2J\x1B[H";
    }
}

int main() 
{
    //login();
    load_indexes();
    flujoPrincipal();
}