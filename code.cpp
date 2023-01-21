#include <iostream>
#include <getopt.h>
#include <cstring>
#include <signal.h>
#include <fstream>

using namespace std;

struct queuePoint* sortProcNumCircular(queuePoint* header);
struct node* sortAraival(node* header);
struct node* sortPriority(node* header); 
struct node* sortBurst(node *header);
struct queuePoint* sortAraivalCircular(queuePoint* header);
void getOption(char* File,char* outF);
void fcfs(char *File);
void sjfcNonPremp(char *File);
void sjsfPremp(char *File);
struct node* getMinRemNode(node* header, int clock);
void prioritySchedulingNonPremp(char *File);
void prioritySchedulingPremp(char *File);
struct node* getMinPriorityNode(node* header, int clock);
void roundRobin(char* File);
struct node *newNode(char *b,char *a,char *p);
struct queuePoint *insertCirculer( queuePoint *header,char *b,char *a,char *p);
struct node *insertLinerBack( node *header,char *b,char *a,char *p);
void displayCirculer(struct queuePoint *header);
void displayLiner(struct node *header);

struct node{
    char *b;
    char *a;
    char *p;
    bool isDone = false;
    int pocCT;
    int procRemTime;
    int pocTAT;
    int pocWT;
    int procNum;
    struct node *next;
    struct node *pre;
};
struct queuePoint{
  node *front,*rear;  
};

int main(int argc,char *argv[]){
    int opt;
    while((opt =getopt(argc,argv,"fo:")) != -1)
    {
        switch(opt){
            case'f':
                
                break;
            case'o':
                
                break;
            default:
                fprintf(stderr,"Usage: %s [-f input.txt] [-o output.txt ] \n",argv[0]);
                exit(EXIT_FAILURE);
        }
    }
   if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }
    FILE *readFile;
    readFile = fopen(argv[4],"r"); //open -read
    
    if(readFile == NULL){ //if not exist
        printf("\n***************ERROR***************\n|.....%s File Dose Not Exist....|\n",argv[4]); 
    }else{
        getOption(argv[4],argv[3]);
    } 
   exit(EXIT_SUCCESS);
}
int isPreemptive = 0;
string scheduling ="None";
string endMsg = "";


void getOption(char* File,char* outF){
    bool cont = true;
    while(cont){

    char *temp = File; 
    char *out = outF;
    int quantumTime;
    cout<<"\n\n**********CPU Scheduler Simulator**********\n";
        cout<<"1) Scheduling Method("<<scheduling<<")\n";
        if(isPreemptive == 0){
            cout<<"2) Preemptive Mode (Off)\n";
        }else{
            cout<<"2) Preemptive Mode (On)\n";
        }
        cout<<"3) Show Result\n";
        cout<<"4) End Program\n";
        cout<<"Option> ";
        int option,option2;
        cin>>option;
        if(option == 1){
            cout<<"\n-----Scheduling Method(None)-----\n";
            cout<<"1) First Come, First Served Scheduling\n";
            cout<<"2) Shortest-Job-First Scheduling\n";
            cout<<"3) Priority Scheduling\n";
            cout<<"4) Round-Robin Scheduling\n";
            cout<<"Option> ";
            cin>>option2;
            switch(option2){
                case 1:{
                    scheduling = "First Come, First Served";
                    
                }break;
                case 2 :{
                    scheduling = "Shortest-Job-First";
                }break;
                case 3 :{
                    scheduling = "Priority";
                }break;
                case 4 :{
                    scheduling = "Round-Robin";

                }break;
                default:
                    cout<<"\n\n*******************ERROR: Unknown Input*******************\n\n";
                    exit(-1);
            }
         
        }else if(option == 2){
            if(isPreemptive == 0){
                isPreemptive = 1;
            }else{
                isPreemptive = 0;
            }
        }else if(option == 3){
             if(scheduling == "First Come, First Served"){
                    if(isPreemptive == 0){
                        fcfs(temp);
                    }else{
                     string YN;
                       cout<<"\n***Warning***\nFirst Come, First Served CANNOT run in Preemptive mode..\n";
                        cout<<"Iam aware...continue...(Y/N)> ";
                        cin>>YN;
                        if((YN == "Y")||(YN == "y")){
                            fcfs(temp);
                        }else{getOption(temp,out);}
                }
                
            }else if(scheduling == "Shortest-Job-First"){
                if(isPreemptive == 0){
                   sjfcNonPremp(temp);
                }else{
                   sjsfPremp(temp);
                }
            }else if(scheduling == "Priority"){
                if(isPreemptive == 0){
                    prioritySchedulingNonPremp(temp);
                }else{
                    prioritySchedulingPremp(temp);
                }
            }else if(scheduling == "Round-Robin"){
                    if(isPreemptive == 1){
                    roundRobin(temp);
                    }else{
                     string YN;
                        cout<<"Iam aware...continue...(Y/N)> ";
                        cin>>YN;
                        if((YN == "Y")||(YN == "y")){
                            roundRobin(temp);
                        }
                }
                
            }
        }else if(option == 4){
            cout << endMsg;
            std::ofstream outputFile(out);
            if (outputFile.is_open()) {
            outputFile << endMsg;
            outputFile.close();
            cont = false;
            }

        }else{
            cout<<"\n\n*******************ERROR: Unknown Input*******************\n\n";
            exit(-1);
            
        }
        
}  
}
int procCounter1 = 1; 
int procCounter2 = 1; 
void fcfs(char *File){                 

    char *inputFile = File;
    FILE *readFile;
    char Burst_Time[10];
    char Araivel_Time[10];
    char Priority[10];
    
    readFile = fopen(inputFile,"r");
    node* header = NULL;
    int count = 0;
    int procWTime = 0;
    string outputMsg = "";
    int totalBurst = 0;
    while(fscanf(readFile,"%s : %s : %s",Burst_Time,Araivel_Time,Priority) != -1){ //not file end
        header = insertLinerBack(header,Burst_Time,Araivel_Time,Priority);
        }
    fclose(readFile); 
    header = sortAraival(header);
    do{
            outputMsg+= "\nP"+to_string(header->procNum) + ": " + to_string(procWTime)+"\n";
            procWTime += *header->b -48;
            count +=1;
            header = header->next;
            if(header!=NULL)
                totalBurst = totalBurst+procWTime;
    }
    while(header !=NULL);
            
        
        float avgTime = (float)totalBurst / (float)count;
        string fcfsMsg = "";
    fcfsMsg+="\n---------Scheduling Method: First Come Fist Served---------\n******************  Process Waiting Times  ******************";
    fcfsMsg+="\n____________________________________________________________________\n";
    fcfsMsg+= outputMsg;
    fcfsMsg += "\nAverage Waiting Time: "+ to_string(avgTime) +" ms";
    fcfsMsg+="\n____________________________________________________________________";
    cout<<fcfsMsg;
    
        
    endMsg += "\n" + fcfsMsg + "\n";
    procCounter1 = 1;
    procCounter2 = 1;
    node* temp = header;
    while (header!=NULL){
        temp = temp->next;
        delete header;
        header = temp;
    }
    totalBurst = 0;
    return;
}

void sjfcNonPremp(char *File) {       
    char *inputFile = File;
    FILE *readFile;
    char Burst_Time[10];
    char Araivel_Time[10];
    char Priority[10];
    
    readFile = fopen(inputFile,"r");
    node* header = NULL;
    
    int clock = 0;
    int count = 0;
    int procWTime = 0;
    string outputMsg = "";
    int totalBurst = 0;
    
    while(fscanf(readFile,"%s : %s : %s",Burst_Time,Araivel_Time,Priority) != -1){ //not file end
        header = insertLinerBack(header,Burst_Time,Araivel_Time,Priority);
        }
    fclose(readFile); 
    header = sortBurst(header);
    
    int procCount = 0;
    node *tempH = header;
    do{
        procCount++;
        tempH = tempH->next;
    }while (tempH!=NULL);
    
    node* current = header;
    while (current != NULL) {
        
        if ((*current->a - 48) <= clock && current->isDone == false) { 
            outputMsg += "\nP" + to_string(current->procNum) + ": " + to_string(procWTime) + "\n";
            procWTime += *current->b - 48;
            clock += *current->b - 48;
            count++;
            current->isDone = true;
            if(count != procCount){
            totalBurst = totalBurst + procWTime;
            }
            current = header;
        }
        else {
            current = current->next;
            
        }
    }
    
    float avgTime = (float)totalBurst / (float)count;
    string sjfsMsg = "";
        sjfsMsg += "\n---------Scheduling Method: Shortest Job First – Non-Preemptive---------\n******************  Process Waiting Times  ******************";
        sjfsMsg += "\n____________________________________________________________________\n";
        sjfsMsg+= outputMsg;
    sjfsMsg += "\nAverage Waiting Time: "+ to_string(avgTime) +" ms";
    sjfsMsg+="\n____________________________________________________________________";
    cout<<sjfsMsg;
        
    endMsg += "\n" + sjfsMsg + "\n";
    procCounter1 = 1;
    procCounter2 = 1;
    node* temp = header;
    while (header!=NULL){
        temp = temp->next;
        header->isDone = false;
        delete header;
        header = temp;
    }
    totalBurst = 0;
    return;
}

void sjsfPremp(char *File){
    char *inputFile = File;
    FILE *readFile;
    char Burst_Time[10];
    char Araivel_Time[10];
    char Priority[10];
    
    readFile = fopen(inputFile,"r");
    node* header = NULL;
    int procCount = 0; 
    string outputMsg = "";
    int totalBurst = 0;
    while(fscanf(readFile,"%s : %s : %s",Burst_Time,Araivel_Time,Priority) != -1){ //not file end
        header = insertLinerBack(header,Burst_Time,Araivel_Time,Priority);
        procCount++;
    }
    fclose(readFile); 
    header = sortAraival(header);
    
    node *tempH = header;
    do{
        tempH->procRemTime = *tempH->b-48; //remaining time = Burst
        tempH = tempH->next;
    }while (tempH!=NULL);
    
    int clock = 0;
    int finished = 0;
    node *current = header;
    while (finished != procCount) {
        current = getMinRemNode(header,clock);
//        cout<<"P"<<current->procNum<<" : "<<current->procRemTime<<endl;
        current->procRemTime -=1;
        clock+=1;
        if(current->procRemTime == 0){
            int originalBurst = *current->b-48;
            int procAT = *current->a-48;
            current->pocCT = clock;
            current->pocTAT = current->pocCT - procAT;
            current->pocWT = current->pocTAT- originalBurst;
            current->isDone = true;
            outputMsg+= "\nP"+to_string(current->procNum) + ": " + to_string(current->pocWT)+" ms\n";
            finished +=1;
        }
    }
    node *temp2 = header;
    while(temp2 != NULL){
        totalBurst += temp2->pocWT;
        temp2 = temp2->next;
    }
    
    float avgTime = (float)totalBurst / (float)procCount;
        string srjfMsg = "";
    srjfMsg+="\n---------Scheduling Method: Shortest Job First -Preemptive---------\n******************  Process Waiting Times  ******************";
    srjfMsg+="\n____________________________________________________________________\n";
    srjfMsg+= outputMsg;
    srjfMsg += "\nAverage Waiting Time: "+ to_string(avgTime) +" ms";
    srjfMsg+="\n____________________________________________________________________";
    cout<<srjfMsg;
    
        
    endMsg += "\n" + srjfMsg + "\n";
    procCounter1 = 1;
    procCounter2 = 1;
    node* temp = header;
    while (header!=NULL){
        temp = temp->next;
        delete header;
        header = temp;
    }
    totalBurst = 0;
    return;
}

node* getMinRemNode(node* header, int clock){
    int min_remaining = 1000;
    node* min_node = NULL;
    node* current = header;
    while(current != NULL){
        if(current->isDone == false && (*current->a-48 <= clock) && (current->procRemTime < min_remaining)){
            min_remaining = current->procRemTime;
            min_node = current;
        }
        current = current->next;
    }
    return min_node;
}


void prioritySchedulingNonPremp(char *File){  
    char *inputFile = File;
    FILE *readFile;
    char Burst_Time[10];
    char Araivel_Time[10];
    char Priority[10];
    
    readFile = fopen(inputFile,"r");
    node* header = NULL;
    
    while(fscanf(readFile,"%s : %s : %s",Burst_Time,Araivel_Time,Priority) != -1){ //not file end
        header = insertLinerBack(header,Burst_Time,Araivel_Time,Priority);
        }
    fclose(readFile); 
    int procCount = 0;
    node *tempH = header;
    do{
        procCount++;
        tempH = tempH->next;
    }while (tempH!=NULL);
    header = sortPriority(header);
    int clock = 0;
    int procWTime = 0;
    string outputMsg = "";
    int totalBurst = 0;
    int count = 0;
    node* current = header;
    while (current != NULL) {
        
        if ((*current->a - 48) <= clock && current->isDone == false) { 
            outputMsg += "\nP" + to_string(current->procNum) + ": " + to_string(procWTime) + "\n";
            procWTime += *current->b - 48;
            clock += *current->b - 48;
            count++;
            current->isDone = true;
            
            if(count != procCount){
            totalBurst = totalBurst + procWTime;
            }
            current = header;
            header = sortPriority(header);
        }
        else {
            int tempLast = *current->b -48;
            current = current->next;
            if(current == NULL){
                totalBurst = totalBurst - tempLast;
            }
        }
    }
    float avgTime = (float)totalBurst / (float)count;
    string priorityNonPremp = "";
        priorityNonPremp += "\n---------Scheduling Method: Priority – Non-Preemptive---------\n******************  Process Waiting Times  ******************";
        priorityNonPremp += "\n____________________________________________________________________\n";
        priorityNonPremp+= outputMsg;
    priorityNonPremp += "\nAverage Waiting Time: "+ to_string(avgTime) +" ms";
    priorityNonPremp+="\n____________________________________________________________________";
    cout<<priorityNonPremp;
        
    endMsg += "\n" + priorityNonPremp + "\n";
    procCounter1 = 1;
    procCounter2 = 1;
    node* temp = header;
    totalBurst = 0;
    while (header!=NULL){
        temp = temp->next;
        header->isDone = false;
        delete header;
        header = temp;
    }
    totalBurst = 0;
    return;
}

void prioritySchedulingPremp(char *File){
    char *inputFile = File;
    FILE *readFile;
    char Burst_Time[10];
    char Araivel_Time[10];
    char Priority[10];
    
    readFile = fopen(inputFile,"r");
    node* header = NULL;
    int procCount = 0; 
    string outputMsg = "";
    int totalBurst = 0;
    while(fscanf(readFile,"%s : %s : %s",Burst_Time,Araivel_Time,Priority) != -1){ //not file end
        header = insertLinerBack(header,Burst_Time,Araivel_Time,Priority);
        procCount++;
    }
    fclose(readFile); 
    header = sortAraival(header);
    
    node *tempH = header;
    do{
        tempH->procRemTime = *tempH->b-48; //remaining time = Burst
        tempH = tempH->next;
    }while (tempH!=NULL);
    
    int clock = 0;
    int finished = 0;
    node *current = header;
    while (finished != procCount) {
        current = getMinPriorityNode(header,clock);
        current->procRemTime -=1;
        clock+=1;
        if(current->procRemTime == 0){
            int originalBurst = *current->b-48;
            int procAT = *current->a-48;
            current->pocCT = clock;
            current->pocTAT = current->pocCT - procAT;
            current->pocWT = current->pocTAT- originalBurst;
            current->isDone = true;
            outputMsg+= "\nP"+to_string(current->procNum) + ": " + to_string(current->pocWT)+" ms\n";
            finished +=1;
        }
    }
    
    node *temp2 = header;
    while(temp2 != NULL){
        totalBurst += temp2->pocWT;
        temp2 = temp2->next;
    }
    
    float avgTime = (float)totalBurst / (float)procCount;
        string priorityPremp = "";
    priorityPremp+="\n---------Scheduling Method: Priority -Preemptive---------\n******************  Process Waiting Times  ******************";
    priorityPremp+="\n____________________________________________________________________\n";
    priorityPremp+= outputMsg;
    priorityPremp += "\nAverage Waiting Time: "+ to_string(avgTime) +" ms";
    priorityPremp+="\n____________________________________________________________________";
    cout<<priorityPremp;
    
        
    endMsg += "\n" + priorityPremp + "\n";
    procCounter1 = 1;
    procCounter2 = 1;
    node* temp = header;
    while (header!=NULL){
        temp = temp->next;
        delete header;
        header = temp;
    }
    totalBurst = 0;
    return;
}

node* getMinPriorityNode(node* header, int clock){
    int min_Priority = 1000; 
    node* min_node = NULL;
    node* current = header;
    while(current != NULL){
        if(current->isDone == false && (*current->a-48 <= clock) && (*current->p-48 < min_Priority)){
            min_Priority = *current->p-48;
            min_node = current;
        }
        current = current->next;
    }
    return min_node;
}

void roundRobin(char* File){
    int quantum;
    cout<<"Enter Quantum Time: > ";
    cin>>quantum;
    char *inputFile = File;
    FILE *readFile;
    char Burst_Time[10];
    char Araivel_Time[10];
    char Priority[10];
    string outputMsg = "";
    int totalBurst = 0;
    int procCount = 0;
    int clock = 0;
    int finished = 0;
    queuePoint *pointers = new queuePoint;
    pointers->front = NULL;
    pointers->rear = NULL;
    
    readFile = fopen(inputFile,"r");
    
    while(fscanf(readFile,"%s : %s : %s",Burst_Time,Araivel_Time,Priority) != -1){ //not file end
        pointers = insertCirculer(pointers,Burst_Time,Araivel_Time,Priority);
        procCount++;
    }
    fclose(readFile);
    pointers = sortAraivalCircular(pointers);
    node *tempH = pointers->front;
    do{
        tempH->procRemTime = *tempH->b-48; //remaining time = Burst
        tempH = tempH->next;
    }while (tempH!=pointers->front);
    
    node * current = pointers->front;
        while(finished != procCount){
            if(current->isDone == false){
                clock +=1;
                if(current->procRemTime - quantum <= 0){
//                    clock+=1;
                    int originalBurst = *current->b-48;
                    int procAT = *current->a-48;
                    current->pocCT = clock;
                    current->pocTAT = abs(current->pocCT - procAT);
                    current->pocWT = abs(current->pocTAT- originalBurst);
                    current->isDone = true;
                    finished +=1;
                }else{
                    current->procRemTime -=quantum;
//                    clock +=1;
                    current = current->next;
                }
            }else{
                current = current->next;
            }
    }
    
    pointers = sortProcNumCircular(pointers);
    
    node *temp2 = pointers->front;
    do{
        outputMsg+= "\nP"+to_string(temp2->procNum) + ": " + to_string(temp2->pocWT)+" ms\n";
        totalBurst += temp2->pocWT;
        temp2 = temp2->next;
    }while(temp2 != pointers->front);
    
    float avgTime = (float)totalBurst / (float)procCount;
        string RRMsg = "";
    RRMsg+="\n---------Scheduling Method: Round Robin---------\n******************  Process Waiting Times  ******************";
    RRMsg+="\n____________________________________________________________________\n";
    RRMsg+= outputMsg;
    RRMsg += "\nAverage Waiting Time: "+ to_string(avgTime) +" ms";
    RRMsg+="\n____________________________________________________________________";
    cout<<RRMsg;
    
        
    endMsg += "\n" + RRMsg + "\n";
    procCounter1 = 1;
    procCounter2 = 1;
    node* temp = pointers->front;
    node* tempN = temp;
    do{
        temp = temp->next;
        tempN->isDone = false;
        delete tempN;
        tempN = temp;
    }while(temp != pointers->front);
    
    return;    
        }
        

 struct node *newNode(char *b,char *a,char *p){ // *** Completed ***
     node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    
    temp->b = (char*)malloc(strlen(b)); //allocate a memory space
    strcpy(temp->b ,b); //pass the value
    
    temp->a = (char*)malloc(strlen(a));
    strcpy(temp->a,a);
    
    temp->p = (char*)malloc(strlen(p));
    strcpy(temp->p,p);
    
    temp->pocCT = 0;
    temp->pocTAT = 0;
    temp->pocWT = 0;
    temp->procRemTime = 0;
    temp->next = NULL;
    temp->pre - NULL;
    return temp;
}


struct queuePoint *insertCirculer( queuePoint *header,char *b,char *a,char *p){ // *** Completed ***
     node *temp;
    temp = newNode(b,a,p);
    temp->procNum = procCounter1;
     if(header->front == NULL){
         header->front = temp;
     }else{
         header->rear->next = temp;
         temp->pre = header->rear;
     }
     header->rear=temp;
     header->rear->next = header->front;
     procCounter1+=1;
     return header;
}


struct node *insertLinerBack( node *header,char *b,char *a,char *p){
    node* temp;
    temp = newNode(b,a,p);
    temp->procNum = procCounter2;
    node* headerTemp;
    if(header == NULL){
        header = temp;
    }else{
        headerTemp = header;
        while(headerTemp->next!=NULL){
            headerTemp = headerTemp->next;
        }
        headerTemp->next = temp;
        temp->pre = headerTemp;
    }
    procCounter2+=1;
    return header;

}

struct node* sortBurst(node* header) {
    node* currentNode = header;
    node* nextNode = header->next;
    while (nextNode != NULL) {
        if (*currentNode->b > *nextNode->b) {
            int tempProcNum = currentNode->procNum;
            char* tempB = currentNode->b;
            char* tempA = currentNode->a;
            char* tempP = currentNode->p;
            currentNode->procNum = nextNode->procNum;
            currentNode->b = nextNode->b;
            currentNode->a = nextNode->a;
            currentNode->p = nextNode->p;
            nextNode->procNum = tempProcNum;
            nextNode->b = tempB;
            nextNode->a = tempA;
            nextNode->p = tempP;
            currentNode = header;
            nextNode = header->next;
            
        }else if((*currentNode->b == *nextNode->b) && (*currentNode->a > *nextNode->a)){
            int tempProcNum = currentNode->procNum;
            char* tempA = currentNode->a;
            char* tempP = currentNode->p;
            currentNode->procNum = nextNode->procNum;
            currentNode->a = nextNode->a;
            currentNode->p = nextNode->p;
            nextNode->procNum = tempProcNum;
            nextNode->a = tempA;
            nextNode->p = tempP;
            currentNode = header;
            nextNode = header->next;
        }else {
            currentNode = currentNode->next;
            nextNode = nextNode->next;
        }
    }
    return header;
}
struct node* sortPriority(node* header) {
    node* currentNode = header;
    node* nextNode = header->next;
    while (nextNode != NULL) {
        if (*currentNode->p > *nextNode->p) {
            int tempProcNum = currentNode->procNum;
            char* tempB = currentNode->b;
            char* tempA = currentNode->a;
            char* tempP = currentNode->p;
            currentNode->procNum = nextNode->procNum;
            currentNode->b = nextNode->b;
            currentNode->a = nextNode->a;
            currentNode->p = nextNode->p;
            nextNode->procNum = tempProcNum;
            nextNode->b = tempB;
            nextNode->a = tempA;
            nextNode->p = tempP;
            currentNode = header;
            nextNode = header->next;
        }else if((*currentNode->p == *nextNode->p) && (*currentNode->a > *nextNode->a)){
            int tempProcNum = currentNode->procNum;
            char* tempA = currentNode->a;
            char* tempB = currentNode->b;
            currentNode->procNum = nextNode->procNum;
            currentNode->a = nextNode->a;
            currentNode->b = nextNode->b;
            nextNode->procNum = tempProcNum;
            nextNode->a = tempA;
            nextNode->b = tempB;
            currentNode = header;
            nextNode = header->next;
        } else {
            currentNode = currentNode->next;
            nextNode = nextNode->next;
        }
    }
    return header;
}
struct node* sortAraival(node* header) {
    node* currentNode = header;
    node* nextNode = header->next;
    while (nextNode != NULL) {
        if (*currentNode->a > *nextNode->a) {
            int tempProcNum = currentNode->procNum;
            char* tempB = currentNode->b;
            char* tempA = currentNode->a;
            char* tempP = currentNode->p;
            currentNode->procNum = nextNode->procNum;
            currentNode->b = nextNode->b;
            currentNode->a = nextNode->a;
            currentNode->p = nextNode->p;
            nextNode->procNum = tempProcNum;
            nextNode->b = tempB;
            nextNode->a = tempA;
            nextNode->p = tempP;
            currentNode = header;
            nextNode = header->next;
        } else {
            currentNode = currentNode->next;
            nextNode = nextNode->next;
        }
    }
    return header;
}
struct queuePoint* sortAraivalCircular(queuePoint* header) {
    node* currentNode = header->front;
    node* nextNode = header->front->next;
    do{
        if (*currentNode->a > *nextNode->a) {
            int tempProcNum = currentNode->procNum;
            char* tempB = currentNode->b;
            char* tempA = currentNode->a;
            char* tempP = currentNode->p;
            currentNode->procNum = nextNode->procNum;
            currentNode->b = nextNode->b;
            currentNode->a = nextNode->a;
            currentNode->p = nextNode->p;
            nextNode->procNum = tempProcNum;
            nextNode->b = tempB;
            nextNode->a = tempA;
            nextNode->p = tempP;
            currentNode = header->front;
            nextNode = header->front->next;
        } else {
            currentNode = currentNode->next;
            nextNode = nextNode->next;
        }
    }while(nextNode != header->front);
    
    return header;
}
struct queuePoint* sortProcNumCircular(queuePoint* header) {
    node* currentNode = header->front;
    node* nextNode = header->front->next;
    do{
        if (currentNode->procNum > nextNode->procNum) {
            int tempProcNum = currentNode->procNum;
            char* tempB = currentNode->b;
            char* tempA = currentNode->a;
            char* tempP = currentNode->p;
            int porcWTtemp = currentNode->pocWT;
            currentNode->procNum = nextNode->procNum;
            currentNode->b = nextNode->b;
            currentNode->a = nextNode->a;
            currentNode->p = nextNode->p;
            currentNode->pocWT = nextNode->pocWT;
            nextNode->procNum = tempProcNum;
            nextNode->b = tempB;
            nextNode->a = tempA;
            nextNode->p = tempP;
            nextNode->pocWT = porcWTtemp;
            currentNode = header->front;
            nextNode = header->front->next;
        } else {
            currentNode = currentNode->next;
            nextNode = nextNode->next;
        }
    }while(nextNode != header->front);
    
    return header;
}
   
void displayCirculer(struct queuePoint *header){
    struct node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    temp = header->front;
    if(temp == NULL){
        cout<<"***ERROR***\n- Input File Is Empty...";
        exit(-1);
    }
    do{
        cout<<"P"<<temp->procNum<<" :"<<temp->b<<temp->a<<temp->p<<endl;
        temp = temp->next;
        sleep(1);
    }while(temp != NULL);

}




void displayLiner(struct node *header){
    struct node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    temp = header;
    if(temp == NULL){
        cout<<"***ERROR***\n- Input File Is Empty...";
        exit(-1);
    }
    do{
        cout<<"P"<<temp->procNum<<" :"<<temp->b<<" : "<<temp->a<<" : "<<temp->p<<endl;
        temp = temp->next;
    }while(temp != NULL);

}
