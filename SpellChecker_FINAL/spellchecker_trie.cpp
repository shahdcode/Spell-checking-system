#include "spellchecker_trie.h"
#include "ui_spellchecker_trie.h"
#include<QDebug>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
#include<QTextCursor>
#include<QTextStream>
#include<QFile>
#include<QRegularExpression>
#include<QMessageBox>
#include<cmath>
#include"Ltrie.h"
  Trie trie;
QStringList words;
SpellChecker_Trie::SpellChecker_Trie(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpellChecker_Trie)
{
    ui->setupUi(this);
     words = {""};  //kont ba7wl a3ml 7aga
    ui->textBrowser->setOpenExternalLinks(true);

    for (const QString &word : words) {
        addClickableWord(word);
        // ui->textBrowser->append(QString("<a href=\"%1\">%1</a>").arg(word));
    }

    connect(ui->textBrowser, SIGNAL(anchorClicked(const QUrl &)), this, SLOT(onWordClicked(const QUrl &)));

    //ha create a QPushButton
    // QPushButton *pushButton=  new QPushButton("Spell check",this);
    // connect(pushButton,SIGNAL(clicked()),this,SLOT(onButtonClicked()));

    //ba7wl a read from file:
    QFile file("D:\\Desktop\\Univeristy\\Semester 3\\Data structure & algorithms\\Final_project\\words.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        // Insert words into Trie, considering one word per line

        while (!in.atEnd()) {
            QString word = in.readLine();
            trie.insert(word.toStdString());
        }


        file.close();

    } else {
        qDebug() << "Failed to open the file.";
    }

}

SpellChecker_Trie::~SpellChecker_Trie()
{
    delete ui;
}
// string Trie::replaceword(string incorrect, string correct, string text) {
//         // text-> textbox bta3 el gui .getText() //incorrect= word if iscorrect(word)= false
//        if (correct.empty() || incorrect.empty() || text.empty()) {
//            throw invalid_argument("one or more arguments are empty strings");
//        }

//        size_t pos = text.find(incorrect);
//        if (pos == string::npos) {

//            throw runtime_error("the incorrect word was not found in the text");

//        }

//        if (pos != string::npos) {

//            text.replace(pos, incorrect.length(), correct);

//        }
//        return text;
//     }

void SpellChecker_Trie::addClickableWord(const QString &word){
    // QLabel *label= new QLabel(word,this);
    // label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    // label->setOpenExternalLinks(false);

   // ui->textBrowser->append(word);
    QTextCursor cursor= ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);

    //ba7wl azbt eno when i select, y select sa7
    if(!cursor.atBlockStart())
        cursor.insertText("\n");
    QTextCharFormat charFormat= cursor.charFormat();
    charFormat.setAnchor(true);
    charFormat.setAnchorHref(word);
    charFormat.setForeground(QColor(0,0,225)); //bazbt el lon for better visibility
    //charFormat.setBackground(QColor(225,225,225));
    cursor.mergeCharFormat(charFormat);
    cursor.insertText(word);
   // ui->textBrowser->append("");

    // ui->textBrowser->textCursor().insertText("\n");
    // ui->textBrowser->textCursor().insertText(word);
    // disconnect(label,SIGNAL(linkActivated(const QString &)),this,SLOT(onWordClicked(const QString &)));
    // connect(label,SIGNAL(linkActivated(const QString &)),this,SLOT(onWordClicked(const QString &)));

}
void SpellChecker_Trie::onButtonClicked() {
    qDebug() << "Button clicked!";
    ui->textBrowser->clear();

    //mafrod ha call function malak hena
    QStringList newWords={"New", "Content"}; //bagrab 7aga bardo
    ui->textBrowser->setOpenExternalLinks(true);
    for(const QString &word: newWords){
        addClickableWord(word);
    }

}

void SpellChecker_Trie::on_pushButton_clicked()
{
   // onButtonClicked();
    ui->textBrowser->clear();
   TrieNode* root=trie.getNode();
    QStringList w;
   onSpecificButtonClicked();
   // trie.displayWordsWithPrefix(root,"bok",w);
   //  for(const QString& word: w){
   //     addClickableWord(word);
   // }
   //  ui->textBrowser->setText(w.join("\n"));

}


// void  SpellChecker_Trie::onWordClicked(const QUrl &link){
//     QString clickedWord=link.toString();
//     //ui->lineEdit->setText(clickedWord);
// }
void SpellChecker_Trie::onWordClicked(const QUrl &link) {
    QString clickedWord = link.toString();
    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.hasSelection()) {
        // select el kelma el galat
        QString selectedText = cursor.selectedText();
        replaceIncorrectWord(selectedText, clickedWord);
    } else {

        // Get the word under the cursor
        QString selectedText = getWordUnderCursor(cursor);

        // Make the word under the cursor 3and el kelma el galat
        replaceIncorrectWord(selectedText, clickedWord);

        // 7ark el cursor le a5r el text
        cursor.setPosition(cursor.position() - selectedText.length() + clickedWord.length());
    }
}

QString SpellChecker_Trie::getWordUnderCursor(QTextCursor &cursor) {
    cursor.select(QTextCursor::WordUnderCursor);
    return cursor.selectedText();
}

void SpellChecker_Trie::replaceIncorrectWord(const QString &incorrect, const QString &correct) {
    QTextCursor cursor(ui->textEdit->document());


    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = ui->textEdit->document()->find(incorrect, cursor);

        if (!cursor.isNull()) {
            if (cursor.selectedText() == incorrect) {
                // bey replace
                cursor.beginEditBlock();
                cursor.insertText(correct);

                // beyrga3 el default format
                QTextCharFormat format;
                format.setForeground(Qt::black);
                format.setUnderlineStyle(QTextCharFormat::NoUnderline);
                format.setBackground(Qt::transparent);
                cursor.setPosition(cursor.position() - correct.length());
                cursor.mergeCharFormat(format);
                cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, correct.length());
                cursor.mergeCharFormat(format);

                cursor.endEditBlock();
            }
            cursor.movePosition(QTextCursor::NextWord);
        }
    }
}

// void SpellChecker_Trie::replaceIncorrectWord(const QString &incorrect, const QString &correct) {
//     QTextCursor cursor(ui->textEdit->document());

//     // Get the position of the incorrect word in the text
//     int pos = ui->textEdit->toPlainText().indexOf(incorrect);

//     if (pos != -1) {
//         // Replace the incorrect word with the correct word
//         QString text = ui->textEdit->toPlainText();
//         text.replace(pos, incorrect.length(), correct);
//         ui->textEdit->setPlainText(text);

//         // Move the cursor to the position of the replaced word
//         cursor.setPosition(pos);

//         // Reset text format for the replaced word
//         QTextCharFormat format;
//         cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, correct.length());
//         cursor.mergeCharFormat(format);

//         // Set the text color to black for the replaced word
//         QTextCharFormat blackFormat;
//         blackFormat.setForeground(Qt::black);
//         cursor.mergeCharFormat(blackFormat);

//         // Remove underline style from the replaced word
//         QTextCharFormat noUnderlineFormat;
//         noUnderlineFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
//         cursor.mergeCharFormat(noUnderlineFormat);

//         // Remove background color
//         QTextCharFormat noBackgroundFormat;
//         noBackgroundFormat.setBackground(Qt::transparent);
//         cursor.mergeCharFormat(noBackgroundFormat);
//     }
// }
//HOWA DAHHHHHHH!!!!!!
// void SpellChecker_Trie::onWordClicked(const QUrl &link) {
//     QString clickedWord = link.toString();

//     // Get the text cursor
//     QTextCursor cursor = ui->textEdit->textCursor();

//     // Check if there is a selection
//     if (cursor.hasSelection()) {
//         // Make the selected word the incorrect word
//         QString selectedText = cursor.selectedText();
//         replaceIncorrectWord(selectedText, clickedWord);
//     } else {
//         // If no text is selected, replace the word at the cursor position

//         // Get the word under the cursor
//         QString selectedText = getWordUnderCursor(cursor);

//         // Make the word under the cursor the incorrect word
//         replaceIncorrectWord(selectedText, clickedWord);

//         // Move the cursor to the end of the inserted text
//         cursor.setPosition(cursor.position() - selectedText.length() + clickedWord.length());
//     }

// }

// QString SpellChecker_Trie::getWordUnderCursor( QTextCursor &cursor) {
//     cursor.select(QTextCursor::WordUnderCursor);
//     return cursor.selectedText();
// }


// void SpellChecker_Trie::replaceIncorrectWord(const QString &incorrect, const QString &correct) {
//     QString text = ui->textEdit->toPlainText();
//     QTextCursor cursor(ui->textEdit->document());

//     // Get the position of the incorrect word in the text
//     int pos = text.indexOf(incorrect);

//     // Replace the incorrect word with the correct word
//     text.replace(pos, incorrect.length(), correct);
//     ui->textEdit->setPlainText(text);

//     // Move the cursor to the position of the replaced word
//     cursor.setPosition(pos);

//     // Reset text format for the replaced word
//     QTextCharFormat format;
//     cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, correct.length());
//     cursor.mergeCharFormat(format);

//     // Set the text color to black explicitly
//     QTextCharFormat blackFormat;
//     blackFormat.setForeground(Qt::black);
//     cursor.mergeCharFormat(blackFormat);
//     //trie.shouldUnderline =false;
//     // Remove underline style from the replaced word
//     QTextCharFormat noUnderlineFormat;
//     noUnderlineFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
//     cursor.mergeCharFormat(noUnderlineFormat);

//     // Remove background color
//     QTextCharFormat noBackgroundFormat;
//     noBackgroundFormat.setBackground(Qt::transparent);
//     cursor.mergeCharFormat(noBackgroundFormat);
// }
// void SpellChecker_Trie::replaceIncorrectWord(const QString &incorrect, const QString &correct) {
//     QString text = ui->textEdit->toPlainText();
//     text.replace(incorrect, correct);
//     ui->textEdit->setPlainText(text);

// }

// END OF HENA
// void SpellChecker_Trie::onWordClicked(const QUrl &link) {
//     QString clickedWord = link.toString();
//     ui->lineEdit->setText(clickedWord);
// }

// void SpellChecker_Trie::on_textBrowser_anchorClicked(const QUrl &arg1)
// {

// }



void SpellChecker_Trie::on_lineEdit_editingFinished()
 {
//   // QString enteredText = ui->lineEdit->text();
 }


void SpellChecker_Trie::on_textEdit_textChanged()
{

}


// void SpellChecker_Trie::on_textBrowser_anchorClicked(const QUrl &arg1)
// {
//     QString clickedWord=arg1.toString();
//     ui->lineEdit->setText(QString::fromStdString(clickedWord.toStdString()));
//     Trie t;
//     t.displayWordsWithPrefix(t.getNode(),clickedWord.toStdString());
// }
void SpellChecker_Trie::underline_incorrect_word() {
    QString text = ui->textEdit->toPlainText();
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock(); // Start editing block

    // Default format
    QTextCharFormat defaultFormat;
    defaultFormat.setForeground(Qt::black);
    defaultFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);

    // Split text into words
    QStringList words = text.split(QRegularExpression("\\b"), Qt::SkipEmptyParts);

    int prevPos = -1;
    QTextCharFormat prevFormat;

    for (const QString& word : words) {
        if (word.trimmed().isEmpty()) {
            continue;
        }

        int pos = text.indexOf(QRegularExpression("\\b" + word + "\\b"));
        cursor.setPosition(pos);

        QTextCharFormat format;

        if (!trie.search(word.toStdString())) {
            format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
            format.setForeground(QColor(255, 0, 0));
        } else {
            format.setUnderlineStyle(QTextCharFormat::NoUnderline);
            format.setForeground(QColor(0, 128, 0));
        }

        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, word.length());
        cursor.mergeCharFormat(format);

        if (prevPos != -1 && pos != prevPos) {
            cursor.setPosition(pos);
            cursor.mergeCharFormat(prevFormat);
        }

        prevPos = pos + word.length();
        prevFormat = format;
    }

    // Ensure that after space, subsequent words have the default format
    if (prevPos != -1) {
        cursor.setPosition(prevPos);
        cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(defaultFormat);
    }

    cursor.endEditBlock(); // End editing block
    ui->textEdit->setTextCursor(cursor); // Set the updated cursor
}
// DAH CODE HALA EL WORKS
// void SpellChecker_Trie::underline_incorrect_word() {
//     QString text = ui->textEdit->toPlainText();
//     QTextCursor cursor = ui->textEdit->textCursor();
//     cursor.beginEditBlock(); // Start editing block

//     // Default format for newly inserted words
//     QTextCharFormat defaultFormat;
//     defaultFormat.setForeground(Qt::black);

//     // Split text into words
//     QStringList words = text.split(QRegularExpression("\\b"), Qt::SkipEmptyParts);

//     int prevPos = -1;
//     QTextCharFormat prevFormat;

//     for (const QString& word : words) {
//         if (word.trimmed().isEmpty()) {
//             continue;
//         }

//         int pos = text.indexOf(QRegularExpression("\\b" + word + "\\b"));
//         cursor.setPosition(pos);

//         QTextCharFormat format;

//         if (!trie.search(word.toStdString())) {
//             format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
//             format.setForeground(QColor(255, 0, 0)); // Incorrect word: red underline
//         } else {
//             format.setUnderlineStyle(QTextCharFormat::NoUnderline);
//             format.setForeground(QColor(0, 128, 0)); // Correct word: green color
//         }

//         cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, word.length());
//         cursor.mergeCharFormat(format);

//         if (prevPos != -1 && pos != prevPos) {
//             cursor.setPosition(pos);
//             cursor.mergeCharFormat(prevFormat);
//         }

//         prevPos = pos + word.length();
//         prevFormat = format;
//     }

//     // Move cursor to the end after checking
//     cursor.setPosition(text.length());
//     cursor.mergeCharFormat(defaultFormat); // Set default format to any newly inserted text
//     cursor.endEditBlock(); // End editing block
//     ui->textEdit->setTextCursor(cursor); // Set the updated cursor
// }
//code zaina & mariam
// void SpellChecker_Trie::underline_incorrect_word() {

//     QString text=ui->textEdit->toPlainText();//inputtext

//     QTextCursor Cursorremover=ui->textEdit->textCursor();
//     Cursorremover.select(QTextCursor::Document);
//     Cursorremover.setCharFormat(QTextCharFormat());

//     QTextCursor cursor=ui->textEdit->textCursor();
//     cursor.movePosition(QTextCursor::Start);
// QTextCharFormat format;
//     QStringList words =text.split(QRegularExpression("\\b"),Qt::SkipEmptyParts);
//     for(const QString& word:words){
//         if(word.trimmed().isEmpty()){
//             continue;
//         }

//         int pos=text.indexOf(QRegularExpression("\\b" + word + "\\b"));
//         cursor.setPosition(pos);

//         cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,word.length());

//         if(!trie.search(word.toStdString())){


//                 format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
//                 format.setForeground(QColor(125,0,0));
//                // format.setBackground(QColor(225,225,225));
//                  cursor.mergeCharFormat(format);

//            //


//            //  QTextCharFormat formatt;
//            // // formatt.setAnchor(true);
//            //  //charFormat.setAnchorHref(word);
//            //
//            //  cursor.mergeCharFormat(formatt);
//            //  //cursor.insertText(word);
//         }else{
//             format.setUnderlineStyle(QTextCharFormat::NoUnderline);
//             format.setForeground(QColor(0,128,0));
//             //format.setBackground(QColor(225,225,225));
//             cursor.setCharFormat(format);
//         }

//     }
// }


// void SpellChecker_Trie::underline_incorrect_word() {
//     static int lastCheckedPosition = 0;  // Static variable to keep track of last checked position
//     QString text = ui->textEdit->toPlainText();  // Get the entire text

//     // Remove formatting from entire text
//     QTextCursor cursorRemover = ui->textEdit->textCursor();
//     cursorRemover.select(QTextCursor::Document);
//     cursorRemover.setCharFormat(QTextCharFormat());

//     // Move cursor to the last checked position
//     QTextCursor cursor = ui->textEdit->textCursor();
//     cursor.setPosition(lastCheckedPosition);

//     // Split the text into words
//     QStringList words = text.mid(lastCheckedPosition).split(QRegularExpression("\\b"), Qt::SkipEmptyParts);

//     QTextCharFormat format;
//     for (const QString& word : words) {
//         if (word.trimmed().isEmpty()) {
//             continue;
//         }

//         int pos = text.indexOf(QRegularExpression("\\b" + word + "\\b"), lastCheckedPosition);
//         cursor.setPosition(pos);

//         // Check if the word was present before the last check
//         if (!trie.search(word.toStdString())) {
//             format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
//             format.setForeground(QColor(225, 0, 0));
//             cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, word.length());
//             cursor.mergeCharFormat(format);
//         } else {
//             format.setUnderlineStyle(QTextCharFormat::NoUnderline);
//             format.setForeground(QColor(0, 0, 0));  // Set color to black
//             cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, word.length());
//             cursor.mergeCharFormat(format);
//         }
//     }

//     // Update the last checked position to the end of the text
//     lastCheckedPosition = text.length();
// }
void SpellChecker_Trie::on_pushButton_2_clicked()
{
    underline_incorrect_word();

}

//PLAN B
// void SpellChecker_Trie::onSpecificButtonClicked() {
//     QString text = ui->textEdit->toPlainText();
//     QTextCursor cursor = ui->textEdit->textCursor();
//     QStringList words = text.split(QRegularExpression("\\b"), Qt::SkipEmptyParts);

//     for (const QString& word : words) {
//         QString trimmedWord = word.trimmed();
//         if (!trimmedWord.isEmpty() && !trie.search(trimmedWord.toStdString())) {
//             TrieNode* root = trie.getNode();
//             QStringList suggestions = trie.displayWordsWithPrefixAsString(root, text, trimmedWord);

//             if (!suggestions.isEmpty()) {
//                 // Append suggestions to textBrowser without clearing previous content
//                 for (const QString& suggestion : suggestions) {
//                     ui->textBrowser->append(suggestion);
//                 }
//             }
// }
//     }
// }

void SpellChecker_Trie::onSpecificButtonClicked() {
    trie.fillFromFile("D:\\Desktop\\Univeristy\\Semester 3\\Data structure & algorithms\\Final_project\\words.txt");

    QTextCursor cursor = ui->textEdit->textCursor();

    if (cursor.hasSelection()) {
        QString selectedWord = cursor.selectedText().trimmed();
        if (!trie.search(selectedWord.toStdString())) {
            // functionForSelectedWord(selectedWord);
            string selectedWord_String= selectedWord.toStdString();
            //TrieNode* root = trie.getNode(); // Assuming you have a function to get the
            QStringList wordList = trie.displayWordsWithPrefixAsString(trie.getNode(),selectedWord_String,words);
            // textBrowser->append(wordList[0]);
            for(const QString& word : wordList) {
                addClickableWord(word);
                ui->textBrowser->append(word);
            }

}
}
}
//last one working
// void SpellChecker_Trie::onSpecificButtonClicked() {
//     QTextCursor cursor = ui->textEdit->textCursor();

//     if (cursor.hasSelection()) {
//         QString selectedWord = cursor.selectedText().trimmed();
//         if (!trie.search(selectedWord.toStdString())) {
//            // functionForSelectedWord(selectedWord);
//             string selectedWord_String= selectedWord.toStdString();
//             TrieNode* root = trie.getNode(); // Assuming you have a function to get the root of your Trie
//             trie.displayWordsWithPrefix(root,selectedWord_String,words); // Modify the function parameters as per your Trie structure
//             // QMessageBox::information(this, "Selected Word", "You selected: " + selectedWord);
//             // ui->textBrowser->clear();  // Clear existing content
//             // ui->textBrowser->append("Selected Word: " +selectedWord);
//             //ui->textBrowser->setText((trie.displayWordsWithPrefixAsString(root,selectedWord_String,words).toStdString()).join("\n"));
//             QStringList wordList = trie.displayWordsWithPrefixAsString(root, selectedWord_String, words);
//             for(const QString& word : wordList) {
//                 addClickableWord(word);
//                 ui->textBrowser->append(word);
//             }
//         }
//     }
// }
// void SpellChecker_Trie::onSpecificButtonClicked() {
//     QString inputText = ui->textEdit->toPlainText();
//     QStringList incorrectWords;

//     // Split the input text into words
//     QStringList words = inputText.split(QRegularExpression("\\b"), Qt::SkipEmptyParts);

//     // Check each word for correctness
//     for (const QString& word : words) {
//         if (!trie.search(word.toStdString())) {
//             incorrectWords.append(word);
//              addClickableWord(word);
//         }
//     }

//     // Now, incorrectWords contains all the incorrect words
//     // You can use this QStringList as needed

//     // For example, if you want to display suggestions for the first incorrect word:
//     if (!incorrectWords.isEmpty()) {
//         QString firstIncorrectWord = incorrectWords.first();
//         string firstIncorrectWordString = firstIncorrectWord.toStdString();
//         TrieNode* root = trie.getNode();
//         QStringList suggestions;
//         trie.displayWordsWithPrefix(root, firstIncorrectWordString, suggestions);

//         // Do something with suggestions, e.g., display them in the text browser
//         ui->textBrowser->setText(suggestions.join("\n"));
//     }
// }

// void SpellChecker_Trie::on_pushButton_3_clicked()
// {

// }

