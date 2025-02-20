#!/bin/bash

welcome() {
    echo "This is the welcome page."
}

installationtype() {
    echo "This is the installation type page."
}

installationoption() {
    echo "This is the installation option page."
}

main() {
    case $1 in
        0) welcome ;;
        1) installationtype ;;
        2) installationoption ;;
        *) echo "Invalid input. Stopping the script."
    esac
}

main "$@"
