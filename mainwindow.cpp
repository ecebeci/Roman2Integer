/*
 *  QT Üzerinden Roma sayılarını günümüz Arap-Hint sayı sistemine veya tersi durum için çevirme aracı.
 *  Hazırlayan: M. Emre Cebeci
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButton_2_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Roma2TamSayi
void MainWindow::on_pushButton_clicked()
{
    ui->label_3->setText("");
    if(ui->lineEdit->text().isEmpty()){
        ui->label_3->text()="Text boş";
        return;
    }
    firstList.clear();
    int errorFlag=0;
    for(int i=0; i<ui->lineEdit->text().size();i++ ){
        switch(ui->lineEdit->text().at(i).toLatin1()) {
        case 'I':
            firstList.push_back(1);
            break;
        case 'V':
            firstList.push_back(5);
            break;
        case 'X':
            firstList.push_back(10);
            break;
        case 'L':
            firstList.push_back(50);
            break;
        case 'C':
            firstList.push_back(100);
            break;
        case 'D':
            firstList.push_back(500);
            break;
        case 'M':
            firstList.push_back(1000);
            break;
        default:
            ui->label_3->setText("Geçersiz sayı");
            errorFlag = 1;
            break;
        }
        if(errorFlag==1){
            break;
        }
    }
    if(errorFlag==1){
        return;
    }

    for(int i=0; i<firstList.size()-1;i++){ // son elemanın kontrolüne gerek yok
        int j=0; // kaç tane aynı değer var
        errorFlag=1;
        while(j<4){ // 4. tekrar varsa sıkıntı hmmm
            if(i+j < firstList.size()-1){
                if(firstList.at(i+j)!=firstList.at(i+j+1)){
                    errorFlag=0;
                    break;
                }
            } else { // son durumdaysa
                if(j==3){ //4. deger varsa!!
                    break;
                }
                errorFlag=0;
                break;
            }

            j++;
        }
        if(errorFlag==1){
            ui->label_3->setText("Geçersiz sayı!");
            return;
        }
        if(firstList.at(i)<firstList.at(i+1)){ // negatife çevirme örnek: IV varsa -(1) + 5
            firstList[i] =  -firstList[i];
        }
    }

    //Topla
    int convert=0;
    for(int i=0; i<firstList.size();i++){
        convert += firstList.at(i);
    }

    ui->lineEdit_2->setText(QVariant(convert).toString());
    ui->label_3->setText("Roma Rakamları Çevrildi");
    qDebug() << firstList << "Sonuç" << convert;

}

// TamSayi2Roma
void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text().isEmpty()){ // Text mevcut mu?
        ui->label_3->text()="Text boş";
        return;
    }

    QRegExp re("\\d*");  // Sayı mı kontrolü
    if (!re.exactMatch(ui->lineEdit_2->text())) {
        ui->label_3->setText("Sayi hatali formatta");
        return;
    }

    if(ui->lineEdit_2->text().toInt()>3999){
        ui->label_3->setText("Bu sayi çevrilemez");
        return;
    }

    ui->label_3->setText("");
    ui->lineEdit->setText("");

    // Rakamları ayır
    QList<int> tutunamayanlar;
    unsigned int sizeOfText = ui->lineEdit_2->text().length();
    for(unsigned int i = 0; i<sizeOfText;i++){
        tutunamayanlar.push_back(ui->lineEdit_2->text().at(i).digitValue()*qPow(10,(sizeOfText-1)-i));
    }

    qDebug() << tutunamayanlar;
    for(int i=0; i<tutunamayanlar.size();i++){
        QString temp = QString::number(tutunamayanlar.at(i)); // ram usage = ( ͡°͜ʖ ͡°)
        int digit = temp.at(0).digitValue(); // ilk elemanı örnek, tut 2000 ise 2 yi tutar ki MM dönsün sonra. Dikkat at(0) olmalı.
        // Kaç basamaklı ise ona göre roma rakamlarına çevirme. örnek 2131 = 2000 100 30 1  2000 = MM 100 = C 30=XXX 1=I => MMCXXXI
        switch(temp.length()){ // 2000 ise 4 döndürür 100 ise 3 döndürür vs.

        case 1: // Birler basamagi
            if(digit==4){
                ui->lineEdit->setText(ui->lineEdit->text()+ "IV");
                break;
            }
            if(digit==9){
                ui->lineEdit->setText(ui->lineEdit->text()+ "IX");
                break;
            }

            if(digit>4){
                ui->lineEdit->setText(ui->lineEdit->text()+ "V");
                if(digit==5) break;
                for(int j=0; j<=digit-6; j++){
                    ui->lineEdit->setText(ui->lineEdit->text()+ "I");
                }
                break;
            }

            // 1 2 3 durumları
            for(int j=0; j<digit; j++){
                ui->lineEdit->setText(ui->lineEdit->text()+ "I");
            }

            break;

        case 2:  // Onlar basamagi
            if(digit==4){ // 40
                ui->lineEdit->setText(ui->lineEdit->text()+ "XL"); // 10 50, 10 gerisinden olduğundan eksik olur ve 50-10=40
                break;
            }
            if(digit==9){
                ui->lineEdit->setText(ui->lineEdit->text()+ "XC");
                break;
            }

            if(digit>4){
                ui->lineEdit->setText(ui->lineEdit->text()+ "L");
                if(digit==5) break;
                for(int j=0; j<=digit-6; j++){
                    ui->lineEdit->setText(ui->lineEdit->text()+ "X");
                }
                break;
            }

            for(int j=0; j<digit; j++){
                ui->lineEdit->setText(ui->lineEdit->text()+ "X");
            }
            break;

        case 3:  // Yüzler basamagi
            if(digit==4){ // -100 + 500 = 400
                ui->lineEdit->setText(ui->lineEdit->text()+ "CD");
                break;
            }
            if(digit==9){ // 900 için -100 + 1000
                ui->lineEdit->setText(ui->lineEdit->text()+ "CM");
                break;
            }

            if(digit>4){
                ui->lineEdit->setText(ui->lineEdit->text()+ "D"); // 500 belirtilir
                if(digit==5) break; // 500 ise D önceden girildiğinden bırakılır.
                for(int j=0; j<=digit-6; j++){
                    ui->lineEdit->setText(ui->lineEdit->text()+ "X");
                }
                break;
            }

            for(int j=0; j<digit; j++){
                ui->lineEdit->setText(ui->lineEdit->text()+ "C");
            }
            break;

        case 4:  // Binler basamagi

            for(int j=0; j<digit; j++){
                ui->lineEdit->setText(ui->lineEdit->text()+ "M");
            }
            break;
        }
    }
}
