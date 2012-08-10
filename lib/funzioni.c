/*
# This file is part of Computer Vision Exam Project                            
#                                           
# Copyright(c) 2012 Domenico Luciani        
# domenico.luciani@email.it
#  
# 
# This file may be licensed under the terms of of the
# GNU General Public License Version 2 (the ``GPL'').
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

typedef struct
{   
    int H,S,V;
}HSV;

typedef struct
{   
    int xmin,xmax;
    int ymin,ymax;
}Rettangolo;

void leggiConfig(HSV *m,HSV *n,char *file)
{
    FILE *config;
    config = fopen(file,"r");
    if(config != NULL)
        fscanf(config,"%d,%d,%d,%d,%d,%d",&m->H,&m->S,&m->V,&n->H,&n->S,&n->V);
    else
    {
        m->H = m->S = m->V = 0;
        n->H = n->S = n->V = 255;
    }

    printf("--- VALORI PRESI ---\n## MIN ##\nH->%d S->%d V->%d\n## MAX ##\nH->%d S->%d V->%d\n",m->H,m->S,m->V,n->H,n->S,n->V);
    fclose(config);
}

void scriviConfig(HSV *m,HSV *n,char *file)
{
    FILE *config;
    config = fopen(file,"w");
    if(config != NULL)
    {
        fprintf(config,"%d,%d,%d,%d,%d,%d",m->H,m->S,m->V,n->H,n->S,n->V);
        puts("Valori scritti correttamente");
    }
    fclose(config);
}

IplImage* diminuisci(IplImage* file,int perc)
{   
    IplImage *ris = cvCreateImage(cvSize((int)((file->width*perc)/100),(int)((file->height*perc)/100)),8,file->nChannels);

    cvResize(file,ris);

    return ris;
}

void riduciNoise(IplImage *src,IplImage *dst)
{   
    IplImage *buff = cvCreateImage(cvGetSize(src),8,dst->nChannels);
    cvDilate(src,buff,NULL,1);
    cvErode(buff,buff,NULL,2);
    cvSmooth(buff,dst,CV_GAUSSIAN,5);
    cvReleaseImage(&buff);
}

void inserisci(IplImage *small,IplImage *big,int pos1,int pos2)
{   
    CvRect dim = cvRect(pos1,pos2,(int)small->width,(int)small->height);
    cvSetImageROI(big,dim);
    cvCopy(small,big);
    cvResetImageROI(big);
}

