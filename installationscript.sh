#!/bin/bash

welcome() {
    echo "Welcome to Radarch Installer."
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
    echo "Password: ${4//?/*}"
    echo "Require password to login: $6"
}

diskPartitions() {
    echo "That was the disk partitions page."
}

installed() {
    echo "Radarch installed successfully."
}


partitionDisks() {
    local DRIVE="/dev/sda"
    echo "Partitioning the disks"
    # Creating new GPT partition
    parted --script "$DRIVE" mklabel gpt
    # Creating EFI partition (1GB)
    parted --script "$DRIVE" mkpart ESP fat32 1MiB 1025MiB
    parted --script "$DRIVE" set 1 esp on
    # Creating swap partition (4GB)
    parted --script "$DRIVE" mkpart primary linux-swap 1025MiB 5121MiB
    # Creating Root partition (remaining space)
    parted --script "$DRIVE" mkpart primary ext4 5121MiB 100%
}

formatPartitions() {
    echo "Formatting the partitions"
    # Creating Ext4 FS on root partition
    mkfs.ext4 /dev/sda3
    # Initializing swap
    mkswap /dev/sda2
    # Formatting EFI partition to FAT32
    mkfs.fat -F 32 /dev/sda1
}

mountFileSystems() {
    echo "Mounting the file systems"
    # Mounting the root partition to /mnt
    mount /dev/sda3 /mnt
    # Creating /mnt/boot and mounting the EFI partition to it
    mount --mkdir /dev/sda1 /mnt/boot
    # Enabling the swap partition
    swapon /dev/sda2
}

installEssentialPackages() {
    echo "Installing essential packages"
    # Installing linux kernel and firmware with the base package and network manager
    pacstrap -K /mnt base linux linux-firmware networkmanager
}

configureSystem() {
    echo "Configuring the system"
    # Generating fstab file
    genfstab -U /mnt >> /mnt/etc/fstab
    # Copying resolv.conf for network access
    cp --dereference /etc/resolv.conf /mnt/etc/resolv.conf
    # Chrooting into new system
    arch-chroot /mnt /bin/bash <<EOF
        echo Setting the timezone
        ln -sf /usr/share/zoneinfo/"$8" /etc/localtime
        hwclock --systohc
        echo Generating locale
        echo "$9" >> /etc/locale.gen
        locale-gen
        echo Setting the hostname
        echo "$3" > /etc/hostname
        echo Creating new user
        useradd -m -G wheel -s /bin/bash "$2"
        echo "$2:$4" | chpasswd
        echo Installing sudo
        pacman -Syu --noconfirm sudo --verbose
        echo Granting sudo privileges
        echo "$2 ALL=(ALL) ALL" >> /etc/sudoers
        echo Installing grub and efibootmgr
        pacman -Syu --noconfirm grub efibootmgr --verbose
        echo Initializing GRUB
        grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB
        echo Generating GRUB config
        grub-mkconfig -o /boot/grub/grub.cfg
        echo Enabling network manager on boot
        systemctl enable NetworkManager.service
EOF
}

addingGUIConfig() {
arch-chroot /mnt /bin/bash <<EOF
    echo Installing Plasma and SDDM
    pacman -Syu --noconfirm plasma dolphin konsole sddm --verbose

    echo Enabling SDDM
    systemctl enable sddm.service
EOF
    echo "Copying user configuration files"
    cp -r /theme-to-copy/. /mnt/home/$1/
    cp -r /usr-to-copy/. /mnt/usr/
    cp -r /etc-to-copy/. /mnt/etc/
}


unmount() {
    echo "Unmounting /mnt"
    umount -R /mnt
    reboot
}

manualPartitionDisks() {
    echo
}

minimalInstall() {
    echo "Minimal install detected"
    partitionDisks
    formatPartitions
    mountFileSystems
    installEssentialPackages
    configureSystem "$@"
    unmount
}

normalInstall() {
    echo "Normal install detected"
    partitionDisks
    formatPartitions
    mountFileSystems
    installEssentialPackages
    configureSystem "$@"
    addingGUIConfig "$2"
    unmount
}

installing() {
    echo "Installing with following parameters: "
    echo "$@"
    echo

    if [ "$1" -eq 1 ] && [ "$2" -eq 1 ]; then
        shift 2
        normalInstall "$@"
    elif [ "$1" -eq 2 ] && [ "$2" -eq 1 ]; then
        shift 2
        minimalInstall "$@"
    fi

    installed
}

systemLocalization() {
    echo "That was the system localization page."
    echo "Location: ${@: -3}"
    echo "Timezone: ${@: -2:1}"
    echo "Locale: ${@: -1:1}"
    echo

    installing "$@"
}

main() {
    local page=$1
    shift

    case $page in
        0) welcome "$@";;
        1) installationoption "$@";;
        2) installationtype "$@";;
        3) diskPartitions "$@";;
        4) createAccount "$@";;
        5) systemLocalization "$@";;
        *) echo "Invalid input. Stopping the script."
    esac
}

main "$@"
