/*
 * alarm.c
 *
 *  Created on: Dec 1, 2021
 *      Author: Ella Knott, Lal Siama, Zoe Davis, Ella Godfrey
 */

#include <stdio.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"
#include "alarm.h"

/*
*needs:
* OI_OPCODE_PLAY
* OI_OPCODE_SONG
* self->songNumber = packet[41]
* self->songPlaying = packet[42]
* oi_loadSong(int song_index, int num_notes, unsigned char &notes, unsigned char *duration)
* oi_play_song(int index)
*/
int song_index = 0;
int num_notes = 4;


//unsigned char notes; //&num_notes
//unsigned char duration; //*duration



 //(int song_index, int num_notes, unsigned char &notes, unsigned char *duration);
 //song index = 0, num_notes = 3, &notes = 64, *duration =
 //oi_play_song(int index)

 void load_Song(int song_number){
     //INTRUDER SONG
     if (song_number == 2)
     {
         song_index = 0;
         num_notes = 16;
         unsigned char noise[] = {74, 74, 78, 74, 76, 72, 74, 128, 128, 74, 74, 74, 74, 72, 76, 74};
         unsigned char alarmlength[] = { 8,  8, 16, 16, 16, 16, 32,  16,  16,  8,  8,  8,  8, 16, 16, 32};

         oi_loadSong(song_index, num_notes, noise, alarmlength);
     }
     //BASE SONG
     if (song_number == 1)
     {
         song_index = 1;
         num_notes = 20;
         unsigned char noise1[] = {69, 74, 69, 74, 69, 74, 69, 128, 68, 69, 69, 68, 69, 67, 128, 66, 67, 66, 65, 62, 61};
         unsigned char alarmlength1[] = {16, 16, 16, 16,  8, 16,  8,   8,  8, 16,  8,  8,  8,  8,   8,  8,  8,  8, 32,  8, 64};

         oi_loadSong(song_index, num_notes, noise1, alarmlength1);
     }

           //  unsigned char noise[] = {69, 74, 69, 74, 69, 74, 69, 68, 69, 69, 68, 69, 67, 128, 66, 67, 66, 65, 62};
            // unsigned char alarmlength[] = {4, 4, 4, 4, 4, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 2, 4};
       //oi_loadSong(song_index, num_notes, &noise, *alarmlength);
   }

 void soundalarm(int song_index){

        oi_play_song(song_index);

 }
