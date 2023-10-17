#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure used to define a node
typedef struct node_t {
    struct node_t *left, *right;
    int freq;
    char c;
} *node;

// Global variables
int n_nodes = 0, qend = 1;
struct node_t pool[256] = {{0}};
node qqq[255], *q = qqq - 1;
char buf[1024];

// Function to create a new node
node new_node(int freq, char c, node a, node b) {
    node n = pool + n_nodes++;
    if (freq != 0) {
        n->c = c;
        n->freq = freq;
    } else {
        n->left = a, n->right = b;
        n->freq = a->freq + b->freq;
    }
    return n;
}

// Function to insert a node into the priority queue
void qinsert(node n) {
    int j, i = qend++;
    while ((j = i / 2)) {
        if (q[j]->freq <= n->freq) break;
        q[i] = q[j], i = j;
    }
    q[i] = n;
}

node qremove() {
    int i, l;
    node n = q[i = 1];

    if (qend < 2) return 0;
    qend--;
    while ((l = i * 2) < qend) {
        if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) l++;
        q[i] = q[l], i = l;
    }
    q[i] = q[qend];
    return n;
}

void import_table(FILE *fp_table, unsigned int *freq) {
    char c;
    int i = 0;

    while ((c = fgetc(fp_table)) != EOF) {
        freq[i++] = (unsigned char) c;
    }
    for (i = 0; i < 128; i++) {
        if (freq[i]) qinsert(new_node(freq[i], i, 0, 0));
    }
    while (qend > 2)
        qinsert(new_node(0, 0, qremove(), qremove()));
}

void decode(FILE *fp_huffman, FILE *fp_out) {
    int i = 0;
    char c;
    node n = q[1];

    int lim;
    fscanf(fp_huffman, "%d", &lim);
    fseek(fp_huffman, 1, SEEK_CUR);

    printf("Decoded : \n");
    for (i = 0; i < lim; i++) {
        if (i % 8 == 0) {
            c = fgetc(fp_huffman);
        }
        if (c & 128) {
            n = n->right;
        } else {
            n = n->left;
        }
        if (n->c) {
            putchar(n->c);
            fputc(n->c, fp_out);
            n = q[1];
        }
        c = c << 1;
    }

    putchar('\n');
    if (q[1] != n) printf("garbage input\n");
}

int main(int argc, char *argv[]) {
    FILE *fp_table, *fp_huffman, *fp_out;
    char file_name[50] = {0}, temp[50] = {0};
    unsigned int freq[128] = {0};

    system("clear");
    printf("**********************************************************************\n");
    printf("                            Advanced Data Structures\n");
    printf("                                 IT-B-Batch 1(Group 4)\n");
    printf("                             -HUFFMAN ENCODER-\n");
    printf("**********************************************************************\n\n");

    if (argc == 2) {
        strcpy(file_name, argv[1]);
        if (strstr(file_name, "huffman") == NULL) {
            printf("\nERROR: wrong file format!\n");
            return 0;
        }
    } else if (argc > 2) {
        printf("Too many arguments supplied.\n");
    } else {
        printf("Please enter the file to be compressed\t: ");
        scanf("%s", file_name);
        if (strstr(file_name, "huffman") == NULL) {
            printf("\nERROR: wrong file format!\n");
            return 0;
        }
    }

    if ((fp_huffman = fopen(file_name, "r")) == NULL) {
        printf("\nERROR: No such file\n");
        return 0;
    }
    strcat(file_name, ".table");
    if ((fp_table = fopen(file_name, "r")) == NULL) {
        printf("\nERROR: Frequency table cannot be found\n");
        return 0;
    }
    import_table(fp_table, freq);

    *strstr(file_name, ".huffman") = '\0';
    strcpy(temp, "mkdir ");
    strcat(temp, file_name);
    system(strcat(temp, ".decoded"));

    strcpy(temp, "./");
    strcat(temp, file_name);
    strcat(temp, ".decoded/");
    if ((fp_out = fopen(strcat(temp, file_name), "w")) == NULL) {
        printf("ERROR: Creating decoded file failed\n");
        return 0;
    }
    decode(fp_huffman, fp_out);

    fclose(fp_huffman);
    fclose(fp_table);
    fclose(fp_out);
    return 0;
}
