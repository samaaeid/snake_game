#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;


const int N = 4;  //TWL
const int M = 8; //3RD
int counter=0;
char grid[N][M];

const int MAXQUEUE = N*M;
//typedef int QueueEntry;

struct Queue{
 int front;
 int rear;
 int size;
 int entry[MAXQUEUE][2];
};

Queue pq;

void CreateQueue(Queue *pq){
    pq->front= 0;
    pq->rear = -1;
    pq->size = 0;
}

void Append(int a,int b, Queue* pq){
 pq->rear = (pq->rear + 1) % MAXQUEUE;
 pq->entry[pq->rear][0] = a;
 pq->entry[pq->rear][1] = b;
 pq->size++;
}

void Serve(int *a, int *b, Queue * pq){
 *a = pq->entry[pq->front][0];
 *b = pq->entry[pq->front][1];
 pq->front = (pq->front + 1) % MAXQUEUE;
 pq->size--;

}


//This function prints the grid of Gomoku as the game progresses
void print_grid() {
    cout << "\n";
	cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "";
        for (int i = 0; i < M; cout << "", i++);
    }
    for (int i = 0; i < M; cout << "---", i++);
    cout << "----\n";
} 

//This function checks if the game has a win state or not
bool check_eat(int i,int &a, int &b) {
     
    if (i==3){ if(grid[a][b+1]=='+'){ grid[a][b]='_'; grid[a][b+1]='0'; Append(a,b+1,&pq); b+=1;
                                            counter++; return true;               }} //right

 else if (i==1){ if(grid[a-1][b]=='+'){  grid[a][b]='_';   grid[a-1][b]='0'; Append(a-1,b,&pq); a-=1;
                                            counter++; return true;                } }   // up

 else if (i==2){  if(grid[a+1][b]=='+'){grid[a][b]='_'; grid[a+1][b]='0'; Append(a+1,b,&pq);  a+=1;
                                                   counter++; return true;               }}  //down

 else if (i==4){  if(grid[a][b-1]=='+'){grid[a][b]='_';  grid[a][b-1]='0'; Append(a,b-1,&pq);  b-=1;
                                                     counter++; return true;            }}   //left
return false;
}

//This function checks if given position is valid or not
bool check_lose(int i,int a,int b) {
      if (i==3){ if(grid[a][b+1]=='_'){return true;} if(b+1>M-1){return true;}  } //right
 else if (i==1){ if(grid[a-1][b]=='_'){return true;} if(a-1<0){return true;} }   // up
 else if (i==2){ if(grid[a+1][b]=='_'){return true;} if(a+1>N-1){return true;}}   //down
 else if (i==4){ if(grid[a][b-1]=='_'){return true;} if(b-1<0){return true;}}     //left
return false;
 }

//This function checks if given position is valid or not
bool check_valid_direction(int i) {
    if (i==1 || i==2 || i==3 || i==4 ){
        return true;
        }
    else{return false;}
}

//This function generates pac man
void generate_snake(int &a , int &b) {
    srand( (unsigned)time( NULL ) );
    a = rand() % N;
	b = rand() % M;
    grid[a][b] = '0';
    Append(a,b,&pq);
}

//This function generates ghosts
void generate_apple() {
    srand( (unsigned)time( NULL ) );
    int a = rand() % N;
	int b = rand() % M;
    while (grid[a][b] == '_' || grid[a][b] == '0') {
        a = rand() % N;
        b = rand() % M;
	}
    grid[a][b] = '+';

}


//Move with the input direction
void move(int i,int &a,int &b) {
    int x,y;
    if (counter>=1){

    if (i==3){
              Serve(&x,&y,&pq); grid[x][y]=' '; 
              grid[a][b+1]='0'; grid[a][b]='_'; 
              Append(a,b+1,&pq); b+=1;} //right

 else if (i==1){ 
              Serve(&x,&y,&pq); grid[x][y]=' ';
               grid[a-1][b]='0';grid[a][b]='_';
                Append(a-1,b,&pq); a-=1; }   // up

 else if (i==2){
               Serve(&x,&y,&pq); grid[x][y]=' ';
               grid[a+1][b]='0';grid[a][b]='_'; 
               Append(a+1,b,&pq);  a+=1;}  //down

 else if (i==4){
              Serve(&x,&y,&pq); grid[x][y]=' ';
              grid[a][b-1]='0';grid[a][b]='_';
              Append(a,b-1,&pq);  b-=1;}   //left
    }

    else{
              if (i==3){
               Serve(&x,&y,&pq); 
              if(x>=0 && y>=0 ){grid[x][y]=' ';} else {grid[a][b]=' ';} 
               grid[a][b+1]='0'; Append(a,b+1,&pq);
                b+=1; } //right

 else if (i==1){ 
              Serve(&x,&y,&pq);
              if(x>=0 && y>=0 ){grid[x][y]=' ';} else {grid[a][b]=' ';}  
              grid[a-1][b]='0'; Append(a-1,b,&pq);
              a-=1; }   // up

 else if (i==2){  
              Serve(&x,&y,&pq); 
               if(x>=0 && y>=0 ){grid[x][y]=' ';} else {grid[a][b]=' ';} 
               grid[a+1][b]='0'; Append(a+1,b,&pq);
                 a+=1;}  //down

 else if (i==4){  
              Serve(&x,&y,&pq);
              if(x>=0 && y>=0 ){grid[x][y]=' ';} else {grid[a][b]=' ';} 
               grid[a][b-1]='0'; Append(a,b-1,&pq);
               b-=1;}}

              }

//This function clears the game structures
void grid_clear(Queue &pq) {
     for (int i =0 ; i<N; i++){
            for (int j =0 ; j<M; j++){
                grid[i][j]=' ';
            }
        }
    CreateQueue(&pq);
    counter=0;
}
//This function reads a valid direction
void read_input(int &i ) {
    cout << "Enter the direction: ";
	cin >> i;
    while (!check_valid_direction(i)) {
        cout << "Enter a valid direction: ";
		cin >> i;
	}
}
//MAIN FUNCTION
void play_game(int &a,int &b) {
    cout << "snake Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
		int i;
		read_input(i);

        //Check if the state of the grid has a tie state
        if (check_lose(i,a,b)) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "GAME OVER!\n"<<endl;
            cout<<"Your score :"<< counter<<endl;
            break;
        }

        //Check if the state of the grid has a win state
        if (check_eat(i,a,b)) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            generate_apple();

        }
        else {//Move with the input direction
               move(i,a,b);
               }
        cout<<"Your score :"<<counter<<endl;

    }
}
int main() {
    while (true) {
        int a,b;
        Queue pq;
        grid_clear(pq);
        generate_snake(a,b);
        generate_apple();
    	play_game(a,b);
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
    }
}
