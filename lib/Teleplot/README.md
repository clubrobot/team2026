# Teleplot
La librairie Teleplot sert à envoyer des messages interprétables par le (programme éponyme)[https://github.com/clubrobot/teleplot].

# Utilisation
Dans votre code, importez la librairie :
```c++
...
#include <Teleplot.h>
...
```
Ensuite vous devez initialiser la librairie :
```c++
Teleplot teleplot;
```

Vous pouvez ensuite envoyer directement des messages :

```c++
////////////////////////////////////
// Manipulation interne (à éviter)//
////////////////////////////////////
teleplot.send_string("Hello world"); // envoie "Hello world" au programme Teleplot
                                    // NB : vous devez gérer le formatage automatiquement
                                    // pour que Teleplot puisse interpréter le message
                                    // ATTENTION : Cette fonction ne devrait en pratique
                                    // pas être utilisée, notament car elle n'utilise pas
                                    // le tampon interne de la librairie
teleplot.envoie_tampon() // envoie le contenu du tampon interne
teleplot.ajout_ou_envoie_tampon("Hello world"); // ajoute "Hello world" au tampon interne, si le tampon est plein,
                                                // il envoie le contenu du tampon avant d'ajouter le nouveau message
                                                // si le message est trop long, il sera tronqué
///////////////////////////////////////
/////////// Usage normal //////////////
///////////////////////////////////////

teleplot.add_variable_float_2decimal("temperature", 25.5); // ajoute une variable "temperature" avec la valeur 25.5
teleplot.add_variable_int("compteur", 42); // ajoute une variable "compteur" avec la valeur 42
teleplot.add_variable_string("led jaune", "off"); // ajoute une variable "message" avec la valeur "Hello world"
teleplot.add_log("Hello world"); // ajoute un log "Hello world"
```

Pour utiliser les objets 3d, vous devez d'abord les créer :
```c++
// Créé une sphère nommée ballon en (0.5, 0, 0) de rayon 10, avec une rotation défini
// par le quaternion (0, 0, 0, 0) de couleur rouge (#ff0000) et une opacité de 0.8
Sphere sphere("ballon", 0.5, 0, 0, 10, 0, 0, 0, 0, 15, "#ff0000", 0.8);

sphere.sendSphereToTeleplot(teleplot); // envoie la sphère au programme Teleplot

sphere.setColor("#00ff00"); // change la couleur de la sphère en vert
sphere.sendSphereToTeleplot(teleplot); // envoie la sphère au programme Teleplot avec la nouvelle couleur

// Créé un cube nommé robot en (0.5, 0.2, 0) de taille 10x100x20, avec une rotation
// définie par le quaternion (10, 0, 0, 1) de couleur verte (#00ff00) et une opacité de 0.5
Cube cube("robot", 0.5, 0.2, 0, 10, 100, 20, 10, 0, 0, 1, "#00ff00", 0.5);

cube.sendCubeToTeleplot(teleplot); // envoie le cube au programme Teleplot

cube.setZPosition(0.5); // change la position en Z du cube
cube.sendCubeToTeleplot(teleplot); // envoie le cube au programme Teleplot avec la nouvelle position en Z
```