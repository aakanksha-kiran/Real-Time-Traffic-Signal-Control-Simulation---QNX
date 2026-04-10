#include <stdio.h>      // for printf, scanf
#include <unistd.h>     // for sleep()
#include <string.h>     // for string functions
#include <pthread.h>    // for threads

int run = 1, mode = 0, change = 0; // run=program control, mode=operation type, change=restart flag

pthread_mutex_t lock; // mutex for safe printing (avoid mixed output)

// WATCHDOG VARIABLES
int heartbeat = 0;     // shows system is alive (1=active, 0=inactive)
pthread_t wd;          // watchdog thread

// 2 road variables
int e2=0,d2=0;        // e2=emergency, d2=density
char p2='N';          // priority road (A/B)

// 3 road variables
int e3=0,d3=0;        // e3=emergency, d3=density
char p3='N';          // priority road (1/2/3)

pthread_t t1,t2;      // thread handles

// function to display commands
void show(){
    printf("\n--------------------------------\n"); // heading
    printf("\nCOMMAND LIST\n"); // title
    printf("c1 → Only 2-Road\nc2 → Only 3-Road\nc3 → Both\n"); // modes

    printf("\n2-ROAD:\n"); // 2-road options
    printf("eA eB → Emergency\n"); // emergency commands
    printf("dA dB → Density\n");   // density commands
    printf("n2     → Normal\n");   // reset

    printf("\n3-ROAD:\n"); // 3-road options
    printf("e1 e2 e3 → Emergency\n");
    printf("d1 d2 d3 → Density\n");
    printf("n3       → Normal\n");

    printf("\nq → Quit\n"); // quit option
    printf("--------------------------------\n\n"); // footer
}

// WATCHDOG FUNCTION
void* watchdog(void* arg){  // watchdog thread function
    while(run){  // run till program active
        sleep(3); // wait 3 seconds

        if(heartbeat == 0){  // if no activity detected
            pthread_mutex_lock(&lock); // lock before printing
            printf("\n WATCHDOG: System not responding!\n"); // warning
            pthread_mutex_unlock(&lock); // unlock after printing
        }

        heartbeat = 0; // reset for next check
    }
    return NULL; // end thread
}

// 2-road thread
void* r2(void* a){
    while(run && (mode==1 || mode==3)){ // run only in mode 1 or 3

        heartbeat = 1; // signal system is alive

        if(change) pthread_exit(NULL); // exit if mode changes

        if(e2){ // emergency mode
            pthread_mutex_lock(&lock);
            printf("\n[2-ROAD][EMERGENCY] A:%s B:%s\n",
                   (p2=='A')?"GREEN":"RED",
                   (p2=='B')?"GREEN":"RED");
            pthread_mutex_unlock(&lock);
            sleep(1); continue; // repeat
        }

        if(d2){ // density mode
            pthread_mutex_lock(&lock);
            printf("\n[2-ROAD][DENSITY] A:%s B:%s\n",
                   (p2=='A')?"GREEN":"RED",
                   (p2=='B')?"GREEN":"RED");
            pthread_mutex_unlock(&lock);
            sleep(1); continue;
        }

        // normal signal flow

        for(int i=0;i<5 && run;i++){ // green A
            if(e2||d2||change) break; // break if mode changes
            heartbeat = 1; // alive signal
            pthread_mutex_lock(&lock);
            printf("\n[2-ROAD] A:GREEN B:RED\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<2 && run;i++){ // yellow A
            if(e2||d2||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[2-ROAD] A:YELLOW B:RED\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<5 && run;i++){ // green B
            if(e2||d2||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[2-ROAD] A:RED B:GREEN\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<2 && run;i++){ // yellow B
            if(e2||d2||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[2-ROAD] A:RED B:YELLOW\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
    return NULL; // end thread
}

// 3-road thread
void* r3(void* a){
    while(run && (mode==2 || mode==3)){ // run only in mode 2 or 3

        heartbeat = 1; // alive signal

        if(change) pthread_exit(NULL); // exit if mode changes

        if(e3){ // emergency
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD][EMERGENCY] R1:%s R2:%s R3:%s\n",
                   (p3=='1')?"GREEN":"RED",
                   (p3=='2')?"GREEN":"RED",
                   (p3=='3')?"GREEN":"RED");
            pthread_mutex_unlock(&lock);
            sleep(1); continue;
        }

        if(d3){ // density
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD][DENSITY] R1:%s R2:%s R3:%s\n",
                   (p3=='1')?"GREEN":"RED",
                   (p3=='2')?"GREEN":"RED",
                   (p3=='3')?"GREEN":"RED");
            pthread_mutex_unlock(&lock);
            sleep(1); continue;
        }

        // normal signals

        for(int i=0;i<5 && run;i++){ // R1 green
            if(e3||d3||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD] R1:GREEN R2:RED R3:RED\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<2 && run;i++){ // R1 yellow
            if(e3||d3||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD] R1:YELLOW R2:RED R3:RED\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<5 && run;i++){ // R2 green
            if(e3||d3||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD] R1:RED R2:GREEN R3:RED\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<2 && run;i++){ // R2 yellow
            if(e3||d3||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD] R1:RED R2:YELLOW R3:RED\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<5 && run;i++){ // R3 green
            if(e3||d3||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD] R1:RED R2:RED R3:GREEN\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        for(int i=0;i<2 && run;i++){ // R3 yellow
            if(e3||d3||change) break;
            heartbeat = 1;
            pthread_mutex_lock(&lock);
            printf("\n[3-ROAD] R1:RED R2:RED R3:YELLOW\n");
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
    return NULL;
}


// function to start threads
void start(){
    change = 0; // reset change flag

    if(mode==1)
        pthread_create(&t1,NULL,r2,NULL); // start 2-road
    else if(mode==2)
        pthread_create(&t2,NULL,r3,NULL); // start 3-road
    else{
        pthread_create(&t1,NULL,r2,NULL); // start both
        pthread_create(&t2,NULL,r3,NULL);
    }
}


int main(){

    char input[100]; // input buffer

    pthread_mutex_init(&lock,NULL); // initialize mutex

    printf("Press s to start:\n"); // start prompt
    scanf("%s",input); // read input
    getchar(); // clear buffer

    if(input[0]!='s') return 0; // exit if not 's'

    show(); // display commands

    while(mode==0){ // select mode
        printf("Select mode (c1/c2/c3): ");
        fgets(input,100,stdin);

        if(strncmp(input,"c1",2)==0) mode=1;
        else if(strncmp(input,"c2",2)==0) mode=2;
        else if(strncmp(input,"c3",2)==0) mode=3;
    }

    start(); // start traffic threads

    pthread_create(&wd, NULL, watchdog, NULL); // start watchdog automatically

    while(run){ // main loop

        fgets(input,100,stdin); // read input
        char *cmd = strtok(input," \n"); // token size

        while(cmd!=NULL){

            if(strcmp(cmd,"q")==0) run=0; // quit

            else if(strcmp(cmd,"c1")==0 || strcmp(cmd,"c2")==0 || strcmp(cmd,"c3")==0){

                change = 1; // trigger restart

                pthread_cancel(t1); // stop threads
                pthread_cancel(t2);

                if(strcmp(cmd,"c1")==0) mode=1;
                else if(strcmp(cmd,"c2")==0) mode=2;
                else mode=3;

                start(); // restart threads
            }

            else if(strcmp(cmd,"eA")==0 || strcmp(cmd,"eB")==0){
                e2=1; d2=0; p2=cmd[1]; // set emergency
            }
            else if(strcmp(cmd,"dA")==0 || strcmp(cmd,"dB")==0){
                d2=1; e2=0; p2=cmd[1]; // set density
            }
            else if(strcmp(cmd,"n2")==0){
                e2=d2=0; // reset
            }

            else if(strcmp(cmd,"e1")==0 || strcmp(cmd,"e2")==0 || strcmp(cmd,"e3")==0){
                e3=1; d3=0; p3=cmd[1]; // 3-road emergency
            }
            else if(strcmp(cmd,"d1")==0 || strcmp(cmd,"d2")==0 || strcmp(cmd,"d3")==0){
                d3=1; e3=0; p3=cmd[1]; // 3-road density
            }
            else if(strcmp(cmd,"n3")==0){
                e3=d3=0; // reset
            }

            cmd = strtok(NULL," \n"); // next command
        }
    }
    printf("Simulation Ended\n"); // end message
    return 0; // exit program
}
