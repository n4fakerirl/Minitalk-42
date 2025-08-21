# minitalk - 42

## 📚 Description

`minitalk` est un projet de l'école 42 qui permet de communiquer entre deux programmes via **signaux UNIX**.  
Le serveur reçoit les signaux et reconstruit le message, le client envoie les caractères bit par bit avec `SIGUSR1` (1) et `SIGUSR2` (0).  

---

## 🧠 Fonctionnement

* Le serveur affiche son PID
* Le client prend en argument le PID et le message
* Les signaux sont envoyés pour chaque bit
* Le serveur recompose le message et l’affiche
* En bonus, le serveur renvoie un signal au client pour confirmer la réception

---

## ⚙️ Compilation

| Commande      | Description                                 |
| ------------- | ------------------------------------------- |
| `make`        | Compile `client` et `server`                |
| `make clean`  | Supprime les fichiers objets (`.o`)         |
| `make fclean` | Supprime objets et exécutables              |
| `make re`     | Nettoie puis recompile entièrement          |

---

## 🖼️ Note du projet

<p align="center">
  <img width="199" height="169" alt="image" src="https://github.com/user-attachments/assets/0f81d37f-0483-4001-948e-bc940ce6b006" />
</p>

---

## 🫐 Auteur

* Océane (ocviller)
* Projet réalisé à 42 Paris, 2025
