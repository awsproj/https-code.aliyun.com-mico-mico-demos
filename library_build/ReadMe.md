# README

该示例程序说明了如何用mico cube命令生成静态库文件。

1. 先将需要编译的源代码放到一个文件夹中，称为库文件夹
2. 在这个文件夹中，创建一个mk文件，名称是[文件夹名]_src.mk，并且在这个文件中，按照示例的规则，对源代码文件，头文件路径和编译选项进行
3. 在mico应用的根目录下，执行命令`ico makelib [库文件夹]`,例如`ico makelib library_build/hello`,则编译系统会自动在库文件夹的上一层目录中生成针对不同硬件架构的静态库文件。

除此之外，本示例程序还提供了一个方法，对库的源代码进行调试，参考组件的描述文件，如library_build.mk中，

```
ifneq ($(wildcard $(CURDIR)Lib_Hello.$(HOST_ARCH).$(TOOLCHAIN_NAME).release.a),)
$(NAME)_PREBUILT_LIBRARY := Lib_Hello.$(HOST_ARCH).$(TOOLCHAIN_NAME).release.a
else
# Build from source
Lib_hello_DIR := hello
include $(CURDIR)$(Lib_hello_DIR)/hello_src.mk
endif
```

如果静态库不存在，则直接用静态库的源代码进行编译；反之，则用库进行编译。

-------------------------------------------------------------------------------
