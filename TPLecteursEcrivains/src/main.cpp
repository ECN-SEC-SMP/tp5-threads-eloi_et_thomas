/**
 * @file main.cpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr) & Thomas Verron (Thomas.Verron@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 12-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <thread>
#include "Semaphore.hpp"

int ressourcePartagee;

Semaphore mySemaphore(1); // Sémaphore pour la ressource partagée

void lecteur(int numLecteur)
{
  for (int i = 0; i < 4; i++)
  {
    std::cout << "Lecteur n° " << numLecteur << " en cours " << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 20000));
    mySemaphore.P(numLecteur); // Demande d'accès à la ressource
    std::cout << "        Valeur lue = " << ressourcePartagee << "  " << endl;
    mySemaphore.V(numLecteur); // Libération de la ressource
  }
}

void ecrivain(int numEcrivain)
{
  int x;
  for (int i = 0; i < 4; i++)
  {
    std::cout << "Ecrivain n° " << numEcrivain << " en cours " << endl;
    mySemaphore.P(numEcrivain); // Demande d'accès à la ressource
    x = ressourcePartagee;
    this_thread::sleep_for(chrono::milliseconds(rand() % 20000));
    std::cout << "valeur à incrémenter de la ressourcePartagee = " << x << "  " << endl;
    ressourcePartagee = x + 1;
    mySemaphore.V(numEcrivain); // Libération de la ressource
  }
}

int main()
{
  const int nbr = 8;
  std::thread r[nbr];
  std::thread w[nbr];
  int ressourcePartagee = 0;

  for (int i = 1; i < nbr; i++)
  {
    r[i] = std::thread(lecteur, -i);
    w[i] = std::thread(ecrivain, i);
  }
  // Join des threads
  for (int i = 1; i < nbr; i++)
  {
    r[i].join();
    w[i].join();
  }
  return 0;
}
