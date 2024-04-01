#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define MAX_TREE_HT 100 


char table_char[128]; 
char table_code[128][40];

int table_count = 0; 
  

void printbin(char ch){
    for (int i =7 ; i>= 0; i--){
        printf("%d", (ch >> i) & 1 );
    }
}


struct MinHeapNode { 

    char data; 
  

    unsigned freq; 
  

    struct MinHeapNode *left, *right; 
}; 
  

struct MinHeap { 
  
    unsigned size; 
  
    unsigned capacity; 
  
    struct MinHeapNode** array; 
}; 
  

struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
    struct MinHeapNode* temp 
        = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
} 
  

struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
  
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
void swapMinHeapNode(struct MinHeapNode** a, 
                     struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
        void minHeapify(struct MinHeap* minHeap, int idx) 
        
        { 
        
            int smallest = idx; 
            int left = 2 * idx + 1; 
            int right = 2 * idx + 2; 
        
            if (left < minHeap->size && minHeap->array[left]-> 
        freq < minHeap->array[smallest]->freq) 
                smallest = left; 
        
            if (right < minHeap->size && minHeap->array[right]-> 
        freq < minHeap->array[smallest]->freq) 
                smallest = right; 
        
            if (smallest != idx) { 
                swapMinHeapNode(&minHeap->array[smallest], 
                                &minHeap->array[idx]); 
                minHeapify(minHeap, smallest); 
            } 
        } 
        
 
int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  

struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] 
        = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  

void insertMinHeap(struct MinHeap* minHeap, 
                   struct MinHeapNode* minHeapNode) 
  
{ 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
  
void buildMinHeap(struct MinHeap* minHeap) 
  
{ 
  
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
  
void printArr(int arr[], int n,int  khorogi[20], char yechizi[128][8]) 
{ 
    
    int i; 
    for (i = 0; i < n; ++i) {
        if(arr[i] != 0 ){
            khorogi[i] = 1;
        }  else{
            khorogi[i] = 2;
        }  
        
    }
    // putchar('\n');


    for (i = 0; i < n; ++i) {
        // printf("%d", arr[i]);
        if(arr[i] == 1)        table_code[table_count][i] = '1'; 
        else         table_code[table_count][i] = '0'; 


    }
    // putchar('\n'); 
} 
  
int isLeaf(struct MinHeapNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 
  

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode *left, *right, *top; 
 
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    while (!isSizeOne(minHeap)) { 
  

        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
   
        top = newNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    } 

    return extractMin(minHeap); 
} 
  

void printCodes(struct MinHeapNode* root, int arr[], int top, int khorogi[][20]) 
  
{ 
  
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1, khorogi); 
    } 
  
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1, khorogi); 
    } 


    if (isLeaf(root)) { 
        char yechizi[128][8] = {0}; 
        // printf("%c: ", root->data); 

        table_char[table_count]  = root->data; 
        
        printArr(arr, top, khorogi[root->data], yechizi); 

        table_count++; 
        
        

    
} 
}

void HuffmanCodes(char data[], int freq[], int size, int khorogi[128][20]) 
  
{ 
    struct MinHeapNode* root 
        = buildHuffmanTree(data, freq, size); 
  

    int arr[MAX_TREE_HT], top = 0; 
  
    printCodes(root, arr, top, khorogi); 
} 
  
int main(int argv, char *argc[]) 
{ 
  //table vairiabls 


    if(!strcmp(argc[argv -1], "--help")){
    



        printf("Usage: your_program [OPTIONS]\n\n");
        printf("Compress text files' size using the Huffman algorithm. By default, it operates in the current directory.\n\n");
        printf("Options:\n");
        printf("  -c, --compress [FILE]  Compress the specified text file. If no option is provided, do the same.\n");
        printf("  -d, --decode [FILE]    Decode a compressed file using the specified output.bin and table.txt files.\n");
        printf("  -h, --help             Display this help message.\n\n");
        printf("Description:\n");
        printf("  If you want to compress a file's size, use the -c option along with the file path or leave it empty with no option. The program will create two files: table.txt (Huffman algorithm table) and output.bin (compressed file).\n");
        printf("  To decode a compressed file, provide the -d option along with the output.bin and table.txt file paths. The program will create one file: original.txt (it has the original file without decoding)\n\n");
        printf("Example:\n");
        printf("  Compress file.txt:\n");
        printf("    your_program file.txt -c \n\n");
        printf("  Decode compressed file:\n");
        printf("    your_program output.bin table.txt -d \n");
        
}else if(argv == 1 ){
            fprintf(stderr, "\033[1;31mPlease insert input file path\033[0m\n");
            printf("\n\nFor more help try --help\n");

    }else if((argv == 2 && !strcmp(argc[argv -1] , "-c"))){
            
            fprintf(stderr, "\033[1;31mPlease insert input file path\033[0m\n");
            printf("\n\nFor more help try --help\n");

    }else if(!strcmp(argc[argv -1], "-d") && argv == 2){
            fprintf(stderr, "\033[1;31mPlease insert outptput and table file path\033[0m\n");
            printf("\n\nFor more help try --help\n");

    }else if((strcmp(argc[argv -1], "-d") || strcmp(argc[argv -1], "-c") ) && argv == 3){
            fprintf(stderr, "\033[1;31mPlease clarify your option -d or -c or --help\033[0m\n");
            printf("\n\nFor more help try --help\n");

    }

    else if(argv == 2|| !strcmp(argc[2], "-c")){

        FILE * fptri; 
        fptri = fopen(argc[1], "r"); 
        
        if(fptri == NULL){
            // perror("Error opening file");
            fprintf(stderr, "\033[1;31mError opening file\033[0m\n");
            perror(argc[1]);
            printf("\nfor more help try --help\n"); 

            return 0; 
        }

        char * input; 

        fseek(fptri, 0, SEEK_END); 
        long filei_size = ftell(fptri); 
        rewind(fptri);

        input = (char *)malloc(filei_size +1); 

        if (input == NULL) {
            perror("Error allocating memory");
            fclose(fptri);
            return 1;
        }

        fread(input, 1, filei_size, fptri);

        input[filei_size] = '\0'; 



        FILE * fptro = fopen("output.bin", "wb"); 

        if(fptro == NULL){
            // perror("Error opening file");
            fprintf(stderr, "\033[1;31mError creating file\033[0m\n");
            perror("output.bin");
            printf("\nfor more help try --help\n"); 


            return 0; 
        }
        
        // strcpy(input, argc[1]) ; 
        int tekrar[128][2] = {0};
        int khorogi[128][20] = {0}; 
        
        int size_in = strlen(input);

        int count_char = 0; 

        for (int i = 0 ; i < size_in; i++){
            char this_char = input[i]; 
            tekrar[this_char][0]  = this_char;
            tekrar[this_char][1] ++;  
            if(tekrar[this_char][1] == 1){
                count_char++;
            }
        }

        
        int j = 0; 
        char arr[count_char];
        int freq[count_char];
        
        for (int i =0; i< 128; i++){
            if(tekrar[i][0] == 0) continue;
            else{
                arr[j] = tekrar[i][0];
                freq[j] = tekrar[i][1]; 
                j++;
            } 
        }

    
        int size = sizeof(arr) / sizeof(arr[0]); 
    
        HuffmanCodes(arr, freq, size, khorogi); 

        char newline = '\n';

// savin table code 

        FILE * ftable = fopen("table.txt", "wb"); 
        
        if(ftable == NULL){
            // perror("Error opening file");
            fprintf(stderr, "\033[1;31mError creating file\033[0m\n");
            perror("table.txt");
            printf("\nfor more help try --help\n"); 

            return 0; 
        }

        for (int i =0 ; i < table_count; i++){
            // fwrite(&table_char[i], 1, 1, ftable);
            fprintf(ftable,"%d ",(int)table_char[i]); 
            fwrite(table_code[i], strlen(table_code[i]), 1, ftable); 
            fwrite(&newline, sizeof(char), 1, ftable); 
        } 


        // putchar('\n'); 

        int count = 0; 

        // این قسمت رو درست کن بعدا 
        char *EntireHuffman = (char *) malloc(1000000 * 1024) ; 

        

        

        for (int i =0; i < size_in; i++){

            char current_char  = input[i]; 
            
            
            for(int j =0 ; khorogi[current_char][j] != 0; j ++){

                if(khorogi[current_char][j] == 2){
                    // printf("%d", 0);
                    EntireHuffman[count] = '0'; 
                    count++; 
                }

                else{
                    // printf("%d", khorogi[current_char][j]);
                    EntireHuffman[count] = '1';
                    count++;
                } 
            }
        }


        char eighBits[9] = {0}; 
        int Binary_deciamal; 

        for (int i = 0 ; i <= count ; i += 8){
            strncpy(eighBits,EntireHuffman+i, 8); 
            Binary_deciamal = strtol(eighBits, NULL, 2); 
            eighBits[8] = '\0';
            // printf("%d\n", Binary_deciamal); 
            fwrite(&Binary_deciamal, 1, 1, fptro); 
        } 

    
        fclose(fptri);

        free(input);

        fclose(fptro);

        // putchar('\n'); 

//printing Huffman codes of the original file

        // FILE * fptr2 =  fopen("output.bin", "rb");
        // char ch; 
        // while(fread(&ch, 1, 1, fptr2) == 1){
        //     printbin(ch);
        // } 




    printf("\n\033[1;32m    File compressed successfully!\033[0m\n\n");






    }else if(!strcmp(argc[argv -1], "-d") && argv == 3){
            fprintf(stderr, "\033[1;31mPlease insert table file path\033[0m\n");
            printf("\n\nFor more help try --help\n");

    }
    
    
    
    
    else if(!strcmp(argc[3], "-d") && argv == 4){
    
    FILE * fptr2 =  fopen(argc[1], "rb");

        if(fptr2 == NULL){
            // perror("Error opening file");
            fprintf(stderr, "\033[1;31mError opening file\033[0m\n");
            perror(argc[1]);
            printf("\nfor more help try --help\n"); 

            return 0; 
        }



//reading table code 
    FILE * freadtablecode = fopen(argc[2],"r"); 

    
        if(freadtablecode == NULL){
            // perror("Error opening file");
            fprintf(stderr, "\033[1;31mError opening file\033[0m\n");
            perror(argc[2]);
            printf("\nfor more help try --help\n"); 

            return 0; 
        }

    char line[8]; 
    int ncn =0; 
    while (fscanf(freadtablecode, "%d %s", &table_char[ncn], table_code[ncn]) == 2) {
        ncn++;
    }
    table_count = ncn; 

    

        FILE * fptrO = fopen("original.txt", "w"); 

        if(fptrO == NULL){
            // perror("Error opening file");
            fprintf(stderr, "\033[1;31mError creating file\033[0m\n");
            perror("original.txt");
            printf("\nfor more help try --help\n"); 

            return 0; 
        }




        
         
        fseek(fptr2, 0, SEEK_END); 
        long sizeFileOut = ftell(fptr2);
        rewind(fptr2);  
        char *WholeCode = (char *)malloc(sizeFileOut * 8); 

        if (WholeCode == NULL) {
            perror("Error allocating memory");
            fclose(fptr2);
            fclose(freadtablecode);
            fclose(fptrO);
            return 1;
        } 


        char ch_bin; 
        long int cnt_WholeCode = 0; 
        while(fread(&ch_bin, 1, 1, fptr2) == 1){
            for (int i = 7;  i >= 0; i --){
                int bit_bit = (ch_bin >> i) & 1;
                if (bit_bit == 1){
                    WholeCode[cnt_WholeCode] = '1'; 
                    cnt_WholeCode++;
                }else {
                    WholeCode[cnt_WholeCode] = '0'; 
                    cnt_WholeCode++; 
                }
            }
        } 


        // printf("\n%d %ld\n", cnt_WholeCode, sizeFileOut); 
        WholeCode[cnt_WholeCode] = '\0'; 
        // printf("%s", WholeCode); 
        int iterate = 0; 
        long int iterateW = 0; 
        char iterate_c[40]; 
                    

        while (iterateW< cnt_WholeCode){ 
            iterate_c[iterate] = WholeCode[iterateW];
            char this_iterate[40]; 
            int flag = 0; 

            for (int i =0 ; i <= iterate; i ++){
                this_iterate[i] = iterate_c[i]; 
            }

            int baghi_this_iterate = 0; 
            baghi_this_iterate = 40 - (iterate + 1); 

            for (int i =0 ;  i  < baghi_this_iterate; i++){
                this_iterate[iterate +1 +i] = '\0'; 
            }

            for(int i = 0; i <= table_count; i++){
                if(!strcmp(this_iterate , table_code[i])) {
                    // printf("%c", table_char[i]); 
                    fwrite(&table_char[i], 1, 1, fptrO); 
                    iterate = 0; 
                    for (int j = 0; j < 8; j++){
                        iterate_c[j] = '\0'; 
                    }
                    iterateW++; 
                    flag = 1; 
                    break;
                }
            }
            if(flag == 0){
            iterate++;
            iterateW++;   
            }
        }


        // printf("im heeere");
        
        
        fclose(fptr2);
        fclose(fptrO); 

        fclose(freadtablecode); 
        free(WholeCode);

        printf("\n\033[1;32m    original.txt created successfully! (if you want to see your decoded text file open origianl.txt in the current directory)\033[0m\n\n");


    }



    return 0;

}