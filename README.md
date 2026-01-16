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

#### Description et code LE

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

#### Exemple d'exécution LE

```term
valeur initiale du sémaphore = 1
Lecteur n° -1 en cours
Lecteur n° -2 en cours
Ecrivain n° 2 en cours
Lecteur n° -4 en cours
Ecrivain n° 3 en cours
Lecteur n° -5 en cours
Ecrivain n° 6 en cours
Lecteur n° -7 en cours
Ecrivain n° Lecteur n° 4 en cours
Ecrivain n° 5 en cours
Ecrivain n° Lecteur n° -6 en cours
1 en cours
-3 en cours
Ecrivain n° 7 en cours
valeur à incrémenter de la ressourcePartagee = 0  
Ecrivain n° 2 en cours 
valeur à incrémenter de la ressourcePartagee = 1  
Ecrivain n° 2 en cours 
valeur à incrémenter de la ressourcePartagee = 2  
Ecrivain n° 2 en cours 
valeur à incrémenter de la ressourcePartagee = 3  
valeur à incrémenter de la ressourcePartagee = 4  
Ecrivain n° 5 en cours 
valeur à incrémenter de la ressourcePartagee = 5  
Ecrivain n° 5 en cours 
valeur à incrémenter de la ressourcePartagee = 6  
Ecrivain n° 5 en cours
valeur à incrémenter de la ressourcePartagee = 7  
        Valeur lue = 8  
Lecteur n° -6 en cours
        Valeur lue = 8
Lecteur n° -5 en cours
        Valeur lue = 8
Lecteur n° -1 en cours
        Valeur lue = 8
Lecteur n° -2 en cours
valeur à incrémenter de la ressourcePartagee = 8  
Ecrivain n° 3 en cours
valeur à incrémenter de la ressourcePartagee = 9  
Ecrivain n° 3 en cours
valeur à incrémenter de la ressourcePartagee = 10  
Ecrivain n° 3 en cours
valeur à incrémenter de la ressourcePartagee = 11
```

## Les Trains

### Q 2.1 Compléter le programme fourni du processus Controleur de façon à ce que le programme fonctionne correctement par rapport à cette première contrainte.

#### Description et code

Nous avons créé un booléen sens en plus de val qui permet de compter le nombre de trains en simultané.

```c++
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
```

#### Exemple d'exécution

```term
Train n° 1 arrive en A vers B 
Train n° -2 arrive en B vers A
Train n° -3 arrive en B vers A
Train n° -1 arrive en B vers A
Train n° 2 arrive en A vers B
Train n° 4 arrive en A vers B
Train n° 3 arrive en A vers B
Train n° -5 arrive en B vers A
Train n° 6 arrive en A vers B
Train n° 5 arrive en A vers B
Train n° 7 arrive en A vers B
Train n° -7 arrive en B vers A
Train n° 8 arrive en A vers B
Train n° -8 arrive en B vers A
Train n° -4 arrive en B vers A
Train n° -6 arrive en B vers A
Train n° -8 circule de B vers A  <<<<<<<<
Train n° -8 quitte le tronçon de voie unique 
Train n° 3 circule de A vers B  >>>>>> 
Train n° 7 circule de A vers B  >>>>>> 
Train n° 3 quitte le tronçon de voie unique 
Train n° 7 quitte le tronçon de voie unique 
Train n° -4 circule de B vers A  <<<<<<<<
Train n° -4 quitte le tronçon de voie unique
Train n° -7 circule de B vers A  <<<<<<<<
Train n° -3 circule de B vers A  <<<<<<<<
Train n° -3 quitte le tronçon de voie unique 
Train n° -7 quitte le tronçon de voie unique 
Train n° -6 circule de B vers A  <<<<<<<<
Train n° -6 quitte le tronçon de voie unique 
Train n° 4 circule de A vers B  >>>>>>
Train n° 4 quitte le tronçon de voie unique 
Train n° 1 circule de A vers B  >>>>>> 
Train n° 2 circule de A vers B  >>>>>> 
Train n° 1 quitte le tronçon de voie unique 
Train n° 2 quitte le tronçon de voie unique 
Train n° 6 circule de A vers B  >>>>>>
Train n° 5 circule de A vers B  >>>>>> 
Train n° 6 quitte le tronçon de voie unique 
Train n° 8 circule de A vers B  >>>>>> 
Train n° 5 quitte le tronçon de voie unique 
Train n° 8 quitte le tronçon de voie unique 
Train n° -2 circule de B vers A  <<<<<<<<
Train n° -2 quitte le tronçon de voie unique 
Train n° -5 circule de B vers A  <<<<<<<<
Train n° -1 circule de B vers A  <<<<<<<<
Train n° -5 quitte le tronçon de voie unique 
Train n° -1 quitte le tronçon de voie unique
```

### Q 2.2 Modifier le programme précédent du processus Controleur de façon à ce que le programme fonctionne correctement par rapport à la première contrainte et en évitant le risque de coalition.

#### Description et code 2

Nous avons modifié les conditions d'entrées des trains pour qu'un maximum de 2 trains puissent être sur le tronçon en même temps, dans le même sens. Il nous as suffit de rajouter une condition en plus du sens sur la variable val.

```c++
class Controleur
{
public:
  Controleur(int valeur_initiale) : val(valeur_initiale)
  {
  }

  bool controlinEnB(int numero)
  {
    if (val == 0 || (sens == 0 && val < 2))
    {
      val++;
      sens = 0;
      return true;
    }
    return false;
  }

  bool controlinEnA(int numero)
  {
    if (val == 0 || (sens == 1 && val < 2))
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
```

#### Exemple d'exécution 2

```term
Train n° 1 arrive en A vers B 
Train n° 2 arrive en A vers B 
Train n° -1 arrive en B vers A 
Train n° -2 arrive en B vers A 
Train n° -3 arrive en B vers A
Train n° 3 arrive en A vers B 
Train n° -4 arrive en B vers A 
Train n° 4 arrive en A vers B 
Train n° 5 arrive en A vers B 
Train n° 6 arrive en A vers B 
Train n° -6 arrive en B vers A 
Train n° -5 arrive en B vers A 
Train n° 7 arrive en A vers B 
Train n° -7 arrive en B vers A 
Train n° -8 arrive en B vers A 
Train n° 8 arrive en A vers B 
Train n° -8 circule de B vers A  <<<<<<<<
Train n° -7 circule de B vers A  <<<<<<<<
Train n° -7 quitte le tronçon de voie unique 
Train n° -8 quitte le tronçon de voie unique 
Train n° 2 circule de A vers B  >>>>>> 
Train n° 2 quitte le tronçon de voie unique 
Train n° 1 circule de A vers B  >>>>>> 
Train n° 1 quitte le tronçon de voie unique 
Train n° -2 circule de B vers A  <<<<<<<<
Train n° -2 quitte le tronçon de voie unique 
Train n° -6 circule de B vers A  <<<<<<<<
Train n° -6 quitte le tronçon de voie unique 
Train n° -5 circule de B vers A  <<<<<<<<
Train n° -5 quitte le tronçon de voie unique 
Train n° 4 circule de A vers B  >>>>>> 
Train n° 5 circule de A vers B  >>>>>> 
Train n° 5 quitte le tronçon de voie unique 
Train n° 7 circule de A vers B  >>>>>> 
Train n° 4 quitte le tronçon de voie unique 
Train n° 7 quitte le tronçon de voie unique 
Train n° 6 circule de A vers B  >>>>>> 
Train n° 6 quitte le tronçon de voie unique 
Train n° -3 circule de B vers A  <<<<<<<<
Train n° -3 quitte le tronçon de voie unique
Train n° -1 circule de B vers A  <<<<<<<<
Train n° -4 circule de B vers A  <<<<<<<<
Train n° -1 quitte le tronçon de voie unique 
Train n° -4 quitte le tronçon de voie unique 
Train n° 3 circule de A vers B  >>>>>> 
Train n° 8 circule de A vers B  >>>>>> 
Train n° 3 quitte le tronçon de voie unique 
Train n° 8 quitte le tronçon de voie unique
```

### Q 2.3 Modifier le programme précédent du processus Controleur de façon à ce que le programme fonctionne correctement par rapport à la première contrainte et en évitant le risque de coalition et en étant équitable.

#### Description et code 3

Nous avons ajouté deux compteurs de trains dans chaque sens pour limiter le nombre de trains successifs dans un même sens à 3. Dès qu'un train d'un sens passe, on remet à 0 le compteur de l'autre sens.

```c++
class Controleur
{
public:
  Controleur(int valeur_initiale) : val(valeur_initiale)
  {
  }

  bool controlinEnB(int numero)
  {
    if ((val == 0 || (sens == 0 && val < 2)) && nbTrainsB < 3)
    {
      nbTrainsA = 0;
      val++;
      nbTrainsB++;
      sens = 0;
      return true;
    }
    return false;
  }

  bool controlinEnA(int numero)
  {
    if ((val == 0 || (sens == 1 && val < 2)) && nbTrainsA < 3)
    {
      nbTrainsB = 0;
      val++;
      nbTrainsA++;
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
  int nbTrainsA = 0;
  int nbTrainsB = 0;
};
```

#### Exemple d'exécution 3

```term
Train n° 1 arrive en A vers B 
Train n° 2 arrive en A vers B 
Train n° -1 arrive en B vers A 
Train n° -3 arrive en B vers A 
Train n° 3 arrive en A vers B 
Train n° -2 arrive en B vers A 
Train n° -4 arrive en B vers A
Train n° 5 arrive en A vers B
Train n° -5 arrive en B vers A
Train n° 4 arrive en A vers B
Train n° 7 arrive en A vers B
Train n° -7 arrive en B vers A
Train n° 8 arrive en A vers B
Train n° -8 arrive en B vers A
Train n° 6 arrive en A vers B
Train n° -6 arrive en B vers A
Train n° -5 circule de B vers A  <<<<<<<<
Train n° -3 circule de B vers A  <<<<<<<<
Train n° -3 quitte le tronçon de voie unique 
Train n° -5 quitte le tronçon de voie unique 
Train n° -7 circule de B vers A  <<<<<<<<
Train n° -7 quitte le tronçon de voie unique 
Train n° 6 circule de A vers B  >>>>>>
Train n° 2 circule de A vers B  >>>>>> 
Train n° 6 quitte le tronçon de voie unique 
Train n° 2 quitte le tronçon de voie unique 
Train n° -6 circule de B vers A  <<<<<<<<
Train n° -1 circule de B vers A  <<<<<<<<
Train n° -6 quitte le tronçon de voie unique 
Train n° -8 circule de B vers A  <<<<<<<<
Train n° -1 quitte le tronçon de voie unique 
Train n° -8 quitte le tronçon de voie unique 
Train n° 7 circule de A vers B  >>>>>> 
Train n° 7 quitte le tronçon de voie unique 
Train n° 3 circule de A vers B  >>>>>> 
Train n° 3 quitte le tronçon de voie unique 
Train n° -2 circule de B vers A  <<<<<<<<
Train n° -2 quitte le tronçon de voie unique 
Train n° 1 circule de A vers B  >>>>>> 
Train n° 1 quitte le tronçon de voie unique 
Train n° 8 circule de A vers B  >>>>>> 
Train n° 8 quitte le tronçon de voie unique 
Train n° -4 circule de B vers A  <<<<<<<<
Train n° -4 quitte le tronçon de voie unique 
Train n° 4 circule de A vers B  >>>>>> 
Train n° 5 circule de A vers B  >>>>>>
Train n° 4 quitte le tronçon de voie unique 
Train n° 5 quitte le tronçon de voie unique
```

#### Tests finaux dans le main

Nous avons augmenté le nombre de train dans un sens 20 dans l'un et 5 dans l'autre et nous voyons bien qu'il n'y en a bien que 1 de temps, en temps dans un sens.

#### Remarque Bonus

Si tous les trains dans un sens sont passé et qu'il en reste dans l'autre sens. Seuls 3 trains passerons, il faudrait vérifier, s'il n'y a plus de trains dans un sens, pour laisser passer tous les trains qui restent.
