#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

;
    // setting zero on startup
   clear_info();

    // setting mem to 0
    memory_data = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_info()
{
    ui->LCD_answer->display(LCD_data_string);
    ui->history->setText(history_num_display);
}
void MainWindow::clear_info()
{
    history_num_display = QString::number(0);
    ui->history->setText(history_num_display);
    LCD_data_string = QString::number(0);
    ui->LCD_answer->display(LCD_data_string);
}

// add to history (operation)
void MainWindow::display_numbers(char operation)
{
    QString ops = "-+/*S^";
    if (ops.contains(operation) && history_num_display.back() != '.')
    {
        // prevent adding 0.00000000.....
        if (history_num_display.back() == operation )
        {
            // do nothing. operation is same
        }
        else if (ops.contains(history_num_display.back()))
        {
            // replace operation with new
            history_num_display.chop(1);
            history_num_display += operation;
        }
        else
        {
            // add operation
            QString temp = LCD_data_string;
            temp.remove('0');
            if (LCD_data_string.contains('.') && (temp == '.' || temp == "-."))
            {
                //do_nothing(); only zeros in LCD.
            }
            else
            {
                history_num_display += operation;
                LCD_data_string = "0";
            }

        }
    }
    // only dot left
    else
    {
        QString temp_str_for_dot_count = LCD_data_string;
        temp_str_for_dot_count.remove('.');

        if (history_num_display.back() != '.' && !ops.contains(history_num_display.back()) && (LCD_data_string.length()-temp_str_for_dot_count.length()<1))
        {
            history_num_display += operation;
            LCD_data_string += operation;
        }
        else
        {
            //dot is already exist
        }
    }
    display_info();
}

// show entred numbers
void MainWindow::display_numbers(int num)
{ 
    // adding
    if (LCD_data_string == "0")
    {
        if (history_num_display.back() == '0' || LCD_data_string == "-0")
         {
          history_num_display.chop(1);
         }
         history_num_display += QString::number(num);
         LCD_data_string = QString::number(num);
    }
    else
    {
        history_num_display += QString::number(num);
        LCD_data_string += QString::number(num);
    }
    display_info();
}


// Button =
void MainWindow::on_button_enter_clicked()
{
QString z = Calc_actions().evaluate(history_num_display);
// everything ok
if (z.back() != '$')
{
    ui->LCD_answer->display(z.toDouble());
}
else
{
    // error caught
    ui->LCD_answer->display(0);
    z.chop(1);
    ui->history->setText(z);
}
history_num_display = QString::number(0);
LCD_data_string = QString::number(0);
}

// num buttons
void MainWindow::on_button_1_clicked(){display_numbers(1);}
void MainWindow::on_button_2_clicked(){display_numbers(2);}
void MainWindow::on_button_3_clicked(){display_numbers(3);}
void MainWindow::on_button_4_clicked(){display_numbers(4);}
void MainWindow::on_button_5_clicked(){display_numbers(5);}
void MainWindow::on_button_6_clicked(){display_numbers(6);}
void MainWindow::on_button_7_clicked(){display_numbers(7);}
void MainWindow::on_button_8_clicked(){display_numbers(8);}
void MainWindow::on_button_9_clicked(){display_numbers(9);}
void MainWindow::on_button_0_clicked(){display_numbers(0);}

//basic operation buttons
void MainWindow::on_button_devide_clicked(){display_numbers('/');}
void MainWindow::on_button_multipy_clicked(){display_numbers('*');}
void MainWindow::on_button_minus_clicked(){display_numbers('-');}
void MainWindow::on_button_plus_clicked(){display_numbers('+');}

// advanced operation buttons
void MainWindow::on_button_pow_n_clicked(){display_numbers('^');}
void MainWindow::on_button_sqrt_advanced_clicked(){display_numbers('S');}
// pow_2
void MainWindow::on_button_x_x_x_clicked(){ui->LCD_answer->display(pow((ui->LCD_answer->value()),2));}
void MainWindow::on_button_sqrt_clicked()
{
    if(LCD_data_string[0] == '-')
    {
        ui->history->setText("sqrt() from negative");
    }
    ui->LCD_answer->display(pow((ui->LCD_answer->value()),0.5));
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    // numeric keys
    case Qt::Key_0:
        on_button_0_clicked();
        break;
    case Qt::Key_1:
        on_button_1_clicked();
        break;
    case Qt::Key_2:
        on_button_2_clicked();
        break;
    case Qt::Key_3:
        on_button_3_clicked();
        break;
    case Qt::Key_4:
        on_button_4_clicked();
        break;
    case Qt::Key_5:
        on_button_5_clicked();
        break;
    case Qt::Key_6:
        on_button_6_clicked();
        break;
    case Qt::Key_7:
        on_button_7_clicked();
        break;
    case Qt::Key_8:
        on_button_8_clicked();
        break;
    case Qt::Key_9:
        on_button_9_clicked();
        break;

    //function keys        
    case Qt::Key_Backspace:
        on_button_clear_last_clicked();
        break;
    case Qt::Key_Delete:
        on_button_clear_all_clicked();
        break;
    case Qt::Key_C:
        on_button_clear_element_clicked();
        break;

        //operations
    case Qt::Key_Plus:
        on_button_plus_clicked();
        break;
    case Qt::Key_Minus:
        on_button_minus_clicked();
        break;
    case Qt::Key_Slash:
        on_button_devide_clicked();
        break;
    case Qt::WA_Resized:
        on_button_multipy_clicked();
        break;
    case Qt::Key_Return:
        // premeditated fall through
    case Qt::Key_Equal:
    case Qt::Key_Enter:
        on_button_enter_clicked();
        break;
    case Qt::Key_AsciiCircum:
        on_button_pow_n_clicked();
        break;
    case Qt::Key_Comma:
    case Qt::Key_Period:
        on_button_dot_clicked();
        break;
    }
}

void MainWindow::on_button_plus_and_minus_clicked()
{
    if(LCD_data_string == '0' || (LCD_data_string[0] == 0 && LCD_data_string[1] != '.'))
    {
     // do_nothing();
    }
    else
    {
        if (LCD_data_string[0] != '-')
        {
            history_num_display.chop(LCD_data_string.length());
            LCD_data_string = '-'+LCD_data_string;
            history_num_display += LCD_data_string;
        }
        else
        {
           history_num_display.remove(history_num_display.length()-LCD_data_string.length(),1);
           LCD_data_string.remove(0,1);
        }
    }
    display_info();
}

// add this to num in memory
void MainWindow::on_button_mem_plus_clicked(){memory_data = memory_data + ui->LCD_answer->value();}
// substract this from num in memory
void MainWindow::on_button_mem_minus_clicked(){memory_data = memory_data - ui->LCD_answer->value();}

// append num from mem on LCD
void MainWindow::on_button_mem_append_clicked()
{
    if(LCD_data_string != "0")
    {
        history_num_display.chop(LCD_data_string.length());
    }
    else
    {
        on_button_clear_element_clicked();
    }
    history_num_display +=  QString::number(memory_data);
    LCD_data_string = QString::number(memory_data);

    display_info();
}
// reset mem
void MainWindow::on_button_mem_delete_clicked()
{
 memory_data = 0;
}
// button C
void MainWindow::on_button_clear_last_clicked()
{    
    QString ops = "-+/*S^";
    if (LCD_data_string.length() == 3 && LCD_data_string[2] == '.')
    {
        //prevent -00000000.00... etc
        LCD_data_string = "0";
        history_num_display.chop(3);
    }
    else if (LCD_data_string.length() == 2 && LCD_data_string[0] == '-')
    {
        if (history_num_display.length() == 2)
        {
            history_num_display = "0";
            LCD_data_string = "0";
        }
        else
        {
            history_num_display.chop(2);
            LCD_data_string = "0";
        }
    }
    else if (LCD_data_string.length() == 1)
    {
        if (LCD_data_string == "0")
        {
            // do_nothing();
        }
        else
        {
            if (history_num_display.length() == 1)
            {
                history_num_display = "0";
                LCD_data_string = "0";
            }
            else
            {
                 history_num_display.chop(1);
                LCD_data_string = "0";
            }
        }
    }
    else
    {
        history_num_display.chop(1);
        LCD_data_string.chop(1);
    }

    display_info();
}
// button CE
void MainWindow::on_button_clear_element_clicked()
{
    if (LCD_data_string != "0")
    {
        history_num_display.chop(LCD_data_string.length());
        LCD_data_string = "0";
        if (history_num_display.length() < 1)
        {
            history_num_display = "0";
        }
        display_info();
    }
}
// button CA
void MainWindow::on_button_clear_all_clicked(){ clear_info();}
void MainWindow::on_button_dot_clicked(){display_numbers('.');}
