/*
# This file is part of Computer Vision Exam Project
#
# Copyright(c) 2012 Domenico Luciani
# domenicoleoneluciani@gmail.com
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
#include <time.h>
#include "../lib/funzioni.h"
//Nome della gui
#define NOME "Control"

int main(int argc,char **argv)
{
    if(argc != 2)
    {
        printf("usage: %s <mode>\n0 - integrate webcam\n1 - external webcam\n",argv[0]);
        exit(-1);
    }
    else
    {
        int web=atoi(argv[1]);
        if(web >= 0 && web <= 1)
        {
            CvCapture *cam = cvCaptureFromCAM(web);
    	    cvSetCaptureProperty(cam,CV_CAP_PROP_FRAME_WIDTH,640);
            cvSetCaptureProperty(cam,CV_CAP_PROP_FRAME_HEIGHT,480);
            IplImage *img = cvQueryFrame(cam);
            IplImage *copia = cvCreateImage(cvGetSize(img),8,3);
            IplImage *prima = NULL;
            IplImage *binary = cvCreateImage(cvGetSize(img),8,1);
            IplImage *ris = cvCreateImage(cvGetSize(img),8,3);

            cvNamedWindow(NOME,1);
            //Variabili per prendere l'orario e la data correnti
            time_t tempo;
            struct tm *timeobj;
            time(&tempo);
            timeobj = localtime(&tempo);

            char nome[25];
            long int num=0;
            //Funzione per inserire i dati del tempo in nome
            strftime(nome,24,"%H-%M-%S_%F.avi",timeobj);
            //Creo il writer che si occuperà di scrivere i vari frame presi come video compresso in formato divx
            CvVideoWriter *video = cvCreateVideoWriter(nome,CV_FOURCC('D','I','V','X'),15,cvSize(640,480),1);
            //Inizializzo i font
            CvFont scritta,info;
            cvInitFont(&scritta,CV_FONT_HERSHEY_SIMPLEX,1.0,1.0,0,5,CV_AA);
            cvInitFont(&info,CV_FONT_HERSHEY_SIMPLEX,.6,.6,0,1,6);

            char tasto;
            int i,j,trovato=0,scelta,step = binary->widthStep/sizeof(uchar);
            uchar *target = (uchar*)binary->imageData;
            //Scelta fra dinamica e statica
            do
            {
                printf("-- Scelta modalita' --\n1)Dinamica -- Se ci saranno variazioni tra un frame e l'altro\n2)Statica -- Se ci sono variazioni fra un determinato frame e il frame corrente\nScelta: ");
                scanf("%1d",&scelta);
            }while(scelta < 1 || scelta > 2);

            while(img)
            {
                //Ruoto l'immagine
                cvFlip(img,img,1);
                //Prendo le informazioni sul tempo
                time(&tempo);
                timeobj = localtime(&tempo);
                strftime(nome,24,"%H:%M:%S %F",timeobj);
                //Scrivo le info a schermo
                cvPutText(img,nome,cvPoint(415,475),&info,CV_RGB(0,255,255));
                //Copio il frame
                cvCopy(img,copia);

                riduciNoise(img,img);
                //Dinamica
                if(scelta == 1)
                {
                    //Se è il primo frame preso
                    if(prima == NULL)
                    {
                        prima = cvCreateImage(cvGetSize(img),8,3);
                        //Copio img in prima
                        cvCopy(img,prima);
                    }
                    else
                    {
                        //Se non è il primo frame controllo se ci sono differenze
                        cvAbsDiff(img,prima,ris);
                        //Da colore a grigia
                        cvCvtColor(ris,binary,CV_BGR2GRAY);
                        //Il threshold dell'immagine
                        cvThreshold(binary,binary,62,255,CV_THRESH_BINARY);
                        riduciNoise(binary,binary);
                        cvCopy(img,prima);
                    }

                }
                //Statica
                else
                {
                    //Se ho preso il frame da monitorare
                    if(prima != NULL)
                    {
                        cvAbsDiff(img,prima,ris);
                        cvCvtColor(ris,binary,CV_BGR2GRAY);
                        cvThreshold(binary,binary,62,255,CV_THRESH_BINARY);
                        riduciNoise(binary,binary);

                    }

                }

                //Controllo l'immagine pixel per pixel
                for(i=0; i < binary->height && trovato != 1; i++)
                {
                    for(j=0; j < binary->width && trovato != 1; j++)
                    {
                        if(target[i*step+j] == 255)
                            trovato = 1;
                    }
                }

                //Se trovo un cambiamento
                if(trovato)
                {
                    num++;
                    //Inserisco "REC O" nell'immagine
                    cvPutText(copia,"REC",cvPoint(10,25),&scritta,CV_RGB(255,0,0));
                    cvCircle(copia,cvPoint(100,15),5,CV_RGB(255,0,0),20,8);
                    //Salvo il frame trovato
                    cvWriteFrame(video,copia);
                    trovato = 0;
                }
                //Mostro l'immagine
                cvShowImage(NOME,copia);

                tasto = cvWaitKey(15);

                if(tasto == 'q')
                    break;
                //Se premo v salvo il frame da monitorare
                else if(tasto == 'v' && scelta == 2)
                {
                    prima = cvCreateImage(cvGetSize(img),8,3);
                    cvCopy(img,prima);
                }

                img = cvQueryFrame(cam);
            }
            //Se ho preso dei frame
            if(num != 0)
            {
                //Scrivo il video
                cvReleaseVideoWriter(&video);
                printf("Video %s salvato\n",nome);
            }
        }
        else
            puts("webcam not found");
    }
    return 0;
}

