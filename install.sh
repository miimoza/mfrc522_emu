cd ..
git clone https://github.com/torvalds/linux.git linux
cd linux
git checkout v4.9
git am ../mfrc522_emu/patches/*.patch
