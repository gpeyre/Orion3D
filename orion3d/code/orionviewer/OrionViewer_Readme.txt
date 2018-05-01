             - OrionViewer -
---------------------------------------------
   copyright (c) gabriel&antoche 2000
---------------------------------------------
par Gabriel Peyre - nikopol0@club-internet.fr
  & Antoche       - antoche@altern.org
---------------------------------------------
Derniere release & code sources diponibles 
sur le site d'Orion3D :
http://perso.wanadoo.fr/orion3d
---------------------------------------------
Commentaires :
* Programme de test d'Orion3D.
* Permet de charger les différents types de
fichiers d'Orion3D :
  - .KSP : géométrie statique [les décors], 
fichiers produits par le plug-in pour 3DSMax
KSPExporter.
  - .KRD : géométrie dynamique [les objets],
fichiers produits par le programme 
KRDConverter [a partir de fichiers .ASE], et 
bientôt par le plug-in pour 3DSMax, 
KRDExporter
* Permet de tester les différentes librairies
d'effets spéciaux entre autre :
  - MathsSurfaces : gestion de surfaces ma-
tématiques.
  - MetaBalls : gestion de meta-balls.
  - Particules : gestion de systemes de par-
ticules.
----------------------------------------------
Utilisation :
* En appuyant sur espace, on jongle entre le
mode "deplacement" et le mode "menu".
* En mode "deplacement", il y a deux types de
camera :
  - satellite : bouton droit+deplacement pour 
tourner autour de l'objet, bouton droit+gauche
pour avancer/reculer.
  - libre : bouton droit+deplacement pour 
bouger la tête, fleche pour se déplacer.
* En mode menu, on peut faire apparaitre un
menu ave le bouton droit, qui permet de
choisir le type de caméra, de charger des 
fichiers, etc.
----------------------------------------------

###############################################################
#                     compilation notes                       #
###############################################################

To compile under the following OS, set the "compilation direcives"
lines [in OR_Config.h] to :

       WIN32        #        UNIX         #        MAC OS
################################################################
// #define _UNIX_   # #define _UNIX_      # // #define _UNIX_
// #define _MAC_OS_ # // #define _MAC_OS_ # #define _MAC_OS_
#define _WIN32_     # // #define _WIN32_  # // #define _WIN32_

To use the following API for input/output, set the "input/output directives"
lines [in OR_Config.h] to :

       GLUT            #        WIN32
###############################################
#define _USE_GLUT_     # // #define _USE_GLUT_    
// #define _USE_WIN32_ # #define _USE_WIN32_