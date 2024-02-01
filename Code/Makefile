build:
	build

run: build
	# ctrl-a x to terminate :D
	mkdir -p ${WORKSPACE}/UEFI_disk/
	cp ${WORKSPACE}/Build/AzSakhtPkg/RELEASE_GCC5/X64/MainTable.efi ${WORKSPACE}/UEFI_disk/
	qemu-system-x86_64 -drive if=pflash,format=raw,file=${WORKSPACE}/Build/OvmfX64/RELEASE_GCC5/FV/OVMF.fd \
					   -drive format=raw,file=fat:rw:${WORKSPACE}/UEFI_disk \
					   -display default,show-cursor=on
					#    -drive format=raw,file=fat:rw:${WORKSPACE}/UEFI_disk \
                    #    -nographic \
					#    -net none
