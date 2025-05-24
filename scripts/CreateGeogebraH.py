from geogebra import Geogebra
import os
import re
#Exporte les points du fichier geogbra sous forme d'un .h.
#les points d'interet du geogbra doivent contenir un des trois mots-clés
#   Bleu: pour les points d'intérêt de l'équipe bleu
#   Jaune: pour les points d'intérêt de l'équipe jaune
#   All: pour les points d'intéret commun aux deux équipes.
#Pour chaque variable avec Bleu il en faut une autre avec Jaune à la place.

CHEMIN_POINT_H="../include/Geogebra.h"
CHEMIN_GEOGEBRA="../maps/map_2025.ggb"
#on lit les angles pour pouvoir les sauvegarder et ne pas les ecraser
f = open(CHEMIN_POINT_H, "r")
thetas_bleu={}
thetas_jaune={}
lines=f.readlines()
pattern = r"Position\([^,]+,\s*[^,]+,\s*([^)]+)\),\s*//\s*(\w+)_\s*(\w+)"
for l in lines:
    match = re.search(pattern, l)
    if(match):
        a = match.group(1)  # "A"
        b = match.group(2)  # "B"
        color = match.group(3)  # "C"
        if(color=="jaune"):
            thetas_jaune[b]=a
        else:
            thetas_bleu[b]=a
f.close()

#charge le fichier geogebra
geo=Geogebra(CHEMIN_GEOGEBRA)

all=geo.getall("")

elements = geo.root.findall("./construction/element")

# Extraire les valeurs des attributs 'label'
element_names = [elem.get("label") for elem in elements if elem.get("label") is not None]
liste_bleu=[]
liste_jaune=[]
for e in element_names:
    if(e.lower().__contains__("bleu")):
        liste_bleu.append(e)
    elif(e.lower().__contains__("jaune")):
        liste_jaune.append(e)
    elif(e.lower().__contains__("all")):
        liste_bleu.append(e)
        liste_jaune.append(e)

noms=""
var_bleu=""
var_jaunes=""
id=0
error=0
for e in liste_bleu:
    other_name=e.lower().replace("bleu","jaune")
    found=False
    #on cherche pour un point jaune avec le même nom
    for e_j in liste_jaune:
        #quand il est trouve on l'ajoute au .h
        if(e_j.lower()==other_name):
            name=e.lower().replace("bleu","")
            noms+="#define "+name+" "+str(id)+"\n"
            point=geo.get(e_j)
            theta="1.570796327"
            if(thetas_jaune.__contains__(name)):
                theta=thetas_jaune[name]
            var_jaunes+="   Position("+str(point[0])+"f, "+str(point[1])+"f,"+theta+"), //"+name+"_jaune"+"\n"
            found=True
            break

    #si on a pas de point avec le même nom on met une erreur
    if not found:
        error=1
        print("Le point",e," n'a pas de point de la team jaune associé.")
    #o najoute le point bleu.
    point=geo.get(e)
    theta="1.570796327"
    if(thetas_bleu.__contains__(name)):
        theta=thetas_bleu[name]
    var_bleu+="   Position("+str(point[0])+"f, "+str(point[1])+"f,"+theta+"), //"+name+"_bleu"+"\n"
    id+=1

#on crée le fichier
f = open(CHEMIN_POINT_H, "w")
f.write("#ifndef TEAM2025_GEOGEBRA_H\n#define TEAM2025_GEOGEBRA_H\n#include \"Odometry.h\" \n")
f.write(noms)
f.write("\n")

f.write("//position geogebra de la team jaune\n")
f.write("struct Position positions_jaune[] = {\n")
f.write(var_jaunes)
f.write("};\n")
f.write("\n")
f.write("//position geogebra de la team bleu\n")
f.write("struct Position positions_bleu[] = {\n")
f.write(var_bleu)
f.write("};\n")
f.write("\n")
f.write("struct Position* positions_match;//ce pointeur vaut soit positions_jaunes soit positions_bleu en fonction de la couleur.\n")
f.write("#endif //TEAM2025_GEOGEBRA_H\n")


f.close()

print("Création du fichier avec",error,"erreurs")
    