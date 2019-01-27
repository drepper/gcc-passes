#! /bin/bash
#set -x

plugindir=$PWD

declare -a flags=(0 g 1 s 2 3 fast)
check_flag() {
    local fl="$1"
    declare -i i
    for i in $(seq 0 $((${#flags[*]} - 1))); do
        if [ "$fl" == ${flags[$i]} ]; then
            return
        fi
    done
    printf "Error: Unknown flag %s\n" "$fl"
    exit 1
}

run() {
    local o="$1"
    echo 'void f(void) {}' |
    g++ -fplugin=${plugindir}/passes.so -x c++ -S -o /dev/null -O$o - 2>&1
}

if [ ${#*} -eq 1 ]; then
    o="$1"
    check_flag "$o"
    run "$o"
elif [ ${#*} -eq 2 ]; then
    l="$1"
    r="$2"
    check_flag "$1"
    check_flag "$2"
    colordiff -y -W 80 <(run "$l") <(run "$r")
else
	printf "Usage: %s <OPT> [<OPT>]\n" "$0"
	(IFS=,; printf "       where OPT ∈ {${flags[*]})\n")
	exit 1
fi
