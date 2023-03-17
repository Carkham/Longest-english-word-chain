//
// Created by AORUS on 2023/3/17.
//

#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QLineEdit>
#include <QButtonGroup>
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
    void functionButton_clicked(int id);
private:
    Ui::MainWindow *ui;
    QButtonGroup *buttonGroup;
    int word_num, result_num;
    long s, e;
    char **words, **results, last_fn;
    char head = 0, tail = 0, d_head = 0;
    bool enable_loop;
    void read_status();

    static void release_array(char **array, int &n) {
        for (int i = 0; i < n; ++i) {
            delete[] array[i];
        }
        n = 0;
    }

    static std::string to_second_string(long delta) {
        double seconds = ((double ) delta) / 1000.;
        char result[10] = {};
        sprintf(result, "%.2f", seconds);
        std::string string(result);
        return string;
    }
};


#endif //GUI_MAINWINDOW_H
