#include <stdio.h>
#include <stdlib.h>
#include <mcrypt.h>
#include <string.h>
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

char* hex_to_bin(const char* hex_string, int hex_size){
  const char* pos = hex_string;
  char *val = malloc (sizeof (char) * hex_size);
  size_t count = 0;

  for(count = 0; count < hex_size; count++) {
    sscanf(pos, "%02hhx", &val[count]);
    pos += 2 * sizeof(char);
  }

  return val;
}

int main (int argc, char* argv[]) {

  // char* password = hex_to_bin("61626364656667686162636465666768", 16);
  // char* iv       = hex_to_bin("31323334353637386162636465666768", 16);
  // char* text     = hex_to_bin("3132333435363738313233343536373831323334353637383132333435363738", 32);

  // BLOWFISH
  char* password = hex_to_bin("0123456789ABCDEFF0E1D2C3B4A59687", 16);
  char* iv       = hex_to_bin("FEDCBA9876543210", 8);
  char* text     = hex_to_bin("37363534333231204E6F77206973207468652074696D6520666F722000", 32);

  // RC4
  // char* password[]  = "0123456789ABCDEFF0E1D2C3B4A59687"; */
  // char* iv[]        = "FEDCBA9876543210"; */
  // char* text[]      = "37363534333231204E6F77206973207468652074696D6520666F722000000000"; */

  printf("%s\n", password);
  printf("%s\n", iv);
  printf("%s\n", text);

  char* key;

  //char mcrypt_algorithm[] = MCRYPT_RIJNDAEL_128;
  char mcrypt_algorithm[] = MCRYPT_BLOWFISH;

  char mcrypt_mode[] = "cfb";

  MCRYPT td = mcrypt_module_open(mcrypt_algorithm, NULL, mcrypt_mode, NULL);

  int key_size = mcrypt_enc_get_key_size(td);

  key = (char*) malloc(key_size);
  bzero(key, key_size);
  strncpy(key, password, strlen(password));

  int iv_size = mcrypt_enc_get_iv_size(td);

  int text_size = strlen(text);

  int i = 0;

  print_hex("Key", key, key_size);
  print_hex("IV", iv, iv_size);
  print_hex("Text", text, text_size);

  mcrypt_generic_init(td, key, key_size, iv);

  for(i=0; i<text_size; i++){
    mcrypt_generic(td, &text[i], 1);
  }

  print_hex("Encrypted", text, text_size);

  mcrypt_generic_end(td);

  return 0;
}
