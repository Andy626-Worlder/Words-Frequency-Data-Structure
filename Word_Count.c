#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

//Struct stores the number of times a word appears in the text for each word
struct node {
    unsigned long key;
    char word[100];
    int count;
    struct node *vasen;
    struct node *oikea;
};

struct node* newNode();
void addNode(struct node *node);
void countEsiintymiset(struct node *node, int *countArr);
void fillTopSata(struct node *node, struct node *tulosteArr[], int minValue, int *startIndex);
unsigned long hash(char *str);

struct node *rootNode;
int diffWordCount;
//Global variables for readable words
char sana[100];
//See how many times the most commonly used words appear
int maxCount = 0;


int main() {
    FILE* tiedosto;
    char ch;
    int n = 0;
    rootNode = newNode();
    rootNode -> key = 0;
    int wordCount = 0;
    diffWordCount = 0;
    char path[300];

    while (1) {
        printf("Name of the text file: ");
        fgets(path, 300, stdin);

        path[strlen(path)-1] = 0;

        tiedosto = fopen(path, "r");

        if (tiedosto != NULL) {
            printf("\n");
            break;
        }
        else {
            printf("File not found!\n");
        }
    }

    clock_t begin = clock();

    //Read words from the file and make each word a new node
    while (ch != EOF) {
        ch = fgetc(tiedosto);

        if (isalpha(ch) || ch == '\'') {
            sana[n] = ch;
            n++;
        }
        else if (n > 0) {
            sana[n] = 0;
            n = 0;
            wordCount++;

            int i = 0;
            while(sana[i]) {
                sana[i] = toupper(sana[i]);
                i++;
            }

            addNode(newNode());
        }
    }

//Calculate the number of words that appear x times
//Maxcount is the most common word
    int countArr[maxCount+1];
    int startIndex[maxCount + 1];
    for (int i = 0; i < maxCount+1; i++) {
        countArr[i] = 0;
        startIndex[i] = 0;
    }

    countEsiintymiset(rootNode, countArr);

//Find out the number of times to reach the top 100A
//How many words does the top 100 contain
//Multiple occurrences of words
    int topSataCount = 0;
    int minValue = 0;
    for (int i = maxCount; i >= 0; i--) {
        if (countArr[i] > 0) {
            topSataCount += countArr[i];
            if (topSataCount >= 100) {
                minValue = i;
                break;
            }
        }
    }

//Calculate the x times of each word that appears. word
//Starting index in Top100 table
    int kumulointi = 0;
    for (int i = minValue; i < maxCount + 1; i++) {
        if (countArr[i] > 0) {
            startIndex[i] = kumulointi;
            kumulointi += countArr[i];
        }
    }

    struct node *tulosteArr[topSataCount];

    for (int i = 0; i < topSataCount; i++) {
        tulosteArr[i] = NULL;
    }

    fillTopSata(rootNode, tulosteArr, minValue, startIndex);

    clock_t end = clock();

//Final output
    printf("Aikaa meni %lf sekuntia\n", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Total number of words = %d\n", wordCount);
    printf("Number of different words = %d\n", diffWordCount);
    printf("The %d most common words:\n%-16s%s\n", topSataCount, "WORD", "NUMBER OF OCCURRENCES");

    for (int i = topSataCount - 1; i >= 0; i--) {
        printf("%-16s%d\n", tulosteArr[i] -> word, tulosteArr[i] -> count);
    }

    return 0;
}

//Creates a new node and returns its pointer
struct node* newNode() {
    struct node* node = (struct node*)malloc(sizeof(struct node));

    node -> key = hash(sana);

    for (int i = 0; i < strlen(sana); i++) {
        node -> word[i] = sana[i];
    }

    node -> word[strlen(sana)] = 0;

    node -> count = 1;
    node -> vasen = NULL;
    node -> oikea = NULL;

    return(node);
}

// Add node to binary tree
void addNode(struct node *node) {
    if (rootNode -> key == 0) {
        rootNode = node;
        diffWordCount++;
    }
    else {
        struct node* currentNode = rootNode;

        while (1) {
// If the new node key is smaller than the key of the node in question, then
// add it to the left child of the knot under consideration or continue
// Tree passage
            if (node -> key < currentNode -> key) {
                if (currentNode -> vasen == NULL) {
                    currentNode -> vasen = node;
                    diffWordCount++;
                    break;
                }
                else {
                    currentNode = currentNode -> vasen;
                }
            }
// If those keys are bigger, the same thing on the right
            else if (node -> key > currentNode -> key) {
                if (currentNode -> oikea == NULL) {
                    currentNode -> oikea = node;
                    diffWordCount++;
                    break;
                }
                else {
                    currentNode = currentNode -> oikea;
                }
            }
            // Sam hashtag
            else {
                currentNode -> count = currentNode -> count + 1;

                if (currentNode -> count > maxCount) maxCount = currentNode -> count;

                break;
            }
        }
    }
}

// Enter how many paragraphs there are words that appear x times
void countEsiintymiset(struct node *node, int *countArr) {
    if (node -> vasen != NULL) {
        countEsiintymiset(node -> vasen, countArr);
    }

    if (node -> oikea != NULL) {
        countEsiintymiset(node -> oikea, countArr);
    }

    countArr[node -> count] = countArr[node -> count] + 1;
}

/*
Sort the words TOP100 (or more if the words "divided place") in the table.
Let's go over all the nodes and if there's enough pronunciation for TOP100
add it to table. The word placement in the table is explained by how many
times top100 words appear. For example, if the least-used words appear in the TOP100 table
have appeared seven times and in those thirty paragraphs, so the TOP100 table is to be filled in
zero of the index and the following 30-digit positions belong to seven-time words. Eight times
start with index 30, etc.
*/
void fillTopSata(struct node *node, struct node *tulosteArr[], int minValue, int *startIndex) {
    if (node -> vasen != NULL) {
        fillTopSata(node -> vasen, tulosteArr, minValue, startIndex);
    }

    if (node -> oikea != NULL) {
        fillTopSata(node -> oikea, tulosteArr, minValue, startIndex);
    }

    if (node -> count >= minValue) {
        int i = 0;
        while (1) {

            if (tulosteArr[startIndex[node -> count] + i] == NULL) {
                tulosteArr[startIndex[node -> count] + i] = node;
                break;
            }
            i++;
        }
    }
}

// djb2: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
