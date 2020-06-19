#!/bin/bash

case $1 in
	help)
		echo "[compileAll] compile ALL source files"
    echo "[compile] compile a specific source file"
		echo "[cleanup] delete binaries"
		;;
	compileAll)
		echo "compiling."
		make
		;;
	cleanup)
		echo "cleaning up."
		make clean
		;;
  compile)
    echo "[1] Oneway-UDP-IPv4"
    echo "[2] Oneway-UDP-IPv6"
    echo "Selection: "
    read -p "Please select: " select
    if (( select git == 1 )); then
      make oneway-udp-ipv4
    elif (( select == 2)); then
      make oneway-udp-ipv6
    fi 
    ;;
	*)
		echo "Use 'help' for details"
		;;
esac