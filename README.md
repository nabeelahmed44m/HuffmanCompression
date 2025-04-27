# Huffman Coding Compression Project

## 📚 Problem Statement

This project focuses on building and applying the Huffman Coding algorithm to achieve lossless data compression. Huffman coding assigns variable-length binary codes to characters, where shorter codes are assigned to more frequent characters, ensuring no ambiguity during decoding (Prefix Codes).

---

## 🛠️ Tasks

### Task 1: 
- Read a text file.
- Build a simple tree-based Huffman coding scheme.
- Display the tree structure and generated codes.

### Task 2:
- Use a predefined priority queue to build an **optimal Huffman tree**.
- Maintain trees ordered by character frequencies.
- Efficiently traverse the Huffman tree to generate and print codes.

### Task 3:
- Take a sample file and compress it using the generated Huffman coding scheme.
- Show compression results and evaluate performance.

---

## 🎯 Objectives

- Read a file and calculate the frequency of each character.
- Construct a binary Huffman Tree based on character frequencies.
- Traverse the tree and assign binary codes to characters.
- Compress the original file using these codes.
- Achieve lossless compression while maintaining data integrity.

---

## 🔥 Key Concepts

- **Huffman Tree Construction**: A binary tree where each leaf node represents a character, and paths to leaves represent the binary codes.
- **Prefix Codes**: Codes assigned so that no code is the prefix of another, avoiding ambiguity.
- **Priority Queue**: Used to efficiently combine the least frequent nodes during tree construction.

---

## 💡 Example

Suppose you have characters `a`, `b`, `c`, and `d` with frequencies. A non-prefix-safe encoding like:
