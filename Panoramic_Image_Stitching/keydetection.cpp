#include "keydetection.h"
#include "ui_keydetection.h"
#include <QPoint>
#include <cmath>

Keydetection::Keydetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Keydetection)
{

    ui->setupUi(this);

}

Keydetection::~Keydetection()
{
    delete ui;
}

void Keydetection::on_pushButton_clicked()
{
    if(index==0){   //if you get first key detection
        connect(this,SIGNAL(sendArray(int**)),parent(),SLOT(RecvFirstArray(int**)));
        emit sendArray(nonMax_result);
    }
    else if(index==1){
        connect(this,SIGNAL(sendArray(int**)),parent(),SLOT(RecvSecondArray(int**)));
        emit sendArray(nonMax_result);
    }
    //
    close();
}

//it performed like a main function
void Keydetection::on_pushButton_2_clicked()
{
    GaussianFilter();   //to make blur and grayscale image
    dx_gradient();      //to calculate gradient x and make 2d array
    dy_gradient();      //to calculate gradient y and make 2d array
    Calculate_window(); //to calculate R and corner
    nonMaximumSuppression();  //to get non maximum suppression
    Paint(nonMax_result);            //to paint the corner with red color on the Image

    qDebug()<<"To find the corner : "<<cnt;
    qDebug()<<"Non maximum suppression the corner : "<<cnt_non;

}


//you get paddingArray from QImage
int** Keydetection::Padding(QImage blurImage, int width, int height, int paddingSize)
{
    //initialize padding2Darray
    int ** padding2Darray = new int *[height+paddingSize*2];
    for(int i=0; i<height +paddingSize*2; i++){
        padding2Darray[i] = new int[width+paddingSize*2];
    }

    //put blurImageColor on the padding2Darray
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
        padding2Darray[i+paddingSize][j+paddingSize] = blurImage.pixelColor(j,i).red();
        }
    }

    //Fill an empty space with same padding
    for(int i=0; i<height; i++){
        padding2Darray[i+1][0] = blurImage.pixelColor(0,i).red();
        padding2Darray[i+1][width+2*paddingSize-1] = blurImage.pixelColor(width-1,i).red();
    }

    //Fill an empty space with same padding
    for(int i=0; i<width; i++){
        padding2Darray[0][i+1] = blurImage.pixelColor(i,0).red();
        padding2Darray[height+2*paddingSize-1][i+1] = blurImage.pixelColor(i,height-1).red();
    }

    //Fill an empty space with same padding
    padding2Darray[0][0] = blurImage.pixelColor(0,0).red();
    padding2Darray[height+2*paddingSize-1][0] = blurImage.pixelColor(0,height-1).red();
    padding2Darray[0][width+2*paddingSize-1] = blurImage.pixelColor(width-1,0).red();
    padding2Darray[height+2*paddingSize-1][width+2*paddingSize-1] = blurImage.pixelColor(width-1,height-1).red();


    return padding2Darray;
}

//you get paddingArray from another 2Darray
int **Keydetection::paddingArray(int **arr2D, int width, int height, int paddingSize)
{
    //initialize finalPaddingArray
    int **finalPaddingArray = new int *[height+paddingSize*2];
    for(int i = 0; i< height +paddingSize*2; i++ ){
        finalPaddingArray[i] = new int [width+paddingSize*2];
    }

    //put arr2D value on the finalPaddingArray
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            finalPaddingArray[i+paddingSize][j+paddingSize] = arr2D[i][j];
        }
    }

    //Fill an empty space with zero padding
    for(int j = 0; j < paddingSize; j++){
        for(int i = 0; i< width+2*paddingSize-1; i++){
            finalPaddingArray[0+j][i] = 0;
            finalPaddingArray[height+2*paddingSize-j-1][i] = 0;
        }
    }

    //Fill an empty space with zero padding
    for(int j = 0; j< paddingSize; j++){
        for(int i = 0; i <height+paddingSize;i++){
            finalPaddingArray[paddingSize+i][j] = 0;
            finalPaddingArray[paddingSize+i][width+2*paddingSize-j-1] = 0;
        }
    }

    return finalPaddingArray;
}

//to get Gaussian blur image
//get a new image - blurImage
void Keydetection::GaussianFilter()
{
    //to initialize blur image
    wei = cylindricalImage.width();
    hei = cylindricalImage.height();
    blurImage = QImage(wei,hei,QImage::Format_RGB888);
    blurImage.fill(0);

    //First, Smoothing the image with Gaussian Filter
    int kernal[3][3] = { {1, 2, 1},
                         {2, 4, 2},
                         {1, 2, 1} };

    float kernel_sum = 16.0;

    for(int i = 1; i < wei-1; i++){
        for(int j = 1; j < hei-1; j++){
           float r = 0, b = 0, g = 0;

           //set Red color***********************************************
           r = (kernal[0][0]* cylindricalImage.pixelColor(i-1,j-1).red())+
               (kernal[0][1]* cylindricalImage.pixelColor(i,j-1).red()  )+
               (kernal[0][2]* cylindricalImage.pixelColor(i+1,j-1).red())+

               (kernal[1][0]* cylindricalImage.pixelColor(i-1,j).red()  )+
               (kernal[1][1]* cylindricalImage.pixelColor(i,j).red()    )+
               (kernal[1][2]* cylindricalImage.pixelColor(i+1,j).red()  )+

               (kernal[2][0]* cylindricalImage.pixelColor(i-1,j+1).red()  )+
               (kernal[2][1]* cylindricalImage.pixelColor(i,j+1).red()     )+
               (kernal[2][2]* cylindricalImage.pixelColor(i+1,j+1).red() );
           //**************************************************************

           //set Green color***********************************************
           g = (kernal[0][0]* cylindricalImage.pixelColor(i-1,j-1).green() )+
               (kernal[0][1]* cylindricalImage.pixelColor(i,j-1).green()  ) +
               (kernal[0][2]* cylindricalImage.pixelColor(i+1,j-1).green() )+

               (kernal[1][0]* cylindricalImage.pixelColor(i-1,j).green()   )+
               (kernal[1][1]* cylindricalImage.pixelColor(i,j).green()    ) +
               (kernal[1][2]* cylindricalImage.pixelColor(i+1,j).green()  ) +

               (kernal[2][0]* cylindricalImage.pixelColor(i-1,j+1).green())  +
                (kernal[2][1]* cylindricalImage.pixelColor(i,j+1).green() )   +
                (kernal[2][2]* cylindricalImage.pixelColor(i+1,j+1).green());
           //**************************************************************

           //set Blue color***********************************************
             b =  (kernal[0][0]* cylindricalImage.pixelColor(i-1,j-1).blue())+
                  (kernal[0][1]* cylindricalImage.pixelColor(i,j-1).blue() ) +
                  (kernal[0][2]* cylindricalImage.pixelColor(i+1,j-1).blue())+

                  (kernal[1][0]* cylindricalImage.pixelColor(i-1,j).blue() ) +
                  (kernal[1][1]* cylindricalImage.pixelColor(i,j).blue()   ) +
                  (kernal[1][2]* cylindricalImage.pixelColor(i+1,j).blue() )+

                  (kernal[2][0]* cylindricalImage.pixelColor(i-1,j+1).blue() ) +
                  (kernal[2][1]* cylindricalImage.pixelColor(i,j+1).blue()   ) +
                  (kernal[2][2]* cylindricalImage.pixelColor(i+1,j+1).blue());
           //**************************************************************
         new_rgb.setRgb(r/kernel_sum,g/kernel_sum,b/kernel_sum);
         blurImage.setPixelColor(i,j,new_rgb);
        }


    }

    //Second, change color image to grayscale image
    for(int i=0; i<wei; i++){
        for(int j=0; j<hei; j++){
            int r = 0, g = 0, b =0, gy=0;
            r = blurImage.pixelColor(i,j).red();
            g = blurImage.pixelColor(i,j).green();
            b = blurImage.pixelColor(i,j).blue();

            //fomula for make the gray color with RGB colors
            gy = 0.299*r + 0.587*g + 0.114*b;

            gray.setRgb(gy,gy,gy);
            blurImage.setPixelColor(i,j,gray);  //get gray color and set pixel color on blurImage
        }
    }

}


//get gradient x with sobel mask
//save the value in 2D array - _dx[][]
void Keydetection::dx_gradient()
{
    float new_dx = 0;

    int Gx[3][3] = { {-1, 0, 1},
                     {-2, 0, 2},
                     {-1, 0, 1}};

    int pad_size = 1;
    int ** sobel_result = Padding(blurImage, wei, hei, pad_size);
    //initialize Dynamic allocation of 2D arrays
    _dx = new int *[hei];
    for(int i=0; i<hei; i++){
        _dx[i] = new int[wei];  //initialize Dynamic allocation of 2D arrays
    }

    //to calcualte sobel operator
    for(int i=pad_size; i<hei + pad_size; i++){
        for(int j=pad_size; j<wei + pad_size;j++){
            //sobel operator************************************************
            new_dx = Gx[0][0]* sobel_result[i-1][j-1]+
                    Gx[0][1]* sobel_result[i-1][j]+
                    Gx[0][2]* sobel_result[i-1][j+1]+
                    Gx[1][0]* sobel_result[i][j-1]+
                    Gx[1][1]* sobel_result[i][j]+
                    Gx[1][2]* sobel_result[i][j+1]+
                    Gx[2][0]* sobel_result[i+1][j-1]+
                    Gx[2][1]* sobel_result[i+1][j]+
                    Gx[2][2]* sobel_result[i+1][j+1];
            //***************************************************************

            //to get gradient x data
            _dx[i-pad_size][j-pad_size] = new_dx;

        }
    }
}

//get gradient y with sobel mask
//save the value in 2D array - _dy[][]
void Keydetection::dy_gradient()
{
        float new_dy = 0;

        int Gy[3][3] = { {1, 2, 1},
                         {0, 0, 0},
                         {-1,-2,-1}};

        int pad_size = 1;
        int ** sobel_result = Padding(blurImage, wei, hei, pad_size);

        //initialize Dynamic allocation of 2D arrays
        _dy = new int *[hei];
        for(int i=0; i<hei; i++){
            _dy[i] = new int[wei];
        }

        //to calcualte sobel operator
        for(int i=pad_size; i<hei + pad_size; i++){
            for(int j=pad_size; j<wei + pad_size;j++){
                //sobel operator************************************************
                new_dy = Gy[0][0]* sobel_result[i-1][j-1]+
                        Gy[0][1]* sobel_result[i-1][j]+
                        Gy[0][2]* sobel_result[i-1][j+1]+
                        Gy[1][0]* sobel_result[i][j-1]+
                        Gy[1][1]* sobel_result[i][j]+
                        Gy[1][2]* sobel_result[i][j+1]+
                        Gy[2][0]* sobel_result[i+1][j-1]+
                        Gy[2][1]* sobel_result[i+1][j]+
                        Gy[2][2]* sobel_result[i+1][j+1];
                //***************************************************************

                //to get gradient x data
                _dy[i-pad_size][j-pad_size] = new_dy;

            }
        }

}

//paint with Image but it is too small
void Keydetection::Paint(int **arr){

    for(int i = 0;i<hei;i++){
        for(int j = 0; j<wei; j++){
            if(arr[i][j]!=0){
            cylindricalImage.setPixelColor(j,i,QColor(255,0,0));
            }
        }
    }

    pix = QPixmap::fromImage(cylindricalImage);
    ui->resultImage->setPixmap(pix);
    ui->resultImage->setScaledContents(true);
}

//get non maximum suppression
//you can adjust padding size at this function
void Keydetection::nonMaximumSuppression()
{

    int pad_size = 10;  //when you want to change pad_size, just change it.
    int **temp_result = paddingArray(thresh_result,wei,hei,pad_size);

    //initialize Dynamic allocation of 2D arrays
    nonMax_result = new int *[hei];
    for(int i = 0; i< hei; i++){
        nonMax_result[i] = new int[wei];
    }

    //Check if there is a large value around paddingSize
    for(int i = pad_size;i< hei+ pad_size; i++){
        for(int j = pad_size; j < wei + pad_size; j++){
            //save the value on that location
            int valueOfCenter = temp_result[i][j];

            //if you don't find it, you get value on that location
            nonMax_result[i-pad_size][j-pad_size] = temp_result[i][j];

            for(int a = -pad_size; a < pad_size+1;a++){
                for(int b = -pad_size; b < pad_size+1; b++){
                    int valueOfTemp = temp_result[i+a][j+b];
                    if((a != 0 )&&( b != 0)){ //you don't need to check it when a == 0 and b == 0
                        if(valueOfTemp > valueOfCenter){
                            //if you find the large value, you get '0' on that location
                            nonMax_result[i-pad_size][j-pad_size] = 0;

                        }
                    }
                }
            }

        }
    }

    //to calculate how may corner when you do non-maximum suppression
    for(int i = 0; i< hei; i++){
        for(int j = 0; j< wei; j++){
            if(nonMax_result[i][j] > 0){
                cnt_non++;
            }
        }
    }


}

//to calculate R with 3*3 window
void Keydetection::Calculate_window()
{
    //initialize Dynamic allocation of 2D arrays
    thresh_result = new int *[hei];
    for(int i=0; i<hei; i++){
        thresh_result[i] = new int[wei];
    }

    //First, just put '0' in thresh_result_2Darray
    for(int i=0; i<hei; i++){
       for(int j=0; j<wei; j++){
           thresh_result[i][j] = 0;
        }
     }

    //Calculate the R with all pixel
    for(int i =1; i < blurImage.height()-1; i++){
        for(int j=1; j<blurImage.width()-1; j++){
           int Ix_sqr = 0,Iy_sqr = 0 ,IxIy = 0;
           float k = 0.04;
           int deter = 0, trace = 0, threshold = 0;
           //qDebug()<<i<<j;

           //you must set vector empty space
           x_store.clear();
           y_store.clear();

           //you can get update dx,dy in this function
           x_store = Get_window_dx(i,j);
           y_store = Get_window_dy(i,j);

           //calculate Ix_sqr, IxIy, Iy_sqr
           for(int k = 0; k <9 ; k++){
               int temp_x = 0, temp_y = 0;
               temp_x = x_store.at(k);
               temp_y = y_store.at(k);
               //qDebug()<<temp_x<<" "<<temp_y;
               Ix_sqr += temp_x * temp_x;
               IxIy += temp_x * temp_y;
               Iy_sqr += temp_y * temp_y;
           }

           //calculate the R
           deter = (Ix_sqr * Iy_sqr) - (IxIy * IxIy);
           trace = pow((Ix_sqr + Iy_sqr),2);
           threshold = deter - (k*trace);

           //Set a threshold value and update the thresh_result_2Darray
           //Actually, I don't know how to set the proper threshold.
           if(threshold>1000000000){
               thresh_result[i][j] = threshold;
               cnt++;
           }
        }
    }
}

//input : pixel(i,j)
//output : a vector containing the value of dx
//3*3 window so we can get 9 values of _dx
QVector<int> Keydetection::Get_window_dx(int i, int j)
{
   QVector<int> get_dx;

   //get gradient value surrounding (i,j) points - 3*3 window
   for(int a = -1; a < 2; a ++){
       for(int b = -1; b < 2; b++){
           get_dx.push_back(_dx[i+a][j+b]);  //put _dx in vector
       }
   }

   return get_dx;
}


//input : pixel(i,j)
//output : a vector containing the value of dy
//3*3 window so we can get 9 values of _dy
QVector<int> Keydetection::Get_window_dy(int i, int j)
{
    QVector<int> get_dy;

    //get gradient value surrounding (i,j) points - 3*3 window
    for(int a = -1; a < 2; a ++){
        for(int b = -1; b < 2; b++){
            get_dy.push_back(_dy[i+a][j+b]);  //put _dy in vector
        }
    }

    return get_dy;
}





