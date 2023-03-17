//
// Created by AORUS on 2023/3/17.
//

#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QLineEdit>
#include "QFileDialog"
#include "QMessageBox"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void on_toolButton_clicked();
    void on_runButton_clicked();
    void on_exportButton_clicked();
private:
    Ui::MainWindow *ui;
    int word_num, result_num;
    long s, e;
    char **words, **results, last_fn;
    char head = 0, tail = 0, d_head = 0;
    bool enable_loop;
    void read_status();
    QString to_QString();

    static void release_array(char **array, int &n) {
        for (int i = 0; i < n; ++i) {
            delete[] array[i];
        }
    }
};


#endif //GUI_MAINWINDOW_H
