git pull
rm -rf ../linux/drivers/gistre
cp -r gistre ../linux/drivers
cd ../linux
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
make versatile_defconfig
echo "CONFIG_GISTRE_CARD=y" >> .config
make
qemu-system-arm -M versatilepb -m 128 -kernel arch/arm/boot/zImage -dtb arch/arm/boot/dts/versatile-pb.dtb -initrd ../mfrc522_emu/rootfs/rootfs.cpio.gz -serial stdio -append "console=ttyAMA0,115200 initrd=/bin/bash"
