#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tb_extra->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetInputText(const std::string& text)
{
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text)
{
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text)
{
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text)
{
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key)
{
    if (key.has_value()) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb)
{
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb)
{
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb)
{
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb)
{
    controller_cb_ = cb;
}

void MainWindow::on_btn_0_clicked()
{
    if (digit_cb_) {
        digit_cb_(0);
    }
}

void MainWindow::on_btn_1_clicked()
{
    if (digit_cb_) {
        digit_cb_(1);
    }
}

void MainWindow::on_btn_2_clicked()
{
    if (digit_cb_) {
        digit_cb_(2);
    }
}

void MainWindow::on_btn_3_clicked()
{
    if (digit_cb_) {
        digit_cb_(3);
    }
}

void MainWindow::on_btn_4_clicked()
{
    if (digit_cb_) {
        digit_cb_(4);
    }
}

void MainWindow::on_btn_5_clicked()
{
    if (digit_cb_) {
        digit_cb_(5);
    }
}

void MainWindow::on_btn_6_clicked()
{
    if (digit_cb_) {
        digit_cb_(6);
    }
}

void MainWindow::on_btn_7_clicked()
{
    if (digit_cb_) {
        digit_cb_(7);
    }
}

void MainWindow::on_btn_8_clicked()
{
    if (digit_cb_) {
        digit_cb_(8);
    }
}

void MainWindow::on_btn_9_clicked()
{
    if (digit_cb_) {
        digit_cb_(9);
    }
}

void MainWindow::on_btn_plus_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::ADDITION);
    }
}

void MainWindow::on_btn_minus_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::SUBTRACTION);
    }
}

void MainWindow::on_btn_mult_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::MULTIPLICATION);
    }
}

void MainWindow::on_btn_div_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::DIVISION);
    }
}

void MainWindow::on_btn_xy_clicked()
{
    if (operation_cb_) {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::on_btn_equally_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::EQUALS);
    }
}

void MainWindow::on_btn_c_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::CLEAR);
    }
}

void MainWindow::on_btn_ms_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::MEM_SAVE);
    }
}

void MainWindow::on_btn_mr_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::MEM_LOAD);
    }
}

void MainWindow::on_btn_mc_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::MEM_CLEAR);
    }
}

void MainWindow::on_btn_plus_minus_clicked()
{
    if(control_cb_){
        control_cb_(ControlKey::PLUS_MINUS);
    }
}

void MainWindow::on_btn_delete_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::BACKSPACE);
    }
}

void MainWindow::on_tb_extra_clicked()
{
    if (control_cb_) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}


void MainWindow::on_cmb_controller_currentIndexChanged()
{
    if (controller_cb_) {
        QString selectedText = ui->cmb_controller->currentText();
        ControllerType controllerType;
        if (selectedText == "double") {
            controllerType = ControllerType::DOUBLE;
        } else if (selectedText == "float") {
            controllerType = ControllerType::FLOAT;
        } else if (selectedText == "uint8_t") {
            controllerType = ControllerType::UINT8_T;
        } else if (selectedText == "int") {
            controllerType = ControllerType::INT;
        } else if (selectedText == "int64_t") {
            controllerType = ControllerType::INT64_T;
        } else if (selectedText == "size_t") {
            controllerType = ControllerType::SIZE_T;
        } else if (selectedText == "Rational") {
            controllerType = ControllerType::RATIONAL;
        } else {
            return;
        }
        controller_cb_(controllerType);
    }
}
