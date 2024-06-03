# frozen_string_literal: true

require "mkmf"

# force usage of the C++ compiler
have_library("stdc++")

# check for OpenSSL
abort("Please install OpenSSL development libraries!") unless have_header("openssl/hmac.h") && have_library("crypto")

# setup build configuration
vendor = File.realpath(File.join(__dir__, "..", "..", "vendor"))
$INCFLAGS << " -I#{vendor}/cybozulib/include -I#{vendor}/msoffice/include"
$defs << "-DCYBOZU_USE_OPENSSL_NEW_HASH=0" # fix compatibility with old OpenSSL versions
$VPATH << "#{vendor}/msoffice/src"
$srcs = ["ooxml_crypt.c", "msocdll.cpp"]

# create makefile
create_makefile("ooxml_crypt/native")
