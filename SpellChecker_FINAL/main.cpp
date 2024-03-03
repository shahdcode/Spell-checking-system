#include "spellchecker_trie.h"

#include <QApplication>
#include<QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString wordpath= QApplication::applicationDirPath();
    QString filepaht= wordpath+ "/word.txt";
    qDebug()<<filepaht;
    // QLabel* label= new QLabel();
    // label->setWindowTitle("Spell Checker");
    SpellChecker_Trie w;
    w.setWindowTitle("Spell Checker");
    w.show();
    return a.exec();
}
