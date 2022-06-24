tp17
## Recherce du plus court chemin dans un réseau ferré

Voici les commandes pour exécuter le programme:
    se déplacer dans le dossier src :

```c
make clean && make
make run
```


![rundiag](exemple/print_ex.png)

# Geneve -> Coire

![rundiag](exemple/Geneve-Coire.png)

# Neuchatel -> Bellinzone

![rundiag](exemple/Neuchatel-Bellinzone.png)


1. J’ai créé la fonction d’erreur de saisie de la ville
2. Connexions entre les cités de couleur verte
3. Trajet de couleur Rouge
4. Ville de départ avec le plus grand carré par rapport aux autres villes
5. Itinéraire avec changement de couleur du cadre en rouge pour mieux identifier le trajet 

## Erreurs

1. Manque à gérer la mémoire d’enfiler, même si j’ai fait le free en parcourant la liste, il me marque encore une erreur
2. Les liaisons en vert entre les villes dans l’impression de la carte ne sont pas entièrement complètes. 
