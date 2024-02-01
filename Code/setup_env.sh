# Run . ./setup_env.sh

if [[ ! $PATH = *"qemu"* ]]; then
    export PATH=$PATH:/home/morabba/Downloads/qemu-8.1.2/build
fi

export WORKSPACE=/home/morabba/sandbox/UEFI-Lessons/Lessons/Lesson_00/edk2
export EDK_TOOLS_PATH=/home/morabba/sandbox/UEFI-Lessons/Lessons/Lesson_00/edk2/BaseTools
export CONF_PATH=`pwd`/Conf

ln -s `pwd`/AzSakhtPkg $WORKSPACE/AzSakhtPkg
. /home/morabba/sandbox/UEFI-Lessons/Lessons/Lesson_00/edk2/edksetup.sh
