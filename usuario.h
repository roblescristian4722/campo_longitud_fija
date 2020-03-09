#ifndef USUARIO_H
#define USUARIO_H

#define LARGO_CODIGO 10
#define LARGO_NOMBRE 50
#define LARGO_APELLIDO 40
#define LARGO_TIPO_SANGRE 4

#include <iostream>
#include <cstring>
using namespace std;

class Usuario
{
public:
    Usuario(){}
    ~Usuario(){}

    // GETTERS
    char* getCodigo() const;
    char* getNombre() const;
    char* getApellido() const;
    char* getTipoSangre() const;
    unsigned int getEdad() const ;
    char getGenero() const;
    float getMasaCorporal() const;
    float getAltura() const;
    float getPeso() const;

    // SETTERS
    void setCodigo(const char* codigo);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setTipoSangre(const char* tipoSangre);
    void setEdad(unsigned int edad);
    void setGenero(char genero);
    void setMasaCorporal(float masaCorporal);
    void setAltura(float altura);
    void setPeso(float peso);
    
private:
    char m_codigo[LARGO_CODIGO];
    char m_nombre[LARGO_NOMBRE];
    char m_apellido[LARGO_APELLIDO];
    char m_tipoSangre[LARGO_TIPO_SANGRE];
    unsigned int m_edad;
    char m_genero;
    float m_altura;
    float m_peso;
    float m_masaCorporal;
};

#endif