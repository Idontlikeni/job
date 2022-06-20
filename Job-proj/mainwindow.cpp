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
    while (!file.atEnd()) {
        QString line = file.readLine();
        line.chop(1);
        s.append(line + "_");
        repeatFinder.calc(line);
        lengthSorter.calc(line);

        qDebug() << line;
    }
    s.chop(1);
    SendToServer(s);
    QString qs1 = "";
    QString qs2 = "";
    QMap<QChar, int> d1 = repeatFinder.get_qdata();
    QMap<int, QVector<QString>> d2 = lengthSorter.get_qdata();

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
    //qDebug() << qs2;
    ui->textBrowser_2->setText(qs2);

    //qDebug() << "First: " << d1 << "Second: " << d2;
//    for(std::unordered_map<char, int>::iterator i = data.begin(); i != data.end(); i++){
//        qs1.append(i->first);
//        qs1.append(" - " + QString::number(i->second) + "\n");
//    }
//    qDebug() << qs1;
//    ui->textBrowser->setText(qs1);
//    QString qs2 = "";
//    for(std::map<int, std::vector<std::string>>::iterator i = data2.begin(); i != data2.end(); i++){
//        int c = 0;
//        for(std::string j: i->second){
//            if(c == 0)qs2.append(QString::number(i->first));
//            else qs2.append(" ");
//            qs2.append(" - " + QString::fromStdString(j) + "\n");
//            c++;
//        }
//    }
//    qDebug() << qs2;
//    ui->textBrowser_2->setText(qs2);
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

void MainWindow::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    out << quint64(0) << str;
    out.device()->seek(0);
    out << quint64(Data.size() - sizeof(quint64));
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
        for (;;) {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            QString str;
            in >> str;
            nextBlockSize = 0;
            ui->textBrowser->append(str);
        }
    }
    else
    {
        ui->textBrowser->append("read error");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    SendToServer("Teeeesting");
}
