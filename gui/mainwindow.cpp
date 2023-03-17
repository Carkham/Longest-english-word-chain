//
// Created by AORUS on 2023/3/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "time.h"
#include "IOUtil.h"
#include "Core.h"
#define bufferSize 1024
#define maxWordNum 10000
#define maxResultNum 20000
#define myIsalpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define myTolower(c) (c <= 'Z' ? (c + 0x20) : (c))

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow), word_num(0), result_num(0), enable_loop(false), last_fn(0),
        words(new char *[maxWordNum]), results(new char *[maxResultNum])
        {
    ui->setupUi(this);
    ui->headParamLineEdit->setMaxLength(1);
    ui->tailParamLineEdit->setMaxLength(1);
    ui->jParamLineEdit->setMaxLength(1);
//    connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(on_toolButton_clicked()));
//    connect(ui->runButton, SIGNAL(clicked(bool)), this, SLOT(on_runButton_clicked()));
//    connect(ui->exportButton, SIGNAL(clicked(bool)), this, SLOT(on_exportButton_clicked()));
}

MainWindow::~MainWindow() {
    delete ui;
    release_array(words, word_num);
    delete[] words;
    release_array(results, result_num);
    delete[] results;
}

void MainWindow::on_toolButton_clicked() {
    QString file_name = QFileDialog::getOpenFileName(
            this,
            tr("open a file"),
            QDir::currentPath(),
            "Text Files(*.txt)"
            );
    if (file_name.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open file!");
    } else {
        try {
            word_num = IOUtil::get_word_from_file(file_name.toLatin1().data(), words);
            QString string = to_QString();
            ui->wordTextEdit->setText(string);
            release_array(words, word_num); // 读完后释放
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Error!", "Failed to open file!");
        }
    }
}

void MainWindow::on_runButton_clicked() {
    try {
        read_status();
    } catch (std::invalid_argument &e) {
        QMessageBox::warning(this, "Error!", e.what());
        return;
    }
    if (ui->nButton->isChecked()) {
        release_array(results, result_num); // 释放之前的
        s = clock();
        ui->resultLabel->setText("正在运行");
        result_num = Core::gen_chains_all(words, word_num, results);
        e = clock();
        QString string;
        string.append("运行结束, 费时:").append(std::to_string(e - s).c_str());
        ui->resultLabel->setText(string);
        last_fn = 'n';
    } else if (ui->wButton->isChecked()) {
        release_array(results, result_num); // 释放之前的
        s = clock();
        ui->resultLabel->setText("正在运行");
        result_num = Core::gen_chain_word(words, word_num, results, head, tail, d_head, enable_loop);
        QString string;
        string.append("运行结束, 费时:").append(std::to_string(e - s).c_str());
        ui->resultLabel->setText(string);
        e = clock();
        last_fn = 'w';
    } else if (ui->cButton->isChecked()) {
        release_array(results, result_num); // 释放之前的
        s = clock();
        ui->resultLabel->setText("正在运行");
        result_num = Core::gen_chain_char(words, word_num, results, head, tail, d_head, enable_loop);
        QString string;
        string.append("运行结束, 费时:").append(std::to_string(e - s).c_str());
        ui->resultLabel->setText(string);
        e = clock();
        last_fn = 'c';
    }
    QString result;
    for (int i = 0; i < result_num; ++i) {
        result.append(results[i]).append("\n");
    }
    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText(result);
}

void MainWindow::read_status() {
    head = ui->headButton->isChecked() ? ui->headParamLineEdit->text().toLatin1().at(0) : 0;
    tail = ui->headButton->isChecked() ? ui->headParamLineEdit->text().toLatin1().at(0) : 0;
    d_head = ui->headButton->isChecked() ? ui->headParamLineEdit->text().toLatin1().at(0) : 0;
    enable_loop = ui->headButton->isChecked();
    if (myIsalpha(head)) {
        head = myTolower(head);
    } else if (head) {
        throw std::invalid_argument("invalid -h option\n");
    }
    if (myIsalpha(tail)) {
        tail = myTolower(tail);
    } else if (tail) {
        throw std::invalid_argument("invalid -t option\n");
    }
    if (myIsalpha(d_head)) {
        d_head = myTolower(d_head);
    } else if (d_head) {
        throw std::invalid_argument("invalid -j option\n");
    }

    QString string = ui->wordTextEdit->toPlainText();
    bool is_word_start = true;
    QString word;
    word_num = 0;
    for (auto c:string) {
        if (is_word_start) {
            if (c.isLetter()) {
                word.append(c.toLower());
                is_word_start = false;
            }
        } else {
            if (c.isLetter()) {
                word.append(c.toLower());
            } else {
                words[word_num] = new char[word.length() + 1];
                strcpy(words[word_num], word.toLatin1().data());
                is_word_start = true;
                word.clear();
            }
        }
    }
}

void MainWindow::on_exportButton_clicked() {
    QString dir_path_name = QFileDialog::getExistingDirectory(
            this,
            tr("open a directory"),
            QDir::currentPath()
    );
    if (dir_path_name.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to find directory!");
    } else {
        QString file_path_name = dir_path_name.append("\\solution.txt");
        try {
            if (last_fn == 'n') {
                IOUtil::output_word_chain_to_file(file_path_name.toLatin1().data(), results, result_num, true);
            } else {
                IOUtil::output_word_chain_to_file(file_path_name.toLatin1().data(), results, result_num, false);
            }
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Error!", e.what());
        }
    }
}

QString MainWindow::to_QString() {
    QString ret;
    for (int i = 0; i < word_num; ++i) {
        ret.append(words[i]).append("\n");
    }
    return ret;
}

