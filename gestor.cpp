#include "gestor.h"

Gestor::Gestor()
{
    char tmpCod[LARGO_CODIGO];
    char tmpStr[LARGO_NOMBRE];
    unsigned int tmpInt;
    float tmpFloat;
    fstream archivo("usuarios.bin", ios::out | ios::in | ios::binary);
    Usuario tmpUsuario;

    if (!archivo.is_open())
    {
        fstream archivo_abrir("usuarios.bin", ios::out);
        archivo_abrir.close();
    }
    else
    {
        archivo.seekg(0);
        while (!archivo.eof())
        {
            archivo.read((char*)&tmpCod, sizeof(tmpCod));
            if (archivo.eof())
                break;
            if (strlen(tmpCod) == 9)
                m_codigos.push_back(tmpStr);

            archivo.read((char*)&tmpStr, sizeof(char[LARGO_NOMBRE]));
            archivo.read((char*)&tmpStr, sizeof(char[LARGO_APELLIDO]));
            archivo.read((char*)&tmpInt, sizeof(tmpInt));
            archivo.read((char*)&tmpStr[0], sizeof(char));
            archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
            archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
            archivo.read((char*)&tmpStr, sizeof(char[LARGO_TIPO_SANGRE]));
            archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
        }
        archivo.close();
    }
}

Gestor::~Gestor()
{}

void Gestor::menu()
{
    char opc;
    do
    {
        CLEAR;
        cout << " Ingrese la opción a ejecutar: " << endl
             << " " << char(OPC_CAPTURAR) << ") Capturar usuario" << endl
             << " " << char(OPC_MOSTRAR) << ") Mostrar usuarios" << endl
             << " " << char(OPC_BUSCAR) << ") Buscar usuario (por código)" << endl
             << " " << char(OPC_MODIFICAR) << ") Modificar usuario" << endl
             << " " << char(OPC_ELIMINAR) << ") Eliminar usuario" << endl
             << " " << char(OPC_SALIR) << ") Salir" << endl
             << " Opción: ";

        cin >> opc;
        CLEAR;
        cin.ignore();
        switch (opc)
        {
            case OPC_CAPTURAR:
            {
                Usuario usuarioTmp;
                capturar_datos(usuarioTmp);
                capturar(usuarioTmp);
                cin.ignore();
            }
            break;

            case OPC_MODIFICAR:
                //modificar();
            break;

            case OPC_BUSCAR:
                buscar();
            break;

            case OPC_ELIMINAR:
                eliminar();
            break;

            case OPC_MOSTRAR:
                CLEAR;
                mostrar();
            break;

            case OPC_SALIR:
                cout << " Hasta la próxima" << endl;
            return;

            default:
                cout << " Dato inválido, presione ENTER para continuar..." << endl;
            break;
        }
        cin.get();
    } while (opc != OPC_SALIR);
}

void Gestor::buscar()
{
    char tmpStr[LARGO_NOMBRE];
    unsigned int tmpInt;
    float tmpFloat;
    bool found = false;
    string codigo;
    Usuario usuarioTmp;
    fstream archivo("usuarios.bin", ios::in);

    if (!m_codigos.size())
        cout << " Aún no se han ingresado usuarios " << endl << endl
             << " Presione ENTER para continuar..." << endl;
    else
    {
        cout << " Ingrese el código a buscar: ";
        getline(cin, codigo);

        for (unsigned int i = 0; !archivo.eof(); ++i)
        {
            if (m_codigos[i] == tmpStr)
            {
                archivo.read((char*)&tmpStr, sizeof(LARGO_CODIGO));
                if (archivo.eof())
                    break;

                usuarioTmp.setCodigo(tmpStr);

                archivo.read((char*)&tmpStr, sizeof(LARGO_NOMBRE));
                usuarioTmp.setNombre(tmpStr);

                archivo.read((char*)&tmpStr, sizeof(LARGO_APELLIDO));
                usuarioTmp.setApellido(tmpStr);

                archivo.read((char*)&tmpInt, sizeof(tmpInt));
                usuarioTmp.setEdad(tmpInt);

                archivo.read((char*)&tmpStr[0], sizeof(char));
                usuarioTmp.setGenero(tmpStr[0]);

                archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
                usuarioTmp.setPeso(tmpFloat);

                archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
                usuarioTmp.setMasaCorporal(tmpFloat);

                archivo.read((char*)&tmpStr, sizeof(LARGO_TIPO_SANGRE));
                usuarioTmp.setTipoSangre(tmpStr);
                
                archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
                usuarioTmp.setAltura(tmpFloat);
            }

            if (codigo ==  usuarioTmp.getCodigo())
                found = true;
        }
        if (found)
        {
            CLEAR;
            cout << endl
                 <<" Código: " << usuarioTmp.getCodigo() << endl
                 << " Nombre: " << usuarioTmp.getNombre() << endl
                 << " Apellido: " << usuarioTmp.getApellido() << endl
                 << " Edad: " << usuarioTmp.getEdad() << endl
                 << " Género: " << usuarioTmp.getGenero() << endl
                 << " Peso: " << usuarioTmp.getPeso() << endl
                 << " Altura: " << usuarioTmp.getAltura() << endl
                 << "----------------------------------------------"
                 << endl << endl
                 << " Presione ENTER para continuar..." << endl;
        }
        else
            cout << " Correo no encontrado" << endl;
    }
}

void Gestor::capturar(const Usuario& usuario)
{
    char tmpStr[LARGO_NOMBRE] = {0};
    unsigned int tmpInt;
    float tmpFloat;
    fstream archivo("usuarios.bin", ios::out | ios::in | ios::app);

    if (!archivo.is_open())
        cerr << "Error en el archivo de salida" << endl;
    
    strcpy(tmpStr, usuario.getCodigo());
    archivo.write((char*)&tmpStr, sizeof(char[LARGO_CODIGO]));
    m_codigos.push_back(tmpStr);

    strcpy(tmpStr, usuario.getNombre());
    archivo.write((char*)&tmpStr, sizeof(char[LARGO_NOMBRE]));

    strcpy(tmpStr, usuario.getApellido());
    archivo.write((char*)&tmpStr, sizeof(char[LARGO_APELLIDO]));

    tmpInt = usuario.getEdad();
    archivo.write((char*)&tmpInt, sizeof(tmpInt));

    tmpStr[0] = usuario.getGenero();
    archivo.write((char*)&tmpStr[0], sizeof(char));

    tmpFloat = usuario.getPeso();
    archivo.write((char*)&tmpFloat, sizeof(tmpFloat));

    tmpFloat = usuario.getMasaCorporal();
    archivo.write((char*)&tmpFloat, sizeof(tmpFloat));

    strcpy(tmpStr, usuario.getTipoSangre());
    archivo.write((char*)&tmpStr, sizeof(char[LARGO_TIPO_SANGRE]));
    
    tmpFloat = usuario.getAltura();
    archivo.write((char*)&tmpFloat, sizeof(tmpFloat));

    
    archivo.close();
    cout << endl
        << " Usuario añadido exitosamente." << endl
        << " Presione ENTER para continuar..." << endl;
}

void Gestor::eliminar()
{
    bool found = false;
    unsigned int opc;
    unsigned char tam;
    char auxChar;
    string aux;
    fstream archivo("usuarios.bin", ios::in | ios::out);
    fstream tmp("usuarios.tmp", ios::out);

    mostrar();
    cout << " Salir = 0" << endl;
    if (!m_codigos.size())
        cout << " Aún no se han ingresado datos. Presione ENTER para continuar" << endl;
    else
    {
        cout << " Ingrese número del usuario a eliminar: ";
        cin >> opc;
        if (opc <= m_codigos.size() && opc)
        {
            while (!archivo.eof())
            {
                for (int i = 0; i < CANTIDAD_CAMPOS; i++)
                {
                    aux = "";
                    archivo.read((char*)&tam, sizeof(tam));
                    if (archivo.eof())
                        break;
                    
                    for (int j = 0; j < int(tam); ++j)
                    {
                        archivo.get(auxChar);
                        aux += auxChar;
                    }
                    if (!i && m_codigos[opc - 1] == aux)
                        found = true;
                    else if (found && i == CANTIDAD_CAMPOS - 1)
                        found = false;
                    else if (!found)
                    {
                        tmp.write((char*)&tam, sizeof(tam));
                        tmp << aux;         
                    }
                }
            }
            m_codigos.erase(m_codigos.begin() + opc - 1);
            tmp.close();
            archivo.close();
            remove("usuarios.bin");
            rename("usuarios.tmp", "usuarios.bin");
        }
        else if (!opc)
            return;
        else
        {
            cout << endl
                << " Dato inválido, presione ENTER para continuar..."
                << endl;
            cin.get();
        }
    }
}
/*
void Gestor::modificar()
{   
    Usuario usuarioTmp;
    unsigned int codMod;
    char opc;
    char auxChar;
    unsigned char tam;
    bool found = false;
    string aux;
    fstream archivo("usuarios.bin", ios::out | ios::in);
    fstream tmp("usuarios.tmp", ios::out);

    mostrar();

    if (!m_codigos.size())
        cout << " Aún no se han ingresado datos. Presione ENTER para continuar" << endl;
    else
    {
        cout << " Ingrese número del usuario a modificar: ";
        cin >> codMod;

        if (codMod <= m_codigos.size() && codMod)
        {   
            do
            {
                cout << endl
                     << " Seleccione el campo a modificar:" << endl;
                cout << char(OPC_CAMPO_NOM) << ") Nombre" << endl
                     << char(OPC_CAMPO_APE) << ") Apellido" << endl
                     << char(OPC_CAMPO_EDAD) << ") Edad" << endl
                     << char(OPC_CAMPO_SEXO) << ") Sexo" << endl
                     << char(OPC_CAMPO_PESO) << ") Peso" << endl
                     << char(OPC_CAMPO_TIPO_SANGRE) << ") Tipo de sangre" << endl
                     << char(OPC_CAMPO_ALTURA) << ") Altura" << endl
                     << char(OPC_CAMPO_CANCELAR) << ") Cancelar" << endl
                     << "Opción: ";
                cin >> opc;
            }while(opc < OPC_CAMPO_NOM || opc > OPC_CAMPO_CANCELAR);
            
            if (opc != OPC_CAMPO_CANCELAR)
            {
                while (codMod--)
                {
                    for (int i = 0; i < CANTIDAD_CAMPOS; ++i)
                    {
                        archivo.read((char*)&tam, sizeof(tam));
                        if (archivo.eof())
                            break;
                        
                        aux = "";
                        for (int j = 0; j < int(tam); ++j)
                        {
                            archivo.get(auxChar);
                            aux += auxChar;
                        }
                        
                        if (!codMod)
                        {
                            switch (i)
                            {
                                case CAMPO_COD:
                                    usuarioTmp.setCodigo(aux);
                                break;
                                case CAMPO_EDAD:
                                    usuarioTmp.setEdad(stoi(aux));
                                break;
                                case CAMPO_PESO:
                                    usuarioTmp.setPeso(stof(aux));
                                break;
                                case CAMPO_SEXO:
                                    usuarioTmp.setGenero(aux[0]);
                                break;
                                case CAMPO_ALTURA:
                                    usuarioTmp.setAltura(stof(aux));
                                break;
                                case CAMPO_APE:
                                    usuarioTmp.setApellido(aux);
                                break;
                                case CAMPO_NOM:
                                    usuarioTmp.setNombre(aux);
                                break;
                                case CAMPO_TIPO_SANGRE:
                                    usuarioTmp.setTipoSangre(aux);
                                break;
                                case CAMPO_MASA:
                                    usuarioTmp.setMasaCorporal(stof(aux));
                                break;
                            }
                        }
                    }
                }
                modificar_datos(usuarioTmp, opc);
                
                archivo.seekg(0);
                while (!archivo.eof())
                {
                    for (int i = 0; i < CANTIDAD_CAMPOS; ++i)
                    {
                        archivo.read((char*)&tam, sizeof(tam));
                        if (archivo.eof())
                            break;

                        aux = "";
                        for (int j = 0; j < int(tam); ++j)
                        {
                            archivo.get(auxChar);
                            aux += auxChar;
                        }
                        if (!i && aux == usuarioTmp.getCodigo())
                            found = true;
                        
                        if (found)
                        {
                            switch (i)
                            {
                                case CAMPO_COD:
                                    tam = usuarioTmp.getCodigo().length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << usuarioTmp.getCodigo();
                                break;
                                case CAMPO_EDAD:
                                    tam = to_string(usuarioTmp.getEdad()).length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << to_string(usuarioTmp.getEdad());
                                break;
                                case CAMPO_PESO:
                                    tam = to_string(usuarioTmp.getPeso()).length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << to_string(usuarioTmp.getPeso());
                                break;
                                case CAMPO_SEXO:
                                    tam = CHAR_SIZE;
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << usuarioTmp.getGenero();
                                break;
                                case CAMPO_ALTURA:
                                    tam = to_string(usuarioTmp.getAltura()).length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << to_string(usuarioTmp.getAltura());
                                    found = false;
                                break;
                                case CAMPO_APE:
                                    tam = usuarioTmp.getApellido().length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << usuarioTmp.getApellido();
                                break;
                                case CAMPO_NOM:
                                    tam = usuarioTmp.getNombre().length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << usuarioTmp.getNombre();
                                break;
                                case CAMPO_TIPO_SANGRE:
                                    tam = usuarioTmp.getTipoSangre().length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << usuarioTmp.getTipoSangre();
                                break;
                                case CAMPO_MASA:
                                    tam = to_string(usuarioTmp.getMasaCorporal()).length();
                                    tmp.write((char*)&tam, sizeof(tam));
                                    tmp << to_string(usuarioTmp.getMasaCorporal());
                                break;
                            }
                        }
                        else
                        {
                            tmp.write((char*)&tam, sizeof(tam));
                            tmp << aux;
                        }
                    }   
                }
                tmp.close();
                archivo.close();
                remove("usuarios.bin");
                rename("usuarios.tmp", "usuarios.bin");

                cout << endl
                     << " Dato modificado correctamente" << endl
                     << " Presione ENTER para continuar..." << endl;
            }
        }
        else if (!codMod)
            return;
        else
        {
            cout << endl
                 << " Dato inválido, presione ENTER para continuar..."
                 << endl;
            cin.get();       
        }
    }
}
*/

void Gestor::mostrar()
{
    unsigned long cont = 0;
    fstream archivo("usuarios.bin", ios::in);
    char tmpStr[LARGO_NOMBRE];
    unsigned int tmpInt;
    float tmpFloat;
    Usuario usuario;

    if (!archivo.is_open())
        cout << " Error en el archivo de entrada" << endl;
    else
    {
        archivo.seekg(ios::beg);
        for (unsigned int i = 0; i < m_codigos.size(); ++i)
        {
            if (archivo.eof())
                break;
            archivo.read((char*)&tmpStr, sizeof(char[LARGO_CODIGO]));
            usuario.setCodigo(tmpStr);

            archivo.read((char*)&tmpStr, sizeof(char[LARGO_NOMBRE]));
            usuario.setNombre(tmpStr);

            archivo.read((char*)&tmpStr, sizeof(char[LARGO_APELLIDO]));
            usuario.setApellido(tmpStr);

            archivo.read((char*)&tmpInt, sizeof(tmpInt));
            usuario.setEdad(tmpInt);

            archivo.read((char*)&tmpStr[0], sizeof(char));
            usuario.setGenero(tmpStr[0]);

            archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
            usuario.setPeso(tmpFloat);

            archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
            usuario.setMasaCorporal(tmpFloat);

            archivo.read((char*)&tmpStr, sizeof(char[LARGO_TIPO_SANGRE]));
            usuario.setTipoSangre(tmpStr);
            
            archivo.read((char*)&tmpFloat, sizeof(tmpFloat));
            usuario.setAltura(tmpFloat);
            
            ++ cont;

            if (cont)
                cout << " Usuario #" << cont << endl
                    << " Código: " << usuario.getCodigo() << endl
                    << " Nombre: " << usuario.getNombre() << endl
                    << " Apellido: " << usuario.getApellido() << endl
                    << " Edad: "   << usuario.getEdad() << endl
                    << " Género: " << usuario.getGenero() << endl
                    << " Peso: " << usuario.getPeso() << endl
                    << " Masa corporal: " << usuario.getMasaCorporal() << endl
                    << " Tipo de sangre: " << usuario.getTipoSangre() << endl
                    << " Altura: " << usuario.getAltura() << endl
                    << "----------------------------------------------"
                    << endl;
            else
                cout << " Aún no se han ingresado usuarios" << endl;
        }
        archivo.close();
    }
}


void Gestor::capturar_datos(Usuario& usuario)
{
    string codigo;
    string nombre;
    string apellido;
    string genero;
    string tipoSangre;
    unsigned int edad;
    float altura;
    float peso;
    bool continuar = false;

    // Expresiones regulares
    regex expCodigo("([1-9]{1}[0-9]{8})$");
    regex expNombre("(?:[a-zA-ZñÑ]{4,})(?: [a-zA-ZñÑ]{4,})?{1,2}");
    regex expApellido("(?:[a-zA-ZñÑ]{4,})(?: [a-zA-ZñÑ]{3,})$");
    regex expGenero("(?:[MF]){1}$");
    regex expTipoSangre("(AB|A|B|O)(?:[+-]{1})$");
    
    cout << " Presione ENTER para continuar e ingrese los siguientes datos"
         << endl << endl;

    // Obtención de código
    do
    {
        CLEAR;
        cout << " Código (9 dígitos): ";
        getline(cin, codigo);
        if (codigo_usado(codigo))
        {
            cout << endl
                 << " Error, código en uso. Presione ENTER para continuar";
            cin.get();
        }
        else if (!regex_match(codigo, expCodigo))
        {
            cout << endl
                 << " Error el código debe de tener 9 dígitos y no debe de"
                 << " empezar con cero" << endl
                 << " Presione ENTER para continuar";
            cin.get();
        }
        else
            continuar = true;
    } while (!continuar);
    continuar = false;

    // Obtención de nombre
    do
    {
        CLEAR;
        cout << " Nombre: ";
        getline(cin, nombre);
        if (!regex_match(nombre, expNombre))
        {
            cout << " Error, introducir mínimo un nombre y máximo tres "
                 << endl
                 << " (mínimo cuatro letras por nombre)"
                 << endl
                 << " Presione ENTER para continuar"
                 << endl;
            cin.get();
        }
        else
            continuar = true;
    } while (!continuar);
    continuar = false;

    // Obtención de apellido
    do
    {
        CLEAR;
        cout << " Apellido: ";
        getline(cin, apellido);
        if (!regex_match(apellido, expApellido))
        {
            cout << " Error, se deben de introducir dos apellidos"
                 << " separados por espacios"
                 << endl
                 << " Presione ENTER para continuar"
                 << endl;
            cin.get();
        }
        else
            continuar = true;
    }while(!continuar);

    do
    {
        CLEAR;
        cout << " Edad (de 12 a 115 años): ";
        cin >> edad;
    }while(edad > 115 || edad < 12);

    do
    {
        CLEAR;
        cout << " Género (M = masculino | F = femenino): ";
        cin >> genero;
    } while(!regex_match(genero, expGenero));

    do
    {
        CLEAR;
        cout << " Peso (de 30 a 300 kg): ";
        cin >> peso;
    }while(peso > 300 || peso < 30);

    continuar = false;
    cin.ignore();
    //Tipo de sangre
    do
    {
        CLEAR;
        cout << " Tipo de sangre (AB, A, B, O)(+, -): ";
        getline(cin, tipoSangre);
        if (!regex_match(tipoSangre, expTipoSangre))
        {
            cout << endl
                 << " Error, vuelva a intentarlo" << endl;
            cin.get();
        }
        else
            continuar = true;
    }while(!continuar);

    do
    {   
        CLEAR;
        cout << " Altura (de 0.8 a 2.5 mts): ";
        cin >> altura;;
    } while (altura < 0.8 || altura > 2.5);

    nombre += '\0';
    apellido += '\0';
    codigo += '\0';
    tipoSangre += '\0';

    usuario.setAltura(altura);
    usuario.setApellido(apellido.c_str());
    usuario.setCodigo(codigo.c_str());
    usuario.setEdad(edad);
    usuario.setGenero(genero[0]);
    usuario.setNombre(nombre.c_str());
    usuario.setPeso(peso);
    usuario.setTipoSangre(tipoSangre.c_str());
    usuario.setMasaCorporal(peso / (altura * altura));
}

bool Gestor::codigo_usado(const string codigo)
{
    for (int i = 0; i < m_codigos.size(); i++)
        if (codigo == m_codigos[i])
            return true;
    return false;
}

/*
void Gestor::modificar_datos(Usuario& usuario, char i)
{
    bool continuar = false;

    // Expresiones regulares
    regex expCodigo("([1-9]{1}[0-9]{8})$");
    regex expNombre("(?:[a-zA-ZñÑ]{4,})(?: [a-zA-ZñÑ]{4,})?{1,2}");
    regex expApellido("(?:[a-zA-ZñÑ]{4,})+(?: [a-zA-ZñÑ]{3,})$");
    regex expGenero("(?:[mMfF]){1}$");
    regex expTipoSangre("(AB|A|B|O)(?:[+-]{1})$");

    cin.ignore();
    switch (i)
    {
        case OPC_CAMPO_NOM:
        {
            string nombre;
            do
            {
                CLEAR;
                cout << " Nombre: ";
                getline(cin, nombre);
                if (!regex_match(nombre, expNombre))
                {
                    cout << " Error, introducir mínimo un nombre y máximo tres "
                        << endl
                        << " (mínimo cuatro letras por nombre)"
                        << endl
                        << " Presione ENTER para continuar"
                        << endl;
                    cin.get();
                }
                else
                    continuar = true;
            } while (!continuar);
            usuario.setNombre(nombre);
        }
        break;

        case OPC_CAMPO_APE:
        {
            string apellido;
            do
            {
                CLEAR;
                cout << " Apellido: ";
                getline(cin, apellido);
                if (!regex_match(apellido, expApellido))
                {
                    cout << " Error, se deben de introducir dos apellidos"
                        << " separados por espacios"
                        << endl
                        << " Presione ENTER para continuar"
                        << endl;
                    cin.get();
                }
                else
                    continuar = true;
            }while(!continuar);
            usuario.setApellido(apellido);
        }
        break;

        case OPC_CAMPO_EDAD:
        {
            unsigned int edad;
            do
            {
                CLEAR;
                cout << " Edad (de 12 a 115 años): ";
                cin >> edad;
            }while(edad > 115 || edad < 12);
            usuario.setEdad(edad);
        }
        break;

        case OPC_CAMPO_PESO:
        {
            float peso;
            do
            {
                CLEAR;
                cout << " Peso (de 30 a 300 kg): ";
                cin >> peso;
            }while(peso > 300 || peso < 30);
            usuario.setPeso(peso);
            usuario.setMasaCorporal(peso / (usuario.getAltura() * usuario.getAltura()));
        }
        break;

        case OPC_CAMPO_SEXO:
        {
            string genero;
            do
            {
                CLEAR;
                cout << " Género (M = masculino | F = femenino): ";
                cin >> genero;
            } while(!regex_match(genero, expGenero));
            usuario.setGenero(genero[0]);
        }
        break;

        case OPC_CAMPO_TIPO_SANGRE:
        {
            string tipoSangre;
            do
            {
                CLEAR;
                cout << " Tipo de sangre (AB, A, B, O)(+, -): ";
                getline(cin, tipoSangre);
                if (codigo_usado(tipoSangre))
                {
                    cout << endl
                        << " Error, código en uso. Presione ENTER para continuar";
                    cin.get();
                }
                else if (!regex_match(tipoSangre, expTipoSangre))
                {
                    cout << endl
                        << " Error, vuelva a intentarlo" << endl;
                    cin.get();
                }
                else
                    continuar = true;
            }while(!continuar);
            usuario.setTipoSangre(tipoSangre);
        }
        break;

        case OPC_CAMPO_ALTURA:
        {
            float altura;
            do
            {   
                CLEAR;
                cout << " Altura (de 0.8 a 2.5 mts): ";
                cin >> altura;;
            } while (altura < 0.8 || altura > 2.5);
            usuario.setAltura(altura);
            usuario.setMasaCorporal(usuario.getPeso() / (altura * altura));
        }
        break;
    }
}
*/