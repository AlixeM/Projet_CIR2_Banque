# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("CIR2_socket_final")

# Incluez les sous-projets.
add_subdirectory (socket)
add_subdirectory (customer)
