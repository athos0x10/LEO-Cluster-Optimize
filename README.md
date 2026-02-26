# Projet ingénierie des réseaux (2025-2026)

## Sujet : Clustering de terminaux utilisateurs dans un réseau de constellations de satellites

On souhaite construire des **clusters d'utilisateurs** afin de faire pointer une constellation de satellite de façon optimale. Les satellites sont du types LEO (Low Earth Orbit), ils servent notamment à fournir un accès au réseau type *Starlink*. Ainsi, il est essentiel de prendre en considération le déplacement constant des satellites dans ce type de constellation. En effet, au bout d'une certaine période, il faudra de nouveau orienter le faisceau des satellites. En conséquence, notre solution doit être un compromis entre rapidité afin de calculer les nouveaux clusters et précision afin de minimiser le nombre de clusters.

Nous possédons les localisations des utlisateurs au format **CSV/HTML**, il faudra donc déveloper une méthode de parsing.

Hypothèses :
    - Cluster de taille fixe (**90km**): chaque cluster aura un diamètre de 90km.
    - Pas de contrainte sur le centre du cluster: pas besoin de pointer le centre sur des endroits précis.
    - Plusieurs clusters peuvent se superposer: permet de répondre à un besoin important dans une zone spécifique.
    - Débit par cluster: 1, 2 ou 3 Gps.

## Ordre de traitement

La première question est de se demander comment nous allons traiter les informations, i.e faire un prétraitement des données, les prendre aléatoirement... Pour cela, on va d'abord faire un état de l'art.

### Propositions précédentes des étudiants de l'ENSEEIHT

Leur idée et de faire une phase de prétraitement afin d'éviter de traiter les données comme un bloc monolithique lors de la phase de recherche de clusters. Leur idée est de répartir la liste de données en sous-groupe dans l'idée d'accroître la performance de l'algorithme de clusters et de répondre au critère technique de la performance. Pour cela, ils ont crée des groupes de points proches en utilisant la distance cartésienne. 

Au départ 87 898 utilisateurs initiaux, l'algorithme génère 4 169 zones connexes.

-> L'idée du prétraitement est clairement pertinente afin de réduire le nombre de données à traiter lors de la recherche des clusters afin d'augmenter la performance de l'algorithme. En effet, ce traitement ne se fait qu'à chaque fois qu'il y a un changement dans la base de données et encore on pourrait adapter l'algorithme pour qu'il ne recalcule que les zones concernés mais cela n'est pas l'objectif. On considère une base de données **statiques**. Traitement monolithique implique une précision maximale pour les clusters mais nécessite plus de temps.