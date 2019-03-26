############################################################################### 
#
#  The MIT License
#  Copyright (c) 2016 MXCHIP Inc.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy 
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights 
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is furnished
#  to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
#  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
#  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
############################################################################### 


NAME := App_library_build_demo

$(NAME)_SOURCES := helloworld.c

GLOBAL_INCLUDES := .

ifneq ($(wildcard $(CURDIR)Lib_Hello.$(HOST_ARCH).$(TOOLCHAIN_NAME).release.a),)
$(NAME)_PREBUILT_LIBRARY := Lib_Hello.$(HOST_ARCH).$(TOOLCHAIN_NAME).release.a
else
# Build from source
Lib_hello_DIR := hello
include $(CURDIR)$(Lib_hello_DIR)/hello_src.mk
endif