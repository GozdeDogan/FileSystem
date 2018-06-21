#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <cstring>
#include <fstream>
#include <cmath>
#include "Thread.h"
#include "File.h"
#include <string>
#include <cstring>

using namespace std;

GTUOS::GTUOS(CPU8080 *cpu, char file[MAX_PATH_LEN]){
	/*threadTable[tableIndex] = new Thread();
	threadTable[tableIndex]->initializeThread(threadID, file, *(cpu->state));
	threadID++;
	runningThread = runningThread + 1;*/

	fileInfoTable = new File();
	indexFileInfo = 0;
}

uint64_t GTUOS::handleCall(CPU8080 & cpu, GTUOS & theOS){
    unsigned int myValue = 0;
    switch(cpu.state->a){
        case 1: // PRINT_B
            PRINT_B(cpu);
            break;
        case 2: // PRINT_MEM
            PRINT_MEM(cpu);
            break;
        case 3: // READ_B
            READ_B(cpu);
            break;
        case 4: // READ_MEM
            READ_MEM(cpu);
            break;
        case 5: // PRINT_STR
            PRINT_STR(cpu);
            break;
        case 6: // READ_STR
            READ_STR(cpu); 
            break;
        case 7:
        	GET_RND(cpu);
        	break;
    	case 8:
    		TExit(cpu);
    		break;
	    case 9:
		    TJoin(cpu);
		    break;
	    case 10:
		    TYield(cpu);
		    break;
	    case 11:
		    TCreate(cpu);
		    break;
	    case 12:
		    FileCreate(cpu);
		    break;
	    case 13:
		    //FileClose(cpu);
		    break;
	    case 14:
		    //FileOpen(cpu);
		    break;
	    case 15:
		    //FileRead(cpu);
		    break;
	    case 16:
		    //FileWrite(cpu);
		    break;
	    case 17:
		    //FileSeek(cpu);
		    break;
	    case 18:
		    //DirRead(cpu);
		    break;
        default:
            cout << "INVALID SYSTEM CALL" << endl;
    }
}

void GTUOS::PRINT_B(CPU8080 & cpu){
    cout << "System Call: PRINT_B" << endl;
    cout << "Value of B " << (unsigned)(cpu.state->b) << endl;
}

void GTUOS::READ_B(CPU8080 & cpu){
    unsigned int myValue;
    cout << "System Call: READ_B" << endl;
    cin >> myValue;
    cpu.state->b = myValue;

}

void GTUOS::PRINT_MEM(CPU8080 & cpu){
    uint16_t wd;
    unsigned int myValue;
    cout << "System Call: PRINT_MEM" << endl;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    myValue = cpu.memory->at(wd);
    cout << "Value of MEM " << myValue << endl;
}

void GTUOS::READ_MEM(CPU8080 & cpu){
    unsigned int myValue;
    uint16_t wd;
    
    cout << "System Call: READ_MEM" << endl;
    cin >> hex >> myValue;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    cpu.memory->at(wd) = myValue;
}

void GTUOS::PRINT_STR(CPU8080 & cpu){
    uint16_t wd;
    cout << "System Call: PRINT_STR" << endl;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    while(cpu.memory->at(wd) != '\0'){
        cout << cpu.memory->at(wd);
        wd++;
    } 
    cout << endl;   
}

void GTUOS::READ_STR(CPU8080 & cpu){
    string s;
    int i=0;
    uint16_t wd;
    
    cout << "System Call: READ_STR" << endl;
    cin >> s;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    i=0;
    while(s[i] != '\0'){
        cpu.memory->at(wd + i) = s[i];
        wd++;
        i++;
    }
    cpu.memory->at(wd + i) = s[i];
    cpu.memory->at(wd + i) = '\0';
}

void GTUOS::GET_RND(CPU8080 & cpu){
	int randomValue;
    int temp;
    
	cout << "System Call: GET_RND" << endl;
	temp = pow(2, 8) - 1;
	randomValue = rand() % temp;
	cpu.state->b = randomValue;
}


void GTUOS::FileCreate(CPU8080 & cpu){
	uint16_t wd;
	string file;
    char fileName[MAXSIZE];
	int i = 0;
    cout << "System Call: FileCreate" << endl;

    cin >> file;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    i=0;
    while(file[i] != '\0'){
        cpu.memory->at(wd + i) = file[i];
        fileName[i] = file[i];
        wd++;
        i++;
    }
    cpu.memory->at(wd + i) = file[i];
    fileName[i] = file[i];
    cpu.memory->at(wd + i) = '\0';

   // cout << "file: " << fileName << endl; 

    ofstream pFile;
    pFile.open(file);
	if(pFile.is_open())
		cpu.state->b = 1;
	else
		cpu.state->b = 0;

    fileInfoTable[indexFileInfo].setFileName(fileName);
    //cout << fileInfoTable[indexFileInfo].getFileName() << endl;
    fileInfoTable[indexFileInfo].setFileCreation(1);
    fileInfoTable[indexFileInfo].setLastModify(0);
    fileInfoTable[indexFileInfo].setLastAccess(1);
    fileInfoTable[indexFileInfo].setFileSize(0);    
    
    indexFileInfo++;
}

void GTUOS::FileOpen(CPU8080 & cpu){
    cout << "System Call: FileOpen" << endl;

	uint16_t wd;
    string file;
    char fileName[MAXSIZE];
	int i = 0;

    cout << "enter file name: ";
    cin >> file;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    i=0;
    while(file[i] != '\0'){
        cpu.memory->at(wd + i) = file[i];
        fileName[i] = file[i];
        wd++;
        i++;
    }
    cpu.memory->at(wd + i) = file[i];
    fileName[i] = file[i];
    cpu.memory->at(wd + i) = '\0';
    
    int index = -1;
    for(int i = 0; i < indexFileInfo; i++){
         if(strcmp(fileName, fileInfoTable[i].getFileName()) == 0){
            index = i;        
        }
    }
    
    if(index == -1)
        cout << file << " invalid" << endl;
    else{
        fstream pFile;
        pFile.open(fileName);
        if(!pFile)
		    cpu.state->b = 1; //1 yerine pFile olmali ama hata veriyor!
	    else
		    cpu.state->b = 0;
 
        fileInfoTable[index].setLastModify(0);
        fileInfoTable[index].setLastAccess(1);
    }
}

void GTUOS::FileClose(CPU8080 & cpu){
	uint16_t wd;
	int i = 0;
    cout << "System Call: FileClose" << endl;
    
    ofstream file;
    //file = cpu.state->b; // file'a adresteki degeri atayamiyorum !

	if (file.is_open()) {
		file.close();
		cpu.state->b = 1;
	}
	else
		cpu.state->b = 0;
    
    fileInfoTable[indexFileInfo].setLastAccess(0);    
}

void GTUOS::FileRead(CPU8080 & cpu){
	std:: ifstream pFile;
	//pFile = cpu.state->e; // pFile'a adresteki deger atanmiyor!

	size_t bytes = 0;
	string line;
	streampos begin,end;

    int iValue;
    
    cout << "System Call: FileRead" << endl;

	if(!pFile.eof()){
		begin = pFile.tellg();
		pFile.seekg (0, ios::end);
		end = pFile.tellg();
		cpu.state->d = end-begin;  


	    while(!pFile.eof()){
	    	pFile >> iValue;
            cout << iValue << endl;
            cpu.state->c = iValue;
	        //cout << iValue << endl;
	    }

	    cpu.state->b = end-begin; 

        cout << "cpu.state->c:" << cpu.state->c << endl;

        fileInfoTable[indexFileInfo].setLastModify(0);
        fileInfoTable[indexFileInfo].setLastAccess(1);
    }
    else
    	cpu.state->b = 0;
}

void GTUOS::FileWrite(CPU8080 & cpu){
	std::ofstream pFile;
	//pFile = cpu.state->e;

	size_t bytes = 0;
	string line;
	streampos begin,end;

    uint16_t wd;
    
    cout << "System Call: FileWrite" << endl;

	pFile << (unsigned)(cpu.state->b);
    bytes++;

    
    fileInfoTable[indexFileInfo].setLastModify(1);
    fileInfoTable[indexFileInfo].setLastAccess(1);

    fileInfoTable[indexFileInfo].setFileSize(fileInfoTable[indexFileInfo].getFileSize() + bytes);
}

void GTUOS::FileSeek(CPU8080 & cpu){
	cout << "System Call: FileSeek" << endl;
}

void GTUOS::DirRead(CPU8080 & cpu){
	cout << "System Call: DirRead" << endl;

    //cout << "fileName\tfileCreation\tlastModify\tlastAccess\tfileSize" << endl;
	for (int i = 0; i < indexFileInfo; ++i)
	{
		printFileInfo(i);
	}
}


int GTUOS::calculateCycle(CPU8080 & cpu){
    int cycle = 0;
    switch(cpu.state->a){
        case 1: // PRINT_B
        case 2: // PRINT_MEM
        case 3: // READ_B
        case 4: // READ_MEM
            cycle = 10;
            break;
        case 5: // PRINT_STR 
        case 6: // READ_STR
            cycle = 100;
            break;
        case 7:
        	cycle = 5;
        	break;
    	case 8:
    		cycle = 50;
    		break;
		case 9:
		case 10:
			cycle = 40;
			break;
		case 11:
			cycle = 80;
			break;
		case 12:
			cycle = 1;
			break;
		case 13:
			cycle = 1;
			break;
		case 14:
			cycle = 1;
			break;
		case 15:
			cycle = 1;
			break;
		case 16:
			cycle = 1;
			break;
		case 17:
			cycle = 1;
			break;
		case 18:
			cycle = 1;
			break;
    }
    return cycle;
}

void GTUOS::saveMemory(char *filename, CPU8080& cpu){
	ofstream output;
	output.open(filename);

    if (!output.is_open()) {
        cerr << "Unable to open output file:" << filename << std::endl;
        exit(0);
    }

    for(int i=0;i<0x1000;++i){
        char str[5];
        sprintf(str,"%04x",i*16);
        output << str << " ";
        for(int j=0;j<0x10;++j) {
            sprintf(str,"%02x",cpu.memory->at(i*16+j));
            output << str << " ";
        }
        output << endl;
    }
}

void GTUOS::printFileInfo(int index){
	fileInfoTable[index].printInfo();
}

void GTUOS::printFilesInfo(){
	//cout << "fileName\tfileCreation\tlastModify\tlastAccess\tfileSize" << endl;
	for (int i = 0; i < indexFileInfo; ++i)
	{
		printFileInfo(i);
	}
}

void GTUOS::printDirInfo(){
    cout << "fileName\tfileCreation\tlastModify\tlastAccess\tfileSize" << endl;
    for (int i = 0; i < indexFileInfo; ++i)
	{
		cout << fileInfoTable[i].getFileName() << endl;
	}
}


void GTUOS::printFileSystem(char fileSystem[MAX_PATH_LEN]){
    ofstream pFile;
    pFile.open(fileSystem);

    if (!pFile.is_open()) {
        cerr << "Unable to open output file:" << fileSystem << std::endl;
        exit(0);
    }

    for(int i = 0; i < indexFileInfo; i++){
    	pFile << fileInfoTable[i].getFileName() << " ";
        pFile << fileInfoTable[i].getFileCreation() << " ";
        pFile << fileInfoTable[i].getLastModify() << " ";
        pFile << fileInfoTable[i].getLastAccess() << " ";
        pFile << fileInfoTable[i].getFileSize() << endl;
    }

    pFile.close();
}
        
void GTUOS::readFileSystem(char fileSystem[MAX_PATH_LEN]){
 
    ifstream pFile;
    pFile.open(fileSystem);

    if (!pFile.is_open()) {
        cerr << "Unable to open output file:" << fileSystem << std::endl;
        exit(0);
    }

    char s[MAX_PATH_LEN];
    int value;
    size_t size;
    int i=0;
    while(!pFile.eof()){
    	pFile >> s;
        fileInfoTable[i].setFileName(s);
        pFile >> value;
        fileInfoTable[i].setFileCreation(value);
        pFile >> value;
        fileInfoTable[i].setLastModify(value);
        pFile >> value;
        fileInfoTable[i].setLastAccess(value);
        pFile >> size;
        fileInfoTable[i].setFileSize(size);

        if(i > 0)
            i++; 
    }

    indexFileInfo = i;

    pFile.close(); 
}


void GTUOS::TExit(CPU8080 & cpu){ 
	if(threadTable[tableIndex]->isAlive()){
		threadTable[tableIndex]->setAlive(0);
		runningThread = runningThread - 1;	
		threadTable[tableIndex]->initializeState8080();
	}
	free(threadTable[tableIndex]);
}

void GTUOS::TJoin(CPU8080 & cpu){
	if(threadTable[tableIndex]->isAlive())
		while(threadTable[tableIndex]->isAlive());
}

void GTUOS::TYield(CPU8080 & cpu){
	threadTable[tableIndex]->setAlive(0);
	threadTable[tableIndex]->setState(BLOCKED);

	//uint32_t address = cpu.memory->at(threadTable[tableIndex]->getStartAddress());
	
	// initialize cpu
	// ReadFileIntoMemoryAt fonksiyonunun cagrildiginda calismasi icin cpu resetlendi
	/*cpu.state->a=0;
    cpu.state->b=0;
    cpu.state->c=0;
    cpu.state->d=0;
    cpu.state->e=0;
    cpu.state->h=0;
    cpu.state->l=0;
    cpu.state->int_enable=0;
    cpu.state->sp=0x4000-1;
    cpu.state->pc=0;
    cpu.state->cc.ac=0;
    cpu.state->cc.cy=0;
    cpu.state->cc.pad=0;
    cpu.state->cc.pad2=0;
    cpu.state->cc.pad3=0;
    cpu.state->cc.s=0;
    cpu.state->cc.z=0;
    cpu.state->cc.p=0;*/

	//addElmInBlockedQueue(&threadTable[tableIndex], 0x0000);
}

uint8_t GTUOS::TCreate(CPU8080 & cpu){
	tableIndex = tableIndex + 1;

	uint8_t nextEmpty = -1; 
	
	for (uint8_t i = 0; i < MAX_THREAD_COUNT; ++i) {
		if (i != tableIndex) {
			nextEmpty = i;
			break;
		}
	}

	if (nextEmpty == -1) { 
		cpu.state->b = 1;
		return 0;
	}

	string filename;
	int i = 0;

	//cout << endl << "TCreate : READ fileName: " << endl;
	
	uint16_t wd;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;

    while( cpu.memory->at(wd) != '\0' ){
        filename.append(1, cpu.memory->at(wd)) ;
        ++wd;
    }

	//cout << endl << "TCreate : fileName: " << filename.c_str() << endl << endl;

	if (strcmp(filename.c_str(), "exit()") == 0) {
		exit(1);
	}

	uint32_t adr = 0x0000;
	char file[MAX_PATH_LEN];
	sprintf(file, "%s", filename.data());
	file[strlen(file)-1] = '\0';


	threadTable[tableIndex] = new Thread();
	threadTable[tableIndex]->initializeThread(threadID, file, *(cpu.state));
	threadID++;
	runningThread = runningThread + 1;
	
	// initialize cpu
	// ReadFileIntoMemoryAt fonksiyonunun cagrildiginda calismasi icin cpu resetlendi
	cpu.state->a=0;
    cpu.state->b=0;
    cpu.state->c=0;
    cpu.state->d=0;
    cpu.state->e=0;
    cpu.state->h=0;
    cpu.state->l=0;
    cpu.state->int_enable=0;
    cpu.state->sp=0x4000-1;
    cpu.state->pc=0;
    cpu.state->cc.ac=0;
    cpu.state->cc.cy=0;
    cpu.state->cc.pad=0;
    cpu.state->cc.pad2=0;
    cpu.state->cc.pad3=0;
    cpu.state->cc.s=0;
    cpu.state->cc.z=0;
    cpu.state->cc.p=0;

	//cout << "startAddress: " << threadTable[tableIndex]->getStartAddress();
	

	cpu.ReadFileIntoMemoryAt(file, adr);
	
	
	threadTable[tableIndex]->initializeState8080();

    *(cpu.state)=threadTable[tableIndex]->getState8080();

	cpu.state->b = threadTable[nextEmpty]->getThreadID(); 

	#ifdef DEBUG
		printProcInfs(nextEmpty);
	#endif

	return cpu.state->b;
}

void GTUOS::saveThreadInfos(string& filename) {

  std::ofstream output;

  output.open(filename.c_str());
  if (!output.is_open()) {
    std::cerr << "Unable to open output file:" << filename << std::endl;
    std::cerr << "Writing processes infos is failed" << std::endl;
    return;
  }

  for (int i = 0; i < MAX_THREAD_COUNT; ++i) {
  	output << threadTable[i]->getState8080().a << endl;
  	output << threadTable[i]->getState8080().b << endl;
  	output << threadTable[i]->getState8080().c << endl;
  	output << threadTable[i]->getState8080().d << endl;
  	output << threadTable[i]->getState8080().e << endl;
  	output << threadTable[i]->getState8080().h << endl;
  	output << threadTable[i]->getState8080().l << endl;

    output << threadTable[i]->getThreadID()<< endl;

    output << threadTable[i]->getCurrentCycle() << endl;
    output << threadTable[i]->getNumOfCycle() << endl;

    output << threadTable[i]->getState() << endl;

    output << threadTable[i]->getStartAddress() << endl;

    output << threadTable[i]->getStackState() << endl;

  }

  output.close();


}

void GTUOS::printThreadInformations(uint64_t ind){
  cout << "Thread ID: " << threadTable[ind]->getThreadID() << endl;
}

void GTUOS::printThreadTable(){

	cout << "Register\tThreadID\tCycle\t#Cycle\tstate\tstartAddress\tStack" << endl;
	for(int i = 0; i <= tableIndex; i++){
		cout << threadTable[i]->getThreadID() << "\t";
		cout << threadTable[i]->getCurrentCycle() << "\t";
		cout << threadTable[i]->getNumOfCycle() << "\t";
		cout << threadTable[i]->getStartAddress() << "\t";
		cout << threadTable[i]->getStackState() << endl;
	}
}


char* GTUOS::changeProgramforState(CPU8080 &cpu){
	threadTable[tableIndex]->setState8080(*(cpu.state));
	*(cpu.state) = threadTable[0]->getState8080();
	return threadTable[0]->getFileCom();
}

bool GTUOS::isFinish(){
	if(runningThread == 0)
		return true;
	return false;
}

bool GTUOS::isEmptyReadyQueue(){
	return readyQueue.empty();
}

bool GTUOS::isEmptyBlockedQueue(){
	return blockedQueue.empty();
}

void GTUOS::addEllmInReadyQueue(Thread thread, uint32_t address){
	QueueElm temp;
	temp.thread = thread;
	temp.address = address; 
	readyQueue.push(temp);
}

void GTUOS::addElmInBlockedQueue(Thread thread, uint32_t address){
	QueueElm temp;
	temp.thread = thread;
	temp.address = address; 
	blockedQueue.push(temp);
}

QueueElm GTUOS::getElmReadyQueue(){
	QueueElm temp = readyQueue.front();
	readyQueue.pop();
	return temp;
}

QueueElm GTUOS::getElmBlockedQueue(){
	QueueElm temp = blockedQueue.front();
	blockedQueue.pop();
	return temp;
}
