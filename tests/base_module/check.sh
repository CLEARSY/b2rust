#!/bin/bash

modele=$1
original=$2

cible="$original.tmp"

cp $original $cible

rustfmt $modele
rustfmt $cible

regex_struct="^[[:space:]]*(pub[[:space:]]+)?struct[[:space:]]+([[:alnum:]_]+)"
regex_method="^[[:space:]]*(pub[[:space:]]+)?fn[[:space:]]+([[:alnum:]_]+)[[:space:]]*\((\s*[^)]*\s*(,\s*[^)]*\s*)*)\)"



# Extraire la déclaration des structs du modèle
declare -a declStruct_modele
while IFS= read -r ligne; do
  if [[ $ligne =~ $regex_struct ]]; then
    entete=${BASH_REMATCH[1]}
    nom_struct=${BASH_REMATCH[2]}
    struct="$entete struct $nom_struct"
    declStruct_modele+=("$struct")
  fi
done < "$modele"

# Extraire la déclaration des structs de la cible
declare -a declStruct_cible
while IFS= read -r ligne; do
  if [[ $ligne =~ $regex_struct ]]; then
    entete=${BASH_REMATCH[1]}
    nom_struct=${BASH_REMATCH[2]}
    struct="$entete struct $nom_struct"
    declStruct_cible+=("$struct")
  fi
done < "$cible"

# Vérifier si les éléments du modèle sont inclus dans la cible
declare -a missing_struct
for struct in "${declStruct_modele[@]}"; do
  if ! [[ " ${declStruct_cible[*]} " =~ " $struct " ]]; then
    missing_struct+=("$struct")
  fi
done

if [ ${#missing_struct[@]} -eq 0 ]; then
  echo "Every struct is implemented."
else
  echo "WARNING: The following structs are not implemented:"
  for struct in "${missing_struct[@]}"; do
    echo "$struct"
  done
  rm $cible
  exit 1
fi

# Extraire les signatures des fonctions déclarées du modèle
declare -a signatures_modele
while IFS= read -r ligne; do
  if [[ $ligne =~ $regex_method ]]; then
    entete=${BASH_REMATCH[1]}
    nom_fonction=${BASH_REMATCH[2]}
    parametres=${BASH_REMATCH[3]}
    signature="$entete fn $nom_fonction($parametres)"
    signatures_modele+=("$signature")
  fi
done < "$modele"

# Extraire les signatures des fonctions déclarées de la cible
declare -a signatures_cible
while IFS= read -r ligne; do
  if [[ $ligne =~ $regex_method ]]; then
    entete=${BASH_REMATCH[1]}
    nom_fonction=${BASH_REMATCH[2]}
    parametres=${BASH_REMATCH[3]}
    signature="$entete fn $nom_fonction($parametres)"
    signatures_cible+=("$signature")
  fi
done < "$cible"

# Vérifier si les éléments du modèle sont inclus dans la cible
declare -a missing_method
for signature in "${signatures_modele[@]}"; do
  if ! [[ " ${signatures_cible[*]} " =~ " $signature " ]]; then
    missing_method+=("$signature")
  fi
done

if [ ${#missing_method[@]} -eq 0 ]; then
  echo "Every method is implemented."
else
  echo "WARNING: The following methods are not implemented:"
  for method in "${missing_method[@]}"; do
    echo "$method"
  done
  rm $cible
  exit 1
fi

rm $cible
