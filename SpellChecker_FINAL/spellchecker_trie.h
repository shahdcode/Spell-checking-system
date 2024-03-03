#ifndef SPELLCHECKER_TRIE_H
#define SPELLCHECKER_TRIE_H

#include <QMainWindow>
#include <QPushButton>
#include<QMainWindow>
#include<QObject>
#include<QTextCursor>
#include<QTextEdit>
QT_BEGIN_NAMESPACE
using namespace std;
namespace Ui {
class SpellChecker_Trie;
}
QT_END_NAMESPACE

class SpellChecker_Trie : public QMainWindow
{
    Q_OBJECT

public:
    SpellChecker_Trie(QWidget *parent = nullptr);
    ~SpellChecker_Trie();
private slots:
    void onButtonClicked();

    void on_pushButton_clicked();

    // void on_label_linkActivated(const QString &link);
    void onWordClicked(const QUrl &link);

    //void on_textBrowser_anchorClicked(const QUrl &arg1);

    void on_lineEdit_editingFinished();
    void addClickableWord(const QString &word);
   void on_textEdit_textChanged();
  // void insertWordsFromFile(const QString &filepath);
  // void on_textBrowser_anchorClicked(const QUrl &arg1);
   void underline_incorrect_word();
   QString getWordUnderCursor( QTextCursor &cursor);
   void replaceIncorrectWord(const QString &incorrect, const QString &correct);
   void on_pushButton_2_clicked();
//void clear_underline_format(QTextEdit* textEdit);
   //void on_pushButton_3_clicked();
   void onSpecificButtonClicked();
   private:
    QPushButton *myButton;
private:
    Ui::SpellChecker_Trie *ui;
};
#endif // SPELLCHECKER_TRIE_H
