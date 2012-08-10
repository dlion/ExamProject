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

#include "funzioni.c"

/*
 * -Funzione per leggere il file di configurazione-
 * I primi 2 parametri indicano dove salvare i valori presi.
 * I valori presi vengono salvato su 2 strutture apposite.
 * Il terzo parametro è il nome del file da cui leggere.
 */
void leggiConfig(HSV*,HSV*,char*);

/*
 * -Funzione per scrivere sul file di configurazione-
 * Stessi parametri di prima.
 */
void scriviConfig(HSV*,HSV*,char*);

/*
 * -Funzione per diminuire la dimensione di un'immagine-
 *  Il primo parametro indica l'immagine.
 *  Il secondo parametro è il valore in percentuale di riduzione.
 *  Viene ritornata l'immagine modificata.
 */
IplImage* diminuisci(IplImage*,int);

/*
 * -Funzione per ridurre i disturbi in un'immagine-
 *  Il primo parametro indica l'immagine sorgente.
 *  Il secondo parametro indica l'immagine di destinazione.
 */
void riduciNoise(IplImage*,IplImage*);

/*
 * -Funzione per inserire un'immagine in un'altra immagine-
 *  Il primo parametro indica l'immagine da inserire.
 *  Il secondo parametro indica dove inserire l'immagine.
 *  Il terzo e il quarto parametro indicano le coordinate dove posizionare l'immagine.
 */
void inserisci(IplImage*,IplImage*,int,int);

