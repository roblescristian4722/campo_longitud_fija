#include "usuario.h"

// GETTERS
char* Usuario::getCodigo() const
{
    char *tmp = new char [LARGO_CODIGO];
    strcpy(tmp, m_codigo);
    return tmp;
}
char* Usuario::getNombre() const
{
    char *tmp = new char[LARGO_NOMBRE];
    strcpy(tmp, m_nombre);
    return tmp;
}
char* Usuario::getApellido() const
{
    char *tmp = new char[LARGO_APELLIDO];
    strcpy(tmp, m_apellido);
    return tmp;
}
char* Usuario::getTipoSangre() const
{
    char *tmp = new char[LARGO_TIPO_SANGRE];
    strcpy(tmp, m_tipoSangre);
    return tmp;
}
unsigned int Usuario::getEdad() const
{ return m_edad; }
char Usuario::getGenero() const
{ return m_genero; }
float Usuario::getAltura() const
{ return m_altura; }
float Usuario::getPeso() const
{ return m_peso; }
float Usuario::getMasaCorporal() const
{ return m_masaCorporal; }

// SETTERS
void Usuario::setCodigo(const char* codigo)
{ strcpy(m_codigo, codigo); }
void Usuario::setNombre(const char* nombre) 
{ strcpy(m_nombre, nombre); }
void Usuario::setApellido(const char* apellido)
{ strcpy(m_apellido, apellido); }
void Usuario::setTipoSangre(const char* tipoSangre)
{ strcpy(m_tipoSangre, tipoSangre); }
void Usuario::setEdad(unsigned int edad)
{ m_edad = edad; }
void Usuario::setGenero(char genero)
{ m_genero = genero; }
void Usuario::setAltura(float altura)
{ m_altura = altura; }
void Usuario::setPeso(float peso)
{ m_peso = peso; }
void Usuario::setMasaCorporal(float masaCorporal)
{ m_masaCorporal = masaCorporal; }