# Guide pour l'organiastion - 42sh

Ce document définit les règles de travail pour le projet **42sh**. L'objectif est de pas faire n'importe quoi et être organisé entre nous.

---

## 📝 Norme de Commit

Pour la défense, on adapte un format de commit. Elle permet d'identifier rapidement l'auteur et ses changements.

**Format :** `[Initiales][Branche] Type: Description`

* **Initiales** : Tes initiales (ex: `[L.J]`).

* **Branche** : La feature concernée (ex: `[history]`).

* **Type** :
    * `Feat` : Nouvelle fonctionnalité.
    * `Fix` : Correction de bug.
    * `Docs` : Documentation (README, Doxygen).
    * `Style` : Changement de formatage/norme (sans impact sur le code).

> **Exemple :** `[L.J][main] Add: Add minshell2 of 'L.J' to 42sh's repository`

---

## 🌿 Stratégie de Branches

* **`main`** : Branche de la TA. Tout code sur cette branche doit compiler et être fonctionnel.

* **Branches de fonctionnalités** : Créer une branche par feature/bonus qu'on fait (ex: `feat/globbing`, `bonus/parrot`).

* **Workflow** : Une branche = une feature. Une fois terminée, ouvrez une **Pull Request (PR)**. Me demander si vous savez pas comment faire.

---

## 🚢 Pull Requests & Validation

Pour assurer la stabilité de la branche main, chaque fusion vers `main` doit respecter :

* **Revue de code** : Validation par au moins **1 ou 2 membres** du groupe.

* **CI/CD** : Les tests GitHub Actions doivent être validés.

* **Zéro Black Box** : Ne fusionnez pas de code que les autres membres ne sont pas capables de reprendre ou de corriger en cas d'absence.

---

## 📂 Organisation du Dépôt

* **Source** : Inclure tous les fichiers nécessaires à la compilation.

* **Nettoyage** : Ne jamais commit de fichiers inutiles (binaires, fichiers temporaires, fichiers `.o`).

---

## 💡 Conseils & Stabilité

* **Documentation** : Pour qu'on puisse tous comprendre le code de chacun, on va faire de la documentation. Pour le cas ici, on va faire du `Doxygen`, on va devoir utiliser ça lors de nos années suppérieurs donc autant utiliser ça. (Extensuion VS Code : `https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen`)

* **Tests Unitaires** : Écrivez des tests au fur et à mesure de l'ajout des fonctionnalités pour sécuriser la croissance du code.

* **Référence** : Le shell de référence pour la syntaxe et la compatibilité est `tcsh`.

* **Communication** : On n'hésite pas à communiquer sur le projet. Et utiliser le Trello que notre cher Sylvain à fait (`https://trello.com/invite/b/69ca8676cd507e8c7aa98a58/ATTIaa9eebddc0d38e3fffb21c7ba31c57d925FB2808/42sh`)

---

*{EPITECH} - Projet 42sh - 2026*
