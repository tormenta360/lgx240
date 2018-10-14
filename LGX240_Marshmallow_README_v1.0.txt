1. Android build
  - Download original android source code ( android-6.0.0_r1  ) from http://source.android.com
    ( $repo init -u https://android.googlesource.com/platform/manifest -b android-6.0.0_r1
      $repo sync -cdq -j12 --no-tags
      $repo start android-6.0.0_r1 --all 
    )

  - Untar opensource packages of X240_Marshmallow_Android.tar.gz into downloaded android source directory
       a) tar -xvzf  X240_Marshmallow_Android.tar.gz
  - And, merge the source into the android source code
  - Run following scripts to build android
    a) source build/envsetup.sh
    b) lunch aosp_hammerhead-userdebug
    c) make -j4
  - When you compile the android source code, you have to add google original prebuilt source(toolchain) into the android directory.
  - After build, you can find output at out/target/product/generic

2. Kernel Build  
  - Uncompress using following command at the android directory
        a) tar -xvzf X240_Marshmallow_Kernel.tar.gz

  - When you compile the kernel source code, you have to add google original prebuilt source(toolchain) into the android directory.
  - Run following scripts to build kernel
    a) cd kernel-3.18
    b) mkdir out
    c) make ARCH=arm64 CROSS_COMPILE=../prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android- lv3_defconfig
    d) make ARCH=arm64 CROSS_COMPILE=../prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android- -j4

    * "-j4" : The number, 4, is the number of multiple jobs to be invoked simultaneously. 
  - After build, you can find the build image(Image.gz) at out/arch/arm/boot/zImage-dtb
