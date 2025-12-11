#!/bin/bash

# Lancer le serveur à gauche
gnome-terminal --geometry=80x50+10+10 -- bash -c "./ircserv 4444 0; exec bash"

# Pause pour que le serveur démarre
sleep 1

# Lancer le premier client en bas à droite
gnome-terminal --geometry=80x25+1200+600 -- bash -c "nc localhost 4444;"

# Lancer le deuxième client en haut à droite
gnome-terminal --geometry=80x25+1200+10 -- bash -c "nc localhost 4444;"
