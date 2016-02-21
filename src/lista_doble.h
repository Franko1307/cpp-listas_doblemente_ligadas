#pragma once
#include "caja.h"
#include <iostream>

enum DONDE {VACIO,INICIO,MITAD, FINAL, FUERA };

template <typename T> class lista_doble {
private:
  caja<T> *principio;
  caja<T> *final;
  caja<T> *anterior;
  DONDE donde;
  bool encontrado;
  void buscar(T var);
public:
  lista_doble(): principio(NULL), final(NULL), donde(INICIO), anterior(NULL), encontrado(false){};
  ~lista_doble();
  bool agregar(T var);
  bool borrar(T var);
  void pintar_1();
  void pintar_2();
};
template <typename T> lista_doble<T>::~lista_doble() {
  caja<T> *p = principio;
  while (principio) {
    p = principio;
    principio = p->siguiente;
    delete p;
  }
  final = NULL;
  donde = INICIO;
  anterior = NULL;
  encontrado = false;
}
template <typename T> void lista_doble<T>::buscar(T var) {
  if (!principio) {
    anterior = NULL;
    donde = VACIO;
    return;
  }
  caja<T> *p = principio;
  while (p) {
    if (p->var == var) {
      encontrado = true;
      if (p == principio) donde = INICIO;
      else donde = MITAD;
      return;
    } else if (p->var < var) {
      anterior = p;
      p = p->siguiente;
    } else {
      encontrado = false;
      if (p == principio) donde = INICIO;
      else donde = MITAD;
      return;
    }
  }
  encontrado = false;
  donde = FINAL;
}
template <typename T> bool lista_doble<T>::agregar(T var) {
  buscar(var);
  if (encontrado) return false;
  caja<T> *p = new caja<T>;
  p->var = var;
  if (donde == MITAD) {
    p->siguiente = anterior->siguiente;
    p->anterior = anterior;
    anterior->siguiente = p;
    p->siguiente->anterior = p;
  } else if (donde == FINAL) {
    p->siguiente = anterior->siguiente;
    p->anterior = anterior;
    anterior->siguiente = p;
    final = p;
  } else if (donde == VACIO){
    p->siguiente = NULL;
    p->anterior = NULL;
    principio = p;
    final = p;
  } else {
    p->siguiente = principio;
    p->anterior = NULL;
    principio->anterior = p;
    principio = p;
  }
  return true;
}
template <typename T> bool lista_doble<T>::borrar(T var) {
  buscar(var);
  if (!encontrado) return false;
  caja<T> *p;
  if (donde == MITAD) {
    p = anterior->siguiente;
    p->siguiente->anterior = anterior;
    anterior->siguiente = p->siguiente;
  } else if (donde == FINAL){
    p = final;
    final = anterior;
    final->siguiente = NULL;
  } else {
    p = principio;
    principio = p->siguiente;
    principio->anterior = NULL;
  }
  delete p;
  return true;
}
template <typename T> void lista_doble<T>::pintar_1() {
  caja<T> *p = principio;
  std::cout << "[ ";
  while (p) {
    std::cout << p->var << ",";
    p = p->siguiente;
  }
  std::cout << "\b ]" << std::endl;
}
template <typename T> void lista_doble<T>::pintar_2() {
  caja<T> *p = final;
  std::cout << "[ ";
  while (p) {
    std::cout << p->var << ",";
    p = p->anterior;
  }
  std::cout << "\b ]" << std::endl;
}
