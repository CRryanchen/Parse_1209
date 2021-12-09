#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xinshengparse.h"
#include "fengxianparse.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnStart, &QPushButton::clicked, [=](){

      QString inputString = ui->inputText->toPlainText();
      if (inputString.isEmpty())
      {
        ui->statusBar->showMessage("请输入你要解析的报文", 3000);
        return ;
      }

      ui->outputText->clear();
      if (ui->comboBox->currentText() == "鄂尔多斯新圣")
      {
          XinShengParse xs(inputString);

          if (ui->lineEdit->text() != NULL)
          {
              // 则使用lineEdit里面的数据作为密钥
              xs.setUseDefaultKey(false);
              xs.SetLatestKey(QByteArray::fromHex(ui->lineEdit->text().toLocal8Bit()));
              qDebug() << ui->lineEdit->text();
              qDebug() << "我要使用新密钥";
          }
          else
          {
              qDebug() << "使用初始密钥";
          }

          xs.StartParse();
          if (xs.m_ErrInfo.isEmpty())
          {
              ui->outputText->append(xs.m_parsedHead);
              ui->outputText->append(xs.m_parsedBody);
              ui->lineEdit->setText(xs.GetLatestKey());
          }
          else
          {
              ui->statusBar->showMessage(xs.m_ErrInfo, 4000);// 状态栏显示错误信息
          }

      }
      else if (ui->comboBox->currentText() == "上海奉贤")
      {
          FengXianParse fx(inputString);

          fx.StartParse();
          ui->outputText->append(fx.m_parsedHead);
          ui->outputText->append(fx.m_parsedBody);
      }

      qDebug() << ui->comboBox->currentText();

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
