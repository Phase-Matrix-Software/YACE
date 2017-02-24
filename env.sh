e() { echo "$@"; "$@"; }

if [ "$SHLVL" -ne "1" ];
then
    echo "Not top level shell"
    echo "Run as \`. $0\`"
    exit
fi

PS3="Select OS: "
oses=("Linux" "Windows")
select opt in "${oses[@]}"
do
    echo
    case $opt in
        "Linux")
            e unset CXX
            e unset LFLAGS
            e unset OS
            break
            ;;
        "Windows")
            e export CXX=x86_64-w64-mingw32-g++
            e export LFLAGS="-static-libgcc -static-libstdc++ -lstdc++ -lpthread"
            e export OS=Windows_NT
            break
            ;;
        *) echo "Invalid option";;
    esac
done
