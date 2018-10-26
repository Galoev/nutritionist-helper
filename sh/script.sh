#!/bin/bash

source script.lib.sh

#---------------------------------------------------------------------------------
path_qt="$(config_get path_qt)";
path_qt_tools="$(config_get path_qt_tools)";
make_prog="$(config_get make_prog)";

git_origin_path="https://github.com/Ilkin-Galoev/nutritionist-helper.git"
repo_name="nutritionist-helper"
path_pro_file="project/program.pro"
qmake_prog="qmake.exe"
binarycreator_prog="/c/Qt/Tools/QtInstallerFramework/3.0/bin/binarycreator.exe"
windeployqt_prog="windeployqt.exe"
executable_name="nutritionist-helper"
#---------------------------------------------------------------------------------

PATH=$path_qt:$PATH
PATH=$path_qt_tools:$PATH

version_idx1=0
version_idx2=0
version_idx3=0
version_previous_num=""
version_previous=""

cd ..
if [ $# -eq 1 ]; then
    case $1 in 
    "--download")
        run_download
    ;;
    "--build")
        run_build
    ;;
    "--install")
        run_build
        run_install
    ;;
    "--publicate")
        run_publicate
    ;;
    *)
    print_hint
    ;;
    esac
    
    tput setaf 2; echo "DONE ALL!"
    exit 0
else 
    echo "Укажите один аргумент"
    print_hint
fi
cd sh/