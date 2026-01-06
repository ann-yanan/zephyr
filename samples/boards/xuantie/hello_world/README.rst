# 概述

`hello_world` 是一个玄铁Zephyr SDK中移植自samples/hello_world的最简单示例，可运行在QEMU环境。

# 基于Linux编译运行

## 编译

```bash
west build -b xuantie_${PLATFORM}_${CPUTYPE}/riscv_${PLATFORM}/${FEATURE} samples/boards/xuantie/hello_world --pristine
```
其中不涉及${FEATURE}编译命令如下:
```bash
west build -b xuantie_${PLATFORM}_${CPUTYPE} samples/boards/xuantie/hello_world --pristine
```
- ${CPUTYPE}: <br />
        e902 e902m e902t e902mt e906 e906f e906fd e906p e906fp e906fdp e907 e907f e907fd e907p e907fp e907fdp <br />
        r908 r908fd r908fdv r908-cp r908fd-cp r908fdv-cp r910 r920 <br />
        c906 c906fd c906fdv c908 c908v c908i <br />
        c910 c910v2 c910v3 c910v3-cp c920 c920v2 c920v3 c920v3-cp<br />
        c907 c907fd c907fdv c907fdvm c907-rv32 c907fd-rv32 c907fdv-rv32 c907fdvm-rv32
- ${PLATFORM}: <br />
        smartl xiaohui
- ${FEATURE}: <br />
        clic

注意: ${FEATURE}中clic仅支持r908系列

以玄铁`e907fdp`类型为例，可以使用如下命令编译:
```bash
west build -b xuantie_smartl_e907fdp samples/boards/xuantie/hello_world --pristine
```
编译r908系列支持clic的,以玄铁`r908fdv`类型为例，可以使用如下命令编译:
```bash
west build -b xuantie_xiaohui_r908fdv/riscv_xiaohui/clic samples/boards/xuantie/hello_world --pristine
```

## 运行

该示例可以基于玄铁QEMU或FPGA平台运行。

### 基于玄铁QEMU运行

```bash
qemu-system-riscv32 -machine smartl -cpu e907fdp -nographic -kernel build/zephyr/zephyr.elf

/rvhome/o_ld02443552/workspace/zephyrproject/xuantie_qemu/bin/qemu-system-riscv64 \
  -machine xiaohui -cpu c908v -smp 4 \
  -nographic -kernel zephyr/zephyr.elf -gdb tcp::7777 -S

/rvhome/o_ld02443552/workspace/zephyrproject/riscv64-unknown-elf/bin/riscv64-unknown-elf-gdb zephyr.elf
```

#### 终端退出qemu

1. 先Ctrl+a
2. 松开所有按键， 紧接着再按下x键

### 基于FPGA平台运行

如何基于FPGA平台运行请参考《玄铁Zephyr SDK用户手册》

### 运行结果
正常运行串口输出内容参考如下
```
*** Booting Zephyr OS build 743af5c2045c ***
Hello World! xuantie_smartl_e907fdp
Hello World! xuantie_smartl_e907fdp, cnt = 10
Hello World! xuantie_smartl_e907fdp, cnt = 9
Hello World! xuantie_smartl_e907fdp, cnt = 8
Hello World! xuantie_smartl_e907fdp, cnt = 7
Hello World! xuantie_smartl_e907fdp, cnt = 6
Hello World! xuantie_smartl_e907fdp, cnt = 5
Hello World! xuantie_smartl_e907fdp, cnt = 4
Hello World! xuantie_smartl_e907fdp, cnt = 3
Hello World! xuantie_smartl_e907fdp, cnt = 2
Hello World! xuantie_smartl_e907fdp, cnt = 1
```

# 相关文档和工具

相关文档和工具下载请从玄铁官方站点 https://www.xrvm.cn 搜索下载

1、《玄铁Zephyr SDK用户手册》

2、玄铁模拟器QEMU工具


# 注意事项

1、Linux平台下基础环境搭建请参考《玄铁Zephyr SDK用户手册》

2、玄铁exx系列cpu仅支持smartl平台，cxx/rxx系列cpu仅支持xiaohui平台。

3、当前仅支持Linux命令行下编译，不支持IDE编译。

4、某些示例跟硬件特性相关，QEMU中相关功能可能未模拟，只能在相应FPGA硬件平台上运行。

5、在使用带有vector or matrix扩展的处理器时，需参考《玄铁Zephyr SDK用户手册》第4节说明正确配置CONFIG_XUANTIE_RISCV_VLENB_LEN和CONFIG_XUANTIE_RISCV_RLENB_LEN。


