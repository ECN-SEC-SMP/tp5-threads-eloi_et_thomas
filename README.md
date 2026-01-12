# TP5 - TP Threads

SEC 2

- Eloi Tourangin - <eloi.tourangin@eleves.ec-nantes.fr>
- Thomas Verron - <thomas.verron@eleves.ec-nantes.fr>

## Table des matières

1. [Compilation et Exécution](#compilation-et-exécution)
2. [Les Lecteurs-Ecrivains](#les-lecteurs-écrivains)
3. [Les Trains](#les-trains)

## Compilation et Exécution

### Méthode 1 : Utiliser make

```bash
# Compiler
make

# Exécuter
./build/main.out
```

### Méthode 2 : Utiliser le script bash

```bash
./build_and_execute.sh
```

## Les Lecteurs-Écrivains

### Q 1.1 Modifier le code des processus lecteur et ecrivain pour que la synchronisation permette de respecter les règles de cohérence de la valeur de la ressource partagée.

Nous avons utilisé la classe sémaphore fournit avec le TP "Semaphore.hpp" pour isoler la variable critique **ressourcePartagee**. Nous créons une semaphore mySemaphore avec une seule place (initialisée à 1) pour protéger l'accès à cette variable.

On encadre l'accès à la variable critique avec les opérations P et V de la sémaphore.

```c++
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
```

## Les Trains