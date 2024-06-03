#include "ooxml_crypt.h"

VALUE rb_encrypt_file(VALUE self, VALUE inFile, VALUE password, VALUE outFile)
{
  char *out  = StringValueCStr(outFile);
  char *in   = StringValueCStr(inFile);
  char *pass = StringValueCStr(password);

  return INT2FIX(MSOC_encryptA(out, in, pass, NULL));
}

VALUE rb_decrypt_file(VALUE self, VALUE inFile, VALUE password, VALUE outFile)
{
  char *out  = StringValueCStr(outFile);
  char *in   = StringValueCStr(inFile);
  char *pass = StringValueCStr(password);

  return INT2FIX(MSOC_decryptA(out, in, pass, NULL));
}

void Init_native(void)
{
  VALUE parent = rb_define_module("OoxmlCrypt");
  VALUE mod = rb_define_module_under(parent, "Native");

  rb_define_module_function(mod, "encrypt_file", rb_encrypt_file, 3);
  rb_define_module_function(mod, "decrypt_file", rb_decrypt_file, 3);
}
