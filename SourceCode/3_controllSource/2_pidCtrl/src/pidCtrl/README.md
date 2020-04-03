![](https://img.shields.io/github/stars/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/forks/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/tag/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/release/Alfystar/Scorbot-CA) ![](https://img.shields.io/github/issues/Alfystar/Scorbot-CA) ![](https://img.shields.io/bower/v/editor.md.svg)

------------

# Pid for Linux

Qui è definita una classe che realizza un PID in linux, viene ora usata all'interno del progetto, istanziandone 1 per ogni motore, e all'arrivo di una nuova lettura di encoder, viene aggiornato il controllo.
Il controllo è pensato per essere tempo variante, infatti il pid si aspetta di sapere quanto tempo è passato dall'ultima chiamata.