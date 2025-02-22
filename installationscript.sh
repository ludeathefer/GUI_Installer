#!/bin/bash

welcome() {
    echo "That was the welcome page."
}

installationoption() {
    echo "That was the installation option page."
}

installationtype() {
    echo "That was the installation type page."
    echo "Type number $1 was selected."
}

createAccount() {
    echo "This was the create account page."
}


main() {
    local page=$1
    shift

    case $page in
        0) welcome "$@";;
        1) installationoption "$@";;
        2) installationtype "$@";;
        3) createAccount "$@";;
        *) echo "Invalid input. Stopping the script."
    esac
}

main "$@"
