#!/bin/bash

case $1 in
	help)
		echo "[compile] compile source files"
		echo "[cleanup] delete binaries"
		;;
	compile)
		echo "compiling."
		make
		;;
	cleanup)
		echo "cleaning up."
		rm -R *.triglia *.out
		;; 
	*)
		echo "Command not found."
		;;
esac