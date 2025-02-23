#!/bin/bash

welcome() {
    echo "That was the welcome page."
}

installationoption() {
    echo "That was the installation option page."
    echo "Selected option: $1"
}

installationtype() {
    echo "That was the installation type page."
    echo "Selected type: $1"
}

createAccount() {
    echo "That was the create account page."
    echo "Name: $1"
    echo "Username: $2"
    echo "Computer's name: $3"
    echo "Password: $4"
    echo "Require password to login: $6"
}

systemLocalization() {
    echo "That was the system localization page."
}

diskPartitions() {
    echo "That was tht disk partitions page."
}

main() {
    local page=$1
    shift

    case $page in
        0) welcome "$@";;
        1) installationoption "$@";;
        2) installationtype "$@";;
        3) createAccount "$@";;
        4) systemLocalization "$@";;
        5) diskPartitions "$@";;
        *) echo "Invalid input. Stopping the script."
    esac
}

main "$@"
