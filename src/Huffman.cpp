#ifndef HUFFMAN_CODE
#define HUFFMAN_CODE

#include <map>
#include "utils/PriorityQueue.cpp"
#include "utils/Node.cpp"
#include "fstream"

#define OUTPUT_FILE "../data/output/output.txt"
#define ENCODING_FILE "../data/output/encoding.txt"

class Huffman {
 private:
  std::map<char, int> alphabet;
  PriorityQueue *pq = new PriorityQueue();
  Node *root;
  std::map<char, std::string> huffmanCode;
  std::string encoded = "";
  std::string text = "";

  void fillPriorityQueue() {
    for (auto &item : alphabet) {
      this->pq->push(item.first, item.second, nullptr, nullptr);
    }
  }

  void decodeHelper(Node *node, int &index, std::string sequence, std::fstream &file) {
    if (this->root == nullptr) {
      return;
    }

    if (!node->left && !node->right) {
      file << node->item;
      return;
    }

    index++;
    if (sequence[index] == '0') {
      decodeHelper(node->left, index, sequence, file);
      return;
    }

    decodeHelper(node->right, index, sequence, file);
  }

  void encodeHelper(Node *node, std::string sequence) {
    if (!node) {
      return;
    }

    if (!node->left && !node->right) {
      this->huffmanCode[node->item] = sequence;
    }

    encodeHelper(node->left, sequence + "0");
    encodeHelper(node->right, sequence + "1");
  }

 public:
  Huffman(std::map<char, int> alphabet) {
    this->alphabet = alphabet;
    fillPriorityQueue();
  }

  void tree() {
    while (this->pq->getSize() != 1) {
      Node *left = pq->pop();
      Node *right = pq->pop();

      int priority = left->priority + right->priority;
      char name = left->item + right->item;
      pq->push(name, priority, left, right);
    }

    this->root = pq->pop();
  }

  void encode() {
    if (!this->root) {
      std::cout << "El árbol aún está vacío" << std::endl;
      return;
    }

    encodeHelper(this->root, "");

    for (auto &character : this->text) {
      this->encoded += this->huffmanCode[character];
    }

    std::fstream file(ENCODING_FILE, std::ios::out | std::ios::app);
    file << this->encoded;
  }

  Huffman *withText(std::string text) {
    this->text = text;

    return this;
  }

  void decode() {
    int index = -1;
    std::fstream file(OUTPUT_FILE, std::ios::out | std::ios::app);

    while (index < (int) this->encoded.size() - 2) {
      decodeHelper(root, index, this->encoded, file);
    }
  }

  void describeEncode() {
    if (huffmanCode.empty()) {
      std::cout << "Está vacio" << std::endl;
      return;
    }

    int total = 0;
    int caracteres = 0;
    int weight = 0;
    for (auto &element : huffmanCode) {
      std::cout << element.first << " - " << element.second << std::endl;
      caracteres += element.second.size();
      weight += alphabet[element.first] * element.second.size();
      total++;
    }

    std::cout << "Total: " << total << " - Cantidad de espacio: " << weight << std::endl;
  }
};

#endif

