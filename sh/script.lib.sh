config_read_file() {
    (grep -E "^${2}=" -m 1 "${1}" 2>/dev/null || echo "VAR=__UNDEFINED__") | head -n 1 | cut -d '=' -f 2-;
}

config_get() {
    val="$(config_read_file config.cfg "${1}")";
    if [ "${val}" = "__UNDEFINED__" ]; then
      os=${OSTYPE//[0-9.-]*/}
      case "$os" in
        darwin)
          val="$(config_read_file config-defaults-darwin.cfg "${1}")";
          ;;
        msys)
          val="$(config_read_file config-defaults-win.cfg "${1}")";
          ;;
        linux)
          echo "Значения по умолчанию для OS Linux не определены"
          ;;
        *)
        echo "Unknown Operating system $OSTYPE"
        exit 1
      esac
      printf -- "%s" "${val}";
    fi
}

print_hint(){
    echo "--download"
    echo "--build"
    echo "--install"
    echo "--publicate"
}

print_err () {  # $1 - 
    if [ $? -eq 0 ]; then
        tput setaf 2
        echo $1 ":DONE"
        tput sgr0
        echo
    else
        tput setaf 1
        echo $1 ":FAIL"
        tput sgr0
        exit 2
    fi
}

cmd_out () {  # $1 - command
    tput setaf 7
    cat $1
    tput setaf 8
}

fill_current_version(){
    ####################################################
    # Считываем версию из файла
    # Присвоить сбоке уникальный номер
    ####################################################
    version_idx1=$(awk 'BEGIN { FS="." } ; { print $1 }' .version)
    version_idx2=$(awk 'BEGIN { FS="." } ; { print $2 }' .version)
    version_idx3=$(awk 'BEGIN { FS="." } ; { print $3 }' .version)
    version_previous_num=$version_idx1.$version_idx2.$version_idx3
    version_previous=v$version_previous_num
}

run_download(){
    ####################################################
    # Проверка нахождения в репозитории
    # Взять из хранилища текущие исходные тексты
    ####################################################

    git_current_path="$(git config --get remote.origin.url)"
    if [[ $git_origin_path = $git_current_path ]]; then
        echo "Текущее расположение - Git репозиторий: Выполняется git pull"
        echo "---------------------"
        tput setaf 7
        git pull 
        print_err "git pull"
    else
        echo "Создание Git репозитория: Выполняется git clone"
        echo "---------------------"
        tput setaf 7
        git clone $git_origin_path  
        print_err "git clone"
        tput setaf 1; cd $repo_name; tput sgr0
        rm ../$0  #Удаление файла скрипта
        exit 1
    fi
}

run_build(){
    fill_current_version
    ####################################################
    # Собрать из них версию продукта
    ####################################################
    echo
    echo "---------------------"
    echo
    echo "Очистка"
    tput setaf 7
    #rm release/*.exe
    tput sgr0

    echo
    echo "Выполняются этапы сборки проекта"
    echo
    echo $qmake_prog ":RUN" 
    tput setaf 7
    $qmake_prog $path_pro_file -spec win32-g++ "VER=$version_previous_num"
    tput sgr0
    print_err $qmake_prog

    echo $make_prog ":RUN" 
    tput setaf 7
    $make_prog -j8
    tput sgr0
    print_err $make_prog

    echo "Очистка"
    tput setaf 7
    rm -r debug
    #rm Makefile*
    #rm .qmake.stash
    #rm ui_*
    tput sgr0

    printf "\nЗапуск\n\n"
    release/$executable_name
}

run_publicate(){
    #TODO: GET REMOUTE LAST TAG
    echo "Получение последнего тега"
    tput setaf 7
    curl -s "https://api.github.com/repos/$repo_owner/$repo_name/tags" \
                | grep -Po '"name": "\K.*?(?=")' -m1 | grep -o [0-9.] | tr -d '\n' \
                > .version 
    print_err "curl"

    fill_current_version


    ####################################################
    # Зафиксировать в хранилище версию исходных текстов
    ####################################################
    echo
    tput setaf 3; echo "Текущая версия: "$version_previous; tput sgr0
    echo "Выберите число номера версии для инкрементирования:"
    echo "  1: Кординальная переработка"
    echo "  2: Существенные для пользователя изменения"
    echo "  3: Идентификация версии для разработчиков"

    while true; do
        read selected_type
        case $selected_type in
        1)
            ((version_idx1++))
            version_idx2=0
            version_idx3=0
            break
        ;;
        2)
            ((version_idx2++))
            version_idx3=0
            break
        ;;
        3)
            ((version_idx3++))
            break
        ;;
        *) #default
            tput setaf 1; echo "Введено неверное значение. Попробуй еще раз, йоу!"; tput setaf sgr0
        ;;
        esac
    done

    version_new_num=$version_idx1.$version_idx2.$version_idx3
    version_new=v$version_new_num
    echo $version_new_num > .version
    tput setaf 3; echo "Новая версия: $version_new"; tput sgr0


    echo
    echo "Фиксироание в хранилище GitHub"
    echo

    echo "git add :RUN"
    tput setaf 7
    git add .
    print_err "git add"

    echo "Изменения для добавления"
    git commit --dry-run

    echo "git commit :RUN"
    tput setaf 7
    git commit -m $version_new
    print_err "git commit"

    echo "git push :RUN"
    tput setaf 7
    git push
    print_err "git push"

    echo "git tag :RUN"
    tput setaf 7
    #git tag -a $version_new -m $version_new
    git tag -a $version_new
    print_err "git tag"

    echo "git push origin  $version_new :RUN"
    tput setaf 7
    git push origin $version_new
    print_err "git push origin"
    tput sgr0
}


run_install(){
    fill_current_version

    ###############################################
    # Создание инсталяции и копирование доп даннных
    ###############################################
    
echo
echo "Создание инсталяции и копирование доп даннных"
tput setaf 7
#rm -r install
mkdir install
cd install
mkdir config
mkdir packages
cd config

cat > config.xml <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<Installer>
    <Name>Помошник диетолога</Name>
    <Version>$version_previous_num</Version>
    <Title>Установщик Промошник диетолога</Title>
    <Publisher>Bogdan Arzhevitin, Galoev Ilkin</Publisher>
    <StartMenuDir>Помошник диетолога</StartMenuDir>
    <TargetDir>@HomeDir@/InstallationDirectory</TargetDir>
</Installer>
EOF

cd ../packages
mkdir com.vendor.product
cd com.vendor.product
mkdir data
mkdir meta
cd meta

cat > package.xml <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<Package>
    <DisplayName>Помошник диетолога</DisplayName>
    <Description>Основной компонент</Description>
    <Version>$version_previous_num</Version>
    <ReleaseDate>$(date +'%Y-%m-%d')</ReleaseDate>
</Package>
EOF

tput setaf 1
cd ../data
cp ../../../../release/$executable_name.exe ../data
tput sgr0

echo
echo "Получение зависимостей"
tput setaf 7
$windeployqt_prog $executable_name.exe
tput sgr0
print_err $windeployqt_prog
echo "Зависимости импортированы"

tput setaf 1
cd ../../../
tput sgr0
echo
echo "Создание инсталятора"
tput setaf 7
$binarycreator_prog -c config/config.xml -p packages $executable_name-$version_previous.exe
tput sgr0
print_err $binarycreator_prog
echo "Инсталятор создан"

echo
echo "Очистка зависимостей"
tput setaf 7
#rm -r config
#rm -r packages
tput setaf 1
cd ..
tput sgr0
}
