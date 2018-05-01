######################################################################
#                       plug ins pour 3DSMax                         #
######################################################################

Tous les plugins d'Orion3D ont ete ecrit par Antoche [antoche@altern.org]

######################################################################
#                       licence notes                                #
######################################################################

All files under /ksp exporter/ and /krd exporter/ are :
       Copyright (C) 2000-2001 The Orion3D Rewiew Board                                  
Refer to orion3d_licence.txt for more details about the Orion3D Licence.
------------------------------------------------------------------------
Tous les fihciers sous les repertoires /ksp exporter/ and /krd exporter/ sont :
       Copyright (C) 2000-2001 The Orion3D Rewiew Board 
Se reporter a orion3d_licence.txt pour plus de details sur cette licence.

######################################################################

krd exporter :
  - Export de la hierarchy dynamique au format krd.
  - Les objets exportes sont pour l'instant :
      * les meshs [support de textures BMP].
      * les lights [target spot, free spot, target direct, free direct].
      * les cameras [free, target].
      * les gizmos [cube, sphere, cylindre].
      * les forces [bientot disponible].
      * les systemes de particules [bientot disponible].
      * les deflecteurs [bientot disponible].
  - pour faire fonctionner le plugin :
      * le fichier krd exporter.dle doit se trouver sous plugins/ de max.
      * selectionner export>fichier krd

ksp exporter :
  - Export de la geometrie statique [les decors] au format ksp.
  - Le format KRD comprend :
      * un BSP utilisé pour la detection de collision.
      * des portals faisant la jonction entre differentes areas, pour accelerer le rendu.
  - Se reporter au fichier instruction_graphistes.txt pour de plus amples details.
  - pour faire fonctionner le plugin :
      * le fichier ksp exporter.dle doit se trouver sous plugins/ de max.
      * selectionner export>fichier ksp.

#######################################################################

