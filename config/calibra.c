/*
# This file is part of Computer Vision Exam Project                            
#                                           
# Copyright(c) 2012 Domenico Luciani        
# domenico.luciani@email.it
#  
# 
# This file may be licensed under the terms of of the
# GNU General Public License Version 3 (the ``GPL'').
# 
# Software distributed under the License is distributed
# on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
# express or implied. See the GPL for the specific language
# governing rights and limitations.
#                
# You should have received a copy of the GPL along with this
# program. If not, go to http://www.gnu.org/licenses/gpl.html
# or write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <cv.h>
#include <highgui.h>
#include "../lib/funzioni.h"
//File di configurazione
#define FILE_CONFIG "config.txt"
//Nomi delle GUI
#define NORMAL "Calibra"
#define BINARY "Calibra - Binaria"

int main(int argc,char *argv[])
{
    int web;
    //Controllo se i parametri sono corretti
    if(argc != 2)
        printf("usage: %s <mode>\n0 - integrate webcam\n1 - external webcam",argv[0]);
    else
    {
        web = atoi(argv[1]);
        
        if(web >= 0 && web <= 1)
        {
            //Inizializzo la webcam
            CvCapture *capt = cvCaptureFromCAM(web);
            //Setto le proprietà della webcam a 640x480
            cvSetCaptureProperty(capt,CV_CAP_PROP_FRAME_WIDTH,640);
            cvSetCaptureProperty(capt,CV_CAP_PROP_FRAME_HEIGHT,480);   
            //Prendo il primo frame dalla webcam e lo salvo
            IplImage *imm = cvQueryFrame(capt);
            //Creo immagini
            IplImage *hsv = cvCreateImage(cvGetSize(imm),8,3);
            IplImage *binary = cvCreateImage(cvGetSize(imm),8,1);

            //Variabili varie
            int i,j,step = binary->widthStep/sizeof(uchar);
            uchar *target = (uchar*)binary->imageData;
            char tasto;
            //Alloco spazio per i valori HSV
            HSV *low = (HSV*)malloc(sizeof(HSV));
            HSV *high = (HSV*)malloc(sizeof(HSV));
            //Alloco spazio per il rettangolo
            Rettangolo *punti = (Rettangolo*)malloc(sizeof(Rettangolo));
            //Leggo i dati dal file di configurazione
            leggiConfig(low,high,(char*)FILE_CONFIG);
            //Creo le GUI
            cvNamedWindow(NORMAL,CV_WINDOW_AUTOSIZE);
            cvNamedWindow(BINARY,CV_WINDOW_AUTOSIZE);
            //Ciclo while che si occuperà di prendere i frame
            while(imm)
            {
                //Creo le trackbar
                cvCreateTrackbar("HMIN",NORMAL,&low->H,255,NULL);
                cvCreateTrackbar("SMIN",NORMAL,&low->S,255,NULL);
                cvCreateTrackbar("VMIN",NORMAL,&low->V,255,NULL);
                
                cvCreateTrackbar("HMAX",NORMAL,&high->H,255,NULL);
                cvCreateTrackbar("SMAX",NORMAL,&high->S,255,NULL);
                cvCreateTrackbar("VMAX",NORMAL,&high->V,255,NULL);
               //Ruoto l'immagine
                cvFlip(imm,imm,1);
                //Converto in hsv
                cvCvtColor(imm,hsv,CV_BGR2HSV);
                //cerco il colore
                cvInRangeS(hsv,cvScalar(low->H,low->S,low->V),cvScalar(high->H,high->S,high->V),binary);
                //Riduco i disturbi
                riduciNoise(binary,binary);
                //Resetto il rettangolo
                *punti = {10000,0,10000,0};

                //Controllo pixel per pixel
                for(i=0; i < binary->height; i++)
                {
                    for(j=0; j < binary->width; j++)
                    {
                        if(target[i*step+j] == 255)
                        {
                            //I punti del nostro rettangolo
                            if(j < punti->xmin)
                                punti->xmin = j;
                            if(j > punti->xmax)
                                punti->xmax = j;
                            if(i < punti->ymin)
                                punti->ymin = i;
                            if(i > punti->ymax)
                                punti->ymax = i;
                        }
                    }
                }
                //Creo il rettangolo
                cvRectangle(imm,cvPoint(punti->xmin,punti->ymin),cvPoint(punti->xmax,punti->ymax),CV_RGB(255,0,0),2,8,0);
               //Creo il baricentro
                cvCircle(imm,cvPoint((punti->xmin+punti->xmax)/2,(punti->ymin+punti->ymax)/2),2,CV_RGB(0,0,255),-1,CV_AA,0);
                //Mostro le GUI
                cvShowImage(NORMAL,imm);
                cvShowImage(BINARY,binary);
                //Aspetto 15 millisecondi
                tasto = cvWaitKey(15);

                switch(tasto)
                {
                    //Se premo 'q' esco
                    case 'q':
                        return 2;
                        break;
                    case 's':
                        //Se premo 's' salvo i dati che mi servono
                        scriviConfig(low,high,(char*)FILE_CONFIG);
                        break;
                }
                //Prendo un altro frame
                imm = cvQueryFrame(capt);
            }
            //Libero tutto ciò che ho allocato in precedenza
            cvReleaseImage(&imm);
            cvReleaseImage(&binary);
            cvReleaseImage(&hsv);
            cvReleaseCapture(&capt);
        }
        else
            puts("webcam not found");
    }
    
    return 0;
}
