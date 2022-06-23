#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <typeinfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    repeatFinder.clear();
    lengthSorter.clear();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString s = "";
    QVector<QString>qv;
    qv.push_back("0");
    while (!file.atEnd()) {
        QString line = file.readLine();
        line.chop(1);
        s.append(line + "_");
        qv.push_back(line);
        repeatFinder.calc(line);
        lengthSorter.calc(line);

        qDebug() << line;
    }
    s.chop(1);
    SendToServer(qv);
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/home",
                                                      tr("text files (*.txt)"));
    ui->label->setText("Path to file:" + path);

}

void MainWindow::on_pushButton_3_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
}

void MainWindow::SendToServer(QVector<QString> str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    out  << str;
    socket->write(Data);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_14);
    if(in.status() == QDataStream::Ok){
//        QString str;
//        in >> str;
//        ui->textBrowser->append(str);
        QMap<QChar, int> d1;
        QMap<int, QVector<QString>> d2;
        QString qs1 = "";
        QString qs2 = "";
        QVector<QString> qv;
        in >> d1 >> d2 >> qv;
        if(d1.size() != 0 && d2.size() != 0){
            //qDebug() << qv;
            nextBlockSize = 0;

            for( QMap<QChar, int>::iterator i = d1.begin(); i != d1.end(); i++){
                qs1.append(i.key());
                qs1.append(" - " + QString::number(i.value()) + "\n");
            }
            ui->textBrowser->setText(qs1);

            for(QMap<int, QVector<QString>>::iterator i = d2.begin(); i != d2.end(); i++){
                int c = 0;
                for(QString j: i.value()){
                    if(c == 0)qs2.append(QString::number(i.key()));
                    else qs2.append(" ");
                    qs2.append(" - " + j + "\n");
                    c++;
                }
            }
            qDebug() << qv;
            ui->textBrowser_2->setText(qs2);
        }
        if(qv.size() != 0){
            ui->textBrowser_3->clear();
            for(int i = 0; i < qv.size(); i++){
                ui->textBrowser_3->append(qv[i]);
            }
        }
    }
    else
    {
        ui->textBrowser->append("read error");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    SendToServer(QVector<QString>{"1"});

}
