// #ifndef LTRIE_H
// #define LTRIE_H

// class LTrie
// {
// public:
//     LTrie();
// };

// #endif // LTRIE_H

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<QTextBrowser>
using namespace std;


class TrieNode {
public:
    char c;
    bool isEndOfWord;
    TrieNode* firstChild;
    TrieNode* nextSibling;
    TrieNode(); // Constructor
    TrieNode(char c)
    {
        this->c = c;
        this->firstChild = NULL;
        this->nextSibling = NULL;
        this->isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;
    string prefix;
public:
    Trie();
    bool shouldUnderline = false;
    bool isEmpty();
    void insert(string word);
    void display(TrieNode* root, string str = "");
    void remove(string key);
    bool search(string key);
    void displayHints(TrieNode* root, TrieNode*& word);
    //void displaySuggestions(TrieNode* root, const string& incorrectWord, string current, int index, int limit);
    //void displayWordsWithPrefix(TrieNode * root, string current, int limit);
    // void displaySuggestions(TrieNode* root, const std::string& incorrectWord, std::string current, int index, int limit);
    //void displaySuggestions(const char* incorrectWord);
    //void displayWordsWithPrefix(TrieNode* root, const string& prefix);
    string replaceword(string incorrect, string correct, string text);
    void displayWordsWithPrefix(TrieNode* root, const string& prefix,QStringList& words);
    void displayWordsFromNode(TrieNode* node, string current,QStringList& words);
    TrieNode* getNode();
    bool compare(const std:: string& current, const std:: string& prefix);
    // QStringList displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord);
    //QStringList displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord);
    QStringList displayWordsWithPrefixAsString(TrieNode* root, const std::string& prefix, QStringList &words);
    void fillFromFile(const std::string& filePath);


   //QStringList displayWordsWithPrefixAsString(TrieNode* root, const std::string& prefix, QStringList& wordsArray);
  //QStringList  displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord);
   // QString displayWordsWithPrefixAsString(TrieNode* root, const QString& prefix, QStringList& wordsArray);
};
class spellChecker {
private:
    Trie dictionary;
public:
    void SpellChecker(const string& dictionaryFile);
    bool isCorrect(const string& inputText);
    void travparagraph(string para);
    string replaceword(string incorrect, string correct, string text);
};
