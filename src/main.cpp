#include <iostream>
#include "File.cpp"
#include "Huffman.cpp"

#define FILENAME "data/sherlock.txt"
#define DEBUG_FILENAME "data/test.txt"

int main() {
  auto file = new File(FILENAME);
  file->generateAlphabet();
  file->describe();

  auto hf = new Huffman(file->getAlphabet());
  hf->withText(file->getText())->tree();
  hf->encode();
  hf->describeEncode();
  hf->decode();

  return 0;
}
