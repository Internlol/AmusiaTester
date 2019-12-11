#include "mbed.h"
#include "stdio.h"      
#include "stdlib.h"     


#define VOLUME 0.5
#define BPM 170.0
#define Ch 1046.502
#define Bh 987.7666
#define Ah 880.0000
#define Gh 783.9909
#define Fsh 739.9888
#define E 659.2551
#define D 587.3295
#define C 523.2511
#define B 493.8833
#define A 440.0000
#define G 391.9954
#define Fs 369.9944


DigitalIn button_1(p11);
DigitalIn button_2(p12);

DigitalOut myled(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);


PwmOut speaker(p21);
PwmOut speaker2(p22);
PwmOut myledR(p23);
PwmOut myledB(p24);
PwmOut myledG(p25);

 
void loser() {
    // loser noise made by alternating between 2 frequencies.
    for (int i = 0; i < 26; i = i + 2) {
        speaker.period(1.0/969.0);
        speaker2.period(1.0/969.0);
        speaker = float(i)/50.0;
        speaker2 = float(i)/50.0;
        myledR = 1.0;
        myledB = 0.0;
        wait(.5);
        speaker.period(1.0/800.0);
        speaker2.period(1.0/800.0);
        myledR = 0.0;
        myledB = 1.0;
        wait(.5);
    }
    // decrease volume
    for (int i = 25; i >= 0; i = i - 2) {
        speaker.period(1.0/969.0);
        speaker2.period(1.0/969.0);
        speaker = float(i)/50.0;
        speaker2 = float(i)/50.0;
        myledR = 1.0;
        myledB = 0.0;
        wait(.5);
        speaker.period(1.0/800.0);
        speaker2.period(1.0/800.0);
        myledR = 0.0;
        myledB = 1.0;
        wait(.5);
    }
    myledR = 0.0;
    myledB = 0.0;
    speaker = 0.0;
    wait(2);
 }
 
void winner() {
    // winner noise
    for (int i = 0; i < 4000; i = i + 100) {
        speaker.period(1.0/float(i));
        speaker2.period(1.0/float(i));
        speaker = 0.5;
        speaker2 = 0.5;
        myledG = 1.0;
        myled = 1.0;
        myled2 = 1.0;
        myled3 = 1.0;
        myled4 = 1.0;
        wait(.1);
        myledG = 0.0;
        myled = 0.0;
        myled2 = 0.0;
        myled3 = 0.0;
        myled4 = 0.0;
    }
    for (int i = 4000; i > 0; i = i - 100) {
        speaker.period(1.0/float(i));
        speaker2.period(1.0/float(i));
        speaker = 0.5;
        speaker2 = 0.5;
        myledG = 1.0;
        myled = 1.0;
        myled2 = 1.0;
        myled3 = 1.0;
        myled4 = 1.0;
        wait(.1);
        myledG = 0.0;
        myled = 0.0;
        myled2 = 0.0;
        myled3 = 0.0;
        myled4 = 0.0;
    }
    myledR = 0.0;
    myledB = 0.0;
    speaker = 0.0;
    speaker2 = 0.0;
    wait(2);
 } 
 
void end(bool win) {
    if (win) {
        printf("Round passed!\n\r");
        winner();
    }
    else {
        printf("You lost.\n\r");
        loser();
    }    
}

void playFreq(float freq, float duration, float volume) {
    speaker.period(1.0/freq); // plays note, 2 speakers to make it louder
    speaker2.period(1.0/freq);
    speaker = volume;
    speaker2 = volume;
    wait(duration);
    speaker = 0.0;
    speaker2 = 0.0;
}


void playOffice() {
    float beat_duration;
    // Notes taken from https://musescore.com/user/15146/scores/40133,
    // which I read and translated into frequecies.
    beat_duration = 60.0 / BPM;
    while(1) {
        
        //// LINE 1
        for (int i = 0; i < 3; i++) {
            playFreq(D, (beat_duration - 0.1), VOLUME);
            playFreq(G, (beat_duration - 0.1), VOLUME);
            playFreq(D, 4*(beat_duration - 0.1), VOLUME);
            playFreq(D, (beat_duration - 0.1), VOLUME);
            playFreq(G, (beat_duration - 0.1), VOLUME);
            
            playFreq(D, (beat_duration - 0.1), VOLUME);
            playFreq(Fs, (beat_duration - 0.1), VOLUME);
            playFreq(D, 4*(beat_duration - 0.1), VOLUME);
            playFreq(D, (beat_duration - 0.1), VOLUME);
            playFreq(Fs, (beat_duration - 0.1), VOLUME);
            
            playFreq(E, (beat_duration - 0.1), VOLUME);
            playFreq(G, (beat_duration - 0.1), VOLUME);
            playFreq(E, 4*(beat_duration - 0.1), VOLUME);
            playFreq(E, (beat_duration - 0.1), VOLUME);
            playFreq(G, (beat_duration - 0.1), VOLUME);
            
            
            playFreq(E, 2*(beat_duration - 0.1), VOLUME);
            playFreq(E, 2*(beat_duration - 0.1), VOLUME);
            playFreq(E, (beat_duration - 0.1), VOLUME);
            playFreq(B, (beat_duration - 0.1), VOLUME);
            playFreq(A, (beat_duration - 0.1), VOLUME);
            playFreq(B, (beat_duration - 0.1), VOLUME);
        }
        
        ////////////////////////// LINE 2
        
        playFreq(G, 4*(beat_duration - 0.1), VOLUME);
        playFreq(E, 4*(beat_duration - 0.1), VOLUME);
        
        wait(4*(beat_duration - 0.1));
        playFreq(Fsh, (beat_duration - 0.1), VOLUME);
        playFreq(Gh, (beat_duration - 0.1), VOLUME);
        playFreq(Fsh, (beat_duration - 0.1), VOLUME);
        playFreq(D, (beat_duration - 0.1), VOLUME);
        
        playFreq(E, 4*(beat_duration - 0.1), VOLUME);
        playFreq(E, 2*(beat_duration - 0.1), VOLUME);
        playFreq(E, 2*(beat_duration - 0.1), VOLUME);
        
        playFreq(C, 2*(beat_duration - 0.1), VOLUME);
        playFreq(C, 2*(beat_duration - 0.1), VOLUME);
        playFreq(C, (beat_duration - 0.1), VOLUME);
        playFreq(B, (beat_duration - 0.1), VOLUME);
        playFreq(A, (beat_duration - 0.1), VOLUME);
        playFreq(B, (beat_duration - 0.1), VOLUME);
        
        
        ///////////////// LINE 3
        
        playFreq(G, 4*(beat_duration - 0.1), VOLUME);
        playFreq(Gh, 4*(beat_duration - 0.1), VOLUME);
        
        wait(4*(beat_duration - 0.1));
        playFreq(Fsh, (beat_duration - 0.1), VOLUME);
        playFreq(Gh, (beat_duration - 0.1), VOLUME);
        playFreq(Ah, (beat_duration - 0.1), VOLUME);
        playFreq(Fsh, (beat_duration - 0.1), VOLUME);
        
        playFreq(E, 4*(beat_duration - 0.1), VOLUME);
        playFreq(E, 2*(beat_duration - 0.1), VOLUME);
        playFreq(E, 2*(beat_duration - 0.1), VOLUME);
        
        playFreq(C, 2*(beat_duration - 0.1), VOLUME);
        playFreq(C, 2*(beat_duration - 0.1), VOLUME);
        playFreq(C, (beat_duration - 0.1), VOLUME);
        playFreq(B, (beat_duration - 0.1), VOLUME);
        playFreq(A, (beat_duration - 0.1), VOLUME);
        playFreq(B, (beat_duration - 0.1), VOLUME);
        
        
    }
}
    
int main() {
        myledR = 0;
        myledB = 0;
        myledG = 0;
        bool win = false;
        bool win2 = false;
        bool win3 = false;
        // round 1
        printf("How many beeps are there? Press as many times as you hear it on the right button, and confirm with the left button.\n\r");
        printf("Press any button to start.\n\r");
        int seed = 0;
        while (1) {
                if (button_1 || button_2) {
                        printf("Playing Beeps.\n\r");
                        wait(1);
                        break;
                    }
                seed = seed + 1;
                wait(0.1);
                if (seed > 1000) { //use clock for randomness, timer does not work on LPC1768
                        seed = 0;
                    }
            }
        int beeps = seed % 10 + 1;
        for (int i = 0; i < beeps; i++) {
                playFreq(Fsh, 60.0/BPM, VOLUME);
                wait(0.2);
            }
        int answer = 0;
        printf("How many beeps were there?\n\r");
        while (1) {
            if (button_1) {
                    answer = answer + 1;
                    if (answer > 10) {
                            answer = 1;
                        }
                    printf("%d beeps.\n\r", answer);
                }
            else if (button_2) {
                    if (answer == beeps) {
                            win = true;
                        }
                    printf("There were %d beeps. You answered %d beeps.\n\r", beeps, answer);
                    end(win);
                    break;
                }
            wait(0.25);
            }
            
            
            
        // proceed to round 2
        if (win) {
                int fseed = seed;
                printf("A comparison of two beeps. Which is higher? The first beep or the second beep?\n\r");
                printf("Press any button to hear the beeps.\n\r");
                while (1) {
                    if (button_1 || button_2) {
                        printf("Playing Beeps.\n\r");
                        wait(1);
                        break;
                    }
                    seed = seed + 1;
                    wait(0.1);
                    if (seed > 1000) {
                            seed = 0;
                        }
                }
                wait(1);
                playFreq(fseed, 2, VOLUME);
                wait(1);
                playFreq(seed, 2, VOLUME);
                printf("Press the left button if you think the first beep was higher. Press the right one if you think the second was higher.\n\r");
                while (1) {
                    if (button_2) {
                        if (fseed > seed) {
                                win2 = true;
                                printf("Correct! The first was higher. %dHz vs %dHz.\n\r", fseed, seed);
                            }
                        else {
                               printf("Nope. The second was higher. %dHz vs %dHz.\n\r", fseed, seed); 
                            }
                        break;
                    }
                    else if (button_1) {
                        if (seed > fseed) {
                                win2 = true;
                                printf("Correct! The second was higher. %dHz vs %dHz.\n\r", fseed, seed);
                            }
                        else {
                               printf("Nope. The first was higher. %dHz vs %dHz.\n\r", fseed, seed); 
                            }
                        break;
                    }
                    wait(0.1);
                }
                end(win2);
                
            }
            
            // Round 3
            if (win && win2) {
                    wait(1);
                    printf("Listen to the frequency and try to choose what note that corresponds to in a different octave. It will play twice.\n\r");
                    printf("Press any button to hear the beeps.\n\r");
                    while (1) {
                        if (button_1 || button_2) {
                            printf("Playing Beeps.\n\r");
                            wait(1);
                            break;
                        }
                        wait(0.1);
                    }
                    int let = seed % 4 + 1;
                    float freq = G;
                    char freqChar = 'G';
                    if (let == 1) {
                            freq = A;
                            freqChar = 'A';
                        }
                    else if (let == 2) {
                            freq = B;
                            freqChar = 'B';
                        }
                    else if (let == 3) {
                            freq = C;
                            freqChar = 'C';
                        }
                    playFreq(freq, 2, VOLUME);
                    wait(1);
                    playFreq(freq, 2, VOLUME);
                    printf("What note is it? Scroll through answers with the right button and confirm with the left button.\n\r");
                    printf("Answers are: G, A, B, C (The note will play when you select it)\n\r");
                    char letter = 'G';
                    answer = 0;
                    float ansFreq = G;
                    while (1) {
                            if (button_1) {
                                    answer = answer + 1;
                                    if (answer > 4) answer = 1;
                                    if (answer == 1) {
                                            letter = 'G';
                                            playFreq(Gh, 1, VOLUME);
                                            ansFreq = G;
                                        }
                                    else if (answer == 2) {
                                            letter = 'A';
                                            playFreq(Ah, 1, VOLUME);
                                            ansFreq = A;
                                        }
                                    else if (answer == 3) {
                                            letter = 'B';
                                            playFreq(Bh, 1, VOLUME);
                                            ansFreq = B;
                                        }
                                    else if (answer == 4) {
                                            letter = 'C';
                                            playFreq(Ch, 1, VOLUME);
                                            ansFreq = C;
                                        }
                                    printf("Your selection: %c\n\r", letter);
                                }
                            else if (button_2) {
                                    if (ansFreq == freq) {
                                            win3 = true;
                                        }
                                    printf("The answer was %c. You answered %c.\n\r", freqChar, letter);
                                    end(win3);
                                    break;
                                }
                            wait(0.25);
                        }
                        
            if (win && win2 && win3) { // fun reward at the end, makes it feel like the game was used to unlock this
                    wait(2);
                    for (int i = 0; i < 20; i++) {
                            printf("\n\r");
                        }
                    playOffice();
                }
            
            }
            
    
        
 
}