#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <algorithm>

#ifndef FILE_CPP
#define FILE_CPP

class File {
 private:
  std::map<char, int> alphabet;
  std::string filename;
//  std::string stopCharacters = "\n#(),.@!?$%<=>\"\'*&/+-_:;[]{}/^ ";
  std::string stopCharacters = "";
  long total;
  std::string text = "";

 public:
  File(std::string filename) {
    this->filename = filename;
    this->total = 0;
  }

  void generateAlphabet() {
    std::fstream file(this->filename, std::ios::in);

    if (!file.is_open()) {
      throw std::invalid_argument("El archivo no está disponible");
    }

    std::string line;
    while (std::getline(file, line)) {
      line += "\n";
      // Filter specify characters, if necessary
      for (auto &character : stopCharacters) {
        line.erase(std::remove(line.begin(), line.end(), character), line.end());
      }

      for (auto &letter : line) {
        // Filter no ASCII characters
        if ((int) letter < 0) {
          continue;
        }

        alphabet[letter]++;
        this->text += letter;
        total++;
      }
    }
  }

  std::string getText() {
    return text;
  }

  std::map<char, int> getAlphabet() {
    return this->alphabet;
  }

  long calculateWeight() {
    return this->total * 8;
  }

  void describe() {
    if (alphabet.empty()) {
      std::cout << "Está vacio" << std::endl;
      return;
    }

    std::cout << "Las frecuencias se encuentran disponibles: " << std::endl;
    for (auto &element : alphabet) {
      std::cout << element.first << " - " << element.second << std::endl;
    }

    std::cout << "Total: " << alphabet.size() << " - caracteres: " << this->total << " - cantidad de espacio: "
              << this->calculateWeight() << std::endl;
  }
};

#endif
