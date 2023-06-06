#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALLOC_SIZE 10

struct pystr {
    int length;
    char *data;
    int alloc; /*size of the data*/
};

//x = str()
struct pystr * pystr_new() {
    struct pystr *p = malloc(sizeof(*p)); //this takes care of the pointer, NOT string data itself
    p->length = 0;
    p->alloc = ALLOC_SIZE;
    p->data = malloc(sizeof(char) * ALLOC_SIZE);//string data
    p->data[0] = '\0';
    return p;
}

//Destructor - del(x)
void pystr_del(const struct pystr *self) {
    free((void *)self->data); //first delete  array
    free((void *)self);
}

void pystr_dump(const struct pystr *self) {
    printf("Pystr length = %i, alloc = %i, data = %s\n", 
            self->length, self->alloc, self->data);
}

int pystr_length(const struct pystr *self) {
    return self->length;
}

char *pystr_str(const struct pystr *self) {
    return self->data;
}

void pystr_append(struct pystr *self, char ch) {
    if ( self->length >= ( self->alloc - 2 )) {
        self->alloc += 10;
        self->data = realloc(self->data, self->alloc);
        if (self->data == NULL) {
            pystr_del(self);
        }
    } 
    char temp;
    for ( unsigned int i = self->length; i < self->length + 1; i++ ) {
        self->data[i] = ch;
    }
    self->data[self->length + 2] = temp;
    
    //update length
    self->length = strlen(self->data);
    /*****************************************
        ***other method without a loop***
        
        temp = self->data[self->length];
        self->data[self->length] = ch;
        self->length = strlen(self->data);
        self->data[self->length] = temp;
        
    ******************************************/
}

void pystr_appends(struct pystr *self, char *str) {
    for (int i = 0; i < strlen(str); i++) {
        pystr_append(self, str[i]);
    }
}

void pystr_assign(struct pystr *self, char *str) {

}

int main(void) {
    struct pystr *string =  pystr_new();
    pystr_dump(string);

    pystr_append(string, 'H');
    pystr_dump(string);
    
    pystr_append(string, 'e');
    pystr_dump(string);

    pystr_append(string, 'l');
    pystr_dump(string);

    pystr_appends(string, "lo world!!! What makes the world beautiful?"); //TODO: fix null finalizer. Its eating up letters
    pystr_dump(string);
    
    return 0;
}
