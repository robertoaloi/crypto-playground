#include <stdio.h>
#include <stdlib.h>
#include <mcrypt.h>
#include <string.h>

void print_hex(char* title, char* text, int size){
  int i;
  printf("%s\n", title);
  for (i=0; i<size; i++) {
    printf("%02hhx", text[i]);
    if (i<size-1)
      printf(":");
  }
  printf("\n");
}

int main () {

  char password[]  = "abcdefghabcdefgh";
  char iv[]        = "12345678abcdefgh";
  char text[]      = "12345678123456781234567812345678";

  char* key;

  int block_size = 1;

  char mcrypt_algorithm[] = MCRYPT_RIJNDAEL_128;
  char mcrypt_mode[] = "cfb";

  MCRYPT td = mcrypt_module_open(mcrypt_algorithm, NULL, mcrypt_mode, NULL);

  //int key_size = mcrypt_enc_get_key_size(td); // 32
  int key_size = 16;
  key = (char*) malloc(key_size);
  bzero(key, key_size);
  strncpy(key, password, strlen(password));

  int iv_size = mcrypt_enc_get_iv_size(td);

  int text_size = strlen(text);

  int i = 0;

  print_hex("Key", key, key_size);
  print_hex("Text", text, text_size);
  print_hex("IV", iv, iv_size);

  mcrypt_generic_init(td, key, key_size, iv);

  for(i=0; i<text_size; i++){
    mcrypt_generic(td, &text[i], 1);
  }

  print_hex("Encrypted", text, text_size);

  mcrypt_generic_end(td);

  return 0;
}
