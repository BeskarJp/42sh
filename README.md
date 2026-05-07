# 42sh - EPITECH Project

> Un interpréteur de commandes complet basé sur l'architecture du shell **TCSH**, développé dans le cadre du module Unix System Programming.

---

## 📝 Description

**42sh** est l'aboutissement du cycle Minishell d'EPITECH. Ce projet consiste en la création d'un shell robuste capable de gérer l'exécution de commandes complexes, la manipulation de variables, le contrôle de processus (Job Control) et une interface utilisateur interactive avancée.

L'objectif principal est la **stabilité** et la conformité avec le comportement du shell de référence : `tcsh`.

---

## Fonctionnalités

### 🛠️ Fondamentaux

* **Exécution standard** : Commandes système avec gestion du PATH.

* **Pipes & Redirections** :
    * Pipes (`|`) pour l'enchaînement.
    * Entrées/Sorties simples et doubles (`>`, `>>`, `<`, `<<`).

* **Séparateurs & Logique** : `;`, `&&`, `||`.

* **Subshells** : Groupement de commandes via `( )`.

### 📦 Gestion Avancée

* **Job Control** : Gestion des tâches en arrière-plan (`&`), et built-ins `jobs`, `fg`, `bg`.

* **Variables** : 
    * Variables d'environnement (`setenv`, `unsetenv`, `env`).
    * Variables locales (`set`, `unset`, `export`).
    * Expansion de variables via `$`.

* **Alias & Historique** : Système d'alias personnalisables et navigation dans l'historique des commandes (`!`).

* **Globbing** : Support des patterns `*`, `?`, `[ ]`.

### ⌨️ Interface Utilisateur

* **Line Edition** : Édition interactive de la ligne de commande (déplacement du curseur, suppression, gestion du mode Raw).

* **Auto-completion** : (Si implémenté) complétion dynamique des commandes et chemins.

* **Inhibiteurs** : Gestion des guillemets et backslashes.

### 🌟 Bonus Exclusifs

* **EpiClaude** : Assistant intelligent intégré pour l'aide aux commandes.

* **Built-in Editor** : Un éditeur de texte visuel (style Emacs) accessible via la commande `party-editor` ou `emac`.

* **Scripting** : Capacité à interpréter des fichiers scripts.

---

## 🚀 Installation et Usage

### Prérequis

* Un compilateur C (EPICLANG)

* La bibliothèque `ncurses` (pour l'éditeur visuel)

### Compilation

Générez l'exécutable à l'aide du Makefile :

```bash
make
```

### Lancement

```bash
./42sh
```

---

## 🧪 Tests et Erreurs

Le shell est conçu pour être rigoureusement identique au TCSH en termes de codes de retour et de messages d'erreur.

* **Codes de sortie** : Un `Segmentation Fault` retournera par exemple `139`.

* **Validation** : Les tests unitaires peuvent être lancés (si présents) via :

```bash
make tests_run
```

---

## ⚠️ Notes Importantes

* **Langage** : Écrit intégralement en C.

* **Avertissement EPITECH** : Ce projet est destiné à un usage pédagogique. Toute tentative de plagiat (copy-paste) par un étudiant d'EPITECH entraînera un score de **-42**.

* **Propriété** : Ce projet n'est absolument pas destiné à la vente.

---

*Projet réalisé par l'équipe 42sh - 2026*

*Laouënan Jupon, Hugo Minet, Joshua Knockaert, Noa Wasielewshi, Sylvain Chen*
