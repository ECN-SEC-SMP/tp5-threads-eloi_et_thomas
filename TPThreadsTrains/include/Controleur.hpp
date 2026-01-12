/**
 * @file Controleur.hpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr) & Thomas Verron (Thomas.Verron@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 12-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class Controleur
{
public:
  Controleur(int valeur_initiale) : val(valeur_initiale)
  {
  }

  bool controlinEnB(int numero)
  {
    return true;
  }

  bool controlinEnA(int numero)
  {
    return true;
  }

  bool controloutEnB(int numero)
  {
    return true;
  }

  bool controloutEnA(int numero)
  {
    return true;
  }

private:
  int val;
};

#endif // CONTROLEUR_HPP
