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
#include <mutex>
#include <condition_variable>
#include "Controleur.hpp"

std::mutex mtx;
std::condition_variable cv;
Controleur ctrl(0); // LE PROCESSUS CONTROLEUR

// TrainAB
void circuleAB(int numTrain)
{
  std::cout << "Train n° " << numTrain << " arrive en A vers B " << endl;
  this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
  std::unique_lock<std::mutex> lck(mtx);
  cv.wait(lck, [numTrain]
          { return ctrl.controlinEnA(numTrain); }); // ATTENTE D'AUTORISATION DE CIRCULER
  lck.unlock();
  // DEBUT DU PARCOURS A->B
  std::cout << "Train n° " << numTrain << " circule de A vers B  >>>>>> " << endl;
  this_thread::sleep_for(chrono::milliseconds(rand() % 100));

  // FIN DU PARCOURS A->B
  std::cout << "Train n° " << numTrain << " quitte le tronçon de voie unique " << endl;
  lck.lock();
  ctrl.controloutEnB(numTrain); // SIGNAL DE SORTIE AU CONTROLEUR
  lck.unlock();
  cv.notify_all();
}

// TrainBA
void circuleBA(int numTrain)
{
  std::cout << "Train n° " << numTrain << " arrive en B vers A " << endl;
  this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
  std::unique_lock<std::mutex> lck(mtx);
  cv.wait(lck, [numTrain]
          { return ctrl.controlinEnB(numTrain); }); // ATTENTE D'AUTORISATION DE CIRCULER
  lck.unlock();
  // DEBUT DU PARCOURSs B->A
  std::cout << "Train n° " << numTrain << " circule de B vers A  <<<<<<<<" << endl;
  this_thread::sleep_for(chrono::milliseconds(rand() % 100));

  // FIN DU PARCOURS B->A
  std::cout << "Train n° " << numTrain << " quitte le tronçon de voie unique " << endl;
  lck.lock();
  ctrl.controloutEnA(numTrain); // SIGNAL DE SORTIE AU CONTROLEUR
  lck.unlock();
  cv.notify_all();
}

int main()
{
  const int nbrA = 5;
  const int nbrB = 20;
  std::srand(std::time(nullptr));
  std::thread trainsAB[nbrA];
  std::thread trainsBA[nbrB];

  // INITALISE TRAINS ET CONTROLEUR
  for (int i = 1; i < nbrA; i++)
  {
    trainsAB[i] = std::thread(circuleAB, i);
  }
  for( int i = 1; i < nbrB; i++){
    trainsBA[i] = std::thread(circuleBA, -i);
  }
  // JOIN DES THREADS
  for (int i = 1; i < nbrA; i++)
  {
    if (trainsAB[i].joinable())
      trainsAB[i].join();
  }
  for( int i = 1; i < nbrB; i++){
    if (trainsBA[i].joinable())
      trainsBA[i].join();
  }
  return 0;
}
