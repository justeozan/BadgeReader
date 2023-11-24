# BadgeReader

# Contrôle d'accès RFID avec ESP32 et Raspberry Pi

Ce projet vise à créer une solution de contrôle d'accès à base de badges RFID en utilisant un microcontrôleur ESP32 et un Raspberry Pi. La solution permet de lire des badges RFID, de les comparer à une liste autorisée, et de signaler l'accès autorisé ou refusé.

## Prérequis

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Bibliothèque MFRC522](https://github.com/miguelbalboa/rfid)
- [Bibliothèque WiFi pour ESP32](https://github.com/espressif/arduino-esp32)
- [Python 3](https://www.python.org/downloads/)
- [Bibliothèque RPi.GPIO](https://pypi.org/project/RPi.GPIO/) (pour la communication avec le Raspberry Pi)

## Configuration matérielle

- ESP32-C3
- Module RFID MFRC522
- Raspberry Pi
- ...

## Installation et Configuration

1. Clonez ce dépôt : `git clone https://github.com/votre-utilisateur/controle-acces-rfid.git`
2. Ouvrez le code Arduino avec l'IDE Arduino.
3. Installez les bibliothèques nécessaires.
4. Téléchargez le code sur l'ESP32.
5. Copiez le script Python sur le Raspberry Pi.
6. Assurez-vous que le Raspberry Pi est configuré avec les bonnes dépendances.

## Utilisation

1. Connectez l'ESP32 et le Raspberry Pi au réseau Wi-Fi.
2. Exécutez le script Python sur le Raspberry Pi : `python raspberry_pi_code.py`
3. Alimentez l'ESP32.
4. Présentez un badge RFID au lecteur de l'ESP32.

## Fonctionnalités supplémentaires

- ...

## Licence

Ce projet est sous licence [MIT License](LICENSE).

---

**Auteur:** Alix WILMART, Lucas FERRAND, Ethan PETIT-JEAN, Ozan SAHIN, Amandine VIALLE-GUERIN
**Projet réalisé dans le cadre de:** Cours d'Hardware - GUARDIA 2
