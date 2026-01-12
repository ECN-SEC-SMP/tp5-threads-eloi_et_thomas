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
    if (val == 0 || sens == 0)
    {
      val++;
      sens = 0;
      return true;
    }
    return false;
  }

  bool controlinEnA(int numero)
  {
    if (val == 0 || sens == 1)
    {
      val++;
      sens = 1;
      return true;
    }
    return false;
  }

  bool controloutEnB(int numero)
  {
    val--;
    return true;
  }

  bool controloutEnA(int numero)
  {
    val--;
    return true;
  }

private:
  int val;
  bool sens;
};

#endif // CONTROLEUR_HPP
