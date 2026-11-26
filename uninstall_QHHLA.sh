# ============================================================================= 
# QHHLA SoftEdu - Quantum HHL Algorithm Educational Software
# =============================================================================
#
# Copyright (C) 2026
#
#   [1] Esteban Pico Rueda*						                       
#   [2] Julian Andrés Salamanca Bernal**                                      
#   [3] Diego Julián Rodríguez Patarroyo***				                   		           
#                                                                             
#   [1] epicor@udistrital.edu.co (Licenciado Universidad Distrital)        
#   [2] jasalamanca@udistrital.edu.co (profesor Universidad Distrital)        
#   [3] djrodriguezp@udistrital.edu.co (profesor Universidad Distrital)       
#									                                           
#  *,** Grupo de Física e Informática (FISINFOR)		                       
#  *** Grupo de Laboratorio de Fuentes Alternas de Energía (LIFAE)	           
#  *,**,*** Universidad Distrital Francisco José de Caldas (Bogotá, Colombia) 
#
#  
# Web page: https://github.com/fisinforgh/SEQHHLA.git 
#
# LICENSE: GNU General Public License v3.0 (GPLv3) or later
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# =============================================================================

#! /bin/bash

#This script UNINSTALL QHHLASoftEdu software

sep="/"
sus="_"
sdot="."
deskEXT="desktop"
cont=0


Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White
Color_Off='\033[0m'       # Text Reset
Bg_red='\033[0;41m'

messageUNIS=$(echo "Welcome to the QHHLA SoftEdu UNINSTALL wizard"
    echo "You are about to uninstall QHHLA SoftEdu software"
    echo "If you are completely sure, please click on UNINSTALL"
)

echo "$messageUNIS" | (zenity --text-info --title="QHHLA SoftEdu uninstall" --width=800 --height=400 --ok-label='UNINSTALL' --cancel-label='Exit')
if [ $? -eq 1 ]; then
    echo "Exit"
    exit 2
fi

(zenity --info --text="Please click CONTINUE to select \"Desktop\" Folder to UNINSTALL QHHLA SoftEdu desktop's icon" --title="QHHLA SoftEdu UNINSTALL desktop icon" --ok-label='CONTINUE' --width=800 --height=400 )

dirDESK=$(zenity --file-selection --directory --title="QHHLA SoftEdu UNINSTALL choose a Desktop Folder" --width=800 --height=400)

cd
homeDIR=$(pwd)
echo "Home folder: $homeDIR/"
echo " "

hiddenFILE=".pathDIR_QHHLASoftEdu.txt"
dirNAME="QHHLASoftEdu"
tarFILE="QHHLASoftEdu.tar"
pathINSTALL=$(echo "$homeDIR$sep$hiddenFILE")

manUNIS=$( echo "Remove QHHLA SoftEdu software manually."
echo ""
echo "1. Find installation folder and remove:"
echo "  $dirNAME and $tarFILE"
echo ""
echo "2. Go to the desktop folder and remove:"
echo "  QHHLA.desktop or $dirNAME.desktop"
echo ""
echo "3. Go to hidden file \".bash_aliases\" and remove these lines:"
echo "   # QHHLASoftEdu globally available executable "
echo "   export PATH=\"some_folder_to$sep QHHLASoftEdu:\$PATH\""
echo ""
echo "4. Check if .pathDIR_QHHLASoftEdu.txt exists, then erase it.")

echo $pathINSTALL

if [ -f $pathINSTALL ]; then
    read -r line < $pathINSTALL
else
    (zenity --info --text="$manUNIS" --width=800 --height=400 --ok-label='Close' )
    exit 2
fi

echo "0. $line"

if [ -d "$line" ]; then
    cd "$line"
    cd ..
    installDIR=$(pwd)
else
    installDIR=$(dirname "$line")
fi

echo "Installation directory: $installDIR"

# 1. Eliminar acceso directo del escritorio (revisa QHHLA.desktop y QHHLASoftEdu.desktop)
echo "$dirDESK"
if [ -n "$dirDESK" ] && [ -d "$dirDESK" ]; then
    if [ -f "$dirDESK/QHHLA.desktop" ]; then
        echo "1 rm $dirDESK/QHHLA.desktop"
        rm -f "$dirDESK/QHHLA.desktop"
    fi
    if [ -f "$dirDESK/$dirNAME.desktop" ]; then
        echo "1 rm $dirDESK/$dirNAME.desktop"
        rm -f "$dirDESK/$dirNAME.desktop"
    fi
fi

# 2. Limpiar entradas de .bash_aliases
if [ -f "$homeDIR/.bash_aliases" ]; then
    echo "2 cleaning .bash_aliases"
    sed -i "/$dirNAME/d" "$homeDIR/.bash_aliases"
fi

# 3. Eliminar el archivo .tar si aún existe en el directorio de instalación
if [ -f "$installDIR/$tarFILE" ]; then
    echo "3 rm $installDIR/$tarFILE"
    rm -f "$installDIR/$tarFILE"
fi

# 4. Eliminar el archivo de rastreo oculto
if [ -f "$pathINSTALL" ]; then
    echo "4 rm $pathINSTALL"
    rm -f "$pathINSTALL"
fi

# 5. Eliminar la carpeta del programa (Último paso para evitar borrar el script en ejecución)
if [ -d "$installDIR/$dirNAME" ]; then
    echo "5 rm -rf $installDIR/$dirNAME"
    rm -rf "$installDIR/$dirNAME"
fi

(zenity --info --text="UNINSTALL successfully completed" --width=800 --height=400 --ok-label='Close' )
exit 0