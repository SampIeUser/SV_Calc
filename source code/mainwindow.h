#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <algorithm>
#include <QKeyEvent>



#include "calc_actions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_enter_clicked();

    void on_button_1_clicked();
    void on_button_2_clicked();
    void on_button_3_clicked();
    void on_button_4_clicked();
    void on_button_5_clicked();
    void on_button_6_clicked();
    void on_button_7_clicked();
    void on_button_8_clicked();
    void on_button_9_clicked();
    void on_button_0_clicked();
    void on_button_devide_clicked();
    void on_button_multipy_clicked();
    void on_button_minus_clicked();
    void on_button_plus_clicked();
    void on_button_pow_n_clicked();
    void on_button_x_x_x_clicked();
    void on_button_sqrt_clicked();
    void on_button_sqrt_advanced_clicked();
    void on_button_plus_and_minus_clicked();
    void on_button_mem_plus_clicked();
    void on_button_mem_minus_clicked();
    void on_button_mem_append_clicked();
    void on_button_mem_delete_clicked();
    void on_button_clear_last_clicked();
    void on_button_clear_element_clicked();
    void on_button_clear_all_clicked();
    void on_button_dot_clicked();

protected:
    void keyPressEvent(QKeyEvent* e);



private:
    Ui::MainWindow *ui;

    //displays entered numbers
    void display_numbers(int num);
    // for operations
    void display_numbers(char operation);
    // LCD
    QString LCD_data_string; // stores value to lcd
    QString history_num_display; // displays all history
    void clear_info(); // clear history and lcd
    // memory
    double memory_data;
    void display_info();

};
#endif // MAINWINDOW_H
