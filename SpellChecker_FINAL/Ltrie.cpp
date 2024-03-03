#include "Ltrie.h"
#include<iostream>
#include <string>
#include<QTextBrowser>
#include<QRegularExpression>
using namespace std;

//constructor (mariam)
TrieNode::TrieNode() {
    this->isEndOfWord = false;
    this->c = ' ';
    this->firstChild = NULL;
    this->nextSibling = NULL;
}
//constructor (mariam)
Trie::Trie() {
    root = new TrieNode;
}

//Empty (Mariam)
bool Trie::isEmpty() {
    return root->c == NULL;
}

//insert (Zaina)
void Trie::insert(string word)
{

    TrieNode* temp = root;
     std::transform(word.begin(),word.end(),word.begin(),::tolower);
    if (root == NULL)
    {
        root = new TrieNode(NULL);
        temp = root;
    }
    for (int i = 0; i < word.length(); i++)
    {
        char ch = word[i];
        TrieNode* child = temp->firstChild;
        while (child != NULL && child->c != ch)
        {
            child = child->nextSibling;
        }
        if (child == NULL)
        {
            child = new TrieNode(ch);
            child->nextSibling = temp->firstChild;
            temp->firstChild = child;

        }
        temp = child;
    }
    temp->isEndOfWord = true;

}


//search (Hala)
bool Trie::search(string key) {
    TrieNode* Finder = root;
    std::transform(key.begin(),key.end(),key.begin(),::tolower);
    for (char c : key) {
        bool found = false;
        TrieNode* child = Finder->firstChild;
        while (child != NULL) {
            if (child->c == c) {
                Finder = child;
                found = true;
                break;
            }
            child = child->nextSibling;
        }
        if (!found) return false;
    }
    return Finder->isEndOfWord;
}
//displayhints (hala)
//Trie ->> points to root of trie
//TrieNode->> points to first node of needed word and its children
//by refrence + static ashan kol call y modify el value of pointer

void Trie::displayHints(TrieNode* root, TrieNode*& word) {

    static  TrieNode* current = nullptr;


    if (word != nullptr && current == nullptr) {
        current = word;
    }
    //checks that current pointer didn't reach the end of the word
    if (current != nullptr) {
        //prints current character
        cout << current->c << endl;
        current = current->firstChild;//this line bikhalih y print recursion letter by letter
        //current = current->nextSibling; //this line bikhalih  print el letters of el root bas
        return;
    }

    if (word == nullptr) {
        return;
    }


}

// Remove (Shahd)
void Trie::remove(string key) {
    TrieNode* currentNode = root;
    TrieNode* lastBranchNode = NULL;
    TrieNode* prevNode = NULL;
    char lastBranchChar = 'a'; // This is just a default value that will be updated as we traverse the Trie.

    for (char c : key) {
        if (currentNode == NULL) {
            cout << "No childNode to remove";
            return;
        }
        else {
            TrieNode* child = currentNode->firstChild;
            TrieNode* prevChild = NULL;
            while (child != NULL && child->c != c) {
                prevChild = child;
                child = child->nextSibling;
            }
            if (child == NULL) {
                cout << "Key not found";
                return;
            }
            if (currentNode->firstChild->nextSibling != NULL || currentNode->isEndOfWord) {
                lastBranchNode = currentNode;
                lastBranchChar = c;
                prevNode = prevChild;
            }
            currentNode = child;
        }
    }

    if (currentNode->firstChild != NULL) {
        if (currentNode->isEndOfWord) {
            currentNode->isEndOfWord = false;
            cout << "Prefix is removed ";
        }
    }
    else if (lastBranchNode != NULL) {
        if (prevNode == NULL) {
            delete lastBranchNode->firstChild;
            lastBranchNode->firstChild = lastBranchNode->firstChild->nextSibling;
        }
        else {
            delete prevNode->nextSibling;
            prevNode->nextSibling = prevNode->nextSibling->nextSibling;
        }
        cout << "removed";
    }
    else {
        delete root->firstChild;
        //root->firstChild = root->firstChild->nextSibling;
        cout << "Word is removed";
    }
}

void Trie::display(TrieNode* root, string str) {
    if (root != NULL) {
        str += root->c; // Add current character to string
        if (root->isEndOfWord) {
            cout << str << endl; // Print string if it's a word
        }
        TrieNode* current = root->firstChild;
        while (current != NULL) {
            display(current, str); // Recurse on child
            current = current->nextSibling; // Go to next sibling
        }
    }
}

// bool Trie::compare(const std:: string& current, const std:: string& prefix){
//     int i=0,j=0, errors=0;
//     while(i<current.length()&& j<prefix.length()){ //checking characters in each word if the match or not if there is a mismatch it counts as ann error
//         if(current[i]!=prefix[j]){
//             errors++;
//         }
//         if(errors>1){
//             return false;
//         }
//         if(current.length()>prefix.length()){
//             i++;
//         }else if(current.length()<prefix.length()){
//             j++;
//         } else{
//             i++;
//             j++;
//         }

//     }
//     if (i<current.length()){
//         return true;
//     }
//     return true;
// }

// void Trie::displayWordsFromNode(TrieNode* node, std::string current,QStringList & words) {
//     if (!node) {
//         return;
//     }

//     if (node->isEndOfWord && compare(current,prefix)){
//         words.append(QString:: fromStdString(current));

//     }

//     TrieNode* child = node->firstChild;
//     while (child) {
//         displayWordsFromNode(child, current + child->c,words);  // Adjusted this line
//         child = child->nextSibling;
//     }
// }

// void Trie::displayWordsWithPrefix(TrieNode* root, const std::string& prefix, QStringList &words) {
//     TrieNode* current = root;

//     this->prefix=prefix;

//     for (char ch : prefix) {
//         current = current->firstChild;
//         while (current && current->c != ch) {

//             current = current->nextSibling;
//         }

//         if (!current) {
//             // Prefix not found, return without displaying words
//             return;
//         }
//     }

//     // Now, 'current' points to the last node of the prefix
//     displayWordsFromNode(current, prefix,words);
// }

// men awl hena
void Trie::displayWordsFromNode(TrieNode* node, string current,QStringList & words) {
    if (!node) {
        return;
    }

    if (node->isEndOfWord) {
        //cout << current << "\n";
        words.append(QString::fromStdString(current));

    }
 TrieNode* child = node->firstChild;
   //  if(node->isEndOfWord){
   //      textBrowser->append(QString::fromStdString(current));
   //  }

    while (child) {
        displayWordsFromNode(child, current + child->c,words);  // Adjusted this line
        child = child->nextSibling;
    }

}
void Trie::displayWordsWithPrefix(TrieNode* root, const string& prefix, QStringList &words) {
    TrieNode* current = root;

    string fixedPrefix=prefix.substr(0,2);

    for (char ch : fixedPrefix) {
        current = current->firstChild;
        while (current && current->c != ch) {

            current = current->nextSibling;
        }

        if (!current) {
            // Prefix not found, return without displaying words
            return;
        }
    }

    // Now, 'current' points to the last node of the prefix
    displayWordsFromNode(current, fixedPrefix,words);
}
void Trie::fillFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string word;
        while (getline(file, word)) {
            insert(word);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
}


}
QStringList Trie::displayWordsWithPrefixAsString(TrieNode* root, const std::string& prefix, QStringList &words) {
    fillFromFile("D:\\Desktop\\Univeristy\\Semester 3\\Data structure & algorithms\\Final_project\\words.txt");

    QStringList wordsArray;

    TrieNode* current = root;

    std::string fixedPrefix=prefix.substr(0,2);

    for (char ch : fixedPrefix) {
        current = current->firstChild;
        while (current && current->c != ch) {

            current = current->nextSibling;
        }

        if (!current) {
            // Prefix not found, return without displaying words
            return wordsArray;
        }
    }
    //cout<<words[0];
    //textBrowser->append(words);

    displayWordsFromNode(current, fixedPrefix,wordsArray);



    return wordsArray;
}
//last working
// QStringList Trie::displayWordsWithPrefixAsString(TrieNode* root, const std::string& prefix, QStringList& wordsArray) {
//     TrieNode* current = root;

//     for (char ch : prefix) {
//         current = current->firstChild;
//         while (current) {
//             if (current->c == ch) {
//                 break;
//             }
//             current = current->nextSibling;
//         }

//         if (!current) {
//             return QStringList();
//         }
//     }

//     displayWordsWithPrefix(current, "", wordsArray);

//     return wordsArray;
// }
// QStringList Trie::displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord) {
//     QStringList wordsArray;

//     int startPos = text.indexOf(QRegularExpression("\\b" + selectedWord + "\\b"));

//     if (startPos != -1) {
//         QString prefix = text.mid(0, startPos);
//         TrieNode* current = root;
//         for (const QChar& ch : prefix) {
//             current = current->firstChild;
//             while (current) {
//                 if (current->c == ch) {
//                     break;
//                 }
//                 current = current->nextSibling;
//             }

//             if (!current) {
//                 return QStringList();
//             }
//         }

//         displayWordsWithPrefix(current, "", wordsArray);
//     }

//     return wordsArray;
// }
// QStringList Trie::displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord) {
//     QStringList wordsArray;

//     int startPos = text.indexOf(QRegularExpression("\\b" + selectedWord + "\\b"));

//     if (startPos != -1) {
//         QString prefix = text.mid(0, startPos);
//         TrieNode* current = root;
//         for (const QChar& ch : prefix) {
//             current = current->firstChild;
//             while (current) {
//                 if (current->c == ch) {
//                     break;
//                 }
//                 current = current->nextSibling;
//             }

//             if (!current) {
//                 return QStringList();
//             }
//         }

//         displayWordsWithPrefix(current, "", wordsArray);

//         // Replace filter with a loop
//         QStringList filteredWords;
//         for (const QString& word : wordsArray) {
//             if (word.startsWith(selectedWord.at(0), Qt::CaseInsensitive)) {
//                 filteredWords.append(word);
//             }
//         }

//         wordsArray = filteredWords;
//     }

//     return wordsArray;
// }
// QStringList Trie::displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord) {
//     QStringList wordsArray;

//     int startPos = text.indexOf(QRegularExpression("\\b" + selectedWord + "\\b"));

//     if (startPos != -1) {
//         QString prefix = text.mid(0, startPos);
//         TrieNode* current = root;
//         for (const QChar& ch : prefix) {
//             current = current->firstChild;
//             while (current) {
//                 if (current->c == ch) {
//                     break;
//                 }
//                 current = current->nextSibling;
//             }

//             if (!current) {
//                 return QStringList();
//             }
//         }

//         displayWordsWithPrefix(current, "", wordsArray);

//         // Replace filter with a loop
//         QStringList filteredWords;
//         for (const QString& word : wordsArray) {
//             if (word.startsWith(selectedWord.at(0), Qt::CaseInsensitive)) {
//                 filteredWords.append(word);
//             }
//         }

//         wordsArray = filteredWords;
//     }

//     return wordsArray;
// }

//PLAN B
// QStringList Trie::displayWordsWithPrefixAsString(TrieNode* root, const QString& text, const QString& selectedWord) {
//     QStringList wordsArray;

//     int startPos = text.indexOf(QRegularExpression("\\b" + selectedWord + "\\b"));

//     if (startPos != -1) {
//         QString prefix = text.mid(0, startPos);
//         TrieNode* current = root;
//         for (const QChar& ch : prefix) {
//             current = current->firstChild;
//             while (current) {
//                 if (current->c == ch) {
//                     break;
//                 }
//                 current = current->nextSibling;
//             }

//             if (!current) {
//                 return QStringList();
//             }
//         }

//         displayWordsWithPrefix(current, "", wordsArray);

//         // Replace filter with a loop
//         QStringList filteredWords;
//         for (const QString& word : wordsArray) {
//             if (word.startsWith(selectedWord.at(0), Qt::CaseInsensitive)) {
//                 filteredWords.append(word);
//             }
//         }

//         wordsArray = filteredWords;
//     }

//     return wordsArray;
// }







// QString Trie::displayWordsWithPrefixAsString(TrieNode* root, const QString& prefix, QStringList& wordsArray) {
//     TrieNode* current = root;
//    string sprefix=prefix.toStdString();
//     for ( char ch: sprefix) {
//         current = current->firstChild;
//         while (current) {
//             if (current->c == ch) {
//                 break;
//             }
//             current = current->nextSibling;
//         }

//         if (!current) {

//             return "";
//         }
//     }
//     displayWordsWithPrefix(current, "", wordsArray);

//     return wordsArray.join("\n");
// }
// void Trie::displayWordsWithPrefix(TrieNode* root, const string& prefix, QStringList& words) {
//     TrieNode* current = root;

//     for (char ch : prefix) {
//         current = current->firstChild;
//         while (current) {
//             if (current->c == ch) {
//                 break;
//             }
//             current = current->nextSibling;
//         }

//         if (!current) {
//             // Prefix not found, return without displaying words
//             return;
//         }
//     }

//     // Now, 'current' points to the last node of the prefix

//     displayWordsFromNode(current, prefix,words);
//    // textbrowser->setPlainText(QString::fromStdString(words));

// }

// void Trie::fillFromFile(const string& filePath) {
//     ifstream file(filePath);
//     if (file.is_open()) {
//         string word;
//         while (getline(file, word)) {
//             insert(word);
//         }
//         file.close();
//     } else {
//         std::cerr << "Unable to open file: " << filePath << std::endl;
//     }
// }

//void Trie::displaySuggestions(TrieNode* root, const std::string& incorrectWord, std::string current, int index, int limit) {
//   // cout << "aho ay 7aga" << endl;
//    if (index == incorrectWord.length()) {
//        displayWordsWithPrefix(root, current,limit);
//        return;
//    }
//
//    char ch = incorrectWord[index];
//    TrieNode* child = root->firstChild;
//
//    while (child != nullptr) {
//        if (child->c == ch) {
//            displaySuggestions(child, incorrectWord, current + ch, index + 1, limit);
//        }
//        child = child->nextSibling;
//    }
//}
//
//void Trie::displayWordsWithPrefix(TrieNode* root, string current, int limit) {
//   // cout << "aho ay 7aga1" << endl;
//    if (root == nullptr) {
//        return;
//    }
//
//    if (root->isEndOfWord) {
//        cout << current << endl;
//        if (--limit == 0) {
//            return;
//        }
//    }
//
//    TrieNode* child = root->firstChild;
//    while (child != nullptr) {
//        displayWordsWithPrefix(child, current + child->c, limit);
//        child = child->nextSibling;
//    }
//}

//void Trie::displayWordsWithPrefix(TrieNode* node, const string& prefix) {
//    if (!node || prefix.empty()) {
//        return;
//    }
//
//    TrieNode* current = node->firstChild;
//    while (current) {
//        displayWordsWithPrefix(current, prefix.substr(1));
//        current = current->nextSibling;
//    }
//
//    if (node->isEndOfWord) {
//        cout << prefix << node->c << "\n";
//    }
//}
//
//void Trie::displaySuggestions(const char* incorrectWord) {
//    TrieNode* current = root;
//    while (*incorrectWord && current) {
//        TrieNode* child = current->firstChild;
//        while (child && child->c != *incorrectWord) {
//            child = child->nextSibling;
//        }
//
//        if (!child) {
//            std::cout << "No suggestions found for '" << incorrectWord << "'.\n";
//            return;
//        }
//
//        current = child;
//        ++incorrectWord;
//    }
//
//    displayWordsWithPrefix(current, incorrectWord);
//}

////display suggestions (malak)
//void Trie::displaySuggestions(TrieNode* root, const string& incorrectWord, string current, int index, int limit) {
//   /* if (root == NULL) {
//        return;
//    }*/
//    if (root->isEndOfWord && index <= limit) {
//        cout << current << endl;  //if we reached the end of the word and it still hasn't reached the limit length then we display it as a suggestion.
//    }
//    if (index == limit) {
//        return;
//    }
//    //initialize child pointer to first child of current node
//    //keep going until no children left to vist
//    //then move on to next sibling of current child
//    for (TrieNode* child = root->firstChild; child != nullptr; child = child->nextSibling) {
//        current.push_back(child->c); //put character at the end of current suggestion
//        displaySuggestions(child, incorrectWord, current, index + 1, limit); //+1 so we can go a level deeper in the trie
//        current.pop_back();//to remove last character from current
//    }
//}


TrieNode* Trie::getNode() {
    return root;
}

//string Trie::replaceword(string incorrect, string correct, string text) {
//    // text-> textbox bta3 el gui .getText() //incorrect= word if iscorrect(word)= false
//    if (correct.empty() || incorrect.empty() || text.empty()) {
//        throw invalid_argument("one or more arguments are empty strings");
//    }
//
//    size_t pos = text.find(incorrect);
//    if (pos == string::npos) {
//
//        throw runtime_error("the incorrect word was not found in the text");
//
//    }
//
//    if (pos != string::npos) {
//
//        text.replace(pos, incorrect.length(), correct);
//
//    }
//    return text;
//}
//


// Display (Malak)
//void Trie::display(Trie* node, TrieNode* root) {
//    if (root != NULL) {
//        TrieNode* current = root->firstChild;
//        while (root != NULL) {
//            cout << current->c;
//            current = current->nextSibling;
//        }
//    }
//    if (root->isEndOfWord) {
//        cout << endl;
//    }
//    for (int i = 0; i < 26; i++) {
//        if (root->firstChild != NULL) {
//            display(node, root->firstChild);
//        }
//        root = root->nextSibling;
//    }
//
//}


//mamno3
//bool Trie::search(string key) {
//    TrieNode* currentNode = root;
//
//    for (char c : key) {
//        if (currentNode == NULL) {
//            return false;
//        }
//        else {
//            TrieNode* child = currentNode->firstChild;
//            while (child != NULL && child->c != c) {
//                child = child->nextSibling;
//            }
//            if (child == NULL) {
//                return false;
//            }
//            currentNode = child;
//        }
//    }
//
//    return currentNode->isEndOfWord;
//}



